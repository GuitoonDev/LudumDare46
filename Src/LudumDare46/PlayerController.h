#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Input.hpp>

namespace godot {
	class PlayerController : public Node2D {
		GODOT_CLASS(PlayerController, Node2D)

		private:
			float m_offsetRadius;
			float m_speed;

			double m_rotation;
			float m_movement;

			Input* m_input;

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
