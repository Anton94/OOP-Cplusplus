#include <iostream>
#include "Market.h"

MarketState simulateMarketState()
{
	DLList<Queue<int>> list;
	Queue<int> queue;
	queue.enqueue(1);
	list.push_back(queue);
	queue.enqueue(1);
	list.push_back(queue);
	queue.enqueue(1);
	list.push_back(queue);
	queue.enqueue(1);
	list.push_back(queue);

	MarketState marketState;
	marketState.numberOfCashDesk = list.getSize();
	marketState.numberOfClientsAtCashDecsk = new int[marketState.numberOfCashDesk];
	
	int counter = 0;
	for (DLList<Queue<int>>::Iterator it = list.begin(); it; ++it)
	{
		marketState.numberOfClientsAtCashDecsk[counter++] = (*it).getSize();
	}
	
	marketState.numberOfClientsAtExpressCashDeck = 13;

	return marketState;
}

void printMarketState(const MarketState & marketState)
{
	std::cout << "marketState.numberOfCashDesk = " << marketState.numberOfCashDesk << std::endl;
	for (int i = 0; i < marketState.numberOfCashDesk; ++i)
	{
		std::cout << "marketState.numberOfClientsAtCashDecsk[" << i << "] = " << marketState.numberOfClientsAtCashDecsk[i] << std::endl;
	}
	std::cout << "marketState.numberOfClientsAtExpressCashDeck = " << marketState.numberOfClientsAtExpressCashDeck << std::endl;
}

void checkMarketStateFunctionality()
{
	std::cout << "Generate market state..." << std::endl; 
	MarketState marketState = simulateMarketState();

	printMarketState(marketState);
	
	std::cout << std::endl;
}

int main()
{
	std::cout << "Here we go..." << std::endl;
	checkMarketStateFunctionality();
	Market m(10);
	printMarketState(m.getMarketState());

	DLList<int> list;
	list.push_back(*new int(5));
	list.push_back(*new int(15));
	list.push_back(*new int(25));



	return 0;
}