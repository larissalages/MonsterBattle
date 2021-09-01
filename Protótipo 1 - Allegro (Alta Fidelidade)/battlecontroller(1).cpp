#include "battlecontroller.h"

Battlecontroller::Battlecontroller()
{
    //Inicializa monstros nulos
    for(int i = 0; i < TEAM_SIZE; i++)
    {
        monsters1[i].id = -1;
        monsters1[i].picture = NULL;
        monsters1[i].portrait = portrait_secret_image;
        monsters1[i].hp = 1;
        monsters1[i].current_hp = 1;

        monsters2[i].id = -1;
        monsters2[i].picture = NULL;
        monsters2[i].portrait = portrait_secret_image;
        monsters2[i].hp = 1;
        monsters2[i].current_hp = 1;
    }

    current_monster1 = NULL;
    current_monster2 = NULL;

    field_position1 = POSITION_NEUTRAL;
    field_position2 = POSITION_NEUTRAL;

    red_trans = 0;
    red_trans_var_speed = 6;
    red_trans_var = red_trans_var_speed;

    blue_trans = 0;
    blue_trans_var_speed = 6;
    blue_trans_var = blue_trans_var_speed;

    animation_state = 0;

    //Estado inicial
    battle_state = START_GAME;
}

void Battlecontroller::P1ChooseMonster()
{
    log.PushMessage("Player 1 choose a monster.");

    //id do monstro escolhido
    int monster_id = -1;

    red_trans = 150;
    blue_trans = 0;

    while(monster_id == -1 && !exit_program)
    {
        ReceiveKeyboardInput();
        ReceiveMouseInput();

        //Sair do jogo
        if(Pressed(KEY_ESC))
            ExitGame();

        //Varia trans
        red_trans += red_trans_var;
        if(red_trans > 210)
        {
            red_trans = 210;
            red_trans_var = -red_trans_var_speed;
        }
        else if(red_trans < 20)
        {
            red_trans = 20;
            red_trans_var = red_trans_var_speed;
        }

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

        if(monster_id != -1)
        {
            //O monstro existe no time e está vivo
            if(IsMonsterOnTeam(monsters1, monster_id))
            {
                //O monstro está vivo
                if(IsMonsterAlive(monsters1, monster_id))
                {
                    for(int i = 0; i < TEAM_SIZE; i++)
                    {
                        //Seta como current monster
                        if(monsters1[i].id == monster_id)
                            current_monster1 = &monsters1[i];
                    }

                    std::string message("Player 1 chose ");
                    message.append(current_monster1->name);
                    message.append("!");
                    log.PushMessage(message);
                }

                //O monstro morreu, não é valido
                else
                {
                    log.PushMessage("Invalid. This monster was defeated.");
                    monster_id = -1;
                }
            }

            //O monstro não está no time mas há vaga para ele
            else if(TeamSlotsLeft(monsters1) > 0)
            {
                for(int i = 0; i < TEAM_SIZE; i++)
                {
                    if(monsters1[i].id == -1)
                    {
                        monsters1[i] = GetMonsterFromID(monster_id);
                        current_monster1 = &monsters1[i];
                        break;
                    }
                }

                std::string message("Player 1 chose ");
                message.append(current_monster1->name);
                message.append("!");
                log.PushMessage(message);
            }

            //O monstro não está no time e não há vaga para ele
            else
            {
                log.PushMessage("Invalid. Your team is full");
                monster_id = -1;
            }
        }

        //Desenha a batalha
        Draw();
    }

    rest(150);
}

