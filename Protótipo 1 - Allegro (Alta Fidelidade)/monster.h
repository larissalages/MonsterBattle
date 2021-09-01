#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "init.h"
#include "gametype.h"

class Monster
{
    public:
        int id;

        BITMAP* picture;
        BITMAP* portrait;
        char name[50];

        int gametype;
        int hp;
        int attack;
        int defense;
        int speed;

        int current_hp;

        Monster() { picture = NULL; }
        float GetHPPercentage() { return ((float) current_hp) / ((float) hp); }
};

Monster GetMonsterFromID(int monster_id);

#endif
