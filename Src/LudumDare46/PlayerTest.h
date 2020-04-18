#pragma once

#include <core/Godot.hpp>
#include <core/String.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>

namespace godot {
	class PlayerTest : public KinematicBody2D{
		GODOT_CLASS(PlayerTest, KinematicBody2D)
	private:
		Vector2 motion;
		float speed;

	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

#pragma region MyRegion
		PlayerTest();
		~PlayerTest();
#pragma endregion
	};
}
