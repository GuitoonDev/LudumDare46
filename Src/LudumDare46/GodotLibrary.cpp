#include "PlayerTest.h"
#include "GameManager.h"
#include "Meteorite.h"
#include "Planet.h"
#include "PlayerController.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);
	register_class<PlayerTest>();
	register_class<Meteorite>();
	register_class<Planet>();
	register_class<GameManager>();
	register_class<PlayerController>();
}