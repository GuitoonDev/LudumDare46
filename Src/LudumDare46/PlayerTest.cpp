#include "PlayerTest.h"

using namespace godot;

void PlayerTest::_register_methods() 
{
	register_method((char*)"_process", &PlayerTest::_process);
}

void PlayerTest::_init()
{
	Godot::print(String("Pouette"));
}

void PlayerTest::_process(float delta)
{
}

PlayerTest::PlayerTest()
{
}

PlayerTest::~PlayerTest()
{
}
