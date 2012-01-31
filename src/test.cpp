/*
 * test.cpp
 *
 *  Created on: 11.12.2011
 *      Author: eugene
 */
#include "Calculation.h"
#include "Pack.h"
#include "bank.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
std::string from_int(int number);
void createSetOfStakes(int** Stakes, int numberOfRounds, int numberOfGamers);
int main(int argc, char** argv) {

	Player **Gamer;
	int numberOfGamers = 6; // количество игроков за столом
	int numberOfRounds=4;
	Gamer = new Player*[6]; // 6 игроков
	Pack Cards(0); // колода карт
	Card FiveCard[5]; // 5 общих карт
	int nRound = 1; // первый круг торговли
	/* создадим numberOfGamers игроков */
	for (int i = 0; i < numberOfGamers; i++) {
		Gamer[i] = new Player("Gamer" + from_int(i), 50, i);
		Gamer[i][0].SetCards(Cards.getCard(), Cards.getCard());
		std::cout << Gamer[i][0].getLogin() << " "
				<< Gamer[i][0].GetFirstCard().getRank() << " of "
				<< Gamer[i][0].GetFirstCard().getSuit() << " ";
		std::cout << Gamer[i][0].GetSecondCard().getRank() << " of "
				<< Gamer[i][0].GetSecondCard().getSuit() << std::endl;
	}
	// ставки игроков для теста
	/*
	int Stavki[4][6] = {
			{ 2, 2, 2, 2, 2, 2 },
			{ 6, 5, 6, 6, 6, 6 },
			{ 6, 0, 4, 5, 6, 6 },
			{ 2, 0, 0, 0, 4, 5 } };*/
	int **Stavki= new int*[numberOfRounds];
		for (int i=0;i<numberOfRounds;i++)
			Stavki[i]= new int[numberOfGamers];
	createSetOfStakes(Stavki,numberOfRounds,numberOfGamers);
	// объявление банка
	Bank bank(Gamer, numberOfGamers);
	// круг торговли и заполнение банка
	std::cout << "Round " << nRound << std::endl;
	// ставки игроков
	for (int i = 0; i < numberOfGamers; i++) {
		std::cout << "Gamer" << i + 1 << " stake is " << Stavki[nRound - 1][i]
				<< " ";
		bank.addPlayer(*Gamer[i], Stavki[nRound - 1][i], nRound - 1);
	}
	std::cout << std::endl;

	std::cout << "------------Card Pack-----------" << std::endl;
	for (int i = 0; i < 3; i++) {
		FiveCard[i] = Cards.getCard();
		std::cout << FiveCard[i].getRank() << " of " << FiveCard[i].getSuit()
				<< std::endl;
	}

	// круг торговли и заполнение банка
	std::cout << "Round " << ++nRound <<std::endl;
	// ставки игроков
	for (int i = 0; i < numberOfGamers; i++) {
		std::cout << "Gamer" << i + 1 << " stake is" << Stavki[nRound - 1][i]
				<< " ";
		bank.addPlayer(*Gamer[i], Stavki[nRound - 1][i], nRound - 1);
	}
	std::cout << std::endl;

	std::cout << "------------Card Pack-----------" << std::endl;
	FiveCard[3] = Cards.getCard();
	for (int i = 0; i < 4; i++) {
		std::cout << FiveCard[i].getRank() << " of " << FiveCard[i].getSuit()
				<< std::endl;
	}

	// круг торговли и заполнение банка
	std::cout << "Round " << ++nRound << std::endl;;
	// ставки игроков
	for (int i = 0; i < numberOfGamers; i++) {
		std::cout << "Gamer" << i + 1 << " stake is " << Stavki[nRound - 1][i]
				<< " ";
		bank.addPlayer(*Gamer[i], Stavki[nRound - 1][i], nRound - 1);
	}
	std::cout << std::endl;

	std::cout << "------------Card Pack-----------" << std::endl;
	FiveCard[4] = Cards.getCard();
	for (int i = 0; i < 5; i++) {
		std::cout << FiveCard[i].getRank() << " of " << FiveCard[i].getSuit()
				<< std::endl;
	}

	// последний круг торговли и заполнение банка
	std::cout << "Round " << ++nRound << std::endl;
	// ставки игроков
	for (int i = 0; i < numberOfGamers; i++) {
		std::cout << "Gamer" << i + 1 << " stake is" << Stavki[nRound - 1][i]
				<< " ";
		bank.addPlayer(*Gamer[i], Stavki[nRound - 1][i], nRound - 1);
	}
	std::cout << std::endl;

	Calculation counting(Gamer, FiveCard, 6);
	counting.WinnersCalc();
	for (int i = 0; i < 6; i++) {
		std::cout << Gamer[i][0].getLogin() << " is in "
				<< Gamer[i][0].getWinPlace() << " place " << " has "
				<< counting.GetCombinationName(Gamer[i]) << std::endl;
	}
	// раздача денег
	bank.winners();

	std::cout << std::endl;
	for (int i = 0; i < numberOfGamers; i++) {
		std::cout << "Position table: " << Gamer[i]->getPosition() << " "<<Gamer[i]->getLogin()<<" ";
		std::cout << Gamer[i]->getPurse() << "$"<<std::endl;
	}
	std::cout << "SumBank: " << bank.getSumBank() << std::endl;

	for (int i = 0; i < 6; i++) {
		delete[] Gamer[i];
	}
	delete[] Gamer;
	return 0;
}
std::string from_int(int number) {
	std::stringstream out;
	out << number;
	return out.str();
}

void createSetOfStakes(int** Stakes, int numberOfRounds, int numberOfGamers) {

	srand(time(NULL));
	for (int i=0; i<numberOfRounds;i++)
	{
		for (int j=0;j<numberOfGamers;j++)
		{
			Stakes[i][j]=rand()%7;

		}


	}

}

