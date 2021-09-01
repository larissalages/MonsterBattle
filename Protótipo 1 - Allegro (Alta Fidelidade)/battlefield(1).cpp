#include "battlefield.h"

void Battlefield::LoadContent()
{
    fieldlines_image = load_bitmap("sprites/fieldlines.bmp", NULL);
}

void Battlefield::UnloadContent()
{
    destroy_bitmap(fieldlines_image);
}
