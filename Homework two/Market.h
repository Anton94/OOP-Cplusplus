#pragma once

#include "Client.h"
#include "../Double linked list/DLList.h"
#include "../Queue with one link/Queue.h"
#include "MarketState.h"

class Market
{
public:
	Market(int NumberOfAllCashDesks); // max number of Desks (without the express one)
	void AddClient(Client * clients, int number); // add clients in the store (number - how many clients)
	struct MarketState getMarketState(); 
	struct ClientState getClientState(int ID);
private:
	void processOneProduct(DLList<Queue<ClientExtended*>> & list);
	void addNewClients(Client * clients, int number);
	void findPlaceForClient(ClientExtended* client, DLList<Queue<ClientExtended*>>::Iterator & itSkip);
	void addNewClientsIDs(Client * clients, int number);
	bool checkIfNeedToCloseDesk(DLList<Queue<ClientExtended*>>::Iterator& itCloseDesk);
	bool checkIfNeedToRelocateClients(DLList<Queue<ClientExtended*>>::Iterator& itMaxDesk);
	bool checkIfNeedToOpenNewDesk(DLList<Queue<ClientExtended*>>::Iterator& itFullDesk);
	void cleanEmptyDesks();
	bool searchForClientAtListOfQueues(DLList<Queue<ClientExtended*>> & list, ClientState& clientState, int& ID, size_t& deskPosition);
private:
	DLList<Queue<ClientExtended*>> desks;
	DLList<Queue<ClientExtended*>> expressDesks;
	size_t numberOfAllCashDesks;
	static int id;
}; 