#pragma once

#include <core/Godot.hpp>
#include <Area2D.hpp>
#include <Timer.hpp>
#include "GameManager.h"
#include "CameraBehaviour.h"
#include <CollisionShape2D.hpp>
#include <Sprite.hpp>
#include <ShaderMaterial.hpp>
#include <Material.hpp>
#include <Shader.hpp>

namespace godot {
	class Planet : public Area2D {
		GODOT_CLASS(Planet, Area2D)

		private:
			int m_health;
			float m_radius;

			Timer* timer;
			Sprite* m_planetSprite;

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

			void takeDamage(Node* body);
			void onTimeOut();
	};
}
