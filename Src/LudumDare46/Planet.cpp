#include "Planet.h"

using namespace godot;

#define IDLE_ANIMATION "Idle"
#define HURT_ANIMATION "Hurt"
#define DEATH_ANIMATION "Die"

Planet::Planet():
	timer(nullptr),
	m_planetSprite(nullptr),
	m_animationplayer(nullptr)
{ }
Planet::~Planet() { }

// --------------------------------

void Planet::_register_methods() {
	register_method("_ready", &Planet::_ready);

	register_method("takeDamage", &Planet::takeDamage);
	register_method("onTimeOut", &Planet::onTimeOut);
	register_method("onAnimationEnd", &Planet::onAnimationEnd);

	register_property<Planet, int>("health", &Planet::setHealth, &Planet::getHealth, 0);
	register_property<Planet, float>("radius", &Planet::setRadius, &Planet::getRadius, 0);
}

void Planet::_init() {
}

void Planet::_ready() {
	timer = cast_to<Timer>(get_node("Timer"));
	m_planetSprite = cast_to<Sprite>(get_node("Planet"));
	m_planetDamageAudio = cast_to<AudioStreamPlayer>(get_node("PlanetDamageAudio"));
	
	timer->connect("timeout", this, "onTimeOut");
	connect("body_entered", this, "takeDamage");


	m_animationplayer = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	m_animationplayer->connect("animation_finished", this, "onAnimationEnd");
	m_animationplayer->play(IDLE_ANIMATION);

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
		// Hide and disable colliders
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

	// FX
	if (m_health > 0) {
		m_animationplayer->stop();
		m_animationplayer->play(HURT_ANIMATION);
	} else {
		m_animationplayer->stop();
		m_animationplayer->play(DEATH_ANIMATION);
	}

	ShaderMaterial* _sm = cast_to<ShaderMaterial>(m_planetSprite->get_material().ptr());
	_sm->set_shader_param("_State", 3.0 - m_health);


	// Screen shake
	CameraBehaviour* _manager = CameraBehaviour::getManager();
	if (_manager) {
		_manager->screenShake();
	}

	GameManager::GetGameManager()->DamageFlash();

	m_planetDamageAudio->play();
}

void Planet::onTimeOut() {
	GameManager::GetGameManager()->Lose();

	// Destroy
	queue_free();
}

void Planet::onAnimationEnd(String animationName)
{
	m_animationplayer->play(IDLE_ANIMATION);
}
