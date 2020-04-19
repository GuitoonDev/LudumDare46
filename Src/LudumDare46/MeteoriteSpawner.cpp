#include "MeteoriteSpawner.h"

using namespace godot;

MeteoriteSpawner::MeteoriteSpawner()
{
}

MeteoriteSpawner::~MeteoriteSpawner()
{
}

void MeteoriteSpawner::_register_methods()
{
	register_method("_ready", &MeteoriteSpawner::_ready);
	register_method("_process", &MeteoriteSpawner::_process);
}

void MeteoriteSpawner::_init()
{
	Godot::print(String("MeteoriteSpawner::_init"));

	m_spawnTime = 0;
}

void MeteoriteSpawner::_ready() {
	Godot::print(String("MeteoriteSpawner::_ready"));

	ResourceLoader *resourceLoader = ResourceLoader::get_singleton();
	m_meteorite = resourceLoader->load("res://GameContent/Gameplay/Meteorite/Meteorite.tscn");
}

void MeteoriteSpawner::_process(float delta)
{
	m_spawnTime += delta;

	if (m_spawnTime > 1.0)
	{
		if (m_meteorite.is_valid())
		{
			Node* instanceNode = m_meteorite->instance();
			get_tree()->get_root()->add_child(instanceNode, true);
		}

		m_spawnTime = 0;
	}
}
