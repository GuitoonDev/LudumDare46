#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include <core/String.hpp>

namespace godot {
	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
#pragma region Construction
		GameManager();
		~GameManager();
#pragma endregion

#pragma region Godot Methods
		static void _register_methods();
		void _init();
#pragma endregion

#pragma region Game Management
		void AddPoints();
		void StartGame();
		void Lose();
		void Pause();
#pragma endregion
	private:
		float m_score;
	};
}