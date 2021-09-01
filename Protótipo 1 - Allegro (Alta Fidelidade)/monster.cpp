#include "monster.h"

Monster GetMonsterFromID(int monster_id)
{
    Monster monster;

    if(monster_id == 1)
    {
        monster.id = 1;
        monster.picture = monster1_image;
        monster.portrait = portrait1_image;
        strcpy(monster.name, "SANDSLASH");
        monster.gametype = EARTH;
        monster.hp = 220;
        monster.attack = 205;
        monster.defense = 140;
        monster.speed = 165;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 2)
    {
        monster.id = 2;
        monster.picture = monster2_image;
        monster.portrait = portrait2_image;
        strcpy(monster.name, "GEODUDE");
        monster.gametype = EARTH;
        monster.hp = 270;
        monster.attack = 135;
        monster.defense = 200;
        monster.speed = 95;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 3)
    {
        monster.id = 3;
        monster.picture = monster3_image;
        monster.portrait = portrait3_image;
        strcpy(monster.name, "GYARADOS");
        monster.gametype = OCEAN;
        monster.hp = 240;
        monster.attack = 185;
        monster.defense = 170;
        monster.speed = 175;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 4)
    {
        monster.id = 4;
        monster.picture = monster4_image;
        monster.portrait = portrait4_image;
        strcpy(monster.name, "LAPRAS");
        monster.gametype = OCEAN;
        monster.hp = 270;
        monster.attack = 150;
        monster.defense = 170;
        monster.speed = 110;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 5)
    {
        monster.id = 5;
        monster.picture = monster5_image;
        monster.portrait = portrait5_image;
        strcpy(monster.name, "AERODACTYL");
        monster.gametype = SKY;
        monster.hp = 240;
        monster.attack = 180;
        monster.defense = 120;
        monster.speed = 205;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 6)
    {
        monster.id = 6;
        monster.picture = monster6_image;
        monster.portrait = portrait6_image;
        strcpy(monster.name, "PIDGEOT");
        monster.gametype = SKY;
        monster.hp = 245;
        monster.attack = 150;
        monster.defense = 150;
        monster.speed = 195;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 7)
    {
        monster.id = 7;
        monster.picture = monster7_image;
        monster.portrait = portrait7_image;
        strcpy(monster.name, "PRIMEAPE");
        monster.gametype = NATURE;
        monster.hp = 235;
        monster.attack = 180;
        monster.defense = 170;
        monster.speed = 170;
        monster.current_hp = monster.hp;
    }

    else if(monster_id == 8)
    {
        monster.id = 8;
        monster.picture = monster8_image;
        monster.portrait = portrait8_image;
        strcpy(monster.name, "ABSOL");
        monster.gametype = NATURE;
        monster.hp = 245;
        monster.attack = 175;
        monster.defense = 145;
        monster.speed = 185;
        monster.current_hp = monster.hp;
    }

    return monster;
}
