#include <iostream>
#include "MarketState.h"


MarketState::MarketState()
{
	numberOfCashDesk = 0;
	numberOfClientsAtCashDecsk = NULL;
	numberOfClientsAtExpressCashDeck = 0;
}

// what if someone set the numberOfCashDesk to negative number? public not cool.

MarketState::MarketState(const MarketState& other)
{
	numberOfCashDesk = other.numberOfCashDesk;

	numberOfClientsAtCashDecsk = new int[numberOfCashDesk];
	for (int i = 0; i < numberOfCashDesk; ++i)
	{
		numberOfClientsAtCashDecsk[i] = other.numberOfClientsAtCashDecsk[i];
	}

	numberOfClientsAtExpressCashDeck = other.numberOfClientsAtExpressCashDeck;
}

MarketState::~MarketState()
{
	delete[] numberOfClientsAtCashDecsk;
}