void Battlecontroller::P2ChooseMonster()
{
    log.PushMessage("Player 2 choose a monster.");

    //id do monstro escolhido
    int monster_id = -1;

    red_trans = 0;
    blue_trans = 150;

    while(monster_id == -1 && !exit_program)
    {
        ReceiveKeyboardInput();
        ReceiveMouseInput();

        //Sair do jogo
        if(Pressed(KEY_ESC))
            ExitGame();

        //Varia trans
        blue_trans += blue_trans_var;
        if(blue_trans > 210)
        {
            blue_trans = 210;
            blue_trans_var = -blue_trans_var_speed;
        }
        else if(blue_trans < 20)
        {
            blue_trans = 20;
            blue_trans_var = blue_trans_var_speed;
        }

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

        if(monster_id != -1)
        {
            //O monstro existe no time e está vivo
            if(IsMonsterOnTeam(monsters2, monster_id))
            {
                //O monstro está vivo
                if(IsMonsterAlive(monsters2, monster_id))
                {
                    for(int i = 0; i < TEAM_SIZE; i++)
                    {
                        //Seta como current monster
                        if(monsters2[i].id == monster_id)
                            current_monster2 = &monsters2[i];
                    }

                    std::string message("Player 2 chose ");
                    message.append(current_monster2->name);
                    message.append("!");
                    log.PushMessage(message);
                }

                //O monstro morreu, não é valido
                else
                {
                    log.PushMessage("Invalid. This monster was defeated.");
                    monster_id = -1;
                }
            }

            //O monstro não está no time mas há vaga para ele
            else if(TeamSlotsLeft(monsters2) > 0)
            {
                for(int i = 0; i < TEAM_SIZE; i++)
                {
                    if(monsters2[i].id == -1)
                    {
                        monsters2[i] = GetMonsterFromID(monster_id);
                        current_monster2 = &monsters2[i];
                        break;
                    }
                }

                std::string message("Player 2 chose ");
                message.append(current_monster2->name);
                message.append("!");
                log.PushMessage(message);
            }

            //O monstro não está no time e não há vaga para ele
            else
            {
                log.PushMessage("Invalid. Your team is full");
                monster_id = -1;
            }
        }

        //Desenha a batalha
        Draw();
    }

    rest(150);
}

void Battlecontroller::P1ChooseCard()
{
    log.PushMessage("Player 1 choose a card.");

    //id da carta escolhida
    int card_id = -1;

    red_trans = 150;
    blue_trans = 0;

    while(card_id == -1 && !exit_program)
    {
        ReceiveKeyboardInput();
        ReceiveMouseInput();

        //Sair do jogo
        if(Pressed(KEY_ESC))
            ExitGame();

        //Varia trans
        red_trans += red_trans_var;
        if(red_trans > 210)
        {
            red_trans = 210;
            red_trans_var = -red_trans_var_speed;
        }
        else if(red_trans < 20)
        {
            red_trans = 20;
            red_trans_var = red_trans_var_speed;
        }

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

        //Se escolheu alguma carta
        if(card_id != -1)
        {
            //Se a carta está com cooldown zerado
            if(cooldown_values1[card_id] == 0)
            {
                selected_card1 = GetCardFromID(card_id);

                //Se for carta de ataque verifica se é de tipo válido
                if(card_id != 0 && selected_card1.gametype != NATURE && current_monster1->gametype != selected_card1.gametype)
                {
                    log.PushMessage("Invalid. This monster cannot execute this attack.");
                    card_id = -1;
                }

                else
                    cooldown_values1[card_id] = selected_card1.cooldown;
            }

            //Ainda não pode usar por causa do cooldown
            else
            {
                std::string message("Invalid. Wait ");
                char turns_str[33];
                itoa(cooldown_values1[card_id],turns_str,10);
                message.append(turns_str);
                message.append(" turns for cooldown.");
                log.PushMessage(message);

                card_id = -1;
            }
        }

        //Se clicou em alguma field position
        if(MouseButtonPressed(1))
        {
            if(mouse_x >= P1_POS_DEFENSIVE_CENTER-POS_RADIUS && mouse_x <= P1_POS_DEFENSIVE_CENTER+POS_RADIUS
            && mouse_y >= SCREEN_H/2-POS_RADIUS && mouse_y <= SCREEN_H/2+POS_RADIUS)
                field_position1 = POSITION_DEFENSIVE;
            else if(mouse_x >= P1_POS_NEUTRAL_CENTER-POS_RADIUS && mouse_x <= P1_POS_NEUTRAL_CENTER+POS_RADIUS
            && mouse_y >= SCREEN_H/2-POS_RADIUS && mouse_y <= SCREEN_H/2+POS_RADIUS)
                field_position1 = POSITION_NEUTRAL;
            else if(mouse_x >= P1_POS_OFENSIVE_CENTER-POS_RADIUS && mouse_x <= P1_POS_OFENSIVE_CENTER+POS_RADIUS
            && mouse_y >= SCREEN_H/2-POS_RADIUS && mouse_y <= SCREEN_H/2+POS_RADIUS)
                field_position1 = POSITION_OFFENSIVE;
        }

        //Desenha a batalha
        Draw();
    }
}

