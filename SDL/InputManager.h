#pragma once
#include <map>
#include <SDL.h>
#include "Utils.h"

enum KeyState { EMPTY, DOWN, UP, HOLD };

#define IM InputManager::Instance();

class InputManager {
public:
	static InputManager& Instance() {
		static InputManager manager;
		return manager;
	}



	std::map<Sint32, KeyState> keys;
};