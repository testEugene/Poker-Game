#include "Calculation.h"

Calculation::Calculation(Player **players, Card overall[5], int players_count)//вычисление комбинаций игроков
{
	for (int i = 0; i < 5; i++) {
		struct_card card;
		card.rank = (enum_rank) (overall[i].getRankId());
		card.suit = (enum_suit) (overall[i].getSuitId());
		this->overall[i] = card;
	}
	this->players_count = players_count;
	this->players = players;

	combinationNamesOfPlayers = new combinationName[this->players_count];

	combinations = new struct_card*[this->players_count];//создадим массив комбинаций для игроков
	for (int i = 0; i < players_count; i++)
		combinations[i] = new struct_card[5];//комбинация - это совокупность пяти карт

	for (int i = 0; i < players_count; i++) {
		//if(players[i]->GetNowInGame())
		combinationNamesOfPlayers[i] = getCardsCombinationPlayer(i);//вычисляем комбинации(меняется combinations[][]) и имена комбинаций
	}
}

Calculation::~Calculation() {
	for (int i = 0; i < players_count; i++)
		delete[] combinations[i];//замучался удалять!

	delete[] combinations;
	delete[] combinationNamesOfPlayers;

}

void Calculation::WinnersCalc()//присваивает победителям места
{
	int raiting = 1;
	combinationName comb;
	for (comb = ROYAL_FLUSH; comb >= HIGH_CARD; comb = (combinationName) (comb
			- 1))//пройдемся по всем комбинациям
	{
		int winners[6];//индексы победителей с одинаковымыи комбинациями
		int winners_count = 0;
		for (int i = 0; i < players_count; i++)//собираем победителей с одинаковыми (неполными)комбинациями в winners
			if (combinationNamesOfPlayers[i] == comb
					&& players[i]->getInGame() && players[i]->getWinPlace()
					== 0)//поиск игроков(в игре) с одинаковыми комбинациями, не имеющих более старшие комбинации
				winners[winners_count++] = i;
		while (winners_count != 0) {
			int saveWCount = winners_count;//сохраняем  т.к остануться лишь те которые имеют равные полные комбинации
			int tempArrWinners[winners_count];//скопируем индексы игроков равных неполных комбинаций, потом остануться лишь с равными полными
			for (int i = 0; i < winners_count; i++)
				tempArrWinners[i] = winners[i];
			switch (comb)//уменьшает winners_count, оставляет в tempArrWinners только равных по (полной)комбинации (с учетом доп. карт)
			{
			case HIGH_CARD:
				high_card(tempArrWinners, winners_count);
				break; //старшая карта
			case PAIRS:
				pairs(tempArrWinners, winners_count);
				break; //пара
			case TWO_PAIRS:
				two_pairs(tempArrWinners, winners_count);
				break; //2 пары
			case SET:
				set(tempArrWinners, winners_count);
				break; //тройка
			case STRAIGHT:
				straight(tempArrWinners, winners_count);
				break; //стрит, пять по порядку идущих карт
			case FLUSH:
				flush(tempArrWinners, winners_count);
				break; //пять карт одной масти
			case FULL_HOUSE:
				full_house(tempArrWinners, winners_count);
				break; //3 карты одного ранга, 2 карты другого
			case QUADS:
				quads(tempArrWinners, winners_count);
				break; //4 карты одного ранга
			case STRAIGHT_FLUSH:
				straight_flush(tempArrWinners, winners_count);
				break; //пять карт ойдной масти идущих по порядку
				// case ROYAL_FLUSH:      //быть такого не может, что несколько игроков имели рояль-флеш одновременно
			}

			for (int i = 0; i < winners_count; i++)
				players[tempArrWinners[i]]->setWinPlace(raiting);//игрокам места
			raiting++;
			int t0 = tempArrWinners[0];
			int t2 = tempArrWinners[1];

			//удаляем индексы игроков из массива, которым  уже присвоили места
			for (int i = 0; i < winners_count; i++) //индекс игрока который уже получил место
			{
				for (int j = 0; j < saveWCount; j++)//находим его индекс в общем массиве
					if (tempArrWinners[i] == winners[j]) //индекс игрока получившего место == индекс в общем
					{
						deleteWinner(winners, saveWCount, j);
					}
			}

			winners_count = saveWCount;//сохраненное минус кол игроков кот присвоили места


		}

	} //for
}

