#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include <allegro.h>

extern int prev_mouse_b;

bool MouseButtonPressed(int b);
void ReceiveMouseInput();
void DrawMouse(BITMAP* buffer, BITMAP* sprite);

#endif
