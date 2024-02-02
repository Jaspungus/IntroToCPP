#include "Circle.h"

float Circle::CalcArea() {
	return PI * m_radius * m_radius;
}

float Circle::CalcCircum() {
	return 2 * PI * m_radius;
}

Circle::Circle(float a_radius) {
	this->m_radius = a_radius;
}