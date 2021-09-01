#include "battlescreen.h"

void ExecuteAttack(Card* card, Monster* monster_atk, Monster* monster_def, int attack_field_pos, int defense_field_pos)
{
    double atk_multiplier;
    if(attack_field_pos == POSITION_DEFENSIVE)
        atk_multiplier = 0.9;
    else if(attack_field_pos == POSITION_NEUTRAL)
        atk_multiplier = 1.0;
    else if(attack_field_pos == POSITION_OFFENSIVE)
        atk_multiplier = 1.1;

    double def_multiplier;
    if(defense_field_pos == POSITION_DEFENSIVE)
        def_multiplier = 1.1;
    else if(defense_field_pos == POSITION_NEUTRAL)
        def_multiplier = 1.0;
    else if(defense_field_pos == POSITION_OFFENSIVE)
        def_multiplier = 0.9;

    int damage = (0.84*((monster_atk->attack*atk_multiplier)/(double)(monster_def->defense*def_multiplier))*(card->power) + 2)*TypeMultiplier(card->gametype, monster_def->gametype);

    monster_def->current_hp -= damage;
    if(monster_def->current_hp < 0)
        monster_def->current_hp = 0;
}

void Player1Choose(int* battle_state, Player* player1, Player* player2, Battlelog* battlelog)
{
    int card_id = -1; //id da carta escolhida

    //Se apertou algum botao de escolher carta
    if(Pressed(KEY_0)) //carta de troca
        card_id = 0;
    else if(Pressed(KEY_1))
        card_id = 1;
    else if(Pressed(KEY_2))
        card_id = 2;
    else if(Pressed(KEY_3))
        card_id = 3;
    else if(Pressed(KEY_4))
        card_id = 4;
    else if(Pressed(KEY_5))
        card_id = 5;
    else if(Pressed(KEY_6))
        card_id = 6;
    else if(Pressed(KEY_7))
        card_id = 7;
    else if(Pressed(KEY_8))
        card_id = 8;
    else if(Pressed(KEY_9))
        card_id = 9;

    //se escolheu alguma carta
    if(card_id != -1)
    {
        //Se é carta de troca
        if(card_id == 0)
        {
            player1->turn_action = ACTION_SWAP;
            *battle_state = PLAYER2_CHOOSE;
        }

        //Se é carta de ataque
        else
        {
            Card* card = GetCardFromID(card_id);

            //Se o jogador pode usar a carta
            if(card->gametype == NATURE || card->gametype == player1->GetCurrentMonster()->gametype)
            {
                player1->card = card;
                *battle_state = PLAYER2_CHOOSE;
            }

            //carta ilegal
            else
            {
                battlelog->PushMessage("This card cannot be used by this monster.");
            }
        }
    }

    //Ajusta a cor do campo pra efeito
    static int red_trans = 200;
    static int red_variation_speed = 3;
    static int red_variation = red_variation_speed;

    red_trans += red_variation;

    if(red_trans <= 80)
    {
        red_variation = red_variation_speed;
        red_trans = 81;
    }

    else if(red_trans >= 255)
    {
        red_variation = -red_variation_speed;
        red_trans = 255;
    }

    rectfill(buffer, 0, 0, SCREEN_W/2, SCREEN_H, makecol(red_trans, 0, 0));
    rectfill(buffer, SCREEN_W/2, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 200));
}

