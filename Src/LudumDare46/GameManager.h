#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>
#include <core/NodePath.hpp>
#include <core/String.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <string>
#include <iostream>
#include <Curve.hpp>
#include <Label.hpp>


namespace godot {

	enum GameState {
		Idle,
		Playing,
		Over
	};

	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
		GameManager();
		~GameManager();

		static void _register_methods();
		void _process();
		void _ready();
		void _init();

		void AddPoints(const int p_points);
		void StartGame();
		void Lose();
		void Pause();
	private:
		int m_score;
		GameState m_gameState;
		Label* m_scoreText;
		Control* m_titleScreen;
		Control* m_defeatScreen;
		//Label* m_finalScoreText;

		void ReloadGame();
		void LeaveGame();
		void DisplayGameOverScreen(const bool p_display);
		void DisplayTitleScreen(const bool p_display);
	};
}
