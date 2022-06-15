#include "visitors/evaluation.h"
#include "tree/leaf_node.h"
#include <iostream>
#include <math.h>
// base evaluation for a node. This is used by LeafNode
void EvaluationVisitor::visit(const LeafNode& node)
{
    stack.push(node.item());
}

// evaluation of a negation (NegateNode)
void EvaluationVisitor::visit(const NegateNode&)
{
    if (!stack.empty()) {
        auto value = stack.top();
        stack.pop();
        stack.push(-value);
    }
}

// evaluation of an addition (AddNode)
void EvaluationVisitor::visit(const AddNode&)
{
    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        stack.push(lhs + rhs);
    }
}

// evaluation of an addition (SubtractNode)
void EvaluationVisitor::visit(const SubtractNode&)
{
    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        stack.push(lhs - rhs);
    }
}

// evaluations of a division (DivideNode)
void EvaluationVisitor::visit(const DivideNode&)
{
    if (stack.size() >= 2 && stack.top()) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        stack.push(lhs / rhs);
    } else {
        std::cerr << "\n\n**ERROR**: Division by zero is not allowed. ";
        std::cerr << "Resetting evaluation visitor.\n\n";
        reset();
    }
}

// evaluations of a modulus (ModulusNode)
void EvaluationVisitor::visit(const ModulusNode&)
{
    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        stack.push(lhs % rhs);
    }
}

// evaluations of a factorial (FactorialNode)
void EvaluationVisitor::visit(const FactorialNode&)
{

    if (!stack.empty()) {
        int value = int(stack.top());
        stack.pop();

        if (value > 12) {
            std::cerr << "\n\n--> Error: Factorials of up to 12 are supported. ";
            std::cerr << "Resetting evaluation visitor.\n\n";
            reset();
        } else {
            auto fact = 1;
            for (int i = 1; i <= value; ++i) {
                fact *= i;
            }

            stack.push(fact);
        }
    }
}

// evaluations of a exponentnode
void EvaluationVisitor::visit(const ExponentNode&)
{

    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        stack.push(pow(lhs, rhs));
    }
}

// evaluations of a division (MultiplyNode)
void EvaluationVisitor::visit(const MultiplyNode&)
{
    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        stack.push(lhs * rhs);
    }
}

void EvaluationVisitor::visit(const CeilingNode&)
{
    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        if (lhs > rhs) {
            stack.push(lhs);
        } else {
            stack.push(rhs);
        }
    }
}

void EvaluationVisitor::visit(const FloorNode&)
{
    if (stack.size() >= 2) {
        auto rhs = stack.top();
        stack.pop();
        auto lhs = stack.top();
        stack.pop();
        if (lhs < rhs) {
            stack.push(lhs);
        } else {
            stack.push(rhs);
        }
    }
}

// print a total for the evaluation
int EvaluationVisitor::total()
{
    if (!stack.empty())
        return stack.top();
    else
        return 0;
}

// reset the evaluation
void EvaluationVisitor::reset()
{
    while (!stack.empty())
        stack.pop();
}
