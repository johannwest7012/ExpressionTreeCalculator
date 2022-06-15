#ifndef VISITOR_H
#define VISITOR_H

class LeafNode;
class NegateNode;
class AddNode;
class SubtractNode;
class DivideNode;
class MultiplyNode;
class ModulusNode;
class FactorialNode;
class ExponentNode;
class CeilingNode;
class FloorNode;
/**
 * @class Visitor
 * @brief Abstract base class for all visitors to all classes that derive
 *        from ComponentNode.
 *
 *        This class plays the role of the "visitor" in the Visitor
 *        pattern.
 */
class Visitor {
public:
    // Visit a LeafNode.
    virtual void visit(const LeafNode& node) = 0;
    // Visit a NegateNode.
    virtual void visit(const NegateNode& node) = 0;
    // Visit a AddNode.
    virtual void visit(const AddNode& node) = 0;
    // Visit a SubtractNode.
    virtual void visit(const SubtractNode& node) = 0;
    // Visit a DivideNode.
    virtual void visit(const DivideNode& node) = 0;
    // Visit a _Multiply_Node.
    virtual void visit(const MultiplyNode& node) = 0;
    // Visit a ModulusNode
    virtual void visit(const ModulusNode& node) = 0;
    // Visit a FactorialNode
    virtual void visit(const FactorialNode& node) = 0;
    // Visit a ExponentNode
    virtual void visit(const ExponentNode& node) = 0;
    // Visit a CeilingNode
    virtual void visit(const CeilingNode& node) = 0;
    // Visit a FloorNode
    virtual void visit(const FloorNode& node) = 0;

    // No-op destructor to hold things together.
    virtual ~Visitor() = default;
};

#endif // VISITOR_H
