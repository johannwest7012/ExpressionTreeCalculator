//
// Created by Johan on 4/24/2022.
//

#ifndef StatsESSIONTREE_STATS_H
#define StatsESSIONTREE_STATS_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class StatsCommand
 * @brief Set the desired Statsession, e.g., "1+2*3".
 */
class StatsCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and the requested Statsession.
    StatsCommand(Context&, std::string);

    // Create the desired Statsession tree.
    bool execute() override;

private:
    // Requested Statsession.
    std::string Statsession;
};

#endif // StatsESSIONTREE_STATS_H
