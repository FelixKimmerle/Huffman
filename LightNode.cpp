#include "LightNode.hpp"

LightNode::LightNode(char data)
{
    this->data = data;
    this->right = nullptr;
    this->left = nullptr;
}
LightNode::~LightNode()
{
    if (left != nullptr)
    {
        delete left;
        left = nullptr;
    }
    if (right != nullptr)
    {
        delete right;
        right = nullptr;
    }
}