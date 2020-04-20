#include "CameraBehaviour.h"

using namespace godot;

CameraBehaviour* CameraBehaviour::m_manager = nullptr;

// --------------------------------

CameraBehaviour::CameraBehaviour() { }

CameraBehaviour::~CameraBehaviour() { }

// --------------------------------

void CameraBehaviour::_register_methods() {
	register_property<CameraBehaviour, float>("Screen shake Duration", &CameraBehaviour::m_screenShakeDuration, 0);
	register_property<CameraBehaviour, float>("Screen shake Force", &CameraBehaviour::m_screenShakeForce, 0);

	register_method("_ready", &CameraBehaviour::_ready);
	register_method("_process", &CameraBehaviour::_process);
}

void CameraBehaviour::_init() {
}

void CameraBehaviour::_ready() {
	// Set singleton
	m_manager = this;

	m_screenShakeTimer = m_screenShakeDuration;
}

void CameraBehaviour::_process(float delta) {
	if (m_screenShakeTimer < m_screenShakeDuration) {
		// Do it

		m_screenShakeTimer += delta;
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
