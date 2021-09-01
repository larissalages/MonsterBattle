#include "gametype.h"

float TypeMultiplier(int type_atk, int type_def)
{
    if(type_atk == EARTH)
    {
        if(type_def == OCEAN)
            return TYPE_ADVANTAGE_MULTIPLIER;
        else if(type_def == SKY)
            return TYPE_DISADVANTAGE_MULTIPLIER;
        else
            return TYPE_NEUTRAL_MULTIPLIER;
    }

    else if(type_atk == OCEAN)
    {
        if(type_def == SKY)
            return TYPE_ADVANTAGE_MULTIPLIER;
        else if(type_def == EARTH)
            return TYPE_DISADVANTAGE_MULTIPLIER;
        else
            return TYPE_NEUTRAL_MULTIPLIER;
    }

    else if(type_atk == SKY)
    {
        if(type_def == EARTH)
            return TYPE_ADVANTAGE_MULTIPLIER;
        else if(type_def == OCEAN)
            return TYPE_DISADVANTAGE_MULTIPLIER;
        else
            return TYPE_NEUTRAL_MULTIPLIER;
    }

    else
        return TYPE_NEUTRAL_MULTIPLIER;
}

bool FloatEq(float a, float b)
{
    static float dif = 0.0001;
    if(a > b-dif && a < b+dif)
        return true;
    return false;
}
