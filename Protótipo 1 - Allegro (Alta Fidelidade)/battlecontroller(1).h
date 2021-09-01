#ifndef BATTLECONTROLLER_H_INCLUDED
#define BATTLECONTROLLER_H_INCLUDED

#include "init.h"
#include "card.h"
#include "monster.h"
#include "battlelog.h"
#include "gametype.h"

#define TEAM_SIZE 3

#define POS_RADIUS 70
#define P1_POS_DEFENSIVE_CENTER 150
#define P1_POS_NEUTRAL_CENTER 320
#define P1_POS_OFENSIVE_CENTER 490
#define P2_POS_DEFENSIVE_CENTER 780
#define P2_POS_NEUTRAL_CENTER 950
#define P2_POS_OFENSIVE_CENTER 1120

#define ENABLE_CARD_ACCURACY 1

enum BATTLESTATES
{
    START_GAME,
    TURN_CHOOSE_ACTION,
    TURN_EXECUTE_ACTION,
    P1_WINS,
    P2_WINS
};

enum FIELDPOSITIONS
{
    POSITION_DEFENSIVE,
    POSITION_NEUTRAL,
    POSITION_OFFENSIVE
};

class Battlecontroller
{
    private:
        int field_position1;
        int field_position2;
        Card selected_card1;
        Card selected_card2;
        Monster monsters1[TEAM_SIZE];
        Monster monsters2[TEAM_SIZE];
        Monster* current_monster1;
        Monster* current_monster2;

        int battle_state;
        Battlelog log;

        int red_trans;
        int red_trans_var;
        int red_trans_var_speed;

        int blue_trans;
        int blue_trans_var;
        int blue_trans_var_speed;

        int animation_state;
        int animation_x;

    public:
        Battlecontroller();

        void P1ChooseMonster();
        void P2ChooseMonster();
        void P1ChooseCard();
        void P2ChooseCard();
        void P1ExecuteAttack();
        void P2ExecuteAttack();

        void AttackAnimation(int damage, Monster* monster);

        bool P1HasMonstersLeft();
        bool P2HasMonstersLeft();
        bool IsMonsterOnTeam(Monster team[TEAM_SIZE], int monster_id);
        bool IsMonsterAlive(Monster team[TEAM_SIZE], int monster_id);
        int TeamSlotsLeft(Monster team[TEAM_SIZE]);

        void Update();
        void Draw();

        int GetWinner();
};

#endif
