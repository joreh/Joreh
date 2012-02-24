#ifndef __COMMAND_PARSER_H
#define __COMMAND_PARSER_H

#include <string>
#include <vector>
#include "Parser/Command.h"

std::vector<Command *> *parseCommandMessage( std::string str );

#endif
