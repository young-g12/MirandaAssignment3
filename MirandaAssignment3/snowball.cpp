#include "snowball.h"
#include "constants.h"

#include <allegro5/allegro_image.h>
#include <cmath>

snowball::snowball()
{
    x = 0;
    y = 0;

    dx = 0;
    dy = 0;

    active = false;

    image = nullptr;
}

snowball::~snowball()
{
    if (image)
        al_destroy_bitmap(image);
}

bool snowball::LoadImage(const char* filename)
{
    image = al_load_bitmap(filename);

    if (!image)
        return false;

    return true;
}

void snowball::Fire(float startX, float startY, float angle)
{
    x = startX;
    y = startY;

    float speed = 8.0f;

    dx = speed * sin(angle);
    dy = -speed * cos(angle);

    active = true;
}

void snowball::Update()
{
    if (!active)
        return;

    x += dx;
    y += dy;

    if (x < -50 || x > SCREEN_W + 50 ||
        y < -50 || y > SCREEN_H + 50)
    {
        active = false;
    }
}

void snowball::Draw()
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
        20,
        20,
        0);
}

bool snowball::IsActive() const
{
    return active;
}

void snowball::SetActive(bool state)
{
    active = state;
}

float snowball::GetX() const
{
    return x;
}

float snowball::GetY() const
{
    return y;
}

int snowball::GetWidth() const
{
    if (!image)
        return 0;

    return al_get_bitmap_width(image);
}

int snowball::GetHeight() const
{
    if (!image)
        return 0;

    return al_get_bitmap_height(image);
}