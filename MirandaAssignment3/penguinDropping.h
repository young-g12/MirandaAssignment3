// Gilberto Miranda

#ifndef PENGUINDROPPING_H
#define PENGUINDROPPING_H

#include <allegro5/allegro.h>

// Class for falling penguins
class penguinDropping
{
public:
    // Constructor and destructor
    penguinDropping();
    ~penguinDropping();

    // Load penguin image
    bool LoadImage(const char* filename);

    // Spawn, update, and draw penguins
    void Spawn();
    void Update();
    void Draw();

    // Check and set active state
    bool IsActive() const;
    void SetActive(bool state);

    // Return position
    float GetX() const;
    float GetY() const;

    // Return collision dimensions
    int GetWidth() const;
    int GetHeight() const;

private:
    // Position
    float x;
    float y;

    // Falling speed
    float speed;

    // Active state
    bool active;

    // Penguin image
    ALLEGRO_BITMAP* image;
};

#endif