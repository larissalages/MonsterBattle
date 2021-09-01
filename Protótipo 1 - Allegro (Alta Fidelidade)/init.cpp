#include "init.h"

///*******************
///VARIÁVEIS GLOBAIS
volatile int msecs;
volatile int ticks;
volatile bool exit_program;
BITMAP* buffer;

///**************************************************
///TIMER DE MILISEGUNDOS
void MsecCounter() { msecs++; }
END_OF_FUNCTION(MsecCounter);

void TickCounter() { ticks++; }
END_OF_FUNCTION(TickCounter)

///**************************************************
///EXIT CALLBACK
void ExitGame() { exit_program = true; }
END_OF_FUNCTION(Exit_Game)

///**************************************************
///Inicia o Allegro
///**************************************************
void Initialize()
{
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    set_color_depth(32);
    srand(time(NULL));
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0);

    set_window_title("Monster Battle");

    exit_program = false;
    LOCK_FUNCTION(ExitGame);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(ExitGame);

    msecs = 0;
    LOCK_FUNCTION(MsecCounter);
    LOCK_VARIABLE(msecs);
    install_int_ex(MsecCounter, MSEC_TO_TIMER(1));

    ticks = 0;
    LOCK_FUNCTION(TickCounter);
    LOCK_VARIABLE(ticks);
    install_int_ex(TickCounter, BPS_TO_TIMER(60));

    buffer = create_bitmap(SCREEN_W, SCREEN_H);

    LoadContent();
}

void Deinitialize()
{
    UnloadContent();
    destroy_bitmap(buffer);
    clear_keybuf();
    allegro_exit();
}

int funcMax(int a, int b)
{
    if(a >= b)
        return a;
    return b;
}

int funcMin(int a, int b)
{
    if(a <= b)
        return a;
    return b;
}
