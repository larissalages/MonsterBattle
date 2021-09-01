#ifndef CONTENT_H_INCLUDED
#define CONTENT_H_INCLUDED

#include <allegro.h>
#include <cstdio>

//Fonts
extern FONT* font_impact;

//Sprites
extern BITMAP* background_image;
extern BITMAP* red_image;
extern BITMAP* blue_image;
extern BITMAP* fieldlines_image;
extern BITMAP* message_board_image;
extern BITMAP* lifebar_frame_image;
extern BITMAP* lifebar_image;
extern BITMAP* spark_image;
extern BITMAP* monster1_image;
extern BITMAP* monster2_image;
extern BITMAP* monster3_image;
extern BITMAP* monster4_image;
extern BITMAP* monster5_image;
extern BITMAP* monster6_image;
extern BITMAP* monster7_image;
extern BITMAP* monster8_image;
extern BITMAP* portrait1_image;
extern BITMAP* portrait2_image;
extern BITMAP* portrait3_image;
extern BITMAP* portrait4_image;
extern BITMAP* portrait5_image;
extern BITMAP* portrait6_image;
extern BITMAP* portrait7_image;
extern BITMAP* portrait8_image;
extern BITMAP* portrait_secret_image;
extern BITMAP* portrait_eliminated_image;

//Functions
void LoadContent();
void UnloadContent();

#endif
