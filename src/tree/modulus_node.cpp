//
// Created by Johan on 4/21/2022.
//
#include "tree/modulus_node.h"
#include "visitors/visitor.h"

// Ctor
ModulusNode::ModulusNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int ModulusNode::item() const
{
    return '/';
}

// accept a visitor
void ModulusNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
