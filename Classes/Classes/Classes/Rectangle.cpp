#include "Rectangle.h"

float Rectangle::CalcArea() {
	return m_width * m_height;
}

float Rectangle::CalcPerimeter() {
	return 2 * (m_width + m_height);
}