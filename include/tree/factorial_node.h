//
// Created by Johan on 4/21/2022.
//

#ifndef EXPRESSIONTREE_FACTORIAL_NODE_H
#define EXPRESSIONTREE_FACTORIAL_NODE_H

#include "tree/unary_node_left.h"

/**
 * @class FactorialNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left !
 */
class FactorialNode : public UnaryNodeLeft {
public:
    // Ctor
    explicit FactorialNode(ComponentNode* left);

    // Dtor
    ~FactorialNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // EXPRESSIONTREE_FACTORIAL_NODE_H
