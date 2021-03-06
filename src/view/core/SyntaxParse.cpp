#include "../_include/Command.h"

// Dependencies
#include <cstdlib>
#include "../../common/_include/Exception.h"
#include <iostream>

namespace cmd {

Identity CmdIdToIdentity (Token cmdId);

// Temporary parse, need rework in the future.
Command parse (std::vector<Token> list)
try
{
    Command command;
    switch (list.at(0).type()) {
        case Token::CREATE:
            command.actionType_ = Command::Action::CREATE;
            break;
        case Token::REMOVE:
            command.actionType_ = Command::Action::REMOVE;
            break;
        case Token::JOIN:
            command.actionType_ = Command::Action::JOIN;
            break;
        case Token::DISJOIN:
            command.actionType_ = Command::Action::DISJOIN;
            break;
        case Token::MERGE:
            command.actionType_ = Command::Action::MERGE;
            break;
        case Token::UNMERGE:
            command.actionType_ = Command::Action::UNMERGE;
            break;
        case Token::HAS:
            command.actionType_ = Command::Action::HAS;
            break;
        default:
            throw LogicExcept();
    }

    switch (command) {
        default:
            throw LogicExcept();
        case Command::Action::CREATE:
            if (list.at(1).type() == Token::GRAPH &&
                list.at(2).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::GRAPH;
                return command;
            }
            if (list.at(1).type() == Token::VERTEX &&
                list.at(2).type() == Token::AT &&
                list.at(3).type() == Token::GRAPH &&
                list.at(4).type() == Token::ID &&
                list.at(5).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::VERTEX;
                command.resource_ = std::atoi(list.at(4).lexeme()
                                                  .substr(1, list.at(4)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
            }
            throw LogicExcept();
        case Command::Action::REMOVE:
            if (list.at(1).type() == Token::GRAPH &&
                list.at(2).type() == Token::ID &&
                list.at(3).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::VERTEX;
                command.resource_ = std::atoi(list.at(2).lexeme()
                                                  .substr(1, list.at(2)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
            }
            if (list.at(1).type() == Token::VERTEX &&
                list.at(2).type() == Token::ID &&
                list.at(3).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::VERTEX;
                command.resource_ = std::atoi(list.at(2).lexeme()
                                                  .substr(1, list.at(2)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
            }
            throw LogicExcept();
        case Command::Action::HAS:
            // HAS_CYCLE_AT
            if (list.at(1).type() == Token::CYCLE &&
                list.at(2).type() == Token::AT &&
                list.at(3).type() == Token::GRAPH &&
                list.at(4).type() == Token::ID &&
                list.at(5).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::CYCLE;
                command.resource_ = std::atoi(list.at(4).lexeme()
                                                  .substr(1, list.at(4)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
            }
            // HAS_PATH_AT
            else if (list.at(1).type() == Token::PATH &&
                     list.at(2).type() == Token::AT &&
                     list.at(3).type() == Token::VERTEX &&
                     list.at(4).type() == Token::ID &&
                     list.at(5).type() == Token::AND &&
                     list.at(6).type() == Token::ID &&
                     list.at(7).type() == Token::AT &&
                     list.at(8).type() == Token::GRAPH &&
                     list.at(9).type() == Token::ID &&
                     list.at(10).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::PATH;
                command.findPath_ = {
                    .graph_ = CmdIdToIdentity(list.at(9)),
                    .vertexPair_ = { CmdIdToIdentity(list.at(4)),
                                     CmdIdToIdentity(list.at(6)) }
                };
                return command;
            }
            // HAS_SPANNINGTREE_AT
            else if (list.at(1).type() == Token::SPANNINGTREE &&
                     list.at(2).type() == Token::AT &&
                     list.at(3).type() == Token::GRAPH &&
                     list.at(4).type() == Token::ID &&
                     list.at(5).type() == Token::SEMICOLON) {
                command.resourceType_ = Command::Resource::SPANNINGTREE;
                command.resource_ = std::atoi(list.at(4).lexeme()
                                                  .substr(1, list.at(4)
                                                  .lexeme().length())
                                                  .c_str());
                return command;
            }
            throw LogicExcept();

        case Command::Action::JOIN:
        case Command::Action::DISJOIN:
            if (list.at(1).type() == Token::VERTEX &&
                list.at(2).type() == Token::ID &&
                list.at(3).type() == Token::AND &&
                list.at(4).type() == Token::ID &&
                list.at(5).type() == Token::SEMICOLON) {
                command.targetPair_[0] = std::atoi(list.at(2).lexeme()
                                                       .substr(1, list.at(2)
                                                       .lexeme().length())
                                                       .c_str());
                command.targetPair_[1] = std::atoi(list.at(4).lexeme()
                                                       .substr(1, list.at(4)
                                                       .lexeme().length())
                                                       .c_str());
                return command;
            }
            throw LogicExcept();
    }
}
catch (...) {
    throw LogicExcept();
}

Identity CmdIdToIdentity (Token cmdId)
{
    return std::atoi(cmdId.lexeme()
                     .substr(1, cmdId.lexeme().length())
                     .c_str());
}

}
