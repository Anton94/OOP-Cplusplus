#include <iostream>
#include "Market.h"

/*
Sorry for my english... 
	1) Process one product from each desk
	2) Add the new clients
	3) one of the folloing:
		1. Close a desk
		2. Relocate the clients
		3. Open new desk
		** priority: 1 > 2 > 3

		If the clients in the queue are least than 'numberOfAllCashDesks' / 10 - the queue had to be closed and the clients - relocate.
		If some desk has more than 'numberOfAllCashDesks' the queue must be split and half of it to go to new desk.
		If there are two desks with difference between the clients more than 'numberOfAllCashDesks' / 8 - the half of the clients on the longer desk had to be relocate on other desks (so skip the desk where they came from).


	Makes own copy of every client and push the pointer to that copy in some Queue, after the client 'leave' the store, delets this copy. (if in the future there is a hierarchy of clients...)
	I have a list of queues for the express desks because there may be add more express desks...

	The different IDs are because of static variable 'id'.
*/

int Market::id = 0;

// The market starts with one express and one normal desks

Market::Market(int NumberOfAllCashDesks)
{
	numberOfAllCashDesks = NumberOfAllCashDesks;
	Queue<ClientExtended*> queue;
	expressDesks.push_back(queue);
	desks.push_back(queue);
}


void Market::AddClient(Client * clients, int number)
{
	// Process one product from the first client of every Queue in the list of expressDesks
	processOneProduct(expressDesks);

	// Process one product from the first client of every Queue in the list of other desks
	processOneProduct(desks);
	
	addNewClients(clients, number);

	// itHelper to find the searched desk if needed...
	DLList<Queue<ClientExtended*>>::Iterator itHelper = desks.begin();

	if (checkIfNeedToCloseDesk(itHelper))
	{
		while (!(*itHelper).isEmpty())
		{
			findPlaceForClient((*itHelper).dequeue(), itHelper); // find place for the client and skip the queue where he is comming from
		}

		desks.removeAt(itHelper); // remove the empty queue
	}
	else if (checkIfNeedToRelocateClients(itHelper))
	{
		size_t firstHalfOfTheQueue = ((*itHelper).getSize() % 2 == 0) ? (*itHelper).getSize() / 2 : (*itHelper).getSize() / 2 + 1; // if the number is odd->the first half will be + 1 bigger than the second one
		size_t secondHalfOfTheQueue = (*itHelper).getSize() / 2; // example 7/2 = 3 (and 4 for first half)

		// Rotate the first half to become second
		for (size_t i = 0; i < firstHalfOfTheQueue; ++i)
		{
			(*itHelper).enqueue((*itHelper).dequeue());
		}

		// Find new places for the clients from the second half
		for (size_t i = 0; i < secondHalfOfTheQueue; ++i)
		{
			findPlaceForClient((*itHelper).dequeue(), itHelper);
		}
	}
	else if (desks.getSize() < numberOfAllCashDesks && checkIfNeedToOpenNewDesk(itHelper))
	{
		size_t firstHalfOfTheQueue = ((*itHelper).getSize() % 2 == 0) ? (*itHelper).getSize() / 2 : (*itHelper).getSize() / 2 + 1; // if the number is odd->the first half will be + 1 bigger than the second one
		size_t secondHalfOfTheQueue = (*itHelper).getSize() / 2; // example 7/2 = 3 (and 4 for first half)

		// Rotate the first half to become second
		for (size_t i = 0; i < firstHalfOfTheQueue; ++i)
		{
			(*itHelper).enqueue((*itHelper).dequeue());
		}

		// Add the rest of the queue (originaly second half of the queue) to the new queue
		Queue<ClientExtended*> newQueue;
		for (size_t i = 0; i < secondHalfOfTheQueue; ++i)
		{
			newQueue.enqueue((*itHelper).dequeue());
		}

		desks.push_back(newQueue);
	}

	cleanEmptyDesks();
}

// Removes the desks with no clients (exept if there is only one desk).

void Market::cleanEmptyDesks()
{
	for (DLList<Queue<ClientExtended*>>::Iterator it = desks.begin(); it; ++it)
	{
		if ((*it).getSize() == 0 && desks.getSize() > 1)
			desks.removeAt(it);
	}
}

// Process one product from the first client of every Queue in the list of desks(queues) which is given as parameter.

