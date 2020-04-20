#include "CameraBehaviour.h"

using namespace godot;

CameraBehaviour* CameraBehaviour::m_manager = nullptr;

// --------------------------------

CameraBehaviour::CameraBehaviour() { }

CameraBehaviour::~CameraBehaviour() { }

// --------------------------------

void CameraBehaviour::_register_methods() {
	register_property<CameraBehaviour, float>("Screen shake Duration", &CameraBehaviour::m_screenShakeDuration, 0);
	register_property<CameraBehaviour, int>("Screen shake Force", &CameraBehaviour::m_screenShakeForce, 0);

	register_method("_ready", &CameraBehaviour::_ready);
	register_method("_process", &CameraBehaviour::_process);
}

void CameraBehaviour::_init() {
	// Set singleton
	m_manager = this;
}

void CameraBehaviour::_ready() {
	m_screenShakeTimer = m_screenShakeDuration;
}

void CameraBehaviour::_process(float delta) {
	if (m_screenShakeTimer < m_screenShakeDuration) {
		// Random de ses morts
		srand(time(NULL) * m_screenShakeTimer * 100.0);
		float _x = (rand() % 150);

		srand(time(NULL) * m_screenShakeTimer * 200.0);
		float _y = (rand() % 250);

		set_position(Vector2(_x, _y).normalized() * m_screenShakeForce);

		m_screenShakeTimer += delta;

		// Reset position at end
		if (m_screenShakeTimer >= m_screenShakeDuration) {
			set_position(Vector2(0, 0));
		}
	}
}

// --------------------------------

void CameraBehaviour::screenShake() {
	m_screenShakeTimer = 0;
}

// --------------------------------

CameraBehaviour * CameraBehaviour::getManager() {
	return m_manager;
}
