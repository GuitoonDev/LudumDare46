#include "Planet.h"

using namespace godot;

Planet::Planet():timer(nullptr) { }
Planet::~Planet() { }

// --------------------------------

void Planet::_register_methods() {
	register_method("_ready", &Planet::_ready);

	register_method("takeDamage", &Planet::takeDamage);
	register_method("onTimeOut", &Planet::onTimeOut);

	register_property<Planet, int>("health", &Planet::setHealth, &Planet::getHealth, 0);
	register_property<Planet, float>("radius", &Planet::setRadius, &Planet::getRadius, 0);
}

void Planet::_init() {
}

void Planet::_ready() {
	timer = cast_to<Timer>(get_node("Timer"));
	m_planetSprite = cast_to<Sprite>(get_node("Sprite"));

	timer->connect("timeout", this, "onTimeOut");
	connect("body_entered", this, "takeDamage");

	set_scale(Vector2(m_radius, m_radius));
}

// --------------------------------

int Planet::getHealth() {
	return m_health;
}

void Planet::setHealth(int p_health) {
	Godot::print("Damaged");

	if (p_health > 0) {
		m_health = p_health;
	}
	else {
		m_health = 0;

		// FX

		// Hide and disable colliders
		hide();
		get_node("PlayerController")->queue_free();
		get_node("StaticBody2D")->queue_free();
		get_node("Collider")->queue_free();

		// Event
		timer->start();

		Godot::print("Explosion!");
	}
}

float Planet::getRadius() {
	return m_radius;
}

void Planet::setRadius(float p_radius) {
	if (p_radius > 0) {
		m_radius = p_radius;
	}
	else {
		m_radius = 0;
	}
}

// --------------------------------

/// <summary>
/// Decrease this planet health, causing it to explode when reaching 0.
/// </summary>
void Planet::takeDamage(Node* body) {
	setHealth(m_health - 1);

	ShaderMaterial* _sm = cast_to<ShaderMaterial>(m_planetSprite->get_material().ptr());
	_sm->set_shader_param("_State", 3.0 - m_health);
	

	// Screen shake
	CameraBehaviour* _manager = CameraBehaviour::getManager();
	if (_manager) {
		_manager->screenShake();
	}
}

void Planet::onTimeOut() {
	GameManager::GetGameManager()->Lose();

	// Destroy
	queue_free();
}