void Battlecontroller::P2ChooseCard()
{
    log.PushMessage("Player 2 choose a card.");

    //id da carta escolhida
    int card_id = -1;

    red_trans = 0;
    blue_trans = 150;

    while(card_id == -1 && !exit_program)
    {
        ReceiveKeyboardInput();
        ReceiveMouseInput();

        //Sair do jogo
        if(Pressed(KEY_ESC))
            ExitGame();

        //Varia trans
        blue_trans += blue_trans_var;
        if(blue_trans > 210)
        {
            blue_trans = 210;
            blue_trans_var = -blue_trans_var_speed;
        }
        else if(blue_trans < 20)
        {
            blue_trans = 20;
            blue_trans_var = blue_trans_var_speed;
        }

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

        //Se escolheu alguma carta
        if(card_id != -1)
        {
            //Se está com cooldown correto
            if(cooldown_values2[card_id] == 0)
            {
                selected_card2 = GetCardFromID(card_id);

                //Se for carta de ataque verifica se é de tipo válido
                if(card_id != 0 && selected_card2.gametype != NATURE && current_monster2->gametype != selected_card2.gametype)
                {
                    log.PushMessage("Invalid. This monster cannot execute this attack.");
                    card_id = -1;
                }

                else
                    cooldown_values2[card_id] = selected_card2.cooldown;
            }

            //Ainda não pode usar por causa do cooldown
            else
            {
                std::string message("Invalid. Wait ");
                char turns_str[33];
                itoa(cooldown_values2[card_id],turns_str,10);
                message.append(turns_str);
                message.append(" turns for cooldown.");
                log.PushMessage(message);

                card_id = -1;
            }
        }

        //Se clicou em alguma field position
        if(MouseButtonPressed(1))
        {
            if(mouse_x >= P2_POS_DEFENSIVE_CENTER-POS_RADIUS && mouse_x <= P2_POS_DEFENSIVE_CENTER+POS_RADIUS
            && mouse_y >= SCREEN_H/2-POS_RADIUS && mouse_y <= SCREEN_H/2+POS_RADIUS)
                field_position2 = POSITION_DEFENSIVE;
            else if(mouse_x >= P2_POS_NEUTRAL_CENTER-POS_RADIUS && mouse_x <= P2_POS_NEUTRAL_CENTER+POS_RADIUS
            && mouse_y >= SCREEN_H/2-POS_RADIUS && mouse_y <= SCREEN_H/2+POS_RADIUS)
                field_position2 = POSITION_NEUTRAL;
            else if(mouse_x >= P2_POS_OFENSIVE_CENTER-POS_RADIUS && mouse_x <= P2_POS_OFENSIVE_CENTER+POS_RADIUS
            && mouse_y >= SCREEN_H/2-POS_RADIUS && mouse_y <= SCREEN_H/2+POS_RADIUS)
                field_position2 = POSITION_OFFENSIVE;
        }

        //Desenha a batalha
        Draw();
    }
}

void Battlecontroller::P1ExecuteAttack()
{
    red_trans = 0;
    blue_trans = 0;

    //Diz nome do monstro e ataque que utilizou
    std::string message(current_monster1->name);
    message.append(" used ");
    message.append(selected_card1.name);
    message.append("!!!");
    log.PushMessage(message);

    float atk_multiplier;
    if(field_position1 == POSITION_DEFENSIVE)
        atk_multiplier = 0.9;
    else if(field_position1 == POSITION_NEUTRAL)
        atk_multiplier = 1.0;
    else if(field_position1 == POSITION_OFFENSIVE)
        atk_multiplier = 1.1;

    float def_multiplier;
    if(field_position2 == POSITION_DEFENSIVE)
        def_multiplier = 1.1;
    else if(field_position2 == POSITION_NEUTRAL)
        def_multiplier = 1.0;
    else if(field_position2 == POSITION_OFFENSIVE)
        def_multiplier = 0.9;

    //Errou o golpe
    if(rand()%100 > selected_card1.accuracy && ENABLE_CARD_ACCURACY)
    {
        std::string msg(current_monster1->name);
        msg.append(" missed!!!");
        log.PushMessage(msg);
    }

    //Acertou o golpe
    else
    {
        float type_multiplier = TypeMultiplier(selected_card1.gametype, current_monster2->gametype);
        int damage = (0.84*(((float)current_monster1->attack*atk_multiplier)/((float)current_monster2->defense*def_multiplier))*((float)selected_card1.power) + 2.0)*type_multiplier;

        if(FloatEq(type_multiplier, TYPE_ADVANTAGE_MULTIPLIER))
            log.PushMessage("It's super effective!");
        else if(FloatEq(type_multiplier, TYPE_DISADVANTAGE_MULTIPLIER))
            log.PushMessage("It's not very effective...");

        AttackAnimation(damage, current_monster2);

        std::string msg("caused ");
        char damage_str[33];
        itoa(damage,damage_str,10);
        msg.append(damage_str);
        msg.append(" damage.");
        log.PushMessage(msg);

        rest(300);
    }
}

