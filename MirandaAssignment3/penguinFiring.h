#ifndef PENGUINFIRING_H
#define PENGUINFIRING_H

#include <allegro5/allegro.h>

class penguinFiring
{
public:
    penguinFiring();
    ~penguinFiring();

    bool LoadImage(const char* filename);

    void Draw();

    void RotateLeft();
    void RotateRight();

    float GetAngle() const;

    int GetX() const;
    int GetY() const;

private:
    int x;
    int y;

    float angle;

    ALLEGRO_BITMAP* image;
};

#endif