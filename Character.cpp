#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;

    // directional input check
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0; // a vector pointing to the left with a magnitude of 1
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0; // a vector pointing to the right with a magnitude of 1
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0; // a vector pointing to up with a magnitude of 1
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0; // a vector pointing to down with a magnitude of 1

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f) // facing the right
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 25.f : rotation = 0.f;
    }
    else // facing left
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -25.f : rotation = 0.f;
    }

    // draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // DrawRectangleLines(
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}


void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}