void Market::processOneProduct(DLList<Queue<ClientExtended*>> & list)
{
	for (DLList<Queue<ClientExtended*>>::Iterator it = list.begin(); it; ++it)
	{
		if ((*it).getSize() > 0) // in any case ...
		{
			if ((*it).peek()->numberOfGoods <= 0)
			{
				if ((*it).peek()->additionalWaiting > 0)
					--((*it).peek()->additionalWaiting);
				else				
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
	
	// There is no need to skip some queue when the clients are new
	DLList<Queue<ClientExtended*>>::Iterator it = desks.end();
	for (int i = 0; i < number; ++i)
	{
		ClientExtended* newClient = new ClientExtended(clients[i]);

		findPlaceForClient(newClient, it);
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

void Market::findPlaceForClient(ClientExtended*client, DLList<Queue<ClientExtended*>>::Iterator & itSkip)
{
	// check if the client is with empty basket
	if (client->numberOfGoods <= 0)
	{
		return; // don`t do anything if the client has no goodies
	}
	
	if (client->numberOfGoods <= 3)
	{
		// find place for the client on some express desk
		for (DLList<Queue<ClientExtended*>>::Iterator it = expressDesks.begin(); it; ++it)
		{
			if ((*it).getSize() < 2 * numberOfAllCashDesks)
			{
				(*it).enqueue(client);
				return; 
			}
		}
	}
	
	// If the client has more than 3 goodies or the express desks are full...
	// Find the queue with least ammount of clients. minIt will points to that Queue.
	DLList<Queue<ClientExtended*>>::Iterator minIt = desks.begin();
	
	// If the first Queue had to be skiped ->move it to next queue, if there is only one, the client wont be add ...
	if (minIt == itSkip)
		++minIt;
	for (DLList<Queue<ClientExtended*>>::Iterator it = desks.begin(); it; ++it)
	{
		if (it != itSkip && (*it).getSize() < (*minIt).getSize())
			minIt = it;
	}

	(*minIt).enqueue(client);
}

// If the clients in the queue are least than 'numberOfAllCashDesks' / 10
// If so a iterator to that queue is saved in the given parameter 'itCloseDesk' otherwise the 'itCloseDesk' points to invalid field

bool Market::checkIfNeedToCloseDesk(DLList<Queue<ClientExtended*>>::Iterator& itCloseDesk)
{
	itCloseDesk = desks.begin();

	while (itCloseDesk)
	{
		if ((*itCloseDesk).getSize() < numberOfAllCashDesks / 10)
			return true;

		++itCloseDesk;
	}
}

// If there are two desks with difference between the clients more than 'numberOfAllCashDesks' / 8
// If so a iterator to that longer queue is saved in the given parameter 'itMaxDesk' otherwise the 'itMaxDesk' points to invalid field

bool Market::checkIfNeedToRelocateClients(DLList<Queue<ClientExtended*>>::Iterator& itMaxDesk)
{
	// Set the default values for the max and min queues
	DLList<Queue<ClientExtended*>>::Iterator itMinDesk = desks.begin();
	itMaxDesk = desks.begin();

	// find the Queue with maximum elements.
	for (DLList<Queue<ClientExtended*>>::Iterator it = desks.begin(); it; ++it)
	{
		if ((*itMaxDesk).getSize() < (*it).getSize())
			itMaxDesk = it;
	}

	// find the Queue with minimum elements.
	for (DLList<Queue<ClientExtended*>>::Iterator it = desks.begin(); it; ++it)
	{
		if ((*itMinDesk).getSize() > (*it).getSize())
			itMinDesk = it;
	}

	if ((*itMaxDesk).getSize() - (*itMinDesk).getSize() > numberOfAllCashDesks / 8.0)
	{
		return true;
	}
	
	return false;
}

// If on some desk has more than 'numberOfAllCashDesks'
// If so a iterator to that queue(desk) is saved in the given parameter 'itFullDesk' otherwise the 'itFullDesk' points to invalid field

bool Market::checkIfNeedToOpenNewDesk(DLList<Queue<ClientExtended*>>::Iterator& itFullDesk)
{
	itFullDesk = desks.begin();

	while (itFullDesk)
	{
		if ((*itFullDesk).getSize() > numberOfAllCashDesks)
			return true;

		++itFullDesk;
	}

	return false;
}

// Calculate the market state and returns a copy of MarketState..

struct MarketState Market::getMarketState()
{
	MarketState marketState;
	marketState.numberOfCashDesk = desks.getSize();
	marketState.numberOfClientsAtCashDecsk = new int[marketState.numberOfCashDesk];

	int counter = 0;
	for (DLList<Queue<ClientExtended*>>::Iterator it = desks.begin(); it; ++it)
	{
		marketState.numberOfClientsAtCashDecsk[counter++] = (*it).getSize();
	}

	marketState.numberOfClientsAtExpressCashDeck = 0;

	for (DLList<Queue<ClientExtended*>>::Iterator it = expressDesks.begin(); it; ++it)
	{
		marketState.numberOfClientsAtExpressCashDeck += (*it).getSize();
	}
	
	return marketState;
}