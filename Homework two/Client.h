#pragma once



struct Client
{
	int ID;					// Client ID in the market
	int numberOfGoods;		// number of goods of the cleint
	bool creditCard;		// if he is paying with credit card
};

struct ClientState
{
	int CashDeskPosition;	//number of desk
	int QueuePosition;		// number of possition in the queue
	Client * client;
};