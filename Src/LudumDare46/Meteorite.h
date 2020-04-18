#pragma once

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <time.h>

namespace godot {

class Meteorite : public KinematicBody2D
{
	GODOT_CLASS(Meteorite, KinematicBody2D)

private:

	float m_speed;
	Vector2 m_target;

	Vector2 m_velocity;

public:

	Meteorite();
	~Meteorite();

	static void _register_methods();
	void _init();
	void _physics_process(float delta);

	void collide();

};

}