std::string Calculation::GetCombinationName(Player *player) {
	//находим индекс игрока в массиве players, тот же индек указывает на название комбинации в массиве combinations
	int index;
	for (int i = 0; i < players_count; i++)
		if (players[i] == player)
			index = i;
	switch (combinationNamesOfPlayers[index]) {
	case HIGH_CARD:
		return std::string("high card");
	case PAIRS:
		return std::string("pairs");
	case TWO_PAIRS:
		return std::string("two pairs");
	case SET:
		return std::string("set");
	case STRAIGHT:
		return std::string("straight");
	case FLUSH:
		return std::string("flush");
	case FULL_HOUSE:
		return std::string("full house");
	case QUADS:
		return std::string("quads");
	case STRAIGHT_FLUSH:
		return std::string("straight flush");
	case ROYAL_FLUSH:
		return std::string("royal flush");
	}
	return std::string("");
}

////Card Calculation*GetCombinationCards(Player *player)


/////////////
//PRIVATE:///
/////////////

combinationName Calculation::getCardsCombinationPlayer(int player_index)//определение названия комбинации и самой комбинации карт игрока
{
	struct_card _7cards[7];//создадим семерку карт, для удобства работы

	struct_card card;
	card.rank = (enum_rank) (players[player_index]->GetFirstCard().getRankId());
	card.suit = (enum_suit) (players[player_index]->GetFirstCard().getSuitId());
	_7cards[0] = card;
	card.rank
			= (enum_rank) (players[player_index]->GetSecondCard().getRankId());
	card.suit
			= (enum_suit) (players[player_index]->GetSecondCard().getSuitId());
	_7cards[1] = card;

	for (int i = 2; i < 7; i++)
		_7cards[i] = overall[i - 2];

	if (isRoyal_flush(_7cards, player_index))
		return ROYAL_FLUSH;
	if (isStraight_flush(_7cards, player_index))
		return STRAIGHT_FLUSH;
	if (isQuads(_7cards, player_index))
		return QUADS;
	if (isFull_house(_7cards, player_index))
		return FULL_HOUSE;
	if (isFlush(_7cards, player_index))
		return FLUSH;
	if (isStraight(_7cards, player_index))
		return STRAIGHT;
	if (isSet(_7cards, player_index))
		return SET;
	if (isTwo_pairs(_7cards, player_index))
		return TWO_PAIRS;
	if (isPairs(_7cards, player_index))
		return PAIRS;
	if (isHigh_card(_7cards, player_index))
		return HIGH_CARD;
	return HIGH_CARD;
}

void Calculation::completeUntil5(struct_card _7cards[7], int player_index,
		int card_index)//используется для дополнения комбинации до 5 карт, например если 														///при паре для того, чтобы добавить еще 3 карты
{
	struct_card maxRankCard;
	while (card_index < 5) {
		for (int i = 0; i < 7; i++)//ищем одну не использованную (в неполной)комбинации карту в 7ке карт
		{
			bool is_found = true;
			int j;
			for (j = 0; j < card_index; j++)
				if (_7cards[i] == combinations[player_index][j]) {
					is_found = false;
					break;
				}//увы карта использована
			if (is_found) {
				maxRankCard = _7cards[j];
				break;
			}
		}

		for (int i = 0; i < 7; i++)//теперь находим конкретно старшую неиспользованную карту
		{
			if (_7cards[i] > maxRankCard) {
				bool is_found = true;

				for (int j = 0; j < card_index; j++)//проверка неиспользованности
					if (_7cards[i] == combinations[player_index][j]) {
						is_found = false;
						break;// for(j)
					}

				if (is_found)
					maxRankCard = _7cards[i];
			}
		}

		combinations[player_index][card_index++] = maxRankCard;//вот она неиспользованная карта записывается в комбинациюю итак до 5 ки карт
	}

}

