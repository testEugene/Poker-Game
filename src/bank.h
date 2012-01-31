/*
 * bank.h
 *
 *  Created on: 09.12.2011
 *      Author: bot
 */

#ifndef BANK_H_
#define BANK_H_
#include "player.h"
class Bank
{
	int kol;		// количество игроков в банке
	Player **gamer; // игроки участники
	int sum_bank;   // общая сумма в банке
	int round;		// текущий круг
	int winKol[7];	// количество победителей на место
	void setWinKol(int r); // определение количества победителей
						   // на место за пъедесталом в текущем раунде
	int getWinPlaceRound();// определение максимального места
						   // за пъедесталом в раунде
	int minStavkaRound(int p);// определение минимальной ставки в раунде
	void raspredMoney(int vr, int p);// распределение денег из банка в кошелек игроков
public:
	Bank(Player **g, int k = 6);// конструктор
	void addPlayer(Player & p, int st,int r, bool allin = false);// добавление игрока в банк с суммой денег
	void winners();				// раздача денег
	int getSumBank(){
		return sum_bank;
	}
};
#endif /* BANK_H_ */
