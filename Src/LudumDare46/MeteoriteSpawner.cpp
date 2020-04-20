#include "MeteoriteSpawner.h"

using namespace godot;

MeteoriteSpawner::MeteoriteSpawner():m_areAllInstancesActive(false), m_poolIndex(0), m_activatedInstanceAmount(0), m_meteoriteIntervalTimer(0), m_timeSinceStart(0)
{
}

MeteoriteSpawner::~MeteoriteSpawner()
{
}

void MeteoriteSpawner::_register_methods()
{
	register_property<MeteoriteSpawner, float>("screenOffset", &MeteoriteSpawner::m_screenOffset, 0);
	register_property<MeteoriteSpawner, float>("meteoriteInterval", &MeteoriteSpawner::m_meteoriteInterval, 0);
	register_property<MeteoriteSpawner, PoolIntArray>("instanceTimeActivation", &MeteoriteSpawner::m_instanceTimeActivation, PoolIntArray());

	register_method("_ready", &MeteoriteSpawner::_ready);
	register_method("_process", &MeteoriteSpawner::_process);

	register_method("onMeteoriteCollide", &MeteoriteSpawner::onMeteoriteCollide);
	register_method("onGameStarted", &MeteoriteSpawner::onGameStarted);
}

void MeteoriteSpawner::_init()
{
	//Godot::print(String("MeteoriteSpawner::_init"));
}

void MeteoriteSpawner::_ready() {
	// Connect to game start
	GameManager* _manager = GameManager::GetGameManager();
	if (_manager) {
		_manager->connect("game_started", this, "onGameStarted");
	}
}

void MeteoriteSpawner::_process(float delta)
{
	if (m_instances.size() == 0) {
		return;
	}

	m_timeSinceStart += delta;
	m_meteoriteIntervalTimer += delta;

	// Activate meteorites on time
	if (!m_areAllInstancesActive) {
		if (m_instanceTimeActivation[m_activatedInstanceAmount] < m_timeSinceStart) {
			m_activatedInstanceAmount++;
			Godot::print("Activate");

			if (m_activatedInstanceAmount == m_instanceTimeActivation.size()) {
				m_areAllInstancesActive = true;
			}
		}
	}

	// Send meteorite at regular interval
	if (m_meteoriteIntervalTimer > (m_meteoriteInterval / m_activatedInstanceAmount)) {
		//Godot::print("Send");

		for (int _i = 0; _i < m_activatedInstanceAmount; _i++)
		{
			// Activate meteorite
			if (!(as<Meteorite>(m_instances[m_poolIndex]))->getIsActive()) {
				(as<Meteorite>(m_instances[m_poolIndex]))->setIsActive(true);
				Godot::print("Send");

				// Increase pool index
				m_poolIndex++;
				if (m_poolIndex == m_instanceTimeActivation.size()) {
					m_poolIndex = 0;
				}

				// Reset timer
				m_meteoriteIntervalTimer = 0;
				break;
			}
			// If meteorite is not available, try to get the next one
			else {
				m_poolIndex++;
				if (m_poolIndex == m_instanceTimeActivation.size()) {
					m_poolIndex = 0;
				}
			}
		}
	}

	Meteorite* _meteorite;
	for (int _i = 0; _i < m_activatedInstanceAmount; _i++) {
		_meteorite = as<Meteorite>(m_instances[_i]);

		Vector2 _distance = _meteorite->getMaxDistance();
		if (_distance.x > 0) {
			if (_meteorite->get_position().x > _distance.x) {
				setRandomPosition(m_instances[_i], m_timeSinceStart);
			}
		}
		else if (_meteorite->get_position().x < _distance.x) {
			setRandomPosition(m_instances[_i], m_timeSinceStart);
		}
	}

	// --------------------------------


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
	setRandomPosition((Node2D*)p_meteorite, 1);
}

void godot::MeteoriteSpawner::onGameStarted() {
	ResourceLoader *resourceLoader = ResourceLoader::get_singleton();
	m_meteorite = resourceLoader->load("res://GameContent/Gameplay/Meteorite/Meteorite.tscn");

	Node2D* meteoriteNode;
	m_windowSize = get_viewport_rect().size;

	int _rand;

	int _size = m_instanceTimeActivation.size();
	for (int _i = 0; _i < _size; _i++) {
		meteoriteNode = cast_to<Node2D>(m_meteorite->instance());

		// Set different name
		meteoriteNode->set_name("Meteorite " + String(std::to_string(_i).c_str()));

		// Set random position
		meteoriteNode->set_z_index(-100);
		setRandomPosition(meteoriteNode, _i);

		m_instances.push_back(meteoriteNode);

		call_deferred("add_child", meteoriteNode);
		meteoriteNode->connect("collide", this, "onMeteoriteCollide");
	}
}

void MeteoriteSpawner::setRandomPosition(Node2D* p_meteorite, int p_randomHelper)
{
	Vector2 _pos;

	// Set random position
	srand(time(NULL) + (p_randomHelper * 25));
	int _rand = rand() % 10;

	if (_rand > 7.5) {
		_pos.x = (m_windowSize.x / 2) + m_screenOffset;
		_pos.y = rand() % (int)m_windowSize.y - (m_windowSize.y / 2);
	}
	else if (_rand > 5) {
		_pos.x = (m_windowSize.x / -2) - m_screenOffset;
		_pos.y = rand() % (int)m_windowSize.y - (m_windowSize.y / 2);
	}
	else if (_rand > 2.5) {
		_pos.x = rand() % (int)m_windowSize.x - (m_windowSize.x / 2);
		_pos.y = (m_windowSize.y / 2) + m_screenOffset;
	}
	else {
		_pos.x = rand() % (int)m_windowSize.x - (m_windowSize.x / 2);
		_pos.y = (m_windowSize.y / -2) - m_screenOffset;
	}

	p_meteorite->set_position(_pos);
	Meteorite* _meteorite = as<Meteorite>(p_meteorite);
	if (_meteorite) {
		_meteorite->pool();
	}
}
