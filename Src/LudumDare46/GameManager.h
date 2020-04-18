#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
<<<<<<< HEAD
#include <core/NodePath.hpp>
#include <core/String.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <string>
#include <iostream>
#include <Curve.hpp>
#include <Label.hpp>
=======
#include <core/String.hpp>
>>>>>>> Created Game Manager source files and prototype methods

namespace godot {
	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
<<<<<<< HEAD
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
		Label* m_label;

		void ReloadGame();
=======
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
>>>>>>> Created Game Manager source files and prototype methods
	};
}