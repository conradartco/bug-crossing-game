#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        winWidth / 2.0f - 4.0f * (0.5f * width),
        winHeight / 2.0f - 4.0f * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    // initialize direction with 0
    Vector2 direction{};
    // directional input check
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0; // a vector pointing to the left with a magnitude of 1
    if (IsKeyDown(KEY_D))
        direction.x += 1.0; // a vector pointing to the right with a magnitude of 1
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0; // a vector pointing to up with a magnitude of 1
    if (IsKeyDown(KEY_S))
        direction.y += 1.0; // a vector pointing to down with a magnitude of 1

    // use direction to move the map
    // Vector2Length returns a float so we can determine the length of movement direction // if zero, no movement
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos - direction
        // scale the movement using speed and the normalized direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // check and change facing direction
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    // update animation frame
    runningTime += deltaTime;
    // increase frame count per second
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
    // initialize the location on the spritesheet and multiply rightLeft to scale, flipping the value and changing direction
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    // the location in the window to draw the character
    Rectangle dest{screenPos.x, screenPos.y, 4.f * width, 4.f * height};
    // draw the character
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

