// Gilberto Miranda

#include <iostream>
#include <ctime>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "constants.h"
#include "penguinFiring.h"
#include "snowball.h"
#include "penguinDropping.h"

using namespace std;

// Check for collision between two objects
bool CheckCollision(float x1, float y1, int w1, int h1,
    float x2, float y2, int w2, int h2)
{
    return (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2);
}

int main()
{
    // Seed random number generator
    srand(time(NULL));

    // Initialize Allegro
    if (!al_init())
        return -1;

    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Create display window
    ALLEGRO_DISPLAY* display =
        al_create_display(SCREEN_W, SCREEN_H);

    if (!display)
        return -1;

    // Create game timer
    ALLEGRO_TIMER* timer =
        al_create_timer(1.0 / FPS);

    // Create event queue
    ALLEGRO_EVENT_QUEUE* queue =
        al_create_event_queue();

    // Register event sources
    al_register_event_source(
        queue,
        al_get_display_event_source(display));

    al_register_event_source(
        queue,
        al_get_keyboard_event_source());

    al_register_event_source(
        queue,
        al_get_timer_event_source(timer));

    // Create font
    ALLEGRO_FONT* font =
        al_create_builtin_font();

    // Load background image
    ALLEGRO_BITMAP* background =
        al_load_bitmap("bg2.png");

    // Load iceberg image
    ALLEGRO_BITMAP* iceberg =
        al_load_bitmap("iceberg.png");

    // Check background image
    if (!background)
    {
        cout << "Failed to load background.png\n";
        return -1;
    }

    // Check iceberg image
    if (!iceberg)
    {
        cout << "Failed to load iceberg.png\n";
        return -1;
    }

    // Create cannon object
    penguinFiring cannon;

    // Load cannon image
    if (!cannon.LoadImage("penguinFiring.png"))
    {
        cout << "Failed to load penguinFiring.png\n";
        return -1;
    }

    // Create snowball array
    snowball snowballs[NUM_SNOWBALLS];

    // Load snowball images
    for (int i = 0; i < NUM_SNOWBALLS; i++)
    {
        if (!snowballs[i].LoadImage("snowball.png"))
        {
            cout << "Failed to load snowball.png\n";
            return -1;
        }
    }

    // Create penguin array
    penguinDropping penguins[NUM_PENGUINS];

    // Load penguin images
    for (int i = 0; i < NUM_PENGUINS; i++)
    {
        if (!penguins[i].LoadImage("penguinDrop.png"))
        {
            cout << "Failed to load penguinDrop.png\n";
            return -1;
        }
    }

    bool running = true;
    bool redraw = true;

    // Track keyboard input
    bool keys[ALLEGRO_KEY_MAX] = { false };

    // Player score and lives
    int score = 0;
    int lives = MAX_LIVES;

    // Timers for spawning and firing
    int spawnCounter = 0;
    int fireCounter = 0;

    al_start_timer(timer);

    // Main game loop
    while (running)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            keys[ev.keyboard.keycode] = true;

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                running = false;
        }

        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            keys[ev.keyboard.keycode] = false;
        }

        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (lives > 0)
            {
                // Rotate cannon
                if (keys[ALLEGRO_KEY_LEFT])
                    cannon.RotateLeft();

                if (keys[ALLEGRO_KEY_RIGHT])
                    cannon.RotateRight();

                fireCounter++;

                // Fire snowballs
                if (keys[ALLEGRO_KEY_SPACE] &&
                    fireCounter > 10)
                {
                    for (int i = 0; i < NUM_SNOWBALLS; i++)
                    {
                        if (!snowballs[i].IsActive())
                        {
                            snowballs[i].Fire(
                                cannon.GetX(),
                                cannon.GetY(),
                                cannon.GetAngle());

                            fireCounter = 0;
                            break;
                        }
                    }
                }

                spawnCounter++;

                // Spawn falling penguins
                if (spawnCounter > 60)
                {
                    for (int i = 0; i < NUM_PENGUINS; i++)
                    {
                        if (!penguins[i].IsActive())
                        {
                            penguins[i].Spawn();
                            spawnCounter = 0;
                            break;
                        }
                    }
                }

                // Update snowballs
                for (int i = 0; i < NUM_SNOWBALLS; i++)
                    snowballs[i].Update();

                // Update penguins
                for (int i = 0; i < NUM_PENGUINS; i++)
                    penguins[i].Update();

                // Check snowball and penguin collisions
                for (int p = 0; p < NUM_PENGUINS; p++)
                {
                    if (!penguins[p].IsActive())
                        continue;

                    for (int s = 0; s < NUM_SNOWBALLS; s++)
                    {
                        if (!snowballs[s].IsActive())
                            continue;

                        if (CheckCollision(
                            snowballs[s].GetX(),
                            snowballs[s].GetY(),
                            snowballs[s].GetWidth(),
                            snowballs[s].GetHeight(),

                            penguins[p].GetX(),
                            penguins[p].GetY(),
                            penguins[p].GetWidth(),
                            penguins[p].GetHeight()))
                        {
                            snowballs[s].SetActive(false);
                            penguins[p].SetActive(false);

                            score++;
                        }
                    }
                }

                // Check if penguins reach the iceberg
                int icebergY = SCREEN_H - 110;

                for (int i = 0; i < NUM_PENGUINS; i++)
                {
                    if (!penguins[i].IsActive())
                        continue;

                    if (penguins[i].GetY() >= SCREEN_H - 120)
                    {
                        penguins[i].SetActive(false);
                        lives--;
                    }
                }
            }

            redraw = true;
        }

        if (redraw &&
            al_is_event_queue_empty(queue))
        {
            redraw = false;

            al_clear_to_color(
                al_map_rgb(0, 0, 0));

            // Draw background
            al_draw_scaled_bitmap(
                background,
                0,
                0,
                al_get_bitmap_width(background),
                al_get_bitmap_height(background),
                0,
                0,
                SCREEN_W,
                SCREEN_H,
                0);

            // Draw iceberg
            al_draw_scaled_bitmap(
                iceberg,
                0,
                0,
                al_get_bitmap_width(iceberg),
                al_get_bitmap_height(iceberg),
                SCREEN_W / 2 - 175,
                SCREEN_H - 110,
                350,
                110,
                0);

            // Draw cannon
            cannon.Draw();

            // Draw snowballs
            for (int i = 0; i < NUM_SNOWBALLS; i++)
                snowballs[i].Draw();

            // Draw penguins
            for (int i = 0; i < NUM_PENGUINS; i++)
                penguins[i].Draw();

            // Display score
            al_draw_textf(
                font,
                al_map_rgb(255, 255, 255),
                10,
                10,
                0,
                "Score: %d",
                score);

            // Display lives
            al_draw_textf(
                font,
                al_map_rgb(255, 255, 255),
                10,
                40,
                0,
                "Lives: %d",
                lives);

            // Show game over screen
            if (lives <= 0)
            {
                al_draw_text(
                    font,
                    al_map_rgb(255, 0, 0),
                    SCREEN_W / 2,
                    SCREEN_H / 2 - 30,
                    ALLEGRO_ALIGN_CENTER,
                    "GAME OVER");

                al_draw_textf(
                    font,
                    al_map_rgb(255, 255, 255),
                    SCREEN_W / 2,
                    SCREEN_H / 2 + 10,
                    ALLEGRO_ALIGN_CENTER,
                    "Final Score: %d",
                    score);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    SCREEN_W / 2,
                    SCREEN_H / 2 + 40,
                    ALLEGRO_ALIGN_CENTER,
                    "Press ESC to Quit");
            }

            al_flip_display();
        }
    }

    // Free memory
    al_destroy_bitmap(background);
    al_destroy_bitmap(iceberg);

    al_destroy_font(font);

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}