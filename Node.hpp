#pragma once

struct Node
{
    Node(char data, unsigned int freq);
    ~Node();
    unsigned int freq;
    char data;
    bool bit;
    Node *left;
    Node *right;
    Node *parent;
};