void Battlecontroller::P2ExecuteAttack()
{
    red_trans = 0;
    blue_trans = 0;

    //Diz nome do monstro e ataque que utilizou
    std::string message(current_monster2->name);
    message.append(" used ");
    message.append(selected_card2.name);
    message.append("!!!");
    log.PushMessage(message);

    double atk_multiplier;
    if(field_position2 == POSITION_DEFENSIVE)
        atk_multiplier = 0.9;
    else if(field_position2 == POSITION_NEUTRAL)
        atk_multiplier = 1.0;
    else if(field_position2 == POSITION_OFFENSIVE)
        atk_multiplier = 1.1;

    double def_multiplier;
    if(field_position1 == POSITION_DEFENSIVE)
        def_multiplier = 1.1;
    else if(field_position1 == POSITION_NEUTRAL)
        def_multiplier = 1.0;
    else if(field_position1 == POSITION_OFFENSIVE)
        def_multiplier = 0.9;

    //Errou o golpe
    if(rand()%100 > selected_card1.accuracy && ENABLE_CARD_ACCURACY)
    {
        std::string msg(current_monster2->name);
        msg.append(" missed!!!");
        log.PushMessage(msg);
    }

    //Acertou o golpe
    else
    {
        float type_multiplier = TypeMultiplier(selected_card2.gametype, current_monster1->gametype);
        int damage = (0.84*((current_monster2->attack*atk_multiplier)/(double)(current_monster1->defense*def_multiplier))*(selected_card2.power) + 2)*type_multiplier;

        if(FloatEq(type_multiplier, TYPE_ADVANTAGE_MULTIPLIER))
            log.PushMessage("It's super effective!");
        else if(FloatEq(type_multiplier, TYPE_DISADVANTAGE_MULTIPLIER))
            log.PushMessage("It's not very effective...");

        AttackAnimation(damage, current_monster1);

        std::string msg("caused ");
        char damage_str[33];
        itoa(damage,damage_str,10);
        msg.append(damage_str);
        msg.append(" damage.");
        log.PushMessage(msg);

        rest(300);
    }
}

void Battlecontroller::AttackAnimation(int damage, Monster* monster)
{
    //--------------------------------------------------------------
    //Parte 1 animação
    //--------------------------------------------------------------
    animation_state = 1;
    int cont_iterations = 0;

    if(monster == current_monster1)
    {
        if(field_position1 == POSITION_DEFENSIVE)
            animation_x = P1_POS_DEFENSIVE_CENTER;
        else if(field_position1 == POSITION_NEUTRAL)
            animation_x = P1_POS_NEUTRAL_CENTER;
        else
            animation_x = P1_POS_OFENSIVE_CENTER;
    }

    else
    {
        if(field_position2 == POSITION_DEFENSIVE)
            animation_x = P2_POS_DEFENSIVE_CENTER;
        else if(field_position2 == POSITION_NEUTRAL)
            animation_x = P2_POS_NEUTRAL_CENTER;
        else
            animation_x = P2_POS_OFENSIVE_CENTER;
    }

    while(!exit_program && cont_iterations < 20)
    {
        ReceiveKeyboardInput();
        ReceiveMouseInput();

        //Sair do jogo
        if(Pressed(KEY_ESC))
            ExitGame();

        //Faz o draw normal
        Draw();

        //Desenha animação por cima
        if(animation_state == 1)
        {
            if(cont_iterations >= 10)
                animation_state = 2;
        }

        cont_iterations++;
    }

    animation_state = 0;

    //--------------------------------------------------------------
    //Parte 2 subtração de hp
    //--------------------------------------------------------------

    int speed = 2;
    int target_hp = funcMax(0, monster->current_hp - damage);
    bool exit_loop = false;

    while(!exit_program && !exit_loop)
    {
        ReceiveKeyboardInput();
        ReceiveMouseInput();

        //Sair do jogo
        if(Pressed(KEY_ESC))
            ExitGame();

        //Subtrai HP
        monster->current_hp -= speed;

        //Até chegar ao hp final
        if(monster->current_hp <= target_hp)
        {
            monster->current_hp = target_hp;
            exit_loop = true;
        }

        Draw();
    }
}

