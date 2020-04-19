#include "Meteorite.h"

using namespace godot;

Meteorite::Meteorite()
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
}

void Meteorite::_init()
{
	Godot::print(String("Meteorite::_init"));
}

void Meteorite::_ready() {
	Godot::print(String("Meteorite::_ready"));

	srand(time(NULL));

	//float x_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	//float y_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	//set_position(Vector2(x_position, y_position));

	m_velocity = -get_position().normalized();
}

void Meteorite::_physics_process(float delta)
{
	Ref<KinematicCollision2D> collision = move_and_collide(m_velocity * m_speed * delta);

	if (collision.is_valid())
	{
		collide();
	}
}

void Meteorite::collide()
{
	queue_free();
}

