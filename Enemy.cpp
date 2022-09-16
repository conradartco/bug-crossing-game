#include "Enemy.h"
#include "raymath.h"

// colon after initializer class - you guessed it - initializes the variables // only applies to variables that belong to the class of the same name
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) return;

    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    // check length of velocity - length between enemy and character
    if (Vector2Length(velocity) < radius) velocity = {};
    // draw the enemy
    BaseCharacter::tick(deltaTime);

    // call contactDamage()
    if (CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(contactDamage);
        setAlive(false);
    }

}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}