void Calculation::swap(int player_index, int card_index1, int card_index2)//чтоб поменять местами в комбинации карты
{
	struct_card c = combinations[player_index][card_index1];
	combinations[player_index][card_index1]
			= combinations[player_index][card_index2];
	combinations[player_index][card_index2] = c;
}

bool Calculation::isHigh_card(struct_card _7cards[7], int player_index)//true - комбинация есть просто старшая карта
{
	int card_index = 2;//будет передаваться в completeUntil5
	if (_7cards[1] > _7cards[0])//запишем в комбинацию как первые 2 карты, 1ую и 2ую карту игрока по возрастанию
	{
		combinations[player_index][0] = _7cards[0];
		combinations[player_index][1] = _7cards[1];
	} else {
		combinations[player_index][0] = _7cards[1];
		combinations[player_index][1] = _7cards[0];
	}
	/* 2 3 4  */
	completeUntil5(_7cards, player_index, card_index);//дополним комбинацию до 5ти карт

	return true;
}

bool Calculation::isPairs(struct_card _7cards[7], int player_index)//true- комбинация есть "пара"
{
	int index;//индекс карты в комбинации
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1))// ищем ля каждого ранга
	{
		index = 0;
		for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))//все масти
			if (cardIn7cards(_7cards, struct_card(r, s)))//r,s//если карта есть в 7ке карт
				combinations[player_index][index++] = struct_card(r, s);//то запишем его в комбинацию

		if (index == 2)
			break;// значит мы нашли пару

	}

	if (index != 2)
		return false;
	/* 3 4 5*/
	completeUntil5(_7cards, player_index, index);//добавим из 7ки еще 3 карты
	swap(player_index, 2, 4); //после добавления 3-х карт(по убыванию) окажется что 3ья больше пятой, их меняем местами
	return true;
}

bool Calculation::isTwo_pairs(struct_card _7cards[7], int player_index)//true-2пары
{
	int index;//=3 начнем добавление сверху вниз с 4 ой карты
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1)) {
		index = 3;//ищем в другом ранге
		for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))
			if (cardIn7cards(_7cards, struct_card(r, s)))//r,s
				combinations[player_index][index--] = struct_card(r, s);

		if (index == 1)//нашли пару карт
			break;
	}

	if (index != 1)
		return false;
	//теперь ищем младшую пару
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1)) {
		if (r == combinations[player_index][2].rank)
			continue;//карты этого ранга уже использованы
		index = 1; //конец массива комбинации продолжим поиск
		for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))
			if (cardIn7cards(_7cards, struct_card(r, s)))//r,s
				combinations[player_index][index--] = struct_card(r, s);

		if (index == -1)
			break;

	}

	if (index != -1)
		return false;

	/*if(combinations[player_index][0]>combinations[player_index][2])
	 {
	 swap(combination,0,2);
	 swap(combination,1,3);
	 }*/

	completeUntil5(_7cards, player_index, 4);
	return true;
}

bool Calculation::isSet(struct_card _7cards[7], int player_index) {
	int index = 0;
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1))//также поиск начинается с больших карт
	{
		for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))
			if (cardIn7cards(_7cards, struct_card(r, s)))//r,s
				combinations[player_index][index++] = struct_card(r, s);

		if (index == 3)
			break;
		index = 0;//"стираем" заново, но ранк--
	}

	if (index != 3)
		return false;//если в списке комбинаций нет трех карт то эта комбинация

	//тройка определена теперь дополним 5ые и 4ые карты
	completeUntil5(_7cards, player_index, index);
	swap(player_index, 3, 4);//так как нужно положить по возрастанию
	return true;
}

