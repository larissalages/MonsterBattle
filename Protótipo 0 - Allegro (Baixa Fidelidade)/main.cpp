#include <allegro.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>

std::vector<std::string> game_messages;
int disable_move_accuracy = 0;

enum TYPES{ NORMAL, FIRE, WATER, ELETRIC, GRASS };
enum FIELD_POS{ DEFENSIVE, NEUTRAL, OFFENSIVE };

//-----------------------------------------------------------------------------------------
//Monsters
//-----------------------------------------------------------------------------------------
class Monster
{
    public:
        BITMAP* picture;
        int type;
        int hp;
        int attack;
        int defense;
        int speed;

        int max_hp;

        void Initialize(BITMAP* picture, int type, int base_hp, int base_attack, int base_defense, int base_speed);
};

void Monster::Initialize(BITMAP* picture, int type, int base_hp, int base_attack, int base_defense, int base_speed)
{
    this->picture = picture;
    this->type = type;
    this->hp = 2*base_hp + 110;
    this->attack = 2*base_attack + 5;
    this->defense = 2*base_defense + 5;
    this->speed = 2*base_speed + 5;

    this->max_hp = hp;
}


//-----------------------------------------------------------------------------------------
//Moves
//-----------------------------------------------------------------------------------------
class Move
{
    public:
        int type;
        int power;
        int accuracy;
        int max_uses;

        void Initialize(int type, int power, int accuracy, int max_uses)
        {
            this->type = type;
            this->power = power;
            this->accuracy = accuracy;
            this->max_uses = max_uses;
        }
};

double TypeMultiplier(int type_move, int type_defense)
{
    if(type_move == NORMAL)
        return 1.0;

    else if(type_move == FIRE)
    {
        if(type_defense == WATER)
            return 0.9;
        else if(type_defense == GRASS)
            return 1.1;
        else
            return 1.0;
    }

    else if(type_move == WATER)
    {
        if(type_defense == ELETRIC)
            return 0.9;
        else if(type_defense == FIRE)
            return 1.1;
        else
            return 1.0;
    }

    else if(type_move == ELETRIC)
    {
        if(type_defense == GRASS)
            return 0.9;
        else if(type_defense == WATER)
            return 1.1;
        else
            return 1.0;
    }

    else if(type_move == GRASS)
    {
        if(type_defense == FIRE)
            return 0.9;
        else if(type_defense == ELETRIC)
            return 1.1;
        else
            return 1.0;
    }
}

void ExecuteMove(Move* card, Monster* monster1, Monster* monster2, int attack_field_pos, int defense_field_pos)
{
    if((rand()%100 <= card->accuracy) || disable_move_accuracy == 1)
    {
        double atk_multiplier;
        if(attack_field_pos == DEFENSIVE)
            atk_multiplier = 0.9;
        else if(attack_field_pos == NEUTRAL)
            atk_multiplier = 1.0;
        else if(attack_field_pos == OFFENSIVE)
            atk_multiplier = 1.1;

        double def_multiplier;
        if(defense_field_pos == DEFENSIVE)
            def_multiplier = 1.1;
        else if(defense_field_pos == NEUTRAL)
            def_multiplier = 1.0;
        else if(defense_field_pos == OFFENSIVE)
            def_multiplier = 0.9;

        int damage = ((210.0/250.0)*((monster1->attack*atk_multiplier)/(double)(monster2->defense*def_multiplier))*(card->power) + 2)*TypeMultiplier(card->type, monster2->type);
        monster2->hp -= damage;
        if(monster2->hp < 0)
            monster2->hp = 0;
    }
    else
    {
        std::string s = "miss!";
        game_messages.push_back(s);
    }
}

volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

