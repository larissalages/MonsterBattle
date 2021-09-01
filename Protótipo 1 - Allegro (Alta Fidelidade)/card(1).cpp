#include "card.h"

int cooldown_values1[NUM_CARDS];
int cooldown_values2[NUM_CARDS];

Card GetCardFromID(int card_id)
{
    Card card;
    card.id = card_id;

    //SWAP card
    if(card_id == 0)
    {
        card.power = 0;
        card.accuracy = 0;
        card.cooldown = 0;
        strcpy(card.name, "SWAP");
    }

    else if(card_id == 1)
    {
        card.gametype = EARTH;
        card.power = 90;
        card.accuracy = 90;
        card.cooldown = 2;
        strcpy(card.name, "EARTHQUAKE");
    }

    else if(card_id == 2)
    {
        card.gametype = EARTH;
        card.power = 80;
        card.accuracy = 100;
        card.cooldown = 1;
        strcpy(card.name, "ROCK SLIDE");
    }

    else if(card_id == 3)
    {
        card.gametype = OCEAN;
        card.power = 90;
        card.accuracy = 95;
        card.cooldown = 1;
        strcpy(card.name, "SURF");
    }

    else if(card_id == 4)
    {
        card.gametype = OCEAN;
        card.power = 100;
        card.accuracy = 70;
        card.cooldown = 2;
        strcpy(card.name, "HIDRO PUMP");
    }

    else if(card_id == 5)
    {
        card.gametype = SKY;
        card.power = 90;
        card.accuracy = 100;
        card.cooldown = 3;
        strcpy(card.name, "WING ATTACK");
    }

    else if(card_id == 6)
    {
        card.gametype = SKY;
        card.power = 85;
        card.accuracy = 95;
        card.cooldown = 1;
        strcpy(card.name, "HURRICANE");
    }

    else if(card_id == 7)
    {
        card.gametype = NATURE;
        card.power = 100;
        card.accuracy = 70;
        card.cooldown = 2;
        strcpy(card.name, "HYPER BEAM");
    }

    else if(card_id == 8)
    {
        card.gametype = NATURE;
        card.power = 90;
        card.accuracy = 90;
        card.cooldown = 1;
        strcpy(card.name, "DOUBLE EDGE");
    }

    return card;
}

void ApplyCooldown()
{
    for(int i = 0; i < NUM_CARDS; i++)
    {
        cooldown_values1[i]--;

        if(cooldown_values1[i] < 0)
            cooldown_values1[i] = 0;

        cooldown_values2[i]--;

        if(cooldown_values2[i] < 0)
            cooldown_values2[i] = 0;
    }
}
