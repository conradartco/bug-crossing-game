#include "SpawnPoint.h"
#include "raymath.h"

SpawnPoint::SpawnPoint(Vector2 pos, Texture2D tex) :
    worldPos(pos),
    texture(tex)
{
    
}

void SpawnPoint::Render(Vector2 knightPos)
{
    Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle SpawnPoint::getCollisionRec(Vector2 colliderPos)
{
    // calculate the props screenPos
    Vector2 screenPos{ Vector2Subtract(worldPos, colliderPos) };
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}