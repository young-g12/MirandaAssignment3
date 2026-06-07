// Gilberto Miranda

#ifndef SNOWBALL_H
#define SNOWBALL_H

#include <allegro5/allegro.h>

// Class for snowball objects
class snowball
{
public:
    // Constructor and destructor
    snowball();
    ~snowball();

    // Load snowball image
    bool LoadImage(const char* filename);

    // Fire a snowball
    void Fire(float startX, float startY, float angle);

    // Update and draw snowball
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

    // Movement values
    float dx;
    float dy;

    // Active state
    bool active;

    // Snowball image
    ALLEGRO_BITMAP* image;
};

#endif