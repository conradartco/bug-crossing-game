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
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

    // character position at the center of screen
    Vector2 knightPos{
        windowWidth/2.0f - mapScale * (0.5f * (float)knight.width/6.0f),
        windowHeight/2.0f - mapScale * (0.5f * (float)knight.height)
    };

    // character facing / 1 : facing right / -1 : facing left
    float rightLeft{1.f};

    // animation variables
    float runningTime{};
    // current animation frame
    int frame{};
    const int maxFrames{6};
    // animation frame update
    const float updateTime{1.f/12.f};

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
            knight = knight_run;
            // set mapPos = mapPos - direction
            // scale the movement using speed and the normalized direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            // check and change facing direction
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        }
        else
        {
            knight = knight_idle;
        }

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // update animation frame
        runningTime += GetFrameTime();
        // increase frame count per second
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        // initialize the location on the spritesheet and multiply rightLeft to scale, flipping the value and changing direction
        Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        // the location in the window to draw the character
        Rectangle dest{knightPos.x, knightPos.y, mapScale * (float)knight.width/6.0f, mapScale * (float)knight.height};
        // draw the character
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

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