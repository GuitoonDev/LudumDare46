#pragma once

#include <core/Godot.hpp>
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Node2D.hpp>

#include "Meteorite.h"

namespace godot {

class MeteoriteSpawner : public Node2D
{
	GODOT_CLASS(MeteoriteSpawner, Node2D)

private:

	float m_spawnTime;
	Ref<PackedScene> m_meteorite;

public:
	MeteoriteSpawner();
	~MeteoriteSpawner();

	static void _register_methods();
	void _ready();
	void _init();
	void _process(float delta);

	void onMeteoriteCollide(Node* p_meteorite);
};

}
