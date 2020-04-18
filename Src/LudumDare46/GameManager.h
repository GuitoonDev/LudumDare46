#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include <core/String.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <string>
#include <iostream>

namespace godot {
	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
		GameManager();
		~GameManager();

		static void _register_methods();
		void _process();
		void _init();

		void AddPoints(const int points);
		void StartGame();
		void Lose();
		void Pause();
	private:
		int m_score;

		void ReloadGame();
	};
}