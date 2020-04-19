#include "Planet.h"

using namespace godot;

Planet::Planet() { }
Planet::~Planet() { }

// --------------------------------

void Planet::_register_methods() {
	register_method("_ready", &Planet::_ready);

	register_property<Planet, int>("health", &Planet::setHealth, &Planet::getHealth, 0);
	register_property<Planet, float>("radius", &Planet::setRadius, &Planet::getRadius, 0);

	register_signal<Planet>("explode", "owner", GODOT_VARIANT_TYPE_OBJECT);
}

void Planet::_init() {
}

void Planet::_ready() {
	connect("body_entered", this, "takeDamage");

	set_scale(Vector2(m_radius, m_radius));
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
		emit_signal("explode", this);
		//GameManager::GetSingleton()->Lose();

		// Destroy
		queue_free();
	}
}

float godot::Planet::getRadius() {
	return m_radius;
}

void godot::Planet::setRadius(float p_radius) {
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

	Godot::print("Take Damage!");
}
