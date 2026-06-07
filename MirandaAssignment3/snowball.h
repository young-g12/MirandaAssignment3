#ifndef SNOWBALL_H
#define SNOWBALL_H

#include <allegro5/allegro.h>

class snowball
{
public:
    snowball();
    ~snowball();

    bool LoadImage(const char* filename);

    void Fire(float startX, float startY, float angle);

    void Update();
    void Draw();

    bool IsActive() const;
    void SetActive(bool state);

    float GetX() const;
    float GetY() const;

    int GetWidth() const;
    int GetHeight() const;

private:
    float x;
    float y;

    float dx;
    float dy;

    bool active;

    ALLEGRO_BITMAP* image;
};

#endif