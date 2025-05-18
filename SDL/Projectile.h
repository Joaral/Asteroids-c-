#pragma once
#include "GameObject.h"
#include "Vector"

class Projectile : public GameObject {
private:
    SDL_Renderer* renderer;
public:
    
    Projectile(SDL_Renderer* renderer, Vector2Int* texCoor, Vector2Int* sizeClamp, Vector2 position, float rotation, float speed);
    void Update(float dt) override;
    /*void Render(SDL_Renderer* renderer) override;*/
};