int main()
{
    allegro_init();
    install_timer();
    install_mouse();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    set_window_title("Monster Battle Demo");

    exit_program = FALSE;
    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa);

    srand(time(NULL));

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* charmander_pic = load_bitmap("sprites/charmander.bmp", NULL);
    BITMAP* squirtle_pic = load_bitmap("sprites/squirtle.bmp", NULL);
    BITMAP* pikachu_pic = load_bitmap("sprites/pikachu.bmp", NULL);
    BITMAP* bulbasaur_pic = load_bitmap("sprites/bulbasaur.bmp", NULL);
    BITMAP* trade_button_pic = load_bitmap("sprites/trade_button.bmp", NULL);
    BITMAP* begin_round_button_pic = load_bitmap("sprites/begin_round_button.bmp", NULL);

    //Trainer 1
    Monster t1_monsters[2];
    t1_monsters[0].Initialize(charmander_pic, FIRE, 39, 55, 45, 65);
    t1_monsters[1].Initialize(pikachu_pic, ELETRIC, 35, 52, 35, 90);
    Move t1_moves[4];
    t1_moves[0].Initialize(FIRE, 70, 70, 1);
    t1_moves[1].Initialize(ELETRIC, 90, 90, 1);
    t1_moves[2].Initialize(FIRE, 120, 80, 1);
    t1_moves[3].Initialize(NORMAL, 80, 100, 1);
    int t1_selected_monster = 0;
    int t1_selected_card = 0;
    int t1_switch_selected = 0;
    int t1_field_pos = NEUTRAL;

    //Trainer 2
    Monster t2_monsters[2];
    t2_monsters[0].Initialize(squirtle_pic, WATER, 44, 49, 65, 43);
    t2_monsters[1].Initialize(bulbasaur_pic, GRASS, 45, 56, 56, 45);
    Move t2_moves[4];
    t2_moves[0].Initialize(WATER, 70, 70, 1);
    t2_moves[1].Initialize(GRASS, 90, 90, 1);
    t2_moves[2].Initialize(WATER, 120, 80, 1);
    t2_moves[3].Initialize(NORMAL, 80, 100, 1);
    int t2_selected_monster = 0;
    int t2_selected_card = 0;
    int t2_switch_selected = 0;
    int t2_field_pos = NEUTRAL;

    //Battle variables
    int begin_turn_selected = 0;
    int prev_z;

    ///GAME LOOP
    while(!exit_program)
    {
        //-------------------------------
        //UPDATE
        if(key[KEY_ESC])
            fecha_programa();

        //Select move
        if(key[KEY_1])
            t1_selected_card = 0;
        if(key[KEY_2])
            t1_selected_card = 1;
        if(key[KEY_3])
            t1_selected_card = 2;
        if(key[KEY_4])
            t1_selected_card = 3;

        if(key[KEY_7])
            t2_selected_card = 0;
        if(key[KEY_8])
            t2_selected_card = 1;
        if(key[KEY_9])
            t2_selected_card = 2;
        if(key[KEY_0])
            t2_selected_card = 3;

        //Select field position
        if(key[KEY_Q])
            t1_field_pos = DEFENSIVE;
        if(key[KEY_W])
            t1_field_pos = NEUTRAL;
        if(key[KEY_E])
            t1_field_pos = OFFENSIVE;

        if(key[KEY_I])
            t2_field_pos = DEFENSIVE;
        if(key[KEY_O])
            t2_field_pos = NEUTRAL;
        if(key[KEY_P])
            t2_field_pos = OFFENSIVE;

        //Disable move accuracy
        if(prev_z == FALSE && key[KEY_Z] == TRUE)
        {
            if(disable_move_accuracy == 0)
            {
                disable_move_accuracy == 1;
                std::string s = "move accuracy disabled";
                game_messages.push_back(s);
            }
            if(disable_move_accuracy == 1)
            {
                disable_move_accuracy = 0;
                std::string s = "move accuracy enabled";
                game_messages.push_back(s);
            }
        }prev_z = key[KEY_Z];
        poll_keyboard();

        //begin round button
        if(mouse_x > 300 && mouse_x < 300+begin_round_button_pic->w
        && mouse_y > 10 && mouse_y < 10+begin_round_button_pic->h
        && mouse_b == 1 && begin_turn_selected == 0
        && (t1_moves[t1_selected_card].type == NORMAL || (t1_moves[t1_selected_card].type == t1_monsters[t1_selected_monster].type))
        && (t2_moves[t2_selected_card].type == NORMAL || (t2_moves[t2_selected_card].type == t2_monsters[t2_selected_monster].type))
        )
        {
            begin_turn_selected = 1;
            game_messages.clear();

            //Executa primeiro a troca se houver
            if(t1_switch_selected && t1_monsters[!t1_selected_monster].hp > 0)
            {
                t1_selected_monster = !t1_selected_monster;
                std::string s = "p1 switch";
                game_messages.push_back(s);
            }
            if(t2_switch_selected && t2_monsters[!t2_selected_monster].hp > 0)
            {
                t2_selected_monster = !t2_selected_monster;
                std::string s = "p2 switch";
                game_messages.push_back(s);
            }

            //Monstro 1 é mais rápido
            if(t1_monsters[t1_selected_monster].speed >= t2_monsters[t2_selected_monster].speed)
            {
                if(!t1_switch_selected)
                    ExecuteMove(&t1_moves[t1_selected_card], &t1_monsters[t1_selected_monster], &t2_monsters[t2_selected_monster], t1_field_pos, t2_field_pos);
                if(!t2_switch_selected && t2_monsters[t2_selected_monster].hp > 0)
                    ExecuteMove(&t2_moves[t2_selected_card], &t2_monsters[t2_selected_monster], &t1_monsters[t1_selected_monster], t2_field_pos, t1_field_pos);
            }

            //Monstro 2 é mais rápido
            else
            {
                if(!t2_switch_selected)
                    ExecuteMove(&t2_moves[t2_selected_card], &t2_monsters[t2_selected_monster], &t1_monsters[t1_selected_monster], t2_field_pos, t1_field_pos);
                if(!t1_switch_selected && t1_monsters[t1_selected_monster].hp > 0)
                    ExecuteMove(&t1_moves[t1_selected_card], &t1_monsters[t1_selected_monster], &t2_monsters[t2_selected_monster], t1_field_pos, t2_field_pos);
            }

            if(t1_monsters[t1_selected_monster].hp == 0)
                t1_selected_monster = !t1_selected_monster;
            if(t2_monsters[t2_selected_monster].hp == 0)
                t2_selected_monster = !t2_selected_monster;

            //se os dois morreram
            if(t1_monsters[0].hp == 0 && t1_monsters[1].hp == 0)
            {
                allegro_message("PLAYER 2 WINS!");
                exit_program = TRUE;
            }
            else if(t2_monsters[0].hp == 0 && t2_monsters[1].hp == 0)
            {
                allegro_message("PLAYER 1 WINS!");
                exit_program = TRUE;
            }

            t1_switch_selected = 0;
            t2_switch_selected = 0;
        }
        if(mouse_b == 0)
            begin_turn_selected = 0;

        //switch button 1
        if(mouse_x > 85 && mouse_x < 85+trade_button_pic->w
        && mouse_y > 300 && mouse_y < 300+trade_button_pic->h
        && mouse_b == 1)
        {
            t1_switch_selected = 1;
        }

        //switch button 2
        if(mouse_x > 620 && mouse_x < 620+trade_button_pic->w
        && mouse_y > 300 && mouse_y < 300+trade_button_pic->h
        && mouse_b == 1)
        {
            t2_switch_selected = 1;
        }

        //-------------------------------
        //DRAW

        //display game messages
        for(int i = 0; i < game_messages.size(); i++)
            textprintf_ex(buffer, font, 310, 200+i*10, makecol(255,255,0), -1, game_messages[i].c_str());

        //monsters
        draw_sprite(buffer, t1_monsters[t1_selected_monster].picture, 0, 0); //current monster t1
        draw_sprite_ex(buffer, t2_monsters[t2_selected_monster].picture, SCREEN_W-t2_monsters[t2_selected_monster].picture->w, 0, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP); //current monster t2
        textprintf_ex(buffer, font, 100, 260, makecol(255,255,255), -1, "HP: %d", t1_monsters[t1_selected_monster].hp);
        textprintf_ex(buffer, font, 650, 260, makecol(255,255,255), -1, "HP: %d", t2_monsters[t2_selected_monster].hp);

        //lifebars
        rectfill(buffer, 10, 5, 240, 25, makecol(255,0,0));
        rectfill(buffer, 10, 5, 10+(230*(t1_monsters[t1_selected_monster].hp/(double)t1_monsters[t1_selected_monster].max_hp)), 25, makecol(0,255,0));
        rectfill(buffer, 560, 5, 790, 25, makecol(255,0,0));
        rectfill(buffer, 560, 5, 560+(790*(t2_monsters[t2_selected_monster].hp/(double)t2_monsters[t2_selected_monster].max_hp)), 25, makecol(0,255,0));

        //cards p1
        rect(buffer, 10, 500, 80, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 15, 510, makecol(255,255,255), -1, "TYPE: %d", t1_moves[0].type);
        textprintf_ex(buffer, font, 15, 520, makecol(255,255,255), -1, "POW: %d", t1_moves[0].power);
        textprintf_ex(buffer, font, 15, 530, makecol(255,255,255), -1, "ACC: %d", t1_moves[0].accuracy);

        rect(buffer, 90, 500, 160, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 95, 510, makecol(255,255,255), -1, "TYPE: %d", t1_moves[1].type);
        textprintf_ex(buffer, font, 95, 520, makecol(255,255,255), -1, "POW: %d", t1_moves[1].power);
        textprintf_ex(buffer, font, 95, 530, makecol(255,255,255), -1, "ACC: %d", t1_moves[1].accuracy);

        rect(buffer, 170, 500, 240, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 175, 510, makecol(255,255,255), -1, "TYPE: %d", t1_moves[2].type);
        textprintf_ex(buffer, font, 175, 520, makecol(255,255,255), -1, "POW: %d", t1_moves[2].power);
        textprintf_ex(buffer, font, 175, 530, makecol(255,255,255), -1, "ACC: %d", t1_moves[2].accuracy);

        rect(buffer, 250, 500, 320, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 255, 510, makecol(255,255,255), -1, "TYPE: %d", t1_moves[3].type);
        textprintf_ex(buffer, font, 255, 520, makecol(255,255,255), -1, "POW: %d", t1_moves[3].power);
        textprintf_ex(buffer, font, 255, 530, makecol(255,255,255), -1, "ACC: %d", t1_moves[3].accuracy);

        if(t1_selected_card == 0)
            rect(buffer, 10, 500, 80, 590, makecol(255,0,0));
        else if(t1_selected_card == 1)
            rect(buffer, 90, 500, 160, 590, makecol(255,0,0));
        else if(t1_selected_card == 2)
            rect(buffer, 170, 500, 240, 590, makecol(255,0,0));
        else if(t1_selected_card == 3)
            rect(buffer, 250, 500, 320, 590, makecol(255,0,0));

        //cards p2
        rect(buffer, 450, 500, 520, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 455, 510, makecol(255,255,255), -1, "TYPE: %d", t2_moves[0].type);
        textprintf_ex(buffer, font, 455, 520, makecol(255,255,255), -1, "POW: %d", t2_moves[0].power);
        textprintf_ex(buffer, font, 455, 530, makecol(255,255,255), -1, "ACC: %d", t2_moves[0].accuracy);

        rect(buffer, 530, 500, 600, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 535, 510, makecol(255,255,255), -1, "TYPE: %d", t2_moves[1].type);
        textprintf_ex(buffer, font, 535, 520, makecol(255,255,255), -1, "POW: %d", t2_moves[1].power);
        textprintf_ex(buffer, font, 535, 530, makecol(255,255,255), -1, "ACC: %d", t2_moves[1].accuracy);

        rect(buffer, 610, 500, 680, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 615, 510, makecol(255,255,255), -1, "TYPE: %d", t2_moves[2].type);
        textprintf_ex(buffer, font, 615, 520, makecol(255,255,255), -1, "POW: %d", t2_moves[2].power);
        textprintf_ex(buffer, font, 615, 530, makecol(255,255,255), -1, "ACC: %d", t2_moves[2].accuracy);

        rect(buffer, 690, 500, 760, 590, makecol(255,255,255));
        textprintf_ex(buffer, font, 695, 510, makecol(255,255,255), -1, "TYPE: %d", t2_moves[3].type);
        textprintf_ex(buffer, font, 695, 520, makecol(255,255,255), -1, "POW: %d", t2_moves[3].power);
        textprintf_ex(buffer, font, 695, 530, makecol(255,255,255), -1, "ACC: %d", t2_moves[3].accuracy);

        if(t2_selected_card == 0)
            rect(buffer, 450, 500, 520, 590, makecol(255,0,0));
        else if(t2_selected_card == 1)
            rect(buffer, 530, 500, 600, 590, makecol(255,0,0));
        else if(t2_selected_card == 2)
            rect(buffer, 610, 500, 680, 590, makecol(255,0,0));
        else if(t2_selected_card == 3)
            rect(buffer, 690, 500, 760, 590, makecol(255,0,0));

        //switch buttons
        draw_sprite(buffer, trade_button_pic, 85, 300);
        draw_sprite(buffer, trade_button_pic, 620, 300);

        if(t1_switch_selected)
            rect(buffer, 85, 300, 85+trade_button_pic->w, 300+trade_button_pic->h, makecol(255,0,0));
        if(t2_switch_selected)
            rect(buffer, 620, 300, 620+trade_button_pic->w, 300+trade_button_pic->h, makecol(255,0,0));

        //field position
        textprintf_ex(buffer, font, 20, 450, makecol(255,255,255), -1, "DEFENSIVE");
        textprintf_ex(buffer, font, 110, 450, makecol(255,255,255), -1, "NEUTRAL");
        textprintf_ex(buffer, font, 180, 450, makecol(255,255,255), -1, "OFFENSIVE");

        if(t1_field_pos == DEFENSIVE)
            textprintf_ex(buffer, font, 20, 450, makecol(255,0,0), -1, "DEFENSIVE");
        else if(t1_field_pos == NEUTRAL)
            textprintf_ex(buffer, font, 110, 450, makecol(255,0,0), -1, "NEUTRAL");
        else if(t1_field_pos == OFFENSIVE)
            textprintf_ex(buffer, font, 180, 450, makecol(255,0,0), -1, "OFFENSIVE");

        textprintf_ex(buffer, font, 470, 450, makecol(255,255,255), -1, "DEFENSIVE");
        textprintf_ex(buffer, font, 560, 450, makecol(255,255,255), -1, "NEUTRAL");
        textprintf_ex(buffer, font, 630, 450, makecol(255,255,255), -1, "OFFENSIVE");

        if(t2_field_pos == DEFENSIVE)
            textprintf_ex(buffer, font, 470, 450, makecol(255,0,0), -1, "DEFENSIVE");
        else if(t2_field_pos == NEUTRAL)
            textprintf_ex(buffer, font, 560, 450, makecol(255,0,0), -1, "NEUTRAL");
        else if(t2_field_pos == OFFENSIVE)
            textprintf_ex(buffer, font, 630, 450, makecol(255,0,0), -1, "OFFENSIVE");


        //begin round button
        draw_sprite(buffer, begin_round_button_pic, 300, 10);

        //mouse cursor
        if(mouse_on_screen())
            draw_sprite(buffer, mouse_sprite, mouse_x, mouse_y);

        //double buffering
        draw_sprite(screen, buffer, 0, 0);
        clear(buffer);
    }

    ///FINALIZAÇÃO
    destroy_bitmap(buffer);
    destroy_bitmap(charmander_pic);
    destroy_bitmap(squirtle_pic);
    destroy_bitmap(pikachu_pic);
    destroy_bitmap(bulbasaur_pic);
    destroy_bitmap(trade_button_pic);
    destroy_bitmap(begin_round_button_pic);

    return 0;
}
END_OF_MAIN();
