#ifndef GAMETYPE_H_INCLUDED
#define GAMETYPE_H_INCLUDED

#include "init.h"

#define TYPE_ADVANTAGE_MULTIPLIER 1.25
#define TYPE_DISADVANTAGE_MULTIPLIER 0.75
#define TYPE_NEUTRAL_MULTIPLIER 1.0

enum GAMETYPES { EARTH, OCEAN, SKY, NATURE };

float TypeMultiplier(int type_atk, int type_def);
bool FloatEq(float a, float b);

#endif
