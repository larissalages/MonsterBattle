#include "init.h"
#include "battlecontroller.h"

int main()
{
    Initialize();

    Battlecontroller battlecontroller;

    battlecontroller.Update();

    //Tela de vencedor do player 1
    if(battlecontroller.GetWinner() == 1)
    {
        while(!exit_program)
        {
            ReceiveKeyboardInput();
            ReceiveMouseInput();

            if(key[KEY_ESC])
                ExitGame();

            textprintf_centre_ex(buffer, font_impact, SCREEN_W/2, SCREEN_H/2, makecol(255,255,255), -1, "PLAYER 1 WINS!");
            DrawMouse(buffer, NULL);
            draw_sprite(screen, buffer, 0, 0);
            clear(buffer);
        }
    }

    //Tela de vencedor do player 2
    else if(battlecontroller.GetWinner() == 2)
    {
        while(!exit_program)
        {
            ReceiveKeyboardInput();
            ReceiveMouseInput();

            if(key[KEY_ESC])
                ExitGame();

            textprintf_centre_ex(buffer, font_impact, SCREEN_W/2, SCREEN_H/2, makecol(255,255,255), -1, "PLAYER 2 WINS!");
            DrawMouse(buffer, NULL);
            draw_sprite(screen, buffer, 0, 0);
            clear(buffer);
        }
    }

    Deinitialize();

    return 0;
}
END_OF_MAIN()
