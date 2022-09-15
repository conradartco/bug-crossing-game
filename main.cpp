#include "raylib.h"
#include "raymath.h"
#include "Character.h"

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

    // initialize character
    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    // call props

    // call enemies

    // set enemy target

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // moves map in the opposite direction
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the props

        // character health check

        // call the character
        knight.tick(GetFrameTime());

        // check map bounds after calling tick
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check prop collisions

        // get enemy positions

        // attack check

        EndDrawing();
    }
    CloseWindow();
}