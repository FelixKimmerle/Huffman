#include "Decompress.hpp"
#include "LightNode.hpp"
#include "Packet.hpp"

LightNode *read(Packet *packet, unsigned int *pos)
{
    if (!packet->GetBit(*pos))
    {
        (*pos)++;
        LightNode *root = new LightNode('$');
        root->right = read(packet, pos);
        root->left = read(packet, pos);
        return root;
    }
    else
    {
        (*pos)++;
        char ch = packet->GetByte(*pos);
        (*pos) += 8;
        LightNode *a = new LightNode(ch);
        return a;
    }
}

LightNode *ReadTree(Packet *packet, unsigned int *size)
{
    unsigned int pos = 0;
    LightNode *res = read(packet, &pos);
    (*size) = pos;
    return res;
}

std::string *decode(Packet *packet, LightNode *tree, unsigned int startpos)
{
    LightNode *curr = tree;
    std::string *output = new std::string;
    unsigned int size = packet->GetSize();
    for (unsigned int x = startpos; x < size; x++)
    {
        if (!packet->GetBit(x))
        {
            curr = curr->left;
            if (curr->right == nullptr)
            {
                *output += curr->data;
                curr = tree;
            }
        }
        else
        {
            curr = curr->right;
            if (curr->left == nullptr)
            {
                *output += curr->data;
                curr = tree;
            }
        }
    }
    return output;
}

std::string *Decompress(Packet *packet)
{
    packet->Flush();
    unsigned int *size = new unsigned int;
    LightNode *root = ReadTree(packet, size);
    std::string *ret = decode(packet, root, *size);
    delete root;
    delete size;
    return ret;
}
std::string *DecompressFile(const std::string &file)
{
    Packet packet;
    packet.ReadFromFile(file);
    if (packet.GetSize() > 0)
    {
        return Decompress(&packet);
    }
    return new std::string("");
}