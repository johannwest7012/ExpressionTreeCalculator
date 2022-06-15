//
// Created by Johan on 4/22/2022.
//
#include "commands/get.h"
#include "core/context.h"

GetCommand::GetCommand(Context& context, std::string pair)
    : Command_Impl(context)
    , pair(std::move(pair))
{
}

bool GetCommand::execute()
{
    context.get(pair);
    return true;
}