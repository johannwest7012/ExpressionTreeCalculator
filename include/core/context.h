//
// Created by Johan on 4/23/2022.
//
#ifndef CONTEXT_H
#define CONTEXT_H

#include "core/state.h"
#include "interpreter/variable_map.h"
#include "tree/expression_tree.h"
#include <deque>
#include <memory>
#include <string>
/**
 * @class Context
 * @brief Interface for the State pattern that is used to ensure that
 *        commands are invoked according to the correct protocol.
 *
 *        Plays the role of the "context" class in the State pattern
 *        and delegates to the appropriate "state" subclass that
 *        performs the commands.
 */
class Context {
public:
    // Constructor.
    explicit Context(std::ostream&);

    VariableMap& getVariables();

    // Set the desired format to the designated new_format.
    void format(const std::string& newFormat);

    // Make an expression tree based on the designated expression using the previously designated
    // format.
    void makeTree(const std::string& expression);

    // Print the most recently created expression tree using the designated format.
    void print(const std::string& format);

    // Evaluate the "yield" of the most recently created expression tree using the designated
    // format.
    int evaluate(const std::string& format);

    // Set the value of the variable is a string of the format "variable_name=variable_value"
    void set(const std::string& kvPair);

    // get
    // returns value of variable
    void get(const std::string& kvPair);

    // stats
    // returns value of variable
    void stats(const std::string& format);

    // returns all variables and values
    void list();

    // returns the history of commands
    void history();

    // Return a pointer to the current State.
    [[nodiscard]] State* state() const;

    // Set the current State to the designated new_state pointer.
    void state(State* new_state);

    // Return a reference to the current ExpressionTree.
    ExpressionTree& tree();

    // Set the current ExpressionTree to the newTree.
    void tree(const ExpressionTree& newTree);

    // Returns whether or not a successful format call has been called
    [[maybe_unused]] [[nodiscard]] bool formatted() const;

    // Where all output should be printed
    [[nodiscard]] std::ostream& output() const;

    // adds the command to the history, keeping the history count of commands at 5 or below
    void addToHist(const std::string& command);

    std::deque<std::string> hist;

private:
    // Persistent interpreter context for variables. Our interpreter
    // will change values inside of this, so I just stuck the variable
    // in the public section.
    VariableMap variables;
    // Keep track of the current state that we're in.  We use an @a
    // std::unique_ptr to simplify memory management and avoid memory leaks.
    std::unique_ptr<State> treeState;
    // Current expression tree.
    ExpressionTree expTree;
    // Had the format been set
    bool isFormatted;
    // Where is output being directed
    std::ostream& os;
};

#endif // CONTEXT_H
