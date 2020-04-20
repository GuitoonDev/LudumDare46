#include "Meteorite.h"

using namespace godot;

Meteorite::Meteorite() :m_isActive(false)
{
}

Meteorite::~Meteorite()
{
	Godot::print("~Meteorite");
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
	Godot::print(String("Meteorite::_init"));

	//s_instanceCount++;
}

void Meteorite::_ready() {
	Godot::print(String(get_name() + " _ready | " + String(std::to_string(m_isActive).c_str())));

	//srand(time(NULL));

	//float x_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	//float y_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	//set_position(Vector2(x_position, y_position));

	m_velocity = -get_position().normalized() * 100;
}

void Meteorite::_physics_process(float delta)
{
	if (!getIsActive()) {
		return;
	}

	Godot::print("Move");

	Ref<KinematicCollision2D> collision = move_and_collide(m_velocity * m_speed * delta);

	if (collision.is_valid())
	{
		collide();
	}
}

void Meteorite::collide()
{
	emit_signal("collide", this);
	m_isActive = false;
}

bool Meteorite::getIsActive()
{
	return m_isActive;
}

void Meteorite::setIsActive(bool p_isActive)
{
	m_isActive = p_isActive;
	Godot::print(get_name() + " | " + String(std::to_string(m_isActive).c_str()));
}
