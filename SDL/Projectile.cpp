#include "Projectile.h"
#include <cmath>

Projectile::Projectile(SDL_Renderer* renderer, Vector2Int* texCoor, Vector2Int* sizeClamp,
    Vector2 position, float angle, float speed)
    : GameObject(renderer, texCoor, sizeClamp), renderer(renderer)
{
    this->position = position;
    this->rotation = angle;

    float rad = angle * M_PI / 180.0f;
    Vector2 direction(std::cos(rad), std::sin(rad));
    velocity = direction * speed;
}

void Projectile::Update(float dt) {
    position += velocity * dt;
}

//void Projectile::Render(SDL_Renderer* renderer) {
//    SDL_Rect dst;
//    dst.x = (int)position.x;
//    dst.y = (int)position.y;
//    dst.w = sizeToClamp.x;
//    dst.h = sizeToClamp.y;
//
//    SDL_RenderCopyEx(renderer, texture, nullptr, &dst, rotation, nullptr, SDL_FLIP_NONE);
//}
