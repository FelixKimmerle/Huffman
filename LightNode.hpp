#pragma once

struct LightNode
{
    LightNode(char data);
    ~LightNode();
    char data;
    LightNode *left;
    LightNode *right;
};