#include "GameManager.h"

using namespace godot;
using namespace std;

#pragma region Construction
GameManager::GameManager() :
m_score(0), 
m_gameState(Idle),
m_scoreText(nullptr), 
m_titleScreen(nullptr),
m_defeatScreen(nullptr){}

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
	m_scoreText = cast_to<Label>(get_node("UI/HUD/Score/ScoreDisplay"));
	m_titleScreen = cast_to<Control>(get_node("UI/Menu"));
	m_defeatScreen = cast_to<Control>(get_node("UI/GameOverScreen"));

	//Init score text
	m_scoreText->set_text(to_string(m_score).c_str());

	//Set idle game state
	m_gameState = Idle;

	DisplayTitleScreen(true);
	DisplayGameOverScreen(false);
}

void GameManager::_process()
{
	Input* _input = Input::get_singleton();

	switch (m_gameState)
	{
	case Idle:
		if (_input->is_action_just_pressed("ui_accept")) {
			StartGame();
		}

		if (_input->is_action_just_pressed("ui_cancel")) {
			LeaveGame();
		}
		break;

	case Playing:
		if (_input->is_action_just_pressed("ui_accept")) {
			Lose();
		}
		break;

	case Over:
		if (_input->is_action_just_pressed("ui_accept")) {
			ReloadGame();
		}

		if (_input->is_action_just_pressed("ui_cancel")) {
			LeaveGame();
		}
		break;

	default:
		break;
	}
}

void GameManager::_init() {}
#pragma endregion

#pragma region Game Management
void GameManager::AddPoints(const int p_points)
{
	m_score += p_points;
	m_scoreText->set_text(to_string(m_score).c_str());
}

void GameManager::StartGame()
{
	Godot::print("Start game");
	DisplayTitleScreen(false);
	m_gameState = Playing;
	emit_signal("game_started", this);
}

void GameManager::Lose()
{
	m_gameState = Over;
	emit_signal("game_over", this);
}

void GameManager::Pause()
{
	Godot::print("TODO : Pause the game");
}

void GameManager::ReloadGame()
{
	get_tree()->reload_current_scene();
}


void GameManager::DisplayGameOverScreen(const bool p_display)
{
	if (p_display) {
		m_defeatScreen->show();

	} else {
		m_defeatScreen->hide();
	}
}

void GameManager::DisplayTitleScreen(const bool p_display)
{
	if (p_display) {
		m_titleScreen->show();
	} else {
		m_titleScreen->hide();
	}
}

void GameManager::LeaveGame()
{
	get_tree()->quit();
}

#pragma endregion