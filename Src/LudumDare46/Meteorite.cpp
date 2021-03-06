#include "Meteorite.h"

using namespace godot;

Meteorite::Meteorite() :m_isActive(false), m_isDeactivating(false)
{
}

Meteorite::~Meteorite()
{
	//Godot::print("~Meteorite");
}

void Meteorite::_register_methods()
{
	register_method((char*)"_ready", &Meteorite::_ready);
	register_method((char*)"_physics_process", &Meteorite::_physics_process);

	register_property<Meteorite, float>("speed", &Meteorite::m_speed, 0);

	register_signal<Meteorite>("collide", "node", GODOT_VARIANT_TYPE_OBJECT);
}

void Meteorite::_init()
{
	//Godot::print(String("Meteorite::_init"));
}

void Meteorite::_ready() {
	//Godot::print(String(get_name() + " _ready | " + String(std::to_string(m_isActive).c_str())));

	//srand(time(NULL));

	//float x_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	//float y_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	//set_position(Vector2(x_position, y_position));

	m_meteorExplodeAudio = cast_to<AudioStreamPlayer>(get_node("MeteorExplode"));
}

void Meteorite::_physics_process(float delta)
{
	if (!getIsActive()) {
		return;
	}
	if (m_isDeactivating) {
		emit_signal("collide", this);
		m_isActive = false;
		m_isDeactivating = false;
		return;
	}

	Ref<KinematicCollision2D> collision = move_and_collide(m_velocity * m_speed * delta);

	if (collision.is_valid())
	{
		collide();
	}
}

void Meteorite::collide() {
	m_isDeactivating = true;

	m_meteorExplodeAudio->play();
}

bool Meteorite::getIsActive() {
	return m_isActive;
}

void Meteorite::setIsActive(bool p_isActive) {
	m_isActive = p_isActive;
}

Vector2 Meteorite::getMaxDistance() {
	return m_maxDistance;
}


void Meteorite::pool() {
	m_isActive = false;

	m_maxDistance = -get_position();
	m_velocity = m_maxDistance.normalized() * 100;
}