#include "PlayerTest.h"

using namespace godot;

void PlayerTest::_register_methods() 
{
	register_method((char*)"_process", &PlayerTest::_process);
}

void PlayerTest::_init()
{
	set_position(get_position() + Vector2(10.0, 0.0));
}

void PlayerTest::_process(float delta)
{
	Godot::print(String("Pouette"));
	motion = Vector2(2000.0, 0.0);
	set_position(get_position() + Vector2(1.0, 0.0));

	//move_and_slide(motion);
}

PlayerTest::PlayerTest() : motion(Vector2(0,0))
{
}

PlayerTest::~PlayerTest()
{
}
