#pragma once

#include <core/Godot.hpp>
#include <ResourceLoader.hpp>
#include <PackedScene.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <Node2D.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include "GameManager.h"

#include "Meteorite.h"

namespace godot {

class MeteoriteSpawner : public Node2D
{
	GODOT_CLASS(MeteoriteSpawner, Node2D)

private:
	bool m_areAllInstancesActive;
	int m_activatedInstanceAmount;
	int m_poolIndex;
	float m_screenOffset;
	float m_timeSinceStart;
	float m_meteoriteIntervalTimer;
	float m_meteoriteInterval;
	PoolIntArray m_instanceTimeActivation;
	Ref<PackedScene> m_meteorite;
	Size2 m_windowSize;
	std::vector<Node2D*> m_instances;

	void setRandomPosition(Node2D* p_meteorite, int p_randomHelper);

public:
	MeteoriteSpawner();
	~MeteoriteSpawner();

	static void _register_methods();
	void _ready();
	void _init();
	void _process(float delta);

	void onMeteoriteCollide(Node* p_meteorite);
	void onGameStarted();
};

}
