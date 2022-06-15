//
// Created by Johan on 4/23/2022.
//
#include "commands/list.h"
#include "core/context.h"

ListCommand::ListCommand(Context& context)
    : Command_Impl(context)

{
}

bool ListCommand::execute()
{
    context.list();
    return true;
}