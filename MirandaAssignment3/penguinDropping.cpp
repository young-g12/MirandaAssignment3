// Gilberto Miranda

#include "penguinDropping.h"
#include "constants.h"

#include <allegro5/allegro_image.h>
#include <cstdlib>

// Constructor
penguinDropping::penguinDropping()
{
    x = 0;
    y = 0;

    speed = 2.0f;

    active = false;

    image = nullptr;
}

// Destructor
penguinDropping::~penguinDropping()
{
    if (image)
        al_destroy_bitmap(image);
}

// Load the penguin image
bool penguinDropping::LoadImage(const char* filename)
{
    image = al_load_bitmap(filename);

    if (!image)
        return false;

    return true;
}

// Spawn a penguin at a random x position
void penguinDropping::Spawn()
{
    x = rand() % (SCREEN_W - 100) + 50;
    y = -50;

    speed = 2 + rand() % 3;

    active = true;
}

// Move the penguin downward
void penguinDropping::Update()
{
    if (!active)
        return;

    y += speed;

    // Remove penguin if it goes off screen
    if (y > SCREEN_H + 50)
    {
        active = false;
    }
}

// Draw the falling penguin
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

// Check if penguin is active
bool penguinDropping::IsActive() const
{
    return active;
}

// Set penguin active state
void penguinDropping::SetActive(bool state)
{
    active = state;
}

// Return x position
float penguinDropping::GetX() const
{
    return x;
}

// Return y position
float penguinDropping::GetY() const
{
    return y;
}

// Return collision width
int penguinDropping::GetWidth() const
{
    return 50;
}

// Return collision height
int penguinDropping::GetHeight() const
{
    return 50;
}