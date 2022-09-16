#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    // need to create this getter so that we can access the protected screenPos variable
    virtual Vector2 getScreenPos() override;
    // lets us access weaponCollisionRec()
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
};

#endif