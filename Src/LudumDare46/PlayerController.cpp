#include "PlayerController.h"

using namespace godot;

PlayerController::PlayerController():m_movement(0) { }
PlayerController::~PlayerController() { }

// --------------------------------

void PlayerController::_register_methods() {
	register_method("_process", &PlayerController::_process);
	register_method("_ready", &PlayerController::_ready);

	register_property<PlayerController, float>("offsetRadius", &PlayerController::setOffsetRadius, &PlayerController::getOffsetRadius, 0);
	register_property<PlayerController, float>("speed", &PlayerController::setSpeed, &PlayerController::getSpeed, 0);
}

void PlayerController::_init() {
}

void PlayerController::_ready() {
	m_animation = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	m_sprite = cast_to<Sprite>(get_node("Player - Sprite"));
	m_input = Input::get_singleton();
	m_rotation = get_rotation();
	
	m_animation->play("Idle");
	m_sprite->set_position(Vector2(0, -m_offsetRadius));
}

void PlayerController::_process(float delta) {
	// Get input movement
	if (m_input->is_action_just_pressed("ui_right")) {
		m_movement = 1;
		m_animation->play("Move");
		m_sprite->set_flip_h(false);
	}
	else if (m_input->is_action_just_released("ui_right") && (m_movement > 0)) {
		if (m_input->is_action_pressed("ui_left")) {
			m_movement = -1;
			m_sprite->set_flip_h(true);
		}
		else {
			m_movement = 0;
			m_animation->play("Idle");
		}
	}

	if (m_input->is_action_just_pressed("ui_left")) {
		m_movement = -1;
		m_sprite->set_flip_h(true);
		m_animation->play("Move");
	}
	else if (m_input->is_action_just_released("ui_left") && (m_movement < 0)) {
		if (m_input->is_action_pressed("ui_right")) {
			m_movement = 1;
			m_sprite->set_flip_h(false);
		}
		else {
			m_movement = 0;
			m_animation->play("Idle");
		}
	}

	// Now move it
	m_rotation += m_movement * m_speed * delta;
	set_rotation(m_rotation);
}

// --------------------------------

float PlayerController::getOffsetRadius() {
	return m_offsetRadius;
}

void PlayerController::setOffsetRadius(float p_offsetRadius) {
	if (p_offsetRadius > 0) {
		m_offsetRadius = p_offsetRadius;
	}
	else {
		m_offsetRadius = 0;
	}
}


float PlayerController::getSpeed() {
	return m_speed;
}

void PlayerController::setSpeed(float p_speed) {
	if (p_speed > 0) {
		m_speed = p_speed;
	}
	else {
		m_speed = 0;
	}
}
