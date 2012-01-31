#ifndef CALCULATION_H
#define CALCULATION_H

#include "CombinationNames.h"
#include "player.h"
#include "CardEnumsAndCardStruct.h"
#include "Card.h"

class Calculation {
public:
	Calculation(Player **players, Card overall[5], int players_count);//вычисление комбинаций игроков
	void WinnersCalc();
	std::string GetCombinationName(Player *player);
	///Card *GetCombinationCards(Player *player);
	virtual ~Calculation();

private:
	int players_count;
	Player **players;
	struct_card overall[5];
	combinationName *combinationNamesOfPlayers;//комбинации игроков, связка комбинаций с игроками по индексу
	struct_card **combinations;//комбинации карт игроков (комбинация  - это 5 карт из совокупности 5-и карт со стола и 2-х своих)


	combinationName getCardsCombinationPlayer(int player_index);//определение названия комбинации и самой комбинации карт игрока
	//функции составляющие (если возможно) из семерки карт комбинации
	bool isHigh_card(struct_card _7cards[7], int player_index);
	bool isPairs(struct_card _7cards[7], int player_index);
	bool isTwo_pairs(struct_card _7cards[7], int player_index);
	bool isSet(struct_card _7cards[7], int player_index);
	bool isStraight(struct_card _7cards[7], int player_index);
	bool isFlush(struct_card _7cards[7], int player_index);
	bool isFull_house(struct_card _7cards[7], int player_index);
	bool isQuads(struct_card _7cards[7], int player_index);
	bool isStraight_flush(struct_card _7cards[7], int player_index);
	bool isRoyal_flush(struct_card _7cards[7], int player_index);
	void completeUntil5(struct_card _7cards[7], int player_index,
			int card_index);
	void swap(int player_index, int card_index1, int card_index2);

	//если несколько игроков имеют одинаковые комбинация, для определения победителя вмешиваются следующие функции
	inline void high_card(int winners[], int &winners_count);
	inline void pairs(int winners[], int &winners_count);
	inline void two_pairs(int winners[], int &winners_count);
	inline void set(int winners[], int &winners_count);
	inline void straight(int winners[], int &winners_count);
	inline void flush(int winners[], int &winners_count);
	inline void full_house(int winners[], int &winners_count);
	inline void quads(int winners[], int &winners_count);
	inline void straight_flush(int winners[], int &winners_count);
	bool cardIn7cards(struct_card _7cards[7], struct_card card);//true-если в 7ке карт есть такая карта
	inline void deleteWinnersWithSmallCards(int winners[], int&winners_count,
			int card_index);//удаление игроков с младшей картой
	void deleteWinner(int winners[], int &winners_count, int index);//удаление индетификатора игрока из списка победителей
};
#endif // CALCULATION_H
