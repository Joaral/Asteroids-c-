#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:

	Vector2 position;
	Vector2 velocity;
	float rotation;
	Vector2 scale;
	float zRotation;

	SDL_Texture* texture;

	Vector2Int textureCoor;
	Vector2Int sizeToClamp;

public:

	GameObject(SDL_Renderer* renderer, Vector2Int* _textureCoor, Vector2Int* _sizeToClamp);

	virtual void Update(float dt) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	//getters y setters para spaceship
	Vector2 getPosition() const { return position; }
	Vector2 getVelocity() const { return velocity; }
	float getRotation() const { return rotation; }

	void setPosition(const Vector2& pos) { position = pos; }

};
