#pragma once

#include <core/Godot.hpp>
#include <StaticBody2D.hpp>

namespace godot {
	class Planet : public StaticBody2D {
		GODOT_CLASS(Planet, StaticBody2D)

		private:
			bool m_hasExplode = false;
			int m_health;
			float m_radius;

		public:
			Planet();
			~Planet();

		// ---------------

			static void _register_methods();
			void _init();
			void _ready();

		// ---------------

			int getHealth();
			void setHealth(int p_health);

			float getRadius();
			void setRadius(float p_radius);

		// ---------------

			void takeDamage();
	};
}
