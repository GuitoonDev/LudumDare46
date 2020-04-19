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
	Godot::print("MeteoriteSpawner::_ready");

	ResourceLoader *resourceLoader = ResourceLoader::get_singleton();
	m_meteorite = resourceLoader->load("res://GameContent/Gameplay/Meteorite/Meteorite.tscn");

	Node* meteoriteNode;

	meteoriteNode = m_meteorite->instance();
	get_tree()->get_root()->call_deferred("add_child", meteoriteNode);
	meteoriteNode->connect("collide", this, "onMeteoriteCollide");

	meteoriteNode = m_meteorite->instance();
	get_tree()->get_root()->call_deferred("add_child", meteoriteNode);
	meteoriteNode->connect("collide", this, "onMeteoriteCollide");
	
	meteoriteNode = m_meteorite->instance();
	get_tree()->get_root()->call_deferred("add_child", meteoriteNode);
	meteoriteNode->connect("collide", this, "onMeteoriteCollide");
	
	meteoriteNode = m_meteorite->instance();
	get_tree()->get_root()->call_deferred("add_child", meteoriteNode);
	meteoriteNode->connect("collide", this, "onMeteoriteCollide");
}

void MeteoriteSpawner::_process(float delta)
{
	//m_spawnTime += delta;

	//if (m_spawnTime > 1.0)
	//{
	//	if (m_meteorite.is_valid())
	//	{
	//		Godot::print("Instanciate Meteorite");
	//		
	//		//Godot::print("Meteorite name before add_child :" + instanceNode->get_name());
	//		
	//		get_tree()->get_root()->call_deferred("add_child", m_meteoriteNode);

	//		//Godot::print("Meteorite name after add_child :" + instanceNode->get_name());
	//	}

	//	m_spawnTime = 0;
	//}
}

void MeteoriteSpawner::onMeteoriteCollide(Node* p_meteorite)
{
	Godot::print("onMeteoriteCollide : " + p_meteorite->get_name());
}
