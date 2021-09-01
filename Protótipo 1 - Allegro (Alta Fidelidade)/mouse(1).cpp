#include "mouse.h"

int prev_mouse_b;

bool MouseButtonPressed(int b)
{
    return ( (mouse_b & b) && !(prev_mouse_b & b) );
}

void ReceiveMouseInput()
{
    prev_mouse_b = mouse_b;
    poll_mouse();
}

void DrawMouse(BITMAP* buffer, BITMAP* sprite)
{
    if(sprite == NULL)
        sprite = mouse_sprite;
    if(mouse_on_screen())
            draw_sprite(buffer, sprite, mouse_x, mouse_y);
}
