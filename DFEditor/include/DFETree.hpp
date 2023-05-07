#pragma once

#include <vector>

template<typename T>
class DFETree
{
    struct Node
    {
        Node(T value) : m_value(value) {}

        T m_value;
        std::vector<Node *>mp_children;
    };

public:
    DFETree() : root(nullptr) {}

    // GetChildren
    // AddParent
    // AddChild
    // Remove
private:
    Node *root;
};
