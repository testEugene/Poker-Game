/*
 * Card.cpp
 *
 *  Created on: 18.11.2011
 *      Author: eugene
 */
#ifndef CARD_H_
#define CARD_H_
#include <string>
#include <stdexcept>
class Card {
	std::string suit;// переменная, хранящая масть
	std::string rank;//переменная, хранящая ранг
	int suitId;// int от 0 до 3, характеризующая масть
	int rankId;// int от 2 до 14, характеризующая ранг
public:
	Card(int,int);//конструктор параметры (int масть, int ранг)
	Card();
	virtual ~Card();
	std::string getSuit();// получение масти строка
	std::string getRank();// получение ранга строка
	int getSuitId();// получение масти int
	int getRankId();// получение ранга int
	Card& operator=(Card);// оператор присваивания
	friend bool operator==(const Card&, const Card&);// сравнение на равенство
	friend bool operator>(const Card&, const Card&);// сравнение больше ли карта
	friend bool operator<(const Card&, const Card&);// сравнение  меньше ли карта
	friend bool operator>=(const Card&, const Card&);// сравнение больше или равна карта
	friend bool operator<=(const Card&, const Card&);// сравнение меньше или равна карта
};

#endif /* CARD_H_ */
