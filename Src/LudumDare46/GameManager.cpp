#include "GameManager.h"

using namespace godot;
using namespace std;

#pragma region Construction
GameManager::GameManager() :m_score(0), m_label(nullptr) {}
GameManager::~GameManager() {}
#pragma endregion

#pragma region Godot Methods
void GameManager::_register_methods()
{
	register_method("_process", &GameManager::_process);
	register_method("_ready", &GameManager::_ready);
	register_signal<GameManager>("game_started", "owner", GODOT_VARIANT_TYPE_OBJECT);
	register_signal<GameManager>("game_over", "owner", GODOT_VARIANT_TYPE_OBJECT);
}

void GameManager::_ready()
{
	m_label = cast_to<Label>(get_node("UI/HUD/Score/ScoreDisplay"));
	m_titleScreen = cast_to<Control>(get_node("UI/Menu"));
	m_label->set_text(to_string(m_score).c_str());

	DisplayTitleScreen(true);
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

void GameManager::_init() {}
#pragma endregion

#pragma region Game Management
void GameManager::AddPoints(const int points)
{
	m_score += points;
	m_label->set_text(to_string(m_score).c_str());
}

//The start function of the game
void GameManager::StartGame()
{
	Godot::print("Start game");
	DisplayTitleScreen(false);
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
void GameManager::DisplayTitleScreen(const bool display)
{
	if (display == true) {
		m_titleScreen->show();
	} else {
		m_titleScreen->hide();
	}
}
#pragma endregion