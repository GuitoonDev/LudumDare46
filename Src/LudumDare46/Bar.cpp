#include "Bar.h"

using namespace godot;

Bar::Bar() {}
Bar::~Bar() {}

// --------------------------------

void Bar::_register_methods() {
	register_method("_ready", &Bar::_ready);

	register_property<Bar, float>("Width", &Bar::setWidth, &Bar::getWidth, 0);
}

void Bar::_init() {
	Godot::print("Bar Init");
}

void Bar::_ready() {
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
