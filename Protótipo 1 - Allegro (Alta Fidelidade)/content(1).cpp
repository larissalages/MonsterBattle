#include "content.h"

//Fonts
FONT* font_impact;

//Sprites
BITMAP* background_image;
BITMAP* red_image;
BITMAP* blue_image;
BITMAP* fieldlines_image;
BITMAP* message_board_image;
BITMAP* lifebar_frame_image;
BITMAP* lifebar_image;
BITMAP* spark_image;
BITMAP* monster1_image;
BITMAP* monster2_image;
BITMAP* monster3_image;
BITMAP* monster4_image;
BITMAP* monster5_image;
BITMAP* monster6_image;
BITMAP* monster7_image;
BITMAP* monster8_image;
BITMAP* portrait1_image;
BITMAP* portrait2_image;
BITMAP* portrait3_image;
BITMAP* portrait4_image;
BITMAP* portrait5_image;
BITMAP* portrait6_image;
BITMAP* portrait7_image;
BITMAP* portrait8_image;
BITMAP* portrait_secret_image;
BITMAP* portrait_eliminated_image;

void LoadContent()
{
    //Fonts
    font_impact = load_font("fonts/impact.pcx", NULL, NULL);

    //Sprites
    background_image = load_bitmap("sprites/background.bmp", NULL);
    red_image = load_bitmap("sprites/red.bmp", NULL);
    blue_image = load_bitmap("sprites/blue.bmp", NULL);
    fieldlines_image = load_bitmap("sprites/fieldlines.bmp", NULL);
    message_board_image = load_bitmap("sprites/message_board.bmp", NULL);
    lifebar_frame_image = load_bitmap("sprites/lifebar_frame.bmp", NULL);
    lifebar_image = load_bitmap("sprites/lifebar.bmp", NULL);
    spark_image = load_bitmap("sprites/spark.bmp", NULL);
    monster1_image = load_bitmap("sprites/1.bmp", NULL);
    monster2_image = load_bitmap("sprites/2.bmp", NULL);
    monster3_image = load_bitmap("sprites/3.bmp", NULL);
    monster4_image = load_bitmap("sprites/4.bmp", NULL);
    monster5_image = load_bitmap("sprites/5.bmp", NULL);
    monster6_image = load_bitmap("sprites/6.bmp", NULL);
    monster7_image = load_bitmap("sprites/7.bmp", NULL);
    monster8_image = load_bitmap("sprites/8.bmp", NULL);
    portrait1_image = load_bitmap("sprites/portrait1.bmp", NULL);
    portrait2_image = load_bitmap("sprites/portrait2.bmp", NULL);
    portrait3_image = load_bitmap("sprites/portrait3.bmp", NULL);
    portrait4_image = load_bitmap("sprites/portrait4.bmp", NULL);
    portrait5_image = load_bitmap("sprites/portrait5.bmp", NULL);
    portrait6_image = load_bitmap("sprites/portrait6.bmp", NULL);
    portrait7_image = load_bitmap("sprites/portrait7.bmp", NULL);
    portrait8_image = load_bitmap("sprites/portrait8.bmp", NULL);
    portrait_secret_image = load_bitmap("sprites/portrait_secret.bmp", NULL);
    portrait_eliminated_image = load_bitmap("sprites/portrait_eliminated.bmp", NULL);
}

void UnloadContent()
{
    destroy_font(font_impact);

    destroy_bitmap(background_image);
    destroy_bitmap(red_image);
    destroy_bitmap(blue_image);
    destroy_bitmap(fieldlines_image);
    destroy_bitmap(message_board_image);
    destroy_bitmap(lifebar_frame_image);
    destroy_bitmap(lifebar_image);
    destroy_bitmap(spark_image);
    destroy_bitmap(monster1_image);
    destroy_bitmap(monster2_image);
    destroy_bitmap(monster3_image);
    destroy_bitmap(monster4_image);
    destroy_bitmap(monster5_image);
    destroy_bitmap(monster6_image);
    destroy_bitmap(monster7_image);
    destroy_bitmap(monster8_image);
    destroy_bitmap(portrait1_image);
    destroy_bitmap(portrait2_image);
    destroy_bitmap(portrait3_image);
    destroy_bitmap(portrait4_image);
    destroy_bitmap(portrait5_image);
    destroy_bitmap(portrait6_image);
    destroy_bitmap(portrait7_image);
    destroy_bitmap(portrait8_image);
    destroy_bitmap(portrait_secret_image);
    destroy_bitmap(portrait_eliminated_image);
}
