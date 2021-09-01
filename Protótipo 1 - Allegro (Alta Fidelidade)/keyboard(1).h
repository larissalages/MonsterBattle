#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <allegro.h>

extern int prev_keys[KEY_MAX];

void ReceiveKeyboardInput();
int PressedAnyKey();
int Pressed(int Key);
int Holding(int Key);
int Released(int Key);

#endif
