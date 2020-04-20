#include "GameManager.h"

using namespace godot;
using namespace std;

GameManager* GameManager::m_manager = nullptr;

#define WAIT_TIMER_NODE "Lose_Wait_Time"

#pragma region Construction
GameManager::GameManager() :
m_time(0),
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
GameManager* GameManager::GetGameManager()
{
	return m_manager;
}
#pragma endregion


#pragma region Godot Methods
void GameManager::_register_methods()
{
	register_method("_input", &GameManager::_input);
	register_method("_ready", &GameManager::_ready);
	register_method("_process", &GameManager::_process);
	register_method("StopFlash", &GameManager::StopFlash);
	register_signal<GameManager>("game_started", "owner", GODOT_VARIANT_TYPE_OBJECT);
	register_signal<GameManager>("game_over", "owner", GODOT_VARIANT_TYPE_OBJECT);
}

void GameManager::_ready()
{
	m_flashTimer = cast_to<Timer>(get_node("UI/HUD/Flash/FlashTimer"));
	m_flashScreen = cast_to<Control>(get_node("UI/HUD/Flash/FlashScreen"));
	m_scoreText = cast_to<Label>(get_node("UI/HUD/Score/ScoreDisplay"));
	m_timeText = cast_to<Label>(get_node("UI/HUD/Time/TimeDisplay"));
	m_titleScreen = cast_to<Control>(get_node("UI/Menu"));
	m_defeatScreen = cast_to<Control>(get_node("UI/GameOverScreen"));
	m_finalScoreText = cast_to<Label>(get_node("UI/GameOverScreen/Score_Text"));
	m_finalTimeText = cast_to<Label>(get_node("UI/GameOverScreen/Time_Text"));
	m_pauseScreen = cast_to<Control>(get_node("UI/PauseMenu"));

	m_startGameAudio = cast_to<AudioStreamPlayer>(get_node("StartGame_Audio"));
	m_scoreIncrementAudio = cast_to<AudioStreamPlayer>(get_node("ScoreIncrement_Audio"));

	m_musicLoopAudio = cast_to<AudioStreamPlayer>(get_node("MusicLoop_Audio"));

	m_flashTimer->connect("timeout", this, "StopFlash");

	//Init score text
	m_scoreText->set_text(to_string(m_score).c_str());
	m_timeText->set_text("0");

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

void GameManager::_init() {
	//Set singleton
	m_manager = this;
}

void GameManager::_process(float delta) {
	// Increase timer
	if (m_gameState == GameState::Playing) {
		m_time += delta;
		std::stringstream _stream;
		_stream << std::fixed << std::setprecision(2) << m_time;

		m_timeText->set_text(_stream.str().c_str());
	}
}
#pragma endregion

#pragma region Game Management
void GameManager::AddPoints(const int p_points)
{
	m_score += p_points;
	m_scoreText->set_text(to_string(m_score).c_str());

	m_scoreIncrementAudio->play();
}

void GameManager::Flash() {
	m_flashTimer->start();
	m_flashScreen->show();
}

void GameManager::StartGame()
{
	Godot::print("Start game");
	DisplayTitleScreen(false);
	m_gameState = GameState::Playing;
	emit_signal("game_started", this);

	m_startGameAudio->play();
	m_musicLoopAudio->play();
}

void GameManager::Lose()
{
	m_gameState = GameState::Over;
	emit_signal("game_over", this);

	DisplayGameOverScreen(true);
	m_musicLoopAudio->stop();
}

void GameManager::SetPauseMode()
{
	bool _isPaused = get_tree()->is_paused();
	if (_isPaused)
	{
		m_pauseScreen->hide();
		m_musicLoopAudio->play();
	}
	else
	{
		m_pauseScreen->show();
		m_musicLoopAudio->stop();
	}

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

		std::stringstream _stream;
		_stream << std::fixed << std::setprecision(2) << m_time;
		m_finalTimeText->set_text(_stream.str().c_str());

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

void GameManager::StopFlash() {
	m_flashScreen->hide();
}

void GameManager::LeaveGame()
{
	get_tree()->quit();
}

#pragma endregion