bool Battlecontroller::IsMonsterOnTeam(Monster team[TEAM_SIZE], int monster_id)
{
    for(int i = 0; i < TEAM_SIZE; i++)
    {
        if(team[i].id == monster_id)
            return true;
    }

    return false;
}

bool Battlecontroller::IsMonsterAlive(Monster team[TEAM_SIZE], int monster_id)
{
    for(int i = 0; i < TEAM_SIZE; i++)
    {
        if(team[i].id == monster_id && team[i].current_hp > 0)
            return true;
    }

    return false;
}

int Battlecontroller::TeamSlotsLeft(Monster team[TEAM_SIZE])
{
    int freeslots = 0;

    for(int i = 0; i < TEAM_SIZE; i++)
    {
        if(team[i].id == -1)
            freeslots++;
    }

    return freeslots;
}

bool Battlecontroller::P1HasMonstersLeft()
{
    for(int i = 0; i < TEAM_SIZE; i++)
    {
        //Se tem slots vagos de monstros ou ainda tem algum com vida
        if(monsters1[i].id == -1 || (monsters1[i].id != -1 && monsters1[i].current_hp > 0))
            return true;
    }

    return false;
}

bool Battlecontroller::P2HasMonstersLeft()
{
    for(int i = 0; i < TEAM_SIZE; i++)
    {
        //Se tem slots vagos de monstros ou ainda tem algum com vida
        if(monsters2[i].id == -1 || (monsters2[i].id != -1 && monsters2[i].current_hp > 0))
            return true;
    }

    return false;
}

void Battlecontroller::Update()
{
    //Enquanto não acabou a batalha
    while(!exit_program && battle_state != P1_WINS && battle_state != P2_WINS)
    {
        //Inicio da batalha
        if(battle_state == START_GAME)
        {
            P1ChooseMonster();
            P2ChooseMonster();
            battle_state = TURN_CHOOSE_ACTION;
        }

        //Escolhendo ação do turno
        else if(battle_state == TURN_CHOOSE_ACTION)
        {
            ApplyCooldown();
            P1ChooseCard();
            P2ChooseCard();
            battle_state = TURN_EXECUTE_ACTION;
        }

        //Executando ação do turno
        else if(battle_state == TURN_EXECUTE_ACTION)
        {
            log.Clear();

            //Ambos escolheram carta de swap
            if(selected_card1.id == 0 && selected_card2.id == 0)
            {
                P1ChooseMonster();
                P2ChooseMonster();
                battle_state = TURN_CHOOSE_ACTION;
            }

            //Só o player 1 escolheu swap
            else if(selected_card1.id == 0)
            {
                P1ChooseMonster();
                P2ExecuteAttack();
                battle_state = TURN_CHOOSE_ACTION;

                //Se o player 1 morreu com o ataque
                if(current_monster1->current_hp <= 0)
                {
                    //Ainda tem monstros
                    if(P1HasMonstersLeft())
                        P1ChooseMonster();

                    //Perdeu todos
                    else
                        battle_state = P2_WINS;
                }
            }

            //Só o player 2 escolheu swap
            else if(selected_card2.id == 0)
            {
                P2ChooseMonster();
                P1ExecuteAttack();
                battle_state = TURN_CHOOSE_ACTION;

                //Se o player 2 morreu com o ataque
                if(current_monster2->current_hp <= 0)
                {
                    //Ainda tem monstros
                    if(P2HasMonstersLeft())
                        P2ChooseMonster();

                    //Perdeu todos
                    else
                        battle_state = P1_WINS;
                }
            }

            //Ambos atacam e o player 1 é mais rápido
            else if(current_monster1->speed >= current_monster2->speed)
            {
                P1ExecuteAttack();

                //Se player 2 ainda está vivo
                if(current_monster2->current_hp > 0)
                {
                    P2ExecuteAttack();
                    battle_state = TURN_CHOOSE_ACTION;

                    //P1 morreu com o ataque
                    if(current_monster1->current_hp <= 0)
                    {
                        //Ainda tem monstros
                        if(P1HasMonstersLeft())
                            P1ChooseMonster();

                        //Perdeu todos
                        else
                            battle_state = P2_WINS;
                    }
                }

                //Se o player 2 morreu com o ataque
                else
                {
                    //Ainda tem monstros
                    if(P2HasMonstersLeft())
                    {
                        P2ChooseMonster();
                        battle_state = TURN_CHOOSE_ACTION;
                    }

                    //Perdeu todos
                    else
                        battle_state = P1_WINS;
                }
            }

            //Ambos atacam e o player 2 é mais rápido
            else if(current_monster1->speed < current_monster2->speed)
            {
                P2ExecuteAttack();

                //Se player 1 ainda está vivo
                if(current_monster1->current_hp > 0)
                {
                    P1ExecuteAttack();
                    battle_state = TURN_CHOOSE_ACTION;

                    //P2 morreu com o ataque
                    if(current_monster2->current_hp <= 0)
                    {
                        //Ainda tem monstros
                        if(P2HasMonstersLeft())
                            P2ChooseMonster();

                        //Perdeu todos
                        else
                            battle_state = P1_WINS;
                    }
                }

                //Se o player 1 morreu com o ataque
                else
                {
                    //Ainda tem monstros
                    if(P1HasMonstersLeft())
                    {
                        P1ChooseMonster();
                        battle_state = TURN_CHOOSE_ACTION;
                    }

                    //Perdeu todos
                    else
                        battle_state = P2_WINS;
                }
            }
        }
    }
}

