#include <iostream>
#include "Market.h"

/*
	1) Process one product from each deck
	2) Add the new clients
	3) one of the folloing:
		1. Close deck
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

	if (needToCloseDeck)
		// ...
	else if (pendingQueue.getSize() > 0)
		// ...
	else if (needToOpenNewDeck)
		// ...
}

void Market::addNewClients(Client * clients, int number)
{
	// Make ID for every client
	addNewClientsIDs(clients, number);
	
	for (int i = 0; i < number; ++i)
	{
		// check if the client is with empty basket
		if (clients[i].numberOfGoods <= 0)
		{
			;
		}
		else if (clients[i].numberOfGoods <= 3 && expressDeck.getSize() < 2 * numberOfAllCashDecks)
		{
			expressDeck.enqueue(new Client(clients[i]));
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

			(*minIt).enqueue(new Client(clients[i]));
		}
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