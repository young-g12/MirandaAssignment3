#include "penguinFiring.h"
#include "constants.h"

#include <allegro5/allegro_image.h>
#include <cmath>

penguinFiring::penguinFiring()
{
    x = SCREEN_W / 2;
    y = SCREEN_H - 120;

    angle = 0.0f;

    image = nullptr;
}

penguinFiring::~penguinFiring()
{
    if (image)
        al_destroy_bitmap(image);
}

bool penguinFiring::LoadImage(const char* filename)
{
    image = al_load_bitmap(filename);

    if (!image)
        return false;

    return true;
}

void penguinFiring::Draw()
{
    if (!image)
        return;

    float cx = al_get_bitmap_width(image) / 2.0f;
    float cy = al_get_bitmap_height(image) / 2.0f;

    al_draw_rotated_bitmap(
        image,
        cx,
        cy,
        x,
        y,
        angle,
        0
    );
}

void penguinFiring::RotateLeft()
{
    angle -= 0.03f;

    if (angle < -1.047f)
        angle = -1.047f;
}

void penguinFiring::RotateRight()
{
    angle += 0.03f;

    if (angle > 1.047f)
        angle = 1.047f;
}

float penguinFiring::GetAngle() const
{
    return angle;
}

int penguinFiring::GetX() const
{
    return x;
}

int penguinFiring::GetY() const
{
    return y;
}