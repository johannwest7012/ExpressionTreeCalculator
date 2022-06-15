//
// Created by Johan on 4/21/2022.
//
#include "tree/unary_node_left.h"

// Ctor
UnaryNodeLeft::UnaryNodeLeft(ComponentNode* left)
    : ComponentNode()
    , leftChild(left)
{
}

// Return the right child pointer
ComponentNode* UnaryNodeLeft::left() const
{
    return leftChild.get();
}
