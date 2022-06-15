//
// Created by Johan on 4/22/2022.
//

#ifndef EXPRESSIONTREE_GET_H
#define EXPRESSIONTREE_GET_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class GetCommand
 * @brief Gets a variable into the VariableMap stored inside of Context.
 */
class GetCommand : public Command_Impl {
public:
    // Constructor that provides the Context and the k-v pair.
    GetCommand(Context& context, std::string);
    // Evaluate the expression tree.
    bool execute() override;

private:
    // Format to use for the evaluation.
    std::string pair;
};

#endif // EXPRESSIONTREE_GET_H
