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
		static const GameManager* GetGameManager();

		//Godot methods
		static void _register_methods();
		void _input(InputEvent* p_input);
		void _ready();
		void _init();

		//Game management method
		void AddPoints(const int p_points);
		void Lose();

	private:
		int m_score;
		static GameManager* m_manager;
		GameState m_gameState;
		Label* m_scoreText;
		Control* m_titleScreen;
		Control* m_defeatScreen;
		Label* m_finalScoreText;

		void StartGame();
		void Pause();
		void ReloadGame();
		void LeaveGame();
		void DisplayGameOverScreen(const bool p_display);
		void DisplayTitleScreen(const bool p_display);
	};
}
