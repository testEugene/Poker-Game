/*
 * Card.cpp
 *
 *  Created on: 18.11.2011
 *      Author: eugene
 */

#include "Card.h"
int findPosition(std::string);
Card::Card(int s, int v) {
	try {
		suitId = s;
		rankId = v;
		if ((suitId > 3) || (suitId < 0))
			throw std::logic_error("Wrong suitId it's not in 0..3");
		if ((rankId > 14) || (rankId < 2))
			throw std::logic_error("Wrong rankId it's not in 2..14");
	} catch (int suitId) {
	} catch (int rankId) {
	}
	switch (suitId) {
	case 0:
		suit = "spades";
		break;
	case 1:
		suit = "clubs";
		break;
	case 2:
		suit = "diamond";
		break;
	case 3:
		suit = "hearts";
		break;
	}
	std::string value[] = { "two", "three", "four", "five", "six", "seven",
			"eight", "nine", "ten", "jack", "queen", "king", "ace" };
	rank = value[rankId - 2];

}
std::string Card::getSuit() {
	return suit;

}
Card::Card() {
}
std::string Card::getRank() {

	return rank;
}
int Card::getRankId() {
	return rankId;
}
int Card::getSuitId() {
	return suitId;

}

bool operator==(const Card& left, const Card& right) {
	if (left.rankId == right.rankId)
		return true;
	else
		return false;
}
bool operator>(const Card& left, const Card& right) {
	if (left.rankId > right.rankId)
		return true;
	else
		return false;
}
bool operator>=(const Card& left, const Card& right) {
	if (left.rankId >= right.rankId)
		return true;
	else
		return false;
}

bool operator<(const Card& left, const Card& right) {
	if (left.rankId < right.rankId)
		return true;
	else
		return false;
}
bool operator<=(const Card& left, const Card& right) {
	if (left.rankId <= right.rankId)
		return true;
	else
		return false;
}

Card& Card::operator=(Card right) {
	rank = right.rank;
	rankId = right.rankId;
	suit = right.suit;
	suitId = right.suitId;
	return *this;
}
Card::~Card() {
	// TODO Auto-generated destructor stub
}
