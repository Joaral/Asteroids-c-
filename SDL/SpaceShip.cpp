#include "SpaceShip.h"

SpaceShip::SpaceShip(SDL_Renderer* rend, InputManager* inputManager, Vector2Int* texCoor, Vector2Int* sizeClamp)
	: GameObject(rend, new Vector2Int(0, 0), new Vector2Int(30, 40)) {

	// Guardar los valores recibidos
	this->renderer = rend;
	this->texCoor = texCoor;
	this->sizeClamp = sizeClamp;

	this->input = inputManager;

	velocity = Vector2(0, 0);
	acceleration = Vector2(0, 0);
	direction = Vector2(0, 0);

	accelerationFactor = 400.0f;
	linearDrag = 0.90f;
	angularDrag = 0.95f;
	maxSpeed = 250.0f;
	angularVelocity = 0.0f;
}


void SpaceShip::Update(float dt) {
	//printf("Pos: %.2f, %.2f | Vel: %.2f, %.2f\n", position.x, position.y, velocity.x, velocity.y);
	printf("POS: %.2f, %.2f\n", position.x, position.y);

	//printf("ESTOY EN UPDATE\n");
	Vector2 test = direction * accelerationFactor * dt;
	printf("TEST: %.2f, %.2f\n", test.x, test.y);

	printf("dt: %.6f\n", dt);

	const float SCREEN_WIDTH = 800.0f;
	const float SCREEN_HEIGHT = 600.0f;

	// 1. Calcular dirección desde la rotación
	float radians = (zRotation - 90.0f) * (M_PI / 180.0f);  //  gira la base
	direction = Vector2(cos(radians), sin(radians));


	// 2. Aplicar aceleración si  está presionada
	if (input->GetKey(SDLK_UP, HOLD)) {
		velocity += direction * accelerationFactor * dt;
	}

	// 3. Aplicar drag lineal
	velocity = velocity * pow(linearDrag, dt);

	// 4. Aplicar rotación si están presionadas
	float angularSpeed = 540.f;

	if (input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity += angularSpeed * dt;
	}

	if (input->GetKey(SDLK_LEFT, HOLD)) {
		angularVelocity -= angularSpeed * dt;
	}

	// 5. Aplicar drag angular
	if (!input->GetKey(SDLK_LEFT, HOLD) && !input->GetKey(SDLK_RIGHT, HOLD)) {
		angularVelocity *= pow(angularDrag, dt);
	}

	//EXTRA. Aplicar disparo si se ha presionado
	if (input->GetKey(SDLK_SPACE, DOWN)) {
		shoot();
	}

	// 6. Limitar velocidad angular
	const float maxAngularVelocity = 180.f;
	if (angularVelocity > maxAngularVelocity)
		angularVelocity = maxAngularVelocity;
	else if (angularVelocity < -maxAngularVelocity)
		angularVelocity = -maxAngularVelocity;

	// 7. Limitar velocidad lineal
	float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (speed > maxSpeed) {
		velocity = (velocity * (1.0f / speed)) * maxSpeed;
	}

	// 8. Actualizar posición y rotación
	position += velocity * dt;
	zRotation += angularVelocity * dt;

	// EXTRA2. Actualiza cada proyectil
	for (int i = 0; i < projectiles.size(); ) {
		projectiles[i].update(dt);

		// Si sale de pantalla (ejemplo: pantalla 800x600), eliminarlo
		if (projectiles[i].getPosition().x < 0 || projectiles[i].getPosition().x > 800 ||
			projectiles[i].getPosition().y < 0 || projectiles[i].getPosition().y > 600) {
			projectiles.erase(projectiles.begin() + i);
		}
		else {
			++i;
		}
	}

	// 9. Wrap de pantalla
	if (position.x < -sizeToClamp.x) position.x = SCREEN_WIDTH;
	if (position.x > SCREEN_WIDTH) position.x = -sizeToClamp.x;
	if (position.y < -sizeToClamp.y) position.y = SCREEN_HEIGHT;
	if (position.y > SCREEN_HEIGHT) position.y = -sizeToClamp.y;
}

void SpaceShip::render() {

	for (auto& p : projectiles) {
		p.Render();
	}

}

// Projectiles

void SpaceShip::shoot() {
	float projectileSpeed = 300.0f; // velocidad del disparo

	// Crea el proyectil con todos los parámetros que espera el constructor
	Projectile p(renderer, texCoor, sizeClamp, position, rotation, projectileSpeed);

	// Añade el proyectil al vector de proyectiles
	projectiles.push_back(p);
}

