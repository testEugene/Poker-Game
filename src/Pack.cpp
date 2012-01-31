/*
 * Pack.cpp
 *
 *  Created on: 18.11.2011
 *      Author: eugene
 */

#include "Pack.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
Pack::Pack(int c) {
	size = 52;
	int k=0;
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j < 15; j++) {
			Card tempCard(i,j);
			Cards[k]=tempCard;
			k++;
		}

	}
	std::srand(std::time(NULL));
	std::random_shuffle(&Cards[0], &Cards[52]);
	// TODO Auto-generated constructor stub

}

Pack::~Pack() {

}
void Pack::RefreshPack() {
	size = 52;
	std::random_shuffle(&Cards[0], &Cards[52]);

}

Card Pack::getCard() {
	//if (size>0)
	try
	{
	size--;
	if (size<0)
	throw std::logic_error("There is no cards in pack");
	}
	catch (int size)
	{}
	return Cards[size];
}
