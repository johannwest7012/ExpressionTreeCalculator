//
// Created by Johan on 4/23/2022.
//

#ifndef EXPRESSIONTREE_LIST_H
#define EXPRESSIONTREE_LIST_H

#include "commands/command_impl.h"

/**
 * @class ListCommand
 * @brief Prints all the variables and their values
 */
class ListCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit ListCommand(Context&);

    // Quit the event loop.
    bool execute() override;
};

#endif // EXPRESSIONTREE_LIST_H
