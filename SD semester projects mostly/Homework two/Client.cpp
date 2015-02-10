#include "Client.h"

ClientExtended::ClientExtended(const Client& other)
{
	ID = other.ID;
	numberOfGoods = other.numberOfGoods;
	creditCard = other.creditCard;
	additionalWaiting = (other.creditCard) ? 0 : 1; // If there is credit card- no additional waiting
}