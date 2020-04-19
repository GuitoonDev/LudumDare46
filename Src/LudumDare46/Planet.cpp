#include "Planet.h"

using namespace godot;

Planet::Planet() {
}

Planet::~Planet() {
}

// --------------------------------

void Planet::_register_methods() {
	register_method("_ready", &Planet::_ready);

	register_property<Planet, int>("m_health", &Planet::setHealth, &Planet::getHealth, 3);
	register_property<Planet, float>("m_radius", &Planet::setRadius, &Planet::getRadius, 5);
}

void Planet::_init() {
}

void Planet::_ready() {
	set_scale(Vector2(m_radius, m_radius));

	/*Godot::print(std::to_string(get_viewport_rect().size.x).c_str());
	Godot::print(std::to_string(get_viewport_rect().size.y).c_str());

	set_position(get_viewport_rect().size / 2);*/
}

// --------------------------------

int Planet::getHealth() {
	return m_health;
}

void Planet::setHealth(int p_health) {
	if (m_hasExplode)
		return;

	if (p_health > 0) {
		m_health = p_health;
	}
	else {
		m_health = 0;

		// Explode
		m_hasExplode = true;

		// FX
		// Event

		// Destroy
	}
}

float godot::Planet::getRadius() {
	return m_radius;
}

void godot::Planet::setRadius(float p_radius) {
	if (p_radius > 0) {
		m_radius = p_radius;
	}
}

// --------------------------------

/// <summary>
/// Decrease this planet health, causing it to explode when reaching 0.
/// </summary>
void Planet::takeDamage() {
	setHealth(m_health - 1);
}
