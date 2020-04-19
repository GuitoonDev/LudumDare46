#pragma once

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>

namespace godot {
	class Bar : public KinematicBody2D {
		GODOT_CLASS(Bar, KinematicBody2D)

		private:
			float m_width;

		public:
			Bar();
			~Bar();

		// ---------------

			static void _register_methods();
			void _init();
			void _ready();

		// ---------------

			float getWidth();
			void setWidth(float p_width);
	};
}
