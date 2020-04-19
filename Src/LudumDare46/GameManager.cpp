#include "GameManager.h"

using namespace godot;
using namespace std;

GameManager* GameManager::m_manager = nullptr;

#define WAIT_TIMER_NODE "Lose_Wait_Time"

#pragma region Construction
GameManager::GameManager() :
m_score(0), 
m_gameState(GameState::Idle),
m_scoreText(nullptr), 
m_titleScreen(nullptr),
m_defeatScreen(nullptr),
m_finalScoreText(nullptr),
m_pauseScreen(nullptr){}

GameManager::~GameManager() {}
#pragma endregion

#pragma region Properties
const GameManager* GameManager::GetGameManager()
{
	return m_manager;
}
#pragma endregion


#pragma region Godot Methods
void GameManager::_register_methods()
{
	register_method("_input", &GameManager::_input);
	register_method("_ready", &GameManager::_ready);
	register_signal<GameManager>("game_started", "owner", GODOT_VARIANT_TYPE_OBJECT);
	register_signal<GameManager>("game_over", "owner", GODOT_VARIANT_TYPE_OBJECT);
}

void GameManager::_ready()
{
	m_scoreText = cast_to<Label>(get_node("UI/HUD/Score/ScoreDisplay"));
	m_titleScreen = cast_to<Control>(get_node("UI/Menu"));
	m_defeatScreen = cast_to<Control>(get_node("UI/GameOverScreen"));
	m_finalScoreText = cast_to<Label>(get_node("UI/GameOverScreen/Score_Text"));
	m_pauseScreen = cast_to<Control>(get_node("UI/PauseMenu"));

	//Set singleton
	m_manager = this;

	//Init score text
	m_scoreText->set_text(to_string(m_score).c_str());

	//Set idle game state
	m_gameState = GameState::Idle;

	DisplayTitleScreen(true);
	DisplayGameOverScreen(false);
}


void GameManager::_input(InputEvent* p_input)
{
	switch (m_gameState)
	{
	case GameState::Idle:
		if (p_input->is_action_pressed("ui_accept")) {
			StartGame();
		}

		if (p_input->is_action_pressed("ui_cancel")) {
			LeaveGame();
		}
		break;

	case GameState::Playing:
		if (p_input->is_action_pressed("ui_cancel")) {
			SetPauseMode();
		}

		if (p_input->is_action_pressed("ui_accept")) {
			Lose();
		}
		break;

	case GameState::Over:
		if (p_input->is_action_pressed("ui_accept")) {
			ReloadGame();
		}

		if (p_input->is_action_pressed("ui_cancel")) {
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
	m_gameState = GameState::Playing;
	emit_signal("game_started", this);
}

void GameManager::Lose()
{
	m_gameState = GameState::Over;
	emit_signal("game_over", this);

	DisplayGameOverScreen(true);
}

void GameManager::SetPauseMode()
{
	bool _isPaused = get_tree()->is_paused();
	_isPaused ? m_pauseScreen->hide() : m_pauseScreen->show();
	get_tree()->set_pause(!_isPaused);
}

void GameManager::ReloadGame()
{
	get_tree()->reload_current_scene();
}

void GameManager::DisplayGameOverScreen(const bool p_display)
{
	if (p_display) {
		m_defeatScreen->show();
		m_finalScoreText->set_text(to_string(m_score).c_str());

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

