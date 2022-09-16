#include "raylib.h"

class Character
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; } // getter
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{}; // center of the screen
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
};