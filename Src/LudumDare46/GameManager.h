#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include <core/NodePath.hpp>
#include <core/String.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <string>
#include <iostream>
#include <Curve.hpp>
#include <Label.hpp>

namespace godot {
	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
		GameManager();
		~GameManager();

		static void _register_methods();
		void _process();
		void _ready();
		void _init();

		void AddPoints(const int points);
		void StartGame();
		void Lose();
		void Pause();
	private:
		int m_score;
		Label* m_label;

		void ReloadGame();
	};
}