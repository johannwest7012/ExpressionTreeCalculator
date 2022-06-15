//
// Created by Johan on 4/21/2022.
//
#include "tree/binary_node.h"

#ifndef EXPRESSIONTREE_MODULUS_NODE_H
#define EXPRESSIONTREE_MODULUS_NODE_H

/**
 * @class ModulusNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left % right.
 */
class ModulusNode : public BinaryNode {
public:
    // Ctor
    ModulusNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~ModulusNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // EXPRESSIONTREE_MODULUS_NODE_H
