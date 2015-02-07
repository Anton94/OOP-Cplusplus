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

void testMarketState()
{
	checkMarketStateFunctionality();
	Market m(10);
	printMarketState(m.getMarketState());
}

void test_addOneByOne()
{
	std::cout << "Start test addOneByOne" << std::endl;
	Market m(2);
	Client c{ -1, 40, 0 };

	for (int i = 0; i < 10; i++)
	{
		m.AddClient(&c, 1);
	}

	MarketState state = m.getMarketState();

	if (state.numberOfCashDesk != 2)
	{
		std::cout << "we expected 2 open cash desk but we found : " << state.numberOfCashDesk << std::endl;
		return;
	}
	if (state.numberOfClientsAtCashDecsk[0] != 5)
	{
		std::cout << "we expected 5 clients on cash desk [0] but found :" << state.numberOfClientsAtCashDecsk[0] << std::endl;
		return;
	}
	if (state.numberOfClientsAtCashDecsk[1] != 5)
	{
		std::cout << "we expected 5 clients on cash desk [1] but found :" << state.numberOfClientsAtCashDecsk[1] << std::endl;
		return;
	}
	if (state.numberOfClientsAtExpressCashDeck != 0)
	{
		std::cout << "we expected 0 client on expres cash desk but found :" << state.numberOfClientsAtExpressCashDeck << std::endl;
		return;
	}
	std::cout << "test addOneByOne is OK" << std::endl;
}

void test_expresCashDesk()
{

	std::cout << "Start test expresCashDesk" << std::endl;
	Market m(1);
	Client poor{ -1, 2, 0 }, rich{ -1, 10, 0 };

	for (int i = 0; i < 5; i++)
	{
		m.AddClient(&poor, 1);
		m.AddClient(&rich, 1);
	}

	MarketState state = m.getMarketState();

	if (state.numberOfClientsAtCashDecsk[0] != 6)
	{
		std::cout << "we expected 6 clients on cash desk [0] but found :" << state.numberOfClientsAtCashDecsk[0] << std::endl;
		return;
	}
	if (state.numberOfClientsAtExpressCashDeck != 2)
	{
		std::cout << "we expected 2 client on expres cash desk but found :" << state.numberOfClientsAtExpressCashDeck << std::endl;
		return;
	}
	std::cout << "test expresCashDesk is OK" << std::endl;
}

void test_manyClientsInOneTick()
{
	std::cout << "Start test manyClientsInOneTick" << std::endl;
	Market m(4);
	Client crowd[10];

	for (int i = 0; i < 10; i++)
	{
		crowd[i].creditCard = 0;
		crowd[i].ID = -1;
		crowd[i].numberOfGoods = i;
	}

	m.AddClient(crowd, 10);

	MarketState state = m.getMarketState();

	if (state.numberOfCashDesk != 2)
	{
		std::cout << "we expected 2 open cash desk but we found : " << state.numberOfCashDesk << std::endl;
		return;
	}
	if (state.numberOfClientsAtCashDecsk[0] != 3)
	{
		std::cout << "we expected 3 clients on cash desk [0] but found :" << state.numberOfClientsAtCashDecsk[0] << std::endl;
		return;
	}
	if (state.numberOfClientsAtCashDecsk[1] != 3)
	{
		std::cout << "we expected 3 clients on cash desk [1] but found :" << state.numberOfClientsAtCashDecsk[1] << std::endl;
		return;
	}
	if (state.numberOfClientsAtExpressCashDeck != 3)
	{
		std::cout << "we expected 0 client on expres cash desk but found :" << state.numberOfClientsAtExpressCashDeck << std::endl;
		return;
	}

	std::cout << "test manyClientsInOneTick is OK" << std::endl;
}

