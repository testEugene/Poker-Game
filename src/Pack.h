/*
 * Pack.h
 *
 *  Created on: 18.11.2011
 *      Author: eugene
 */
#ifndef PACK_H_
#define PACK_H_
#include "Card.h"
class Pack {
	int size; // кол-во неотданных карт в колоде
	Card Cards[52];	// контейнер, содержащий эти карты
public:
	Pack(int);// контрукция, колода создается "размешанной"
	void RefreshPack();// метод обновляющий колоду.
	Card getCard();// метод, выдающий карту из колоды, карта из нее удаляется.
	virtual ~Pack();
};

#endif /* PACK_H_ */
