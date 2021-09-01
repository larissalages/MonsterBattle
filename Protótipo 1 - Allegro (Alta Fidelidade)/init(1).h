#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include <allegro.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>

#include "keyboard.h"
#include "mouse.h"
#include "content.h"

///*******************
///VARI�VEIS GLOBAIS
extern volatile int msecs;
extern volatile int ticks;
extern volatile bool exit_program;
extern BITMAP* buffer;

///*******************
///FUN��ES
void ContaMilisegundos();
void ExitGame();
void Initialize();
void Deinitialize();

int funcMax(int a, int b);
int funcMin(int a, int b);

#endif
