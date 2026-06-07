// Gilberto Miranda

#include "snowball.h"
#include "constants.h"

#include <allegro5/allegro_image.h>
#include <cmath>

// Constructor
snowball::snowball()
{
    x = 0;
    y = 0;

    dx = 0;
    dy = 0;

    active = false;

    image = nullptr;
}

// Destructor
snowball::~snowball()
{
    if (image)
        al_destroy_bitmap(image);
}

// Load the snowball image
bool snowball::LoadImage(const char* filename)
{
    image = al_load_bitmap(filename);

    if (!image)
        return false;

    return true;
}

// Fire a snowball from the cannon
void snowball::Fire(float startX, float startY, float angle)
{
    x = startX;
    y = startY;

    float speed = 8.0f;

    dx = speed * sin(angle);
    dy = -speed * cos(angle);

    active = true;
}

// Update snowball position
void snowball::Update()
{
    if (!active)
        return;

    x += dx;
    y += dy;

    // Remove snowball when it leaves the screen
    if (x < -50 || x > SCREEN_W + 50 ||
        y < -50 || y > SCREEN_H + 50)
    {
        active = false;
    }
}

// Draw the snowball
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

// Check if snowball is active
bool snowball::IsActive() const
{
    return active;
}

// Set snowball active state
void snowball::SetActive(bool state)
{
    active = state;
}

// Return x position
float snowball::GetX() const
{
    return x;
}

// Return y position
float snowball::GetY() const
{
    return y;
}

// Return collision width
int snowball::GetWidth() const
{
    return 15;
}

// Return collision height
int snowball::GetHeight() const
{
    return 15;
}