#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <string>

namespace godot {
	class Planet : public Node2D {
		GODOT_CLASS(Planet, Node2D)

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

		// ---------------

			int getHealth();
			void setHealth(int p_health);

			float getRadius();
			void setRadius(float p_radius);

		// ---------------

			void takeDamage();
	};
}