void Player1Execute(int* battle_state, Player* player1, Player* player2, Battlelog* battlelog)
{
    //UPDATE

    //Ação de troca
    if(player1->turn_action == ACTION_SWAP)
    {
        int monster_id = -1; //id do monstro escolhido

        //Se apertou algum botao de escolher monstro
        if(Pressed(KEY_1))
            monster_id = 1;
        else if(Pressed(KEY_2))
            monster_id = 2;
        else if(Pressed(KEY_3))
            monster_id = 3;
        else if(Pressed(KEY_4))
            monster_id = 4;
        else if(Pressed(KEY_5))
            monster_id = 5;
        else if(Pressed(KEY_6))
            monster_id = 6;
        else if(Pressed(KEY_7))
            monster_id = 7;
        else if(Pressed(KEY_8))
            monster_id = 8;

        //Se escolheu algum monstro
        if(monster_id != -1)
        {
            //O monstro já está no time e vivo
            if(player1->MonsterIsOnTeam(monster_id))
            {
                if(player1->IsMonsterAlive(monster_id))
                {
                    player1->SetCurrentMonsterFromID(monster_id);
                    *battle_state = PLAYER2_EXECUTE;
                }
            }

            //O monstro não está no time mas há vaga para ele
            else if(player1->GetNumberOfFreeSlots() > 0)
            {
                player1->InsertNewMonster(monster_id);
                player1->SetCurrentMonsterFromID(monster_id);
                *battle_state = PLAYER2_EXECUTE;
            }

            //O monstro não está no time e não há vaga para ele
            else
            {
                char msg[] = "Monster cannot be chosen. Team full.";
                std::string message(msg);
                battlelog->PushMessage(message);
            }
        }
    }

    //Ação de ataque
    else if(player1->turn_action == ACTION_ATTACK)
    {
        ExecuteAttack(player1->card, player1->GetCurrentMonster(), player2->GetCurrentMonster(), player1->field_position, player2->field_position);

        if(player2->GetCurrentMonster()->current_hp <= 0)
        {
            player2->turn_action = ACTION_SWAP;
            *battle_state = PLAYER2_EXECUTE;
        }

        else
            *battle_state = PLAYER2_EXECUTE;
    }

    //DRAW
    rectfill(buffer, 0, 0, SCREEN_W/2, SCREEN_H, makecol(200, 0, 0));
    rectfill(buffer, SCREEN_W/2, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 200));
}

void Player2Choose(int* battle_state, Player* player1, Player* player2, Battlelog* battlelog)
{
    int card_id = -1; //id da carta escolhida

    //Se apertou algum botao de escolher carta
    if(Pressed(KEY_0)) //carta de troca
        card_id = 0;
    else if(Pressed(KEY_1))
        card_id = 1;
    else if(Pressed(KEY_2))
        card_id = 2;
    else if(Pressed(KEY_3))
        card_id = 3;
    else if(Pressed(KEY_4))
        card_id = 4;
    else if(Pressed(KEY_5))
        card_id = 5;
    else if(Pressed(KEY_6))
        card_id = 6;
    else if(Pressed(KEY_7))
        card_id = 7;
    else if(Pressed(KEY_8))
        card_id = 8;
    else if(Pressed(KEY_9))
        card_id = 9;

    //se escolheu alguma carta
    if(card_id != -1)
    {
        //Se é carta de troca
        if(card_id == 0)
        {
            player2->turn_action = ACTION_SWAP;
            *battle_state = PLAYER1_EXECUTE;
        }

        //Se é carta de ataque
        else
        {
            Card* card = GetCardFromID(card_id);

            //Se o jogador pode usar a carta
            if(card->gametype == NATURE || card->gametype == player2->GetCurrentMonster()->gametype)
            {
                player2->card = card;
                *battle_state = PLAYER1_EXECUTE;
            }

            //carta ilegal
            else
            {
                battlelog->PushMessage("This card cannot be used by this monster.");
            }
        }
    }

    //Ajusta a cor do campo pra efeito
    static int blue_trans = 200;
    static int blue_variation_speed = 3;
    static int blue_variation = blue_variation_speed;

    blue_trans += blue_variation;

    if(blue_trans <= 80)
    {
        blue_variation = blue_variation_speed;
        blue_trans = 81;
    }

    else if(blue_trans >= 255)
    {
        blue_variation = -blue_variation_speed;
        blue_trans = 255;
    }

    rectfill(buffer, 0, 0, SCREEN_W/2, SCREEN_H, makecol(200, 0, 0));
    rectfill(buffer, SCREEN_W/2, 0, SCREEN_W, SCREEN_H, makecol(0, 0, blue_trans));
}

