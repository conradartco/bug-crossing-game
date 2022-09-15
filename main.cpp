#include "raylib.h"
#include "raymath.h"

int main()
{
    const float windowWidth{384};
    const float windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Bug Crossing");

    // load background
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    const float mapScale{4.0f};
    // having this out of the while loop saves the value between iterations
    Vector2 mapPos{0.f, 0.f};
    const float speed{4.0f};

    // load character

    // character position on screen

    // character facing

    // animation variables

    // current animation frame

    // animation frame update

    // call character

    // call props

    // call enemies

    // set enemy target

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // initialize direction with 0
        Vector2 direction{};
        // directional input check
        if (IsKeyDown(KEY_A)) direction.x -= 1.0; // a vector pointing to the left with a magnitude of 1
        if (IsKeyDown(KEY_D)) direction.x += 1.0; // a vector pointing to the right with a magnitude of 1
        if (IsKeyDown(KEY_W)) direction.y -= 1.0; // a vector pointing to up with a magnitude of 1
        if (IsKeyDown(KEY_S)) direction.y += 1.0; // a vector pointing to down with a magnitude of 1

        // use direction to move the map
        // Vector2Length returns a float so we can determine the length of movement direction // if zero, no movement
        if (Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // update animation frame

        // draw the props

        // character health check
        
        // check map bounds

        // check prop collisions

        // get enemy positions

        // attack check

        EndDrawing();
    }
    CloseWindow();
}