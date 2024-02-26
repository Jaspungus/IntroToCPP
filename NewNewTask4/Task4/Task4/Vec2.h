#pragma once
struct Vec2I
{
public:
	int X;
	int Y;

public:
	Vec2I();
	Vec2I(const int x, const int y);
	Vec2I(const Vec2I& a_vec2);

public:
	float Magnitude() const;
	float MagnitudeSquared() const;
	float Distance(Vec2I dest) const;
	float DistanceSquared(Vec2I dest) const;

public:
	static Vec2I Zero();
	static Vec2I One();
	static Vec2I Up();
	static Vec2I Down();
	static Vec2I Left();
	static Vec2I Right();

public:
	bool operator == (const Vec2I& other);
	bool operator != (const Vec2I& other);

	Vec2I& operator = (const Vec2I& other);

	const Vec2I operator+(const Vec2I& other) const;
	Vec2I& operator+=(const Vec2I& other);

	const Vec2I operator-(const Vec2I& other) const;
	Vec2I& operator-=(const Vec2I& other);

	const Vec2I operator*(const int& other) const;
	Vec2I& operator*=(const int& other);


};

