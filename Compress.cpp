#include "Compress.hpp"
#include "Node.hpp"
#include "Packet.hpp"
#include <map>
#include <queue>
#include <list>
#include <fstream>
#include <iostream>

void WriteTree(Node *node, Packet *packet)
{
    if (node->right != nullptr)
    {
        packet->AddBit(false);
        WriteTree(node->right, packet);
        WriteTree(node->left, packet);
    }
    else
    {
        packet->AddBit(true);
        for (int i = 0; i < 8; i++)
        {
            if ((node->data >> i) & 1)
            {
                packet->AddBit(true);
            }
            else
            {
                packet->AddBit(false);
            }
        }
    }
}

struct compare
{

    bool operator()(Node *l, Node *r)

    {
        return (l->freq > r->freq);
    }
};

Node *CreateTree(std::map<char, Node *> &Counter)
{
    std::priority_queue<Node *, std::vector<Node *>, compare> Heap;
    Node *left, *right, *top;
    for (auto x = Counter.begin(); x != Counter.end(); x++)
    {
        Heap.push(x->second);
    }
    while (Heap.size() != 1)
    {
        left = Heap.top();
        Heap.pop();
        right = Heap.top();
        Heap.pop();

        top = new Node((char)0, left->freq + right->freq);
        top->left = left;
        top->left->bit = false;
        top->left->parent = top;

        top->right = right;
        top->right->bit = true;
        top->right->parent = top;
        Heap.push(top);
    }
    return Heap.top();
}

void encode(const std::string *str, std::map<char, std::list<bool>> *table, Packet *packet)
{
    for (auto x = str->begin(); x != str->end(); x++)
    {
        std::list<bool> a = (*table)[*x];
        for (auto i = a.begin(); i != a.end(); i++)
        {
            packet->AddBit(*i);
        }
    }
}

Packet *CompressIntern(const std::string *text)
{
    std::map<char, Node *> CounterHeap;
    {
        std::map<char, unsigned int> Counter;
        for (auto x = text->begin(); x != text->end(); x++)
        {
            Counter[*x]++;
        }

        for (auto x = Counter.begin(); x != Counter.end(); x++)
        {
            CounterHeap[x->first] = new Node(x->first, x->second);
        }
    }
    Node *root = CreateTree(CounterHeap);
    Packet *packet = new Packet;
    WriteTree(root, packet);
    std::map<char, std::list<bool>> Table;
    for (auto x = CounterHeap.begin(); x != CounterHeap.end(); x++)
    {
        std::list<bool> set;
        Node *node = x->second;
        while (node != nullptr)
        {
            if (node->parent != nullptr)
            {
                if (node->bit)
                {
                    set.push_front(true);
                }
                else
                {
                    set.push_front(false);
                }
            }
            node = node->parent;
        }
        Table[x->first] = set;
    }
    encode(text, &Table, packet);
    packet->Flush();
    packet->Compress();
    delete root;
    return packet;
}

Packet *CompressFile(const std::string &file)
{
    std::ifstream t(file);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());
    return CompressIntern(&str);
}
Packet *Compress(const std::string &str)
{
    return CompressIntern(&str);
}
//Hallo