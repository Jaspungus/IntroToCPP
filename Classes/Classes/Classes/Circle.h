#pragma once
class Circle
{
private:
	float m_radius;
public:
	const float PI = 3.14159265359f;

	float CalcArea();
	float CalcCircum();

	Circle(float a_radius);
};

