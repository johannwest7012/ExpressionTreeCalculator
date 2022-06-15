#include "core/context.h"
#include <algorithm>
#include <iostream>
#include <string>
Context::Context(std::ostream& os)
    : treeState(new UninitializedState(*this))
    , isFormatted(false)
    , os(os)
{
}

void Context::format(const std::string& newFormat)
{
    treeState->format(newFormat);
    // we only reach here if the format was successful, and once
    // this is set, we will always have at least one valid format
    // because we store the last valid command (which would have
    // a valid format, if this format function has ever been successfully ran
    isFormatted = true;
    std::string add = "format " + newFormat;
    addToHist(add);
}

void Context::makeTree(const std::string& expression)
{
    treeState->makeTree(expression);
    std::string add = "expr " + expression;
    addToHist(add);
}

void Context::print(const std::string& format)
{
    treeState->print(format, os);
    std::string add = "print " + format;
    addToHist(add);
}

int Context::evaluate(const std::string& format)
{
    if (format == "post-order") {
        std::string add = "eval " + format;
        addToHist(add);
    }
    return treeState->evaluate(format);
}

void Context::set(const std::string& kvPair)
{
    std::string input = kvPair;
    // used for keeping track of found characters
    std::string::size_type pos;
    // get rid of all spaces
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    // input should be key=value
    if ((pos = input.find('=')) != std::string::npos) {
        // if the position is not the first char (eg '=value')
        // and position is not the last char (eg 'key=')
        // then split the string and set the interpreter context
        // accordingly
        if (pos != 0 && pos < input.length() - 1) {
            std::string key = input.substr(0, pos);
            std::string value = input.substr(pos + 1);

            variables.set(key, atoi(value.c_str()));
        } else
            throw std::domain_error("Must be in the form key=value");
    } else
        throw std::domain_error("Must have = sign present");

    std::string add = "set " + kvPair;
    addToHist(add);
}

void Context::get(const std::string& kvPair)
{
    if (variables.isEmpty()) {
        throw std::domain_error("ERROR: No variables set yet");
    }

    std::string input = kvPair;
    // used for keeping track of found characters
    // get rid of all spaces
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    // input should be key=value
    auto value = variables.get(input);
    std::string str = std::to_string(value);
    os << input << ": " << str << "\n";

    std::string add = "get " + kvPair;
    addToHist(add);
}

void Context::list()
{
    if (variables.isEmpty()) {
        throw std::domain_error("ERROR: No variables set yet");
    }

    variables.print2(os);
    std::string add = "list";
    addToHist(add);
}

void Context::history()
{
    if (hist.empty()) {
        throw std::domain_error("ERROR: No commands yet");
    }
    int j = 1;
    std::for_each(hist.begin(), hist.end(), [this, &j](std::string i) {
        os << j << ") " << i << "\n";
        j++;
    });
}

State* Context::state() const
{
    return treeState.get();
}

void Context::state(State* state)
{
    treeState.reset(state);
}

ExpressionTree& Context::tree()
{
    return expTree;
}

void Context::tree(const ExpressionTree& tree)
{
    expTree = tree;
}

VariableMap& Context::getVariables()
{
    return variables;
}

bool Context::formatted() const
{
    return isFormatted;
}

std::ostream& Context::output() const
{
    return os;
}

void Context::addToHist(const std::string& command)
{
    if (hist.size() == 5) {
        hist.pop_front();
    }
    hist.push_back(command);
}

void Context::stats(const std::string& format)
{
    int add = 0;
    int ceiling = 0;
    int divide = 0;
    int exponent = 0;
    int factorial = 0;
    int floor = 0;
    int modulus = 0;
    int multiply = 0;
    int subtract = 0;
    int negate = 0;

    std::string ops = "+|/^_%*-";

    for (int i = 0; i < format.length(); i++) {
        char cur = format[i];
        int idxLastChar = 0;
        if (i > 0) {
            for (int j = i - 1; j >= 0; j--) {
                char temp = format[j];
                if (temp != ' ') {
                    idxLastChar = j;
                    break;
                }
            }
        }

        if (i == 0 and cur == '-') {
            negate++;
        } else if (i > 0 and cur == '-' and (ops.find(format[idxLastChar]) != std::string::npos)) {
            negate++;
        } else if (cur == '-') {
            subtract++;
        } else if (cur == '+') {
            add++;
        } else if (cur == '|') {
            ceiling++;
        } else if (cur == '/') {
            divide++;
        } else if (cur == '^') {
            exponent++;
        } else if (cur == '!') {
            factorial++;
        } else if (cur == '_') {
            floor++;
        } else if (cur == '%') {
            modulus++;
        } else if (cur == '*') {
            multiply++;
        }
    }

    std::map<std::string, int> dict { { "+: ", add }, { "|: ", ceiling }, { "/: ", divide },
        { "^: ", exponent }, { "!: ", factorial }, { "_: ", floor }, { "%: ", modulus },
        { "*: ", multiply }, { "- (subtract): ", subtract }, { "- (negate): ", negate } };

    std::map<std::string, int>::iterator it = dict.begin();

    while (it != dict.end()) {
        int count = it->second;
        std::string word = it->first;
        if (count > 0) {
            os << word << count << "\n";
        }
        it++;
    }
}