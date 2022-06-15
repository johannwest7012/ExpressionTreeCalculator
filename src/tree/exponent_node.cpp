//
// Created by Johan on 4/22/2022.
//
#include "tree/exponent_node.h"
#include "visitors/visitor.h"

// Ctor
ExponentNode::ExponentNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int ExponentNode::item() const
{
    return '^';
}

// accept a visitor
void ExponentNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}