bool Calculation::isStraight(struct_card _7cards[7], int player_index) {
	int index;//=4 заполнения комбинации сверху вниз
	for (int i = 0; i < 7; i++)//попробуем найти стрит, положив, что старшая в стрите карта есть  i-ая карта в семёрке
	{
		index = 4;
		for (enum_rank r = _7cards[i].rank; r >= TWO; r = (enum_rank) (r - 1)) {
			if (index == -1)
				break;//достаточно карт для стрита

			if (cardIn7cards(_7cards, struct_card(r, SPADES))) {
				combinations[player_index][index--] = struct_card(r, SPADES);
				continue;
			}//continue - одной карты этого ранга хватит
			if (cardIn7cards(_7cards, struct_card(r, CLUBS))) {
				combinations[player_index][index--] = struct_card(r, CLUBS);
				continue;
			}
			if (cardIn7cards(_7cards, struct_card(r, DIAMONDS))) {
				combinations[player_index][index--] = struct_card(r, DIAMONDS);
				continue;
			}
			if (cardIn7cards(_7cards, struct_card(r, HEARTS))) {
				combinations[player_index][index--] = struct_card(r, HEARTS);
				continue;
			} //значения

			index = 4;//карта не найдена попробуем найти стрит, положив, что старшая в стрите карта есть  следующая карта в семерке
			break;

		}
		if (index == -1)
			return true;
	}
	return false;
}

bool Calculation::isFlush(struct_card _7cards[7], int player_index) {
	int index;//=4начнем с конца
	for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))//ищем флеш для всех мастей
	{
		index = 4;//начнем заполнение с конца массива
		for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1)) {
			if (cardIn7cards(_7cards, struct_card(r, s)))//если в семерке есть таккая карта
			{
				combinations[player_index][index--] = struct_card(r, s);
				if (index == -1)
					break;//хватит=) карт
			}
		}
		if (index == -1)
			break;//если найдены все карты одной масти
	}

	if (index == -1)
		return true;
	return false;
}

bool Calculation::isFull_house(struct_card _7cards[7], int player_index) {
	int index = 0;
	//станчала ищем 3 карты одного ранга
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1)) {
		index = 0;
		for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))
			if (cardIn7cards(_7cards, struct_card(r, s)))//r,s
				combinations[player_index][index++] = struct_card(r, s);
		if (index == 3)
			break;
	}

	if (index != 3)
		return false;//увы не нашли 3 карты

	//нашли 3 карты а теперь еще нужны 2 (одного ранга)
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1)) {
		if (r == combinations[player_index][0].rank)
			continue;//карты ранга r уже использованы
		index = 3;
		for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))
			if (cardIn7cards(_7cards, struct_card(r, s)) && index != 5)//если карта найдена и она не лишьняя
				combinations[player_index][index++] = struct_card(r, s);
		if (index == 5)
			break;
	}

	if (index == 5)//вот они 5 карт
	{
		if (combinations[player_index][0] > combinations[player_index][4])//возможно надо переставлять по возрастанию
		{
			swap(player_index, 0, 4);
			swap(player_index, 1, 3);
		}
		return true;
	} else
		return false;
}

bool Calculation::isQuads(struct_card _7cards[7], int player_index) {
	int index = 0;
	for (enum_rank r = ACE; r >= TWO; r = (enum_rank) (r - 1))
		if (index != 4) {
			index = 0;
			for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))
				if (cardIn7cards(_7cards, struct_card(r, s)))//r,s
					combinations[player_index][index++] = struct_card(r, s);
		} else
			break;
	if (index != 4)
		return false;//не нашли 4-ку
	completeUntil5(_7cards, player_index, index);//дополним пятой картой
	return true;

}

bool Calculation::isStraight_flush(struct_card _7cards[7], int player_index) {
	//проверка на стрит-флеш
	int index = 4;

	for (int i = 0; i < 7; i++)//для всех 7ми карт семерки
	{
		index = 4;
		for (enum_rank r = _7cards[i].rank; r >= TWO; r = (enum_rank) (r - 1))//положив что каждая карта 7 ки старшая в стрите,ищем более меньших
		{
			if (index == -1)
				break;
			struct_card card;
			card.rank = r;
			card.suit = _7cards[i].suit;
			//if (r2==15) card.rank=TWO;
			if (cardIn7cards(_7cards, card))
				combinations[player_index][index--] = card;
			else {
				index = 4;
				break;
			}
		}
		if (index == -1)
			return true;
	}

	return false;
}

