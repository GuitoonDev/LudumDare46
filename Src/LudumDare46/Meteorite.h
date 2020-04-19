#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <time.h>

namespace godot {

class Meteorite : public KinematicBody2D
{
	GODOT_CLASS(Meteorite, KinematicBody2D)

private:

	static int s_instanceCount;

	float m_speed;

	Vector2 m_velocity;

public:

	Meteorite();
	~Meteorite();

	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(float delta);

	void collide();
};

}

