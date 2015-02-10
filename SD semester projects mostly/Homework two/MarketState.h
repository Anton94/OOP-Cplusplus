#pragma once

#include "Market.h"


/*
The MarketState has dynamic array so it need (maybe) copy constructor and destructor for the function getMarektState() where it returns some copy of MarketState...
*/

struct MarketState
{
	int numberOfCashDesk; // number of desks currently open
	int * numberOfClientsAtCashDecsk; // number of clients at every decks opened at the moment
	int numberOfClientsAtExpressCashDeck;
public:
	MarketState();
	MarketState(const MarketState& other);
	~MarketState();
};
