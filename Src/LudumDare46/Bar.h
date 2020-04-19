#pragma once

#include <core/Godot.hpp>
#include <Area2D.hpp>

namespace godot {
	class Bar : public Area2D {
		GODOT_CLASS(Bar, Area2D)

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

		// ---------------

			void sendBack(Node* body);
	};
}
