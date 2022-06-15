//
// Created by Johan on 4/24/2022.
//
#include "commands/stats.h"
#include "core/context.h"

StatsCommand::StatsCommand(Context& context, std::string newStats)
    : Command_Impl(context)
    , Statsession(std::move(newStats))
{
}

bool StatsCommand::execute()
{
    context.stats(Statsession);
    return true;
}