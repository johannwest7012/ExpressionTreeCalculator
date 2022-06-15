#include "core/event_handler.h"
#include "commands/command.h"
#include "commands/command_factory.h"
#include <algorithm>
#include <iostream>
EventHandler* EventHandler::makeHandler(bool verbose, std::ostream& os)
{

    return verbose ? static_cast<EventHandler*>(new VerboseHandler(os))
                   : static_cast<EventHandler*>(new MacroHandler(os));
}

EventHandler::EventHandler(std::ostream& os)
    : context(os)
    , commandFactory(new CommandFactory(context))
    , lastValidCommand(commandFactory->makeNullCommand(""))
{
}

void EventHandler::handle()
{
    // Step 1) Prompt User
    promptUser();
    std::string input;

    // Step 2) Get user input (error getting it shuts down application immediately)
    if (!getInput(input))
        Reactor::instance()->endEventLoop();

    try {
        // Step 3) Make a command
        Command command = makeCommand(input);
        // Step 4) Execute command

        executeCommand(command);

        lastValidCommand = command;

    } catch (std::invalid_argument& e) {
        // better debugger handling
        std::string error = e.what();
        char& back = error.back();
        int idx = input.find_first_of(back);
        int i = 0;
        while (i < idx) {
            context.output() << '-';
            i++;
        }
        context.output() << "^" << e.what() << "\n";
    } catch (ExpressionTree::InvalidIterator& e) {
        std::cerr << "\nERROR: Bad traversal type (" << e.what() << ")\n";
    } catch (State::InvalidState& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
    } catch (std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

bool EventHandler::getInput(std::string& input)
{
    std::getline(std::cin, input);
    return !std::cin.fail();
}

bool EventHandler::executeCommand(Command command)
{
    return command.execute();
}

VerboseHandler::VerboseHandler(std::ostream& os)
    : EventHandler(os)
{
}

void VerboseHandler::promptUser()
{
    context.state()->printValidCommands();
    context.output() << "> ";
    context.output().flush();
}

Command VerboseHandler::makeCommand(const std::string& input)
{
    std::string newInput;
    if (input.find(" ") != std::string::npos) {
        std::string first = input.substr(0, input.find(" "));
        std::string end = input.substr(input.find_first_of(" \t"));
        std::for_each(first.begin(), first.end(), [](char& c) { c = ::tolower(c); });

        newInput = first + end;
    } else {
        newInput = input;
        std::for_each(newInput.begin(), newInput.end(), [](char& c) { c = ::tolower(c); });
    }
    return commandFactory->makeCommand(newInput);
}

MacroHandler::MacroHandler(std::ostream& os)
    : EventHandler(os)
{
}

void MacroHandler::promptUser()
{
    context.output() << "> ";
    context.output().flush();
}

Command MacroHandler::makeCommand(const std::string& input)
{
    return commandFactory->makeMacroCommand(input);
}
