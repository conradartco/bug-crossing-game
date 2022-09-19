#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
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

    // Vector2Length returns a float so we can determine the length of movement direction // if zero, no movement
    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos - velocity
        // scale the movement using speed and the normalized velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        // check and change facing velocity
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // initialize the location on the spritesheet and multiply rightLeft to scale, flipping the value and changing direction
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    // the location in the window to draw the character
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    // draw the character
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);

}