bool Calculation::isRoyal_flush(struct_card _7cards[7], int player_index) {
	//Проверка на рояль-флеш
	int index = 4;
	for (enum_suit s = SPADES; s <= HEARTS; s = (enum_suit) (s + 1))//проверка для всех  мастей
		if (index == -1)
			break; //рояль найден
		else
			for (enum_rank r = ACE; r >= TEN; r = (enum_rank) (r - 1))//начнем с туза закомчим в десятке
			{
				struct_card card;
				card.rank = r;
				card.suit = s;
				if (cardIn7cards(_7cards, card))
					combinations[player_index][index--] = card;
				else {
					index = 4;//конец массива комбинации
					break;//4 выхода по break - комбинация не рояль
				}
			}
	if (index == -1)
		return true;
	return false;
}

bool Calculation::cardIn7cards(struct_card _7cards[7], struct_card card)//true-если в 7ке карт есть такая карта
{
	for (int i = 0; i < 7; i++)
		if (_7cards[i] == card)
			return true;
	return false;
}
inline void Calculation::high_card(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 1);//
	if (winners_count > 1) {
		deleteWinnersWithSmallCards(winners, winners_count, 0);
	}
	for (int i = 4; i >= 2; i--)
		if (winners_count > 1) {
			deleteWinnersWithSmallCards(winners, winners_count, i);
		}
}

inline void Calculation::pairs(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 0);
	for (int i = 4; i >= 2; i--)
		if (winners_count > 1) {
			deleteWinnersWithSmallCards(winners, winners_count, i);
		}

}

inline void Calculation::two_pairs(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 2);
	if (winners_count > 1) {
		deleteWinnersWithSmallCards(winners, winners_count, 0);
	}
	if (winners_count > 1) {
		deleteWinnersWithSmallCards(winners, winners_count, 4);
	}
}
inline void Calculation::set(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 2);
	if (winners_count > 1) {
		deleteWinnersWithSmallCards(winners, winners_count, 4);
	}
	if (winners_count > 1) {
		deleteWinnersWithSmallCards(winners, winners_count, 3);
	}
}

inline void Calculation::straight(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 4);
}

inline void Calculation::flush(int winners[], int &winners_count) {
	for (int i = 4; i >= 0; i--)
		if (winners_count > 1) {
			deleteWinnersWithSmallCards(winners, winners_count, i);
		} else
			break;
}

inline void Calculation::full_house(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 4);
	if (winners_count > 1)
		deleteWinnersWithSmallCards(winners, winners_count, 0);
	if (winners_count > 1)
		deleteWinnersWithSmallCards(winners, winners_count, 2);

}

inline void Calculation::quads(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 0);

}

inline void Calculation::straight_flush(int winners[], int &winners_count) {
	deleteWinnersWithSmallCards(winners, winners_count, 4);
}

void Calculation::deleteWinnersWithSmallCards(int winners[], int&winners_count,
		int card_index) {
	enum_rank max_rank = combinations[winners[0]][card_index].rank;
	//проверка страших карт
	//поиск набольшего рангом
	for (int i = 1; i < winners_count; i++)
		if (combinations[winners[i]][card_index].rank > max_rank)
			max_rank = combinations[winners[i]][card_index].rank;
	//удаление из списка игроков не имеющих  макс ранг старшей
	for (int i = 0; i < winners_count; i++)//Будь осторожен winners_count меняется !!!!!!!!!!!
		if (combinations[winners[i]][card_index].rank != max_rank)
			deleteWinner(winners, winners_count, i);
}

void Calculation::deleteWinner(int winners[], int &winners_count, int index)//удаление индетификатора игрока из списка победителей
{
	for (int i = index; i < winners_count - 1; i++)
		winners[i] = winners[i + 1];
	winners_count--;
}
