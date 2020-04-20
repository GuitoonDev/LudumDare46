#pragma once

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <time.h>
#include <AudioStreamPlayer.hpp>
#include "MeteoriteSpawner.h"

#include <string>

namespace godot {

class Meteorite : public KinematicBody2D
{
	GODOT_CLASS(Meteorite, KinematicBody2D)

private:
	bool m_isActive;
	bool m_isDeactivating;
	float m_speed;

	Vector2 m_velocity;
	Vector2 m_maxDistance;

	AudioStreamPlayer* m_meteorExplodeAudio;

public:
	Meteorite();
	~Meteorite();

	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(float delta);

	void collide();

	bool getIsActive();
	void setIsActive(bool p_isActive);

	Vector2 getMaxDistance();

	void pool();
};

}

