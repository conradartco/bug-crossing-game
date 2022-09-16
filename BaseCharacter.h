#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    // virtual marks an override function in a child class // + override at the end of the child class inheriting this
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};  // characters' position in the world
    Vector2 worldPosLastFrame{}; // last frame before going over the edge
    // character facing / 1 : facing right / -1 : facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    // current animation frame
    int frame{};
    int maxFrames{6};
    // animation frame update
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    // contains information regarding direction of movement as well as distance moved per frame
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif