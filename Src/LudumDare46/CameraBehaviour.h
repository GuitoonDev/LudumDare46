#pragma once

#include <core/Godot.hpp>
#include <Camera2D.hpp>
#include <stdlib.h>
#include <time.h>

#include <string>

namespace godot {
	class CameraBehaviour : public Camera2D {
		GODOT_CLASS(CameraBehaviour, Camera2D)

		private:
			static CameraBehaviour* m_manager;

			float m_screenShakeDuration;
			int m_screenShakeForce;
			float m_screenShakeTimer;

		public:
			CameraBehaviour();
			~CameraBehaviour();

			// ---------------

			static void _register_methods();
			void _init();
			void _ready();
			void _process(float delta);

			// ---------------

			void screenShake();

			// ---------------

			static CameraBehaviour* getManager();
	};
}
