#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "init.h"
#include "gametype.h"

#define NUM_CARDS 9

extern int cooldown_values1[NUM_CARDS];
extern int cooldown_values2[NUM_CARDS];

class Card
{
    public:
        int id;
        int gametype;
        int power;
        int accuracy;
        int cooldown;
        char name[50];
};

Card GetCardFromID(int card_id);
void ApplyCooldown();

#endif
