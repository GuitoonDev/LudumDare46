#include "PlayerTest.h"

using namespace godot;

void PlayerTest::_register_methods() 
{
	register_method((char*)"_process", &PlayerTest::_process);
}

void PlayerTest::_process(float delta)
{
	Godot::print(String("Pouette"));
}

PlayerTest::PlayerTest()
{
}

PlayerTest::~PlayerTest()
{
}
