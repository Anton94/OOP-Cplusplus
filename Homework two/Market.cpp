#include <iostream>
#include "Market.h"

/*
	1) Process one product from each deck
	2) Add the new clients
	3) one of the folloing:
		1. Close a deck
		2. Relocate the clients
		3. Open new deck
		** priority: 1 > 2 > 3

	Makes own copy of every client and push the pointer to that copy in some Queue, after the client 'leave' the store, delets this copy.

	The different IDs are because of static variable 'id'.
*/

int Market::id = 0;

Market::Market(int NumberOfAllCashDecks)
{
	numberOfAllCashDecks = NumberOfAllCashDecks;
}


void Market::AddClient(Client * clients, int number)
{
	// Process one product from each deck
	processOneProduct();

	// Add the new clients
	addNewClients(clients, number);

	//if (needToCloseDeck)
	//	// ...
	//else if (pendingQueue.getSize() > 0)
	//	// ...
	//else if (needToOpenNewDeck)
	//	// ...
}

void Market::addNewClients(Client * clients, int number)
{
	// Make ID for every client
	addNewClientsIDs(clients, number);
	
	for (int i = 0; i < number; ++i)
	{
		findPlaceForClient(new Client(clients[i]));
	}
}

// Find place for the client , the client is passed to the function by it`s pointer (the copy of the client have to be made and argument -> it`s pointer)

void Market::findPlaceForClient(Client* client)
{
	// check if the client is with empty basket
	if (client->numberOfGoods <= 0)
	{
		return; // don`t do anything if the client has no goodies
	}
	else if (client->numberOfGoods <= 3 && expressDeck.getSize() < 2 * numberOfAllCashDecks)
	{
		expressDeck.enqueue(client);
	}
	else
	{
		// Find the queue with least ammount of clients. minIt will points to that Queue.
		DLList<Queue<Client*>>::Iterator minIt = decks.begin();
		for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
		{
			if ((*it).getSize() < (*minIt).getSize())
				minIt = it;
		}

		(*minIt).enqueue(client);
	}
}

// Makes ID for every client

void Market::addNewClientsIDs(Client * clients, int number)
{
	for (int i = 0; i < number; ++i)
	{
		clients[i].ID = id++;
	}
}

void Market::processOneProduct()
{
	// express deck
	if (expressDeck.getSize() > 0)
	{
		if (expressDeck.peek()->numberOfGoods <= 0)
		{
			delete expressDeck.dequeue(); // TO DO make check for credit card
		}
		else
		{
			--(expressDeck.peek()->numberOfGoods);
		}
	}

	// other decks
	for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
	{
		if ((*it).peek()->numberOfGoods <= 0)
		{
			delete (*it).dequeue(); // TO DO make check for credit card 
		}
		else
		{
			--((*it).peek()->numberOfGoods);
		}
	}
}

// If the clients in the queue are least than 'numberOfAllCashDecks' / 10

bool Market::checkIfNeedToCloseDeck(DLList<Queue<Client*>>::Iterator& itCloseDeck)
{
	itCloseDeck = decks.begin();

	while (itCloseDeck)
	{
		if ((*itCloseDeck).getSize() < numberOfAllCashDecks / 10)
			return true;

		++itCloseDeck;
	}
}

// If there are two decks with difference between the clients more than 'numberOfAllCashDecks' / 8

bool Market::checkIfNeedToRelocateClients(DLList<Queue<Client*>>::Iterator& itMaxDeck)
{
	// Set the default values for the max and min queues
	DLList<Queue<Client*>>::Iterator itMinDeck = decks.begin();
	itMaxDeck = decks.begin();

	// find the Queue with maximum elements.
	for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
	{
		if ((*itMaxDeck).getSize() < (*it).getSize())
			itMaxDeck = it;
	}

	// find the Queue with minimum elements.
	for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
	{
		if ((*itMinDeck).getSize() > (*it).getSize())
			itMinDeck = it;
	}

	if ((*itMaxDeck).getSize() - (*itMinDeck).getSize() > numberOfAllCashDecks / 8)
		return true;
	
	return false;
}

// If there are clients at the pending Queue

bool Market::checkIfNeedToRelocateWaitingClients() const
{
	return pendingQueue.getSize() > 0;
}

// If on some deck has more than 'numberOfAllCashDecks'

bool Market::checkIfNeedToOpenNewDeck(DLList<Queue<Client*>>::Iterator& itFullDeck)
{
	itFullDeck = decks.begin();

	while (itFullDeck)
	{
		if ((*itFullDeck).getSize() > numberOfAllCashDecks)
			return true;

		++itFullDeck;
	}

	return false;
}

// Calculate the market state and returns a copy of MarketState..

struct MarketState Market::getMarketState()
{
	MarketState marketState;
	marketState.numberOfCashDesk = decks.getSize();
	marketState.numberOfClientsAtCashDecsk = new int[marketState.numberOfCashDesk];

	int counter = 0;
	for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
	{
		marketState.numberOfClientsAtCashDecsk[counter++] = (*it).getSize();
	}

	marketState.numberOfClientsAtExpressCashDeck = expressDeck.getSize();
	
	return marketState;
}