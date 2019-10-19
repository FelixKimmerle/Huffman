#include "Node.hpp"

Node::Node(char data, unsigned int freq)
{
    this->data = data;
    this->freq = freq;
    this->right = nullptr;
    this->left = nullptr;
    this->parent = nullptr;
}
Node::~Node()
{
    if (right != nullptr)
    {
        delete right;
        right = nullptr;
    }
    if (left != nullptr)
    {
        delete left;
        left = nullptr;
    }
}