#ifndef COMBINATIONNAMES_H
#define COMBINATIONNAMES_H

enum combinationName
{
    HIGH_CARD,       //старшая карта
    PAIRS,            //пара
    TWO_PAIRS,        //2 пары
    SET,              //тройка
    STRAIGHT,         //стрит, пять по порядку идущих карт
    FLUSH,            //пять карт одной масти
    FULL_HOUSE,       //3 карты одного ранга, 2 карты другого
    QUADS,            //4 карты одного ранга
    STRAIGHT_FLUSH,   //пять карт ойдной масти идущих по порядку
    ROYAL_FLUSH       //пять карт ойдной масти идущих по порядку старшей картой туз
};
#endif // COMBINATIONNAMES_H