void Player2Execute(int* battle_state, Player* player1, Player* player2, Battlelog* battlelog)
{
    //UPDATE

    //Ação de troca
    if(player2->turn_action == ACTION_SWAP)
    {
        int monster_id = -1; //id do monstro escolhido

        //Se apertou algum botao de escolher monstro
        if(Pressed(KEY_1))
            monster_id = 1;
        else if(Pressed(KEY_2))
            monster_id = 2;
        else if(Pressed(KEY_3))
            monster_id = 3;
        else if(Pressed(KEY_4))
            monster_id = 4;
        else if(Pressed(KEY_5))
            monster_id = 5;
        else if(Pressed(KEY_6))
            monster_id = 6;
        else if(Pressed(KEY_7))
            monster_id = 7;
        else if(Pressed(KEY_8))
            monster_id = 8;

        //Se escolheu algum monstro
        if(monster_id != -1)
        {
            //O monstro já está no time e vivo
            if(player2->MonsterIsOnTeam(monster_id))
            {
                if(player2->IsMonsterAlive(monster_id))
                {
                    player2->SetCurrentMonsterFromID(monster_id);
                    *battle_state = PLAYER1_CHOOSE;
                }
            }

            //O monstro não está no time mas há vaga para ele
            else if(player2->GetNumberOfFreeSlots() > 0)
            {
                player2->InsertNewMonster(monster_id);
                player2->SetCurrentMonsterFromID(monster_id);
                *battle_state = PLAYER1_CHOOSE;
            }

            //O monstro não está no time e não há vaga para ele
            else
            {
                char msg[] = "Monster cannot be chosen. Team full.";
                std::string message(msg);
                battlelog->PushMessage(message);
            }
        }
    }

    //Ação de ataque
    else if(player2->turn_action == ACTION_ATTACK)
    {
        ExecuteAttack(player2->card, player2->GetCurrentMonster(), player1->GetCurrentMonster(), player2->field_position, player1->field_position);

        if(player1->GetCurrentMonster()->current_hp <= 0)
        {
            player1->turn_action = ACTION_SWAP;
            *battle_state = PLAYER1_EXECUTE;
        }

        else
            *battle_state = PLAYER1_EXECUTE;
    }

    //DRAW
    rectfill(buffer, 0, 0, SCREEN_W/2, SCREEN_H, makecol(200, 0, 0));
    rectfill(buffer, SCREEN_W/2, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 200));
}

