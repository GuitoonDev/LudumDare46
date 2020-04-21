#pragma once

#include <core/Godot.hpp>
#include <Area2D.hpp>
#include <AnimationPlayer.hpp>
#include <AudioStreamPlayer.hpp>
#include "GameManager.h"

namespace godot {
	class Bar : public Area2D {
		GODOT_CLASS(Bar, Area2D)

		private:
			const String ANIM_REFLECT = "Reflect";

			AnimationPlayer* m_animation;

			AudioStreamPlayer* m_meteorParryAudio;

		public:
			Bar();
			~Bar();

		// ---------------

			static void _register_methods();
			void _init();
			void _ready();

		// ---------------

			void sendBack(Node* body);
	};
}
