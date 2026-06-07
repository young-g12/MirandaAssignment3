#include "penguinDropping.h"
#include "constants.h"

#include <allegro5/allegro_image.h>
#include <cstdlib>

penguinDropping::penguinDropping()
{
    x = 0;
    y = 0;

    speed = 2.0f;

    active = false;

    image = nullptr;
}

penguinDropping::~penguinDropping()
{
    if (image)
        al_destroy_bitmap(image);
}

bool penguinDropping::LoadImage(const char* filename)
{
    image = al_load_bitmap(filename);

    if (!image)
        return false;

    return true;
}

void penguinDropping::Spawn()
{
    x = rand() % (SCREEN_W - 100) + 50;
    y = -50;

    speed = 2 + rand() % 3;

    active = true;
}

void penguinDropping::Update()
{
    if (!active)
        return;

    y += speed;

    if (y > SCREEN_H + 50)
    {
        active = false;
    }
}

void penguinDropping::Draw()
{
    if (!active || !image)
        return;

    al_draw_scaled_bitmap(
        image,
        0,
        0,
        al_get_bitmap_width(image),
        al_get_bitmap_height(image),
        x,
        y,
        60,
        60,
        0);
}

bool penguinDropping::IsActive() const
{
    return active;
}

void penguinDropping::SetActive(bool state)
{
    active = state;
}

float penguinDropping::GetX() const
{
    return x;
}

float penguinDropping::GetY() const
{
    return y;
}

int penguinDropping::GetWidth() const
{
    return 50;
}

int penguinDropping::GetHeight() const
{
    return 50;
}