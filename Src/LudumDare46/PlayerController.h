#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Input.hpp>
#include <AnimationPlayer.hpp>
#include <Sprite.hpp>
#include <AudioStreamPlayer.hpp>

namespace godot {
	class PlayerController : public Node2D {
		GODOT_CLASS(PlayerController, Node2D)

		private:
			const String ANIM_IDLE = "Idle";
			const String ANIM_MOVE = "Move";

			const String INPUT_RIGHT = "ui_right";
			const String INPUT_LEFT = "ui_left";

			float m_offsetRadius;
			float m_speed;

			double m_rotation;
			float m_movement;

			AnimationPlayer* m_animation;
			Input* m_input;
			Sprite* m_sprite;

			AudioStreamPlayer* m_movementCharacterLoopAudio;

		public:
			PlayerController();
			~PlayerController();

			// ---------------

			static void _register_methods();
			void _init();
			void _ready();
			void _process(float p_delta);

			// ---------------

			float getOffsetRadius();
			void setOffsetRadius(float p_offsetRadius);

			float getSpeed();
			void setSpeed(float p_speed);
	};
}
