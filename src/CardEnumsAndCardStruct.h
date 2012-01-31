#ifndef EnumsAndStructsH
#define EnumsAndStructsH
enum enum_suit//масти
{
        SPADES,   //пики
        CLUBS,    //крести
        DIAMONDS, //бубны
        HEARTS    //червы
};

enum enum_rank//достоинства карт
{
        TWO=2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        DAMA,
        KING,
        ACE
};


struct struct_card//структура c++
{
        enum_rank rank;
        enum_suit suit;
        struct_card(){};
        struct_card(enum_rank r, enum_suit s)
        {rank=r; suit=s;}
        friend bool operator==(const struct_card&a, const struct_card&b){return a.rank==b.rank&&a.suit==b.suit;}
        friend bool operator!=(const struct_card&a, const struct_card&b){return !(a.rank==b.rank&&a.suit==b.suit);}
        friend bool operator>(const struct_card&a, const struct_card&b){return a.rank>b.rank;}
        friend bool operator<(const struct_card&a, const struct_card&b){return a.rank<b.rank;}


};
#endif
