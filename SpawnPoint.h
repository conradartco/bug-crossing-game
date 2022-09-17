#include "raylib.h"

class SpawnPoint
{
public:
    SpawnPoint(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 colliderPos);
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.0f};
};