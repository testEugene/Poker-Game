/*
 * player.cpp
 *
 *  Created on: 09.12.2011
 *      Author: bot
 */
#include <iostream>
#include <cstring>
using namespace std;
#include "player.h"
Player::Player(string nm, int bank, int pt) {
	login = nm;
	purse = bank; 	//начальный банк игрока
	position = pt; 	//позиция за столом
	isAllin = false;//
	inGame = true; //первоначально не в игре
	winPlace = 0; 	//место победителя
	ostatok = 0.0;	//остаток
}

void Player::SetCards(Card card1, Card card2) {
	cards[0] = card1;
	cards[1] = card2;
}

Card Player::GetFirstCard() {
	return cards[0];
}

Card Player::GetSecondCard() {
	return cards[1];
}

Player::~Player() {

}
std::string Player::getLogin() {	//вывод имени
	return login;
}
void Player::setWinPlace(int w) {	//присвоить победителя
	winPlace = w;
}
int Player::getWinPlace() {			//взять место победителя
	return winPlace;
}
void Player::setCurrrentStavka(int st, int round) { // вывод ставки текущего раунда
	currentRate[round] = st;
}
int Player::getCurrrentStavka(int round) { // ставка в текущем раунде
	return currentRate[round];
}
void Player::setPurse(int bk, double ost) {		// положить деньги в кошелек
	purse = bk;
	ostatok = ost;
}
int Player::getPurse() {			// взять деньги из кошелька
	return purse;
}
double Player::getOstatok(){
	return ostatok;
}
bool Player::getInGame() {			//  проверка игрока на пас
	return inGame;
}
void Player::setInGame(bool b) {	//
	inGame = b;
}
bool Player::getIsAllin() {			// проверка во банк
	return isAllin;
}
void Player::setIsAllin(bool b) {	// пойти во банк
	isAllin = b;
}
int Player::getPosition() {
	return position;
}
void Player::setPosition(int p) {
	position = p;
}

