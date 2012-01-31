/*
 * player.h
 *
 *  Created on: 09.12.2011
 *      Author: bot
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "Card.h"
class Player {
private:
	std::string login;
	Card cards[2];
	int purse;	        // кошелек игрока
	double ostatok;     // остаток при делении выигрыша
	int currentRate[4];	// сколько игрок поставил на 1/2/3 кругах торговли
	bool inGame;		// сбросил ли игрок
	bool isAllin;		// пошел ли в allin(есть ли деньги)
	int winPlace; 		// место за пьедесталом
	int position;		// позиция за столом
public:
	Player(std::string nm = "No name", int pt = 0, int bank = 50);// конструктор
	~Player();
	void SetCards(Card, Card);
	Card GetFirstCard();
	Card GetSecondCard();
	std::string getLogin(); 	// вывод имени
	void setWinPlace(int w); 	// присвоить победителя
	int getWinPlace();			// взять место победителя
	void setCurrrentStavka(int st, int round); // вывод ставки текущего раунда
	int getCurrrentStavka(int round);// ставка в текущем раунде
	void setPurse(int bk, double ost = 0);	// положить деньги в кошелек
	int getPurse();				// взять деньги из кошелька
	double getOstatok();		//
	bool getInGame();			//  проверка игрока на пас
	void setInGame(bool b);		//
	bool getIsAllin();			// проверка во банк
	void setIsAllin(bool b);	// пойти во банк
	int getPosition();
	void setPosition(int p);
};
#endif /* PLAYER_H_ */