void Battlecontroller::Draw()
{
    //--------------------
    //Linhas de campo
    draw_sprite(buffer, background_image, 0, 0);
    set_trans_blender(0, 0, 0, red_trans);
    draw_sprite_ex(buffer, red_image, 0, 0, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
    set_trans_blender(0, 0, 0, blue_trans);
    draw_sprite_ex(buffer, blue_image, SCREEN_W/2, 0, DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
    draw_sprite(buffer, fieldlines_image, 0, 0);

    //--------------------
    //Field positions
    circlefill(buffer, P1_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
    circlefill(buffer, P1_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
    circlefill(buffer, P1_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));

    circlefill(buffer, P2_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
    circlefill(buffer, P2_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));
    circlefill(buffer, P2_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(0,0,0));

    if(field_position1 == POSITION_DEFENSIVE)
    {
        if(current_monster1 != NULL && current_monster1->current_hp > 0)
        {
            circlefill(buffer, P1_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
            draw_sprite(buffer, current_monster1->picture, P1_POS_DEFENSIVE_CENTER - current_monster1->picture->w/2, SCREEN_H/2 - 120);
        }
    }

    else if(field_position1 == POSITION_NEUTRAL)
    {
        if(current_monster1 != NULL && current_monster1->current_hp > 0)
        {
            circlefill(buffer, P1_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
            draw_sprite(buffer, current_monster1->picture, P1_POS_NEUTRAL_CENTER - current_monster1->picture->w/2, SCREEN_H/2 - 120);
        }
    }

    else if(field_position1 == POSITION_OFFENSIVE)
    {
        if(current_monster1 != NULL && current_monster1->current_hp > 0)
        {
            circlefill(buffer, P1_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
            draw_sprite(buffer, current_monster1->picture, P1_POS_OFENSIVE_CENTER - current_monster1->picture->w/2, SCREEN_H/2 - 120);
        }
    }

    if(field_position2 == POSITION_DEFENSIVE)
    {
        if(current_monster2 != NULL && current_monster2->current_hp > 0)
        {
            circlefill(buffer, P2_POS_DEFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
            draw_sprite_h_flip(buffer, current_monster2->picture, P2_POS_DEFENSIVE_CENTER - current_monster2->picture->w/2, SCREEN_H/2 - 120);
        }
    }

    else if(field_position2 == POSITION_NEUTRAL)
    {
        if(current_monster2 != NULL && current_monster2->current_hp > 0)
        {
            circlefill(buffer, P2_POS_NEUTRAL_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
            draw_sprite_h_flip(buffer, current_monster2->picture, P2_POS_NEUTRAL_CENTER - current_monster2->picture->w/2, SCREEN_H/2 - 120);
        }
    }

    else if(field_position2 == POSITION_OFFENSIVE)
    {
        if(current_monster2 != NULL && current_monster2->current_hp > 0)
        {
            circlefill(buffer, P2_POS_OFENSIVE_CENTER, SCREEN_H/2, POS_RADIUS, makecol(255,255,255));
            draw_sprite_h_flip(buffer, current_monster2->picture, P2_POS_OFENSIVE_CENTER - current_monster2->picture->w/2, SCREEN_H/2 - 120);
        }
    }

    //--------------------
    //Battle animations
    if(animation_state == 1)
        draw_sprite(buffer, spark_image, animation_x-110, SCREEN_H/2-120);
    else if(animation_state == 2)
        draw_sprite(buffer, spark_image, animation_x-20, SCREEN_H/2-30);

    //--------------------
    //Lifebars
    textprintf_ex(buffer, font_impact, 70, SCREEN_H-90, makecol(255,255,255), -1, "HP");
    draw_sprite(buffer, lifebar_frame_image, 100, SCREEN_H - 100);
    textprintf_ex(buffer, font_impact, SCREEN_W/2+60, SCREEN_H-90, makecol(255,255,255), -1, "HP");
    draw_sprite(buffer, lifebar_frame_image, SCREEN_W/2+90, SCREEN_H - 100);

    if(current_monster1 != NULL)
    {
        float percentage1 = current_monster1->GetHPPercentage();

        int color1 = makecol(50,200,0);
        if(percentage1 <= 0.3)
            color1 = makecol(230,50,0);
        else if(percentage1 <= 0.6)
            color1 = makecol(200,100,0);

        if(current_monster1->current_hp > 0)
        {
            rectfill(buffer, 113, 630, 113+423*percentage1, 654, color1);
            textprintf_centre_ex(buffer, font_impact, 100+lifebar_frame_image->w/2, SCREEN_H-55, makecol(255,255,255), -1, current_monster1->name);

            textprintf_centre_ex(buffer, font_impact, 325, SCREEN_H-88, makecol(0,0,0), -1, "%d", current_monster1->current_hp);
        }
    }

    if(current_monster2 != NULL)
    {
        float percentage2 = current_monster2->GetHPPercentage();

        int color2 = makecol(50,200,0);
        if(percentage2 <= 0.3)
            color2 = makecol(230,50,0);
        else if(percentage2 <= 0.6)
            color2 = makecol(200,100,0);

        if(current_monster2->current_hp > 0)
        {
            rectfill(buffer, SCREEN_W/2+90+13, 630, SCREEN_W/2+90+13+423*percentage2, 654, color2);
            textprintf_centre_ex(buffer, font_impact, SCREEN_W/2+90+lifebar_frame_image->w/2, SCREEN_H-55, makecol(255,255,255), -1, current_monster2->name);
            textprintf_centre_ex(buffer, font_impact, 950, SCREEN_H-88, makecol(0,0,0), -1, "%d", current_monster2->current_hp);
        }
    }

    //--------------------
    //Portraits
    for(int i = 0; i < TEAM_SIZE; i++)
    {
        draw_sprite(buffer, monsters1[i].portrait, 32+i*(2+monsters1[i].portrait->w), 30);
        if(monsters1[i].current_hp <= 0)
            draw_sprite(buffer, portrait_eliminated_image, 32+i*(2+portrait_eliminated_image->w), 30);

        if(monsters2[i].id != -1)
            draw_sprite_h_flip(buffer, monsters2[i].portrait, 1125+i*(2+monsters2[i].portrait->w), 30);
        else
            draw_sprite(buffer, monsters2[i].portrait, 1125+i*(2+monsters2[i].portrait->w), 30);
        if(monsters2[i].current_hp <= 0)
            draw_sprite(buffer, portrait_eliminated_image, 1125+i*(2+portrait_eliminated_image->w), 30);
    }


    //--------------------
    //Battlelog
    draw_sprite(buffer, message_board_image, SCREEN_W/2 - message_board_image->w/2, 0);
    log.Draw();

    //--------------------
    //Cursor
    DrawMouse(buffer, NULL);

    //--------------------
    //Double buffering
    draw_sprite(screen, buffer, 0, 0);
    clear(buffer);
}

int Battlecontroller::GetWinner()
{
    if(battle_state == P1_WINS)
        return 1;
    else if(battle_state == P2_WINS)
        return 2;
    else
        return 0;
}
