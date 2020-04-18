#include "Meteorite.h"

using namespace godot;

Meteorite::Meteorite()
{
}

Meteorite::~Meteorite()
{
}

void Meteorite::_register_methods()
{
	register_method((char*)"_physics_process", &Meteorite::_physics_process);
}

void Meteorite::_init()
{
	srand(time(NULL));

	float x_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	float y_position = (float(rand()) / float(RAND_MAX)) * 20 - 10;
	set_position(Vector2(x_position, y_position));

	float x_velocity = (float(rand()) / float(RAND_MAX)) * 2 - 1;
	float y_velocity = (float(rand()) / float(RAND_MAX)) * 2 - 1;
	m_velocity = Vector2(x_velocity, y_velocity);
}

void Meteorite::_physics_process(float delta)
{
	Ref<KinematicCollision2D> collision = move_and_collide(m_velocity * delta);

	if (collision.is_valid())
	{
		collide();
	}
}

void Meteorite::collide()
{
	queue_free();
}

