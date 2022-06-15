#include "commands/command_factory.h"
#include "commands/command.h"
#include "commands/eval.h"
#include "commands/expr.h"
#include "commands/format.h"
#include "commands/get.h"
#include "commands/history.h"
#include "commands/list.h"
#include "commands/macro.h"
#include "commands/null.h"
#include "commands/print.h"
#include "commands/quit.h"
#include "commands/set.h"
#include "commands/stats.h"
#include <stdexcept>

// Expression_Tree_Command_Factory_Impl Constructor.
CommandFactory::CommandFactory(Context& cntx)
    : commandMap()
    , context(cntx)
{
    commandMap["format"] = &CommandFactory::makeFormatCommand;
    commandMap["expr"] = &CommandFactory::makeExprCommand;
    commandMap["print"] = &CommandFactory::makePrintCommand;
    commandMap["eval"] = &CommandFactory::makeEvalCommand;
    commandMap["set"] = &CommandFactory::makeSetCommand;
    // get
    commandMap["get"] = &CommandFactory::makeGetCommand;

    // list
    commandMap["list"] = &CommandFactory::makeListCommand;

    // history
    commandMap["history"] = &CommandFactory::makeHistoryCommand;

    // stats
    commandMap["stats"] = &CommandFactory::makeStatsCommand;

    commandMap["quit"] = &CommandFactory::makeQuitCommand;
}

Command CommandFactory::makeCommand(const std::string& input)
{
    // separate the command from the parameters
    std::string::size_type spacePos = input.find(' ');
    std::string parameters = input.substr(spacePos + 1);
    std::string keyword = input.substr(0, spacePos);
    auto iter = commandMap.find(keyword);
    if (iter == commandMap.end())
        throw std::logic_error("Unknown command: " + keyword);
    else {

        auto methodPointer = iter->second;
        return (this->*methodPointer)(parameters);
    }
}

Command CommandFactory::makeFormatCommand(const std::string& param)
{
    return Command(new FormatCommand(context, param));
}

Command CommandFactory::makeExprCommand(const std::string& param)
{
    return Command(new ExprCommand(context, param));
}

Command CommandFactory::makePrintCommand(const std::string& param)
{
    return Command(new PrintCommand(context, param));
}

Command CommandFactory::makeEvalCommand(const std::string& param)
{
    return Command(new EvalCommand(context, param));
}

Command CommandFactory::makeSetCommand(const std::string& param)
{
    return Command(new SetCommand(context, param));
}

// get
Command CommandFactory::makeGetCommand(const std::string& param)
{
    return Command(new GetCommand(context, param));
}
//

Command CommandFactory::makeListCommand(const std::string& param)
{
    return Command(new ListCommand(context));
}

Command CommandFactory::makeHistoryCommand(const std::string& param)
{
    return Command(new HistoryCommand(context));
}

Command CommandFactory::makeQuitCommand(const std::string& param)
{
    return Command(new QuitCommand(context));
}

Command CommandFactory::makeNullCommand(const std::string& params)
{
    return Command(new NullCommand(context));
}

Command CommandFactory::makeMacroCommand(const std::string& expr)
{
    // Create the three commands in sequence
    std::vector<Command> commands;
    commands.push_back(makeFormatCommand("in-order"));
    commands.push_back(makeExprCommand(expr));
    commands.push_back(makeEvalCommand("post-order"));
    // Create the macro command and bridge
    return Command(new MacroCommand(context, commands));
}

Command CommandFactory::makeStatsCommand(const std::string& params)
{
    return Command(new StatsCommand(context, params));
}
