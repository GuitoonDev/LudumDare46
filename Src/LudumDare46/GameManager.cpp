#include "GameManager.h"

using namespace godot;
using namespace std;

#pragma region Construction
GameManager::GameManager() :m_score(0){}
GameManager::~GameManager(){}
#pragma endregion


#pragma region Godot Methods
void GameManager::_register_methods()
{
	register_method((char*)"_process", &GameManager::_process);
	register_signal<GameManager>((char *)"game_started", "owner", GODOT_VARIANT_TYPE_OBJECT);
	register_signal<GameManager>((char *)"game_over", "owner", GODOT_VARIANT_TYPE_OBJECT);
}

void GameManager::_process()
{
	Input* _input = Input::get_singleton();

	if (_input->is_action_just_pressed("ui_accept")) {
		StartGame();
	}

	if (_input->is_action_just_pressed("ui_cancel")) {
		ReloadGame();
	}
}

void GameManager::_init()
{
}
#pragma endregion

#pragma region Game Management
void GameManager::AddPoints(const int points)
{
	m_score += points;
}

//The start function of the game
void GameManager::StartGame()
{
	Godot::print("Start game");
	emit_signal("game_started", this);
}

void GameManager::Lose()
{
	emit_signal("game_over", this);
	Godot::print("Reload");
}

void GameManager::Pause()
{
	Godot::print("TODO : Pause the game");
}
void GameManager::ReloadGame()
{
	get_tree()->reload_current_scene();
}
#pragma endregion
