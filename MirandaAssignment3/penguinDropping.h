#ifndef PENGUINDROPPING_H
#define PENGUINDROPPING_H

#include <allegro5/allegro.h>

class penguinDropping
{
public:
    penguinDropping();
    ~penguinDropping();

    bool LoadImage(const char* filename);

    void Spawn();
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

    float speed;

    bool active;

    ALLEGRO_BITMAP* image;
};

#endif