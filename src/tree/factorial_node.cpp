//
// Created by Johan on 4/21/2022.
//
#include "tree/factorial_node.h"
#include "visitors/visitor.h"

// Ctor
FactorialNode::FactorialNode(ComponentNode* left)
    : UnaryNodeLeft(left)
{
}

int FactorialNode::item() const
{
    return '/';
}

// accept a visitor
void FactorialNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
