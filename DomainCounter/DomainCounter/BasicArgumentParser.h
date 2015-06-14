#pragma once

#include "DomainCounter.h"

struct BasicArgumentParser
{
	// VERY BASIC parse the arguments. This works with the homework type of arguments, were the command is like: "-<command_letter>" for example "-i","-d","-p"
	// If the input is wrong, stops and works with the valid once.
	static	void parseTheInputArguments(int argc, char**argv, DomainCounter& domainCounter);
};