#pragma once

#include "Client.h"
#include "../Double linked list/DLList.h"
#include "../Queue with one link/Queue.h"
#include "MarketState.h"

class Market
{
public:
	Market(int NumberOfAllCashDecks); // max number of Decks (without the express one)
	void AddClient(Client * clients, int number); // add clients in the store (number - how many clients)
	struct MarketState getMarketState(); 
	// TO DO ClientState getClientState(int ID);
private:
	void processOneProduct(DLList<Queue<Client*>> & list);
	void addNewClients(Client * clients, int number);
	void findPlaceForClient(Client* client, DLList<Queue<Client*>>::Iterator & itSkip);
	void addNewClientsIDs(Client * clients, int number);
	bool checkIfNeedToCloseDeck (DLList<Queue<Client*>>::Iterator& itCloseDeck);
	bool checkIfNeedToRelocateClients(DLList<Queue<Client*>>::Iterator& itMaxDeck);
	bool checkIfNeedToOpenNewDeck(DLList<Queue<Client*>>::Iterator& itFullDeck);
private:
	DLList<Queue<Client*>> decks;
	DLList<Queue<Client*>> expressDecks;
	size_t numberOfAllCashDecks;
	static int id;
}; 