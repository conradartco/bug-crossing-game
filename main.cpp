#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Bug Crossing");

    // load background
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    const float mapScale{4.0f};
    // having this out of the while loop saves the value between iterations
    Vector2 mapPos{0.f, 0.f};

    // load heart container
    Texture2D heartFull = LoadTexture("nature_tileset/heart_container_full.png");
    Texture2D heartEmpty = LoadTexture("nature_tileset/heart_container_empty.png");
    Vector2 heartPos{0.f, 0.f};

    // initialize character
    Character knight{windowWidth, windowHeight};

    // call props
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{1000.f, 500.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy goblin2{
        Vector2{800.f, 1200.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 900.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &goblin2,
        &slime};

    // set enemy target
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // moves map in the opposite direction
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the props using a range based array
        for (auto prop : props) // for all 'props' in the props array (Prop class)
        {
            prop.Render(knight.getWorldPos());
        }

        // character health check
        if (!knight.getAlive()) // character is not alive
        {
            DrawText("Game Over!", 65.f, windowHeight/2.f, 40, RED);
            DrawTextureEx(heartEmpty, heartPos, 0.f, mapScale, WHITE);
            DrawTextureEx(heartEmpty, {(heartPos.x + heartFull.width * mapScale), heartPos.y}, 0.f, mapScale, WHITE);
            DrawTextureEx(heartEmpty, {(heartPos.x + heartFull.width * mapScale) * 2.f, heartPos.y}, 0.f, mapScale, WHITE);
            EndDrawing();
            continue;
        }
        else // character is alive
        {
            if (knight.getHealth() > 2.f)
            {
                DrawTextureEx(heartFull, heartPos, 0.f, mapScale, WHITE);
                DrawTextureEx(heartFull, {(heartPos.x + heartFull.width * mapScale), heartPos.y}, 0.f, mapScale, WHITE);
                DrawTextureEx(heartFull, {(heartPos.x + heartFull.width * mapScale) * 2.f, heartPos.y}, 0.f, mapScale, WHITE);
            }
            else if (knight.getHealth() > 1.f)
            {
                DrawTextureEx(heartFull, heartPos, 0.f, mapScale, WHITE);
                DrawTextureEx(heartFull, {(heartPos.x + heartFull.width * mapScale), heartPos.y}, 0.f, mapScale, WHITE);
                DrawTextureEx(heartEmpty, {(heartPos.x + heartFull.width * mapScale) * 2.f, heartPos.y}, 0.f, mapScale, WHITE);
            }
            else if (knight.getHealth() > 0.f)
            {
                DrawTextureEx(heartFull, heartPos, 0.f, mapScale, WHITE);
                DrawTextureEx(heartEmpty, {(heartPos.x + heartFull.width * mapScale), heartPos.y}, 0.f, mapScale, WHITE);
                DrawTextureEx(heartEmpty, {(heartPos.x + heartFull.width * mapScale) * 2.f, heartPos.y}, 0.f, mapScale, WHITE);
            }
            // std::string knightsHealth = "Health: ";
            // knightsHealth.append(std::to_string(knight.getHealth()), 0, 1);
            // DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, WHITE);
        }

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
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }

            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), goblin.getCollisionRec()))
            {
                goblin.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // get enemy positions

        // attack check
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(heartFull);
    UnloadTexture(heartEmpty);
    CloseWindow();
}