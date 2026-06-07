// Gilberto Miranda

#ifndef PENGUINFIRING_H
#define PENGUINFIRING_H

#include <allegro5/allegro.h>

// Class for the player-controlled cannon
class penguinFiring
{
public:
    // Constructor and destructor
    penguinFiring();
    ~penguinFiring();

    // Load cannon image
    bool LoadImage(const char* filename);

    // Draw the cannon
    void Draw();

    // Rotate the cannon
    void RotateLeft();
    void RotateRight();

    // Return current angle
    float GetAngle() const;

    // Return position
    int GetX() const;
    int GetY() const;

private:
    // Position
    int x;
    int y;

    // Rotation angle
    float angle;

    // Cannon image
    ALLEGRO_BITMAP* image;
};

#endif