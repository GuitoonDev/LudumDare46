#include "Bar.h"

using namespace godot;

Bar::Bar() {}
Bar::~Bar() {}

// --------------------------------

void Bar::_register_methods() {
	register_method("_ready", &Bar::_ready);

	register_method("sendBack", &Bar::sendBack);

	register_property<Bar, float>("Width", &Bar::setWidth, &Bar::getWidth, 0);
}

void Bar::_init() {
	Godot::print("Bar Init");
}

void Bar::_ready() {
	connect("body_entered", this, "sendBack");

	///set_scale(Vector2(m_width, get_scale().y));
	Godot::print("Bar Ready");
}

// --------------------------------

float Bar::getWidth() {
	return m_width;
}

void Bar::setWidth(float p_width) {
	if (p_width > 0) {
		m_width = p_width;
	}
	else {
		m_width = 0;
	}
}

// --------------------------------

void Bar::sendBack(Node * body) {
	GameManager::GetGameManager()->AddPoints(50);

	Godot::print("Send Back!");
}
