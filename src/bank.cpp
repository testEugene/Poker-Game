/*
 * bank.cpp
 *
 *  Created on: 09.12.2011
 *      Author: bot
 */
#include <iostream>
using namespace std;
#include "bank.h"
Bank::Bank(Player **g, int k)
{
	sum_bank = 0;
	round = 0;
	kol = k;
	gamer = g;
}
void Bank::addPlayer(Player & p, int st, int r, bool allin)
{
	round = r;
	if (p.getCurrrentStavka(round) == 0 && st > 0)
		p.setCurrrentStavka(st, round);
	else if (p.getCurrrentStavka(round) > 0 && st > 0)
		p.setCurrrentStavka(p.getCurrrentStavka(round) + st, round);
	p.setPurse(p.getPurse() - st);
	sum_bank += st;
}
void Bank::winners()
{
	for(int i = 0; i <= round; round--)         // обработка играков в раунде
	{
		setWinKol(round);
		cout << "round" << round + 1 << "\t";
		for (int i = 0; i < kol; i++)           // обработка каждого игрока с проверкой на нулев. ставку
		{
			cout << gamer[i]->getWinPlace() << " ";
			cout << "b" << gamer[i]->getPurse() << " ";
			if (gamer[i]->getCurrrentStavka(round) != 0)// если нет ставки в данном раунде
			{                                    		// игрок не обрбатывается дальше
				int tmpVremenSum = 0;                   // временная сумма денег победителя
				int tmpPlace = getWinPlaceRound();      // определение максимального места
														// за пъедесталом в раунде
				cout << tmpPlace << " ";
				int tmpMinStavka = minStavkaRound(tmpPlace);// определение победителя с минимальной ставкой
				cout << tmpMinStavka << " ";
				for (int j = 0; j < kol; j++)  // проход по каждому игроку заполняя кошелек победителей
				{
					if (gamer[j]->getCurrrentStavka(round) < tmpMinStavka)// если у игрока ставка меньше минимальной
					{
						sum_bank -= gamer[j]->getCurrrentStavka(round);
						tmpVremenSum += gamer[j]->getCurrrentStavka(round);
						gamer[j]->setCurrrentStavka(0, round);
					}
					else
					{
						int s = gamer[j]->getCurrrentStavka(round);
						s -= tmpMinStavka;
						sum_bank -= tmpMinStavka;
						tmpVremenSum += tmpMinStavka;
						gamer[j]->setCurrrentStavka(s, round);
					}
					cout << tmpVremenSum << "|";
				}
				raspredMoney(tmpVremenSum, tmpPlace);
				cout << gamer[i]->getPurse() << "  ";
				winKol[tmpPlace] -= 1;
				if (gamer[i]->getCurrrentStavka(round) == 0)
					gamer[i]->setIsAllin(true);
			}
		}
	cout << endl;
	}
}
void Bank::setWinKol(int r)
{
	int i;
 	int tmpPlace;
 	cout << kol;
 	for (i = 0; i < 7; i++)
 		winKol[i] = 0;
	for (i = 0; i < kol; i++)
	{
		if(gamer[i]->getCurrrentStavka(r) != 0)
		{
			gamer[i]->setIsAllin(false);// если игрок не пошел вобанк true
			tmpPlace = gamer[i]->getWinPlace();
			winKol[tmpPlace] += 1;
		}
	}
	for (i = 0; i < 7; i++)
		{
			cout << winKol[i] << endl;
		}
}
int Bank::getWinPlaceRound()
{
 	int tmpPlace = 100;
 	int i;
 	for (i = 0; i < kol; i++)
 	{
	 	if (gamer[i]->getWinPlace() < tmpPlace && gamer[i]->getCurrrentStavka(round) != 0)
	 	tmpPlace = gamer[i]->getWinPlace();
    }
    return tmpPlace;
}
int Bank::minStavkaRound(int p)// определение минимальной ставки в раунде
{
 	int tmpMinStavka = 100000;
 	for (int i = 0; i < kol; i++)
 	{
	 	if ((gamer[i]->getWinPlace() == p)
	 		&& (gamer[i]->getCurrrentStavka(round)) < tmpMinStavka
	 		&& (gamer[i]->getCurrrentStavka(round)) != 0)
	 		tmpMinStavka = gamer[i]->getCurrrentStavka(round);
	}
	return tmpMinStavka;
}
void Bank::raspredMoney(int vr, int p)// распределение денег в раунде
{
 	 for (int i = 0; i < kol; i++)
 	 {
	  	 if (gamer[i]->getWinPlace() == p && !gamer[i]->getIsAllin())
	  	 {
	  		 int v = vr / winKol[p] + gamer[i]->getPurse();
	  		 double d = vr;
	  		 double ost = d / winKol[p] + gamer[i]->getOstatok();
	  		 long int vv = ost;
	  		 if(vv)
	  		 {
	  			 v += vv;
	  			 ost -= vv;
	  		 }
	  		 gamer[i]->setPurse(v, ost);
	  	 }
	 }
}
