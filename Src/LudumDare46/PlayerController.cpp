#include "PlayerController.h"

using namespace godot;

PlayerController::PlayerController() {
}

PlayerController::~PlayerController() {
}

// --------------------------------

void PlayerController::_register_methods() {
	register_method("_process", &PlayerController::_process);

	register_property<PlayerController, float>("m_offsetRadius", &PlayerController::setOffsetRadius, &PlayerController::getOffsetRadius, 2.5);
	register_property<PlayerController, float>("m_speed", &PlayerController::setSpeed, &PlayerController::getSpeed, 3);
}

void PlayerController::_init() {
}

void PlayerController::_process(float delta) {
	//Godot::print(std::to_string(m_speed).c_str());
}

// --------------------------------

float PlayerController::getOffsetRadius() {
	return m_offsetRadius;
}

void PlayerController::setOffsetRadius(float p_offsetRadius) {
	if (p_offsetRadius > 0) {
		m_offsetRadius = p_offsetRadius;
	}
}


float PlayerController::getSpeed() {
	return m_speed;
}

void PlayerController::setSpeed(float p_speed) {
	Godot::print("Set Speed");

	if (p_speed > 0) {
		m_speed = p_speed;
	}
}
