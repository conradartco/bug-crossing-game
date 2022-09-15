#include "raylib.h"
#include "raymath.h"

int main()
{
    const float windowWidth{384};
    const float windowHeight{384};

    InitWindow(windowWidth, windowHeight, "Bug Crossing");

    // load background

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

        // directional input check

        // use direction to move the map

        // draw the map

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