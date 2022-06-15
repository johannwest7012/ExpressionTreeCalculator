//
// Created by Johan on 4/23/2022.
//

#include "commands/history.h"
#include "core/context.h"

HistoryCommand::HistoryCommand(Context& context)
    : Command_Impl(context)

{
}

bool HistoryCommand::execute()
{
    context.history();
    return true;
}