void test_unloadMarket()
{
	std::cout << "Start test unloadMarket" << std::endl;
	Market m(4);
	Client crowd[10];

	for (int i = 0; i < 10; i++)
	{
		crowd[i].creditCard = 0;
		crowd[i].ID = -1;
		crowd[i].numberOfGoods = i;
	}

	m.AddClient(crowd, 10);

	for (int i = 0; i < 25; i++)
	{
		m.AddClient(NULL, 0);
	}

	MarketState state = m.getMarketState();

	if (state.numberOfCashDesk != 1)
	{
		std::cout << "we expected 1 open cash desk but we found : " << state.numberOfCashDesk << std::endl;
		return;
	}
	if (state.numberOfClientsAtCashDecsk[0] != 1)
	{
		std::cout << "we expected 1 client on cash desk [0] but found :" << state.numberOfClientsAtCashDecsk[0] << std::endl;
		return;
	}
	if (state.numberOfClientsAtExpressCashDeck != 0)
	{
		std::cout << "we expected 0 client on expres cash desk but found :" << state.numberOfClientsAtExpressCashDeck << std::endl;
		return;
	}
	std::cout << "test unloadMarket is OK" << std::endl;
}

void test_creditCard()
{
	std::cout << "Start test creditCard" << std::endl;
	Market m(1);
	Client crowd[10];

	for (int i = 0; i < 10; i++)
	{
		crowd[i].creditCard = 1;
		crowd[i].ID = -1;
		crowd[i].numberOfGoods = 1;
	}

	m.AddClient(crowd, 10);

	for (int i = 0; i < 5; i++)
	{
		m.AddClient(NULL, 0);
	}

	MarketState state = m.getMarketState();

	if (state.numberOfClientsAtCashDecsk[0] != 6)
	{
		std::cout << "we expected 6 client on cash desk [0] but found :" << state.numberOfClientsAtCashDecsk[0] << std::endl;
		return;
	}
	if (state.numberOfClientsAtExpressCashDeck != 0)
	{
		std::cout << "we expected 0 client on expres cash desk but found :" << state.numberOfClientsAtExpressCashDeck << std::endl;
		return;
	}
	std::cout << "test creditCard is OK" << std::endl;
}

void test_ClientState()
{
	std::cout << "Start test clientState" << std::endl;
	Market m(2);
	Client c{ -1, 40, 0 };
	Client c1{ -1, 3, 0 };

	for (int i = 0; i < 10; i++)
	{
		m.AddClient(&c, 1);
	}

	m.AddClient(&c1, 1);
	m.AddClient(&c1, 1);

	ClientState clientState = m.getClientState(61);

	if (clientState.CashDeskPosition != 0)
	{
		std::cout << "getClientState(61) and we expected CashDeskPosition = 0 but found :" << clientState.CashDeskPosition << std::endl;
		return;
	}
	if (clientState.QueuePosition != 1)
	{
		std::cout << "getClientState(61) and we expected QueuePosition = 1 but found :" << clientState.QueuePosition << std::endl;
		return;
	}

	clientState = m.getClientState(6121);

	if (clientState.CashDeskPosition != -1)
	{
		std::cout << "getClientState(6121) and we expected CashDeskPosition = -1 but found :" << clientState.CashDeskPosition << std::endl;
		return;
	}
	if (clientState.QueuePosition != -1)
	{
		std::cout << "getClientState(6121) and we expected QueuePosition = -1 but found :" << clientState.QueuePosition << std::endl;
		return;
	}
	if (clientState.client != NULL)
	{
		std::cout << "getClientState(6121) and we expected QueuePosition = NULL but found :" << clientState.QueuePosition << std::endl;
		return;
	}

	std::cout << "test clientState is OK" << std::endl;
}

int main()
{
	_CrtMemState s1,s2,s3;
	_CrtMemCheckpoint(&s1);

		std::cout << "Here we go..." << std::endl;

	//	testMarketState();
		std::cout << std::endl;

		std::cout << std::endl;
		test_addOneByOne();
		std::cout << std::endl;
		test_expresCashDesk();
		std::cout << std::endl;
		test_manyClientsInOneTick();
		std::cout << std::endl;
		test_unloadMarket();
		std::cout << std::endl;
		test_creditCard();
		std::cout << std::endl;
		test_ClientState();
		std::cout << std::endl;


	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}