#include <iostream>
#include "Market.h"

/*
Sorry for my english... 
	1) Process one product from each deck
	2) Add the new clients
	3) one of the folloing:
		1. Close a deck
		2. Relocate the clients
		3. Open new deck
		** priority: 1 > 2 > 3

		If the clients in the queue are least than 'numberOfAllCashDecks' / 10 - the queue had to be closed and the clients - relocate.
		If some deck has more than 'numberOfAllCashDecks' the queue must be split and half of it to go to new deck.
		If there are two decks with difference between the clients more than 'numberOfAllCashDecks' / 8 - the half of the clients on the longer deck had to be relocate on other decks.


	Makes own copy of every client and push the pointer to that copy in some Queue, after the client 'leave' the store, delets this copy. (if in the future there is a hierarchy of clients...)
	I have a list of queues for the express decks because there may be add more express decks...

	The different IDs are because of static variable 'id'.
*/

int Market::id = 0;

Market::Market(int NumberOfAllCashDecks)
{
	numberOfAllCashDecks = NumberOfAllCashDecks;
}


void Market::AddClient(Client * clients, int number)
{
	// Process one product from the first client of every Queue in the list of expressDecks
	processOneProduct(expressDecks);

	// Process one product from the first client of every Queue in the list of other decks
	processOneProduct(decks);
	
	addNewClients(clients, number);

	// itHelper to find the searched deck if needed...
	DLList<Queue<Client*>>::Iterator itHelper = decks.begin();

	if (checkIfNeedToCloseDeck(itHelper))
		;
	else if (checkIfNeedToRelocateClients(itHelper))
		;
	else if (checkIfNeedToOpenNewDeck(itHelper))
		;
}

// Process one product from the first client of every Queue in the list of decks(queues) which is given as parameter.

void Market::processOneProduct(DLList<Queue<Client*>> & list)
{
	for (DLList<Queue<Client*>>::Iterator it = list.begin(); it; ++it)
	{
		if ((*it).getSize() > 0) // in any case ...
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

// Makes ID for every client

void Market::addNewClientsIDs(Client * clients, int number)
{
	for (int i = 0; i < number; ++i)
	{
		clients[i].ID = id++;
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
	
	if (client->numberOfGoods <= 3)
	{
		// find place for the client on some express deck
		for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
		{
			if ((*it).getSize() < 2 * numberOfAllCashDecks)
			{
				(*it).enqueue(client);
				return; 
			}
		}
	}
	
	// If the client has more than 3 goodies or the express decks are full...
	// Find the queue with least ammount of clients. minIt will points to that Queue.
	DLList<Queue<Client*>>::Iterator minIt = decks.begin();
	for (DLList<Queue<Client*>>::Iterator it = decks.begin(); it; ++it)
	{
		if ((*it).getSize() < (*minIt).getSize())
			minIt = it;
	}

	(*minIt).enqueue(client);
}

// If the clients in the queue are least than 'numberOfAllCashDecks' / 10
// If so a iterator to that queue is saved in the given parameter 'itCloseDeck' otherwise the 'itCloseDeck' points to invalid field

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
// If so a iterator to that longer queue is saved in the given parameter 'itMaxDeck' otherwise the 'itMaxDeck' points to invalid field

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

// If on some deck has more than 'numberOfAllCashDecks'
// If so a iterator to that queue(deck) is saved in the given parameter 'itFullDeck' otherwise the 'itFullDeck' points to invalid field

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

	marketState.numberOfClientsAtExpressCashDeck = 0;

	for (DLList<Queue<Client*>>::Iterator it = expressDecks.begin(); it; ++it)
	{
		marketState.numberOfClientsAtExpressCashDeck += (*it).getSize();
	}
	
	return marketState;
}