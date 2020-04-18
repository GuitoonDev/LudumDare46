#include "GameManager.h"

using namespace godot;

#pragma region Construction
GameManager::GameManager(){}
GameManager::~GameManager(){}
#pragma endregion


#pragma region Godot Methods
void GameManager::_register_methods()
{
}

void GameManager::_init()
{
	Godot::print("I work !");
}
#pragma endregion

#pragma region Game Management
void GameManager::AddPoints()
{
}

//The start function of the game
void GameManager::StartGame()
{
}

void GameManager::Lose()
{
}

void GameManager::Pause()
{
}
#pragma endregion
