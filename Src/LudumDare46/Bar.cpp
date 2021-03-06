#include "Bar.h"

using namespace godot;

Bar::Bar() {}
Bar::~Bar() {}

// --------------------------------

void Bar::_register_methods() {
	register_method("_ready", &Bar::_ready);

	register_method("sendBack", &Bar::sendBack);
}

void Bar::_init() {
}

void Bar::_ready() {
	connect("body_entered", this, "sendBack");

	m_animation = cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	m_meteorParryAudio = cast_to<AudioStreamPlayer>(get_node("MeteorParryAudio"));
}

// --------------------------------

void Bar::sendBack(Node * body) {
	GameManager::GetGameManager()->AddPoints(50);
	GameManager::GetGameManager()->ReflectFlash();

	Godot::print("Reflect");

	m_animation->stop();
	m_animation->play(ANIM_REFLECT);

	m_meteorParryAudio->play();
}
