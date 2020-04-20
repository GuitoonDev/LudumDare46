#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>
#include <core/NodePath.hpp>
#include <core/String.hpp>
#include <InputEvent.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <Curve.hpp>
#include <Label.hpp>
#include <string>
#include <iostream>
#include <Timer.hpp>
#include <iomanip>
#include <sstream>
#include <Timer.hpp>

namespace godot {

	enum class GameState {
		Idle,
		Playing,
		Over
	};

	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
		GameManager();
		~GameManager();

		//Properties
		static GameManager* GetGameManager();

		//Godot methods
		static void _register_methods();
		void _input(InputEvent* p_input);
		void _ready();
		void _init();
		void _process(float delta);

		//Game management method
		void AddPoints(const int p_points);
		void Flash();
		void Lose();

	private:
		int m_score;
		float m_time;
		static GameManager* m_manager;
		Control* m_flashScreen;
		Timer* m_flashTimer;
		GameState m_gameState;
		Label* m_scoreText;
		Label* m_timeText;
		Control* m_titleScreen;
		Control* m_defeatScreen;
		Label* m_finalScoreText;
		Label* m_finalTimeText;
		Control* m_pauseScreen;

		void StartGame();
		void SetPauseMode();
		void ReloadGame();
		void LeaveGame();
		void DisplayGameOverScreen(const bool p_display);
		void DisplayTitleScreen(const bool p_display);

		void StopFlash();
	};
}
