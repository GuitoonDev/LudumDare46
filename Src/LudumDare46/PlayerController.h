#pragma once

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>

namespace godot {
	class PlayerController : public KinematicBody2D {
		GODOT_CLASS(PlayerController, KinematicBody2D)

		private:
			float m_offsetRadius;
			float m_speed;

		public:
			PlayerController();
			~PlayerController();

			// ---------------

			static void _register_methods();
			void _init();
			void _process(float p_delta);

			// ---------------

			float getOffsetRadius();
			void setOffsetRadius(float p_offsetRadius);

			float getSpeed();
			void setSpeed(float p_speed);
	};
}