void Battlescreen()
{
    //---------------------
    //Variables
    bool exit_screen = false;
    int battle_state = PLAYER1_EXECUTE;
    Battlelog* battlelog = new Battlelog();
    Player* player1 = new Player();
    Player* player2 = new Player();

    //---------------------
    //Load Content
    FONT* font_impact = load_font("fonts/impact.pcx", NULL, NULL);

    BITMAP* fieldlines_image = load_bitmap("sprites/fieldlines.bmp", NULL);
    BITMAP* message_board_image = load_bitmap("sprites/message_board.bmp", NULL);
    BITMAP* lifebar_frame_image = load_bitmap("sprites/lifebar_frame.bmp", NULL);
    BITMAP* lifebar_image = load_bitmap("sprites/lifebar.bmp", NULL);
    BITMAP* monster1_image = load_bitmap("sprites/1.bmp", NULL);
    BITMAP* monster2_image = load_bitmap("sprites/2.bmp", NULL);
    BITMAP* monster3_image = load_bitmap("sprites/3.bmp", NULL);
    BITMAP* monster4_image = load_bitmap("sprites/4.bmp", NULL);
    BITMAP* monster5_image = load_bitmap("sprites/5.bmp", NULL);
    BITMAP* monster6_image = load_bitmap("sprites/6.bmp", NULL);
    BITMAP* monster7_image = load_bitmap("sprites/7.bmp", NULL);
    BITMAP* monster8_image = load_bitmap("sprites/8.bmp", NULL);

    //---------------------
    //Game Loop
    while(!exit_screen && !exit_program)
    {
        while(ticks > 0 && !exit_program)
        {
            //********************************************************************
            //UPDATE
            //********************************************************************

            //--------------------
            //Poll input
            ReceiveKeyboardInput();
            ReceiveMouseInput();

            //--------------------
            //Exit on esc
            if(Pressed(KEY_ESC))
                ExitGame();

            //--------------------
            //Battle states
            if(battle_state == PLAYER1_CHOOSE)
                Player1Choose(&battle_state, player1, player2, battlelog);
            else if(battle_state == PLAYER1_EXECUTE)
                Player1Execute(&battle_state, player1, player2, battlelog);
            else if(battle_state == PLAYER2_CHOOSE)
                Player2Choose(&battle_state, player1, player2, battlelog);
            else if(battle_state == PLAYER2_EXECUTE)
                Player2Execute(&battle_state, player1, player2, battlelog);

            //********************************************************************
            //DRAW
            //********************************************************************

            //--------------------
            //Linhas de campo
            draw_sprite(buffer, fieldlines_image, 0, 0);

            //--------------------
            //Field positions
            circlefill(buffer, P1_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
            circlefill(buffer, P1_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
            circlefill(buffer, P1_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));

            circlefill(buffer, P2_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
            circlefill(buffer, P2_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
            circlefill(buffer, P2_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));

            if(player1->field_position == POSITION_DEFENSIVE){
                circlefill(buffer, P1_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
                if(player1->GetCurrentMonster() != NULL)
                    draw_sprite(buffer, player1->GetCurrentMonster()->picture, P1_POS_DEFENSIVE_CENTER - player1->GetCurrentMonster()->picture->w/2, SCREEN_H/2 - 120);
            }
            else if(player1->field_position == POSITION_NEUTRAL){
                circlefill(buffer, P1_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
                if(player1->GetCurrentMonster() != NULL)
                    draw_sprite(buffer, player1->GetCurrentMonster()->picture, P1_POS_NEUTRAL_CENTER - player1->GetCurrentMonster()->picture->w/2, SCREEN_H/2 - 120);
            }
            else if(player1->field_position == POSITION_OFFENSIVE){
                circlefill(buffer, P1_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
                if(player1->GetCurrentMonster() != NULL)
                    draw_sprite(buffer, player1->GetCurrentMonster()->picture, P1_POS_OFENSIVE_CENTER - player1->GetCurrentMonster()->picture->w/2, SCREEN_H/2 - 120);
            }

            if(player2->field_position == POSITION_DEFENSIVE){
                circlefill(buffer, P2_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
                if(player2->GetCurrentMonster() != NULL)
                    draw_sprite(buffer, player2->GetCurrentMonster()->picture, P2_POS_DEFENSIVE_CENTER - player2->GetCurrentMonster()->picture->w/2, SCREEN_H/2 - 120);
            }
            else if(player2->field_position == POSITION_NEUTRAL){
                circlefill(buffer, P2_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
                if(player2->GetCurrentMonster() != NULL)
                    draw_sprite(buffer, player2->GetCurrentMonster()->picture, P2_POS_NEUTRAL_CENTER - player2->GetCurrentMonster()->picture->w/2, SCREEN_H/2 - 120);
            }
            else if(player2->field_position == POSITION_OFFENSIVE){
                circlefill(buffer, P2_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
                if(player2->GetCurrentMonster() != NULL)
                    draw_sprite(buffer, player2->GetCurrentMonster()->picture, P2_POS_OFENSIVE_CENTER - player2->GetCurrentMonster()->picture->w/2, SCREEN_H/2 - 120);
            }

            //--------------------
            //Lifebars
            textprintf_ex(buffer, font_impact, 70, SCREEN_H-90, makecol(0,0,0), -1, "HP");
            draw_sprite(buffer, lifebar_frame_image, 100, SCREEN_H - 100);
            textprintf_ex(buffer, font_impact, SCREEN_W/2+60, SCREEN_H-90, makecol(0,0,0), -1, "HP");
            draw_sprite(buffer, lifebar_frame_image, SCREEN_W/2+90, SCREEN_H - 100);

            if(player1->GetCurrentMonster() != NULL && player1->GetCurrentMonster()->current_hp > 0)
                rectfill(buffer, 113, 630, 113+423*player1->GetCurrentMonster()->GetHPPercentage(), 654, makecol(83,234,95));

            if(player2->GetCurrentMonster() != NULL && player2->GetCurrentMonster()->current_hp > 0)
                rectfill(buffer, SCREEN_W/2+90+13, 630, SCREEN_W/2+90+13+423*player2->GetCurrentMonster()->GetHPPercentage(), 654, makecol(83,234,95));

            //--------------------
            //Battlelog
            draw_sprite(buffer, message_board_image, SCREEN_W/2 - message_board_image->w/2, 0);
            battlelog->Draw();

            //--------------------
            //Cursor
            DrawMouse(buffer, NULL);

            //--------------------
            //Double buffering
            draw_sprite(screen, buffer, 0, 0);
            clear(buffer);

        ticks--;
        }
    }

    //---------------------
    //Unload Content
    destroy_font(font_impact);

    destroy_bitmap(fieldlines_image);
    destroy_bitmap(message_board_image);
    destroy_bitmap(lifebar_frame_image);
    destroy_bitmap(lifebar_image);
    destroy_bitmap(monster1_image);
    destroy_bitmap(monster2_image);
    destroy_bitmap(monster3_image);
    destroy_bitmap(monster4_image);
    destroy_bitmap(monster5_image);
    destroy_bitmap(monster6_image);
    destroy_bitmap(monster7_image);
    destroy_bitmap(monster8_image);
}
