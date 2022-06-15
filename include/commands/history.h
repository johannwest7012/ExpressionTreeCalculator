//
// Created by Johan on 4/23/2022.
//

#ifndef EXPRESSIONTREE_HISTORY_H
#define EXPRESSIONTREE_HISTORY_H

#include "commands/command_impl.h"

/**
 * @class HistoryCommand
 * @brief Prints all the past commands
 */
class HistoryCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit HistoryCommand(Context&);

    // Quit the event loop.
    bool execute() override;
};

#endif // EXPRESSIONTREE_HISTORY_H
