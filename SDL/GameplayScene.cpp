#include "GamePlayScene.h"
#include "SpaceShip.h"


Vector2Int projectileTexCoor = { 0, 0 };  // Ajusta a la posición correcta en el spritesheet
Vector2Int projectileSizeClamp = { 8, 8 }; // Ajusta al tamaño correcto del sprite

void GamePlayScene::Start(SDL_Renderer* rend) {

	printf("CREANDO NAVE\n");

	Scene::Start(rend);
	Vector2Int* tex = new Vector2Int(0, 0);
	Vector2Int* size = new Vector2Int(30, 40);
	objects.push_back(new SpaceShip(rend, &IM, &projectileTexCoor, &projectileSizeClamp));

}

void GamePlayScene::Update(float dt) {

	Scene::Update(dt);

}

void GamePlayScene::Render(SDL_Renderer* rend) {

	Scene::Render(rend);

}

void GamePlayScene::Exit() {

	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}

	objects.clear();

}