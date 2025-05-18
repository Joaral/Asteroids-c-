#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include <cmath>
#include <vector>
#include "Projectile.h"

class SpaceShip : public GameObject {
private:

	Vector2 velocity;
	Vector2 acceleration;
	Vector2 direction;

	float angularVelocity;
	float linearDrag;
	float angularDrag;
	float maxSpeed;
	float accelerationFactor;

	InputManager* input;
	
	//projectiles
	std::vector<Projectile> projectiles;
	SDL_Renderer* renderer;
	InputManager* inputManager;
	Vector2Int* texCoor;
	Vector2Int* sizeClamp;

public:

	SpaceShip(SDL_Renderer* renderer, InputManager* inputManager, Vector2Int* texCoor, Vector2Int* sizeClamp);
	
	~SpaceShip() {
		delete texCoor;
		delete sizeClamp;
	}

	void Update(float dt) override;
	void render();
	//projectiles
	void shoot();
	

};

