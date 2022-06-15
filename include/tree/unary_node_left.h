//
// Created by Johan on 4/21/2022.
//

#ifndef EXPRESSIONTREE_UNARY_NODE_LEFT_H
#define EXPRESSIONTREE_UNARY_NODE_LEFT_H

#include "tree/component_node.h"
#include <memory>

/**
 * @class UnaryNodeLeft
 * @brief Defines a left child (but not a right one) and thus is useful for
 * factorial operations.
 * @see BinaryNode
 */
class UnaryNodeLeft : public ComponentNode {
public:
    // Ctor
    explicit UnaryNodeLeft(ComponentNode* left);

    // Dtor
    ~UnaryNodeLeft() override = default;

    // Return the left child.
    [[nodiscard]] ComponentNode* left() const override;

private:
    // Left child
    std::unique_ptr<ComponentNode> leftChild;
};

#endif // EXPRESSIONTREE_UNARY_NODE_LEFT_H
