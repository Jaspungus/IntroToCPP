#include "Vec2.h"
#include <cmath>

Vec2I::Vec2I() {
	X = 0;
	Y = 0;
}

Vec2I::Vec2I(const int x, const int y) {
	X = x;
	Y = y;
}

Vec2I::Vec2I(const Vec2I& a_vec2) {
	X = a_vec2.X;
	Y = a_vec2.Y;
}

Vec2I Vec2I::Zero() {
	return Vec2I(0, 0);
}

Vec2I Vec2I::One() {
	return Vec2I(1, 1);
}

Vec2I Vec2I::Up() {
	return Vec2I(0, -1);
}

Vec2I Vec2I::Down() {
	return Vec2I(0, 1);
}

Vec2I Vec2I::Left() {
	return Vec2I(-1, 0);
}

Vec2I Vec2I::Right() {
	return Vec2I(1, 0);
}

const float Vec2I::Magnitude() const {
	return std::sqrtf(pow((float)X, 2) + pow((float)Y, 2));
}

const float Vec2I::MagnitudeSquared() const {
	return pow((float)X, 2) + pow((float)Y, 2);
}


const float Vec2I::Distance(const Vec2I dest) const {
	return (*this - dest).Magnitude();
}

const float Vec2I::DistanceSquared(const Vec2I dest) const {
	return (*this - dest).MagnitudeSquared();
}

const Vec2I Vec2I::Perpindicular() const {
	return Vec2I(Y, X);
}

const int Vec2I::DotProduct(const Vec2I& other) const {
	return (X * other.X) + (Y * other.Y);
}


bool Vec2I::operator==(const Vec2I& other) const
{
	return (X == other.X && Y == other.Y);
}

bool Vec2I::operator!=(const Vec2I& other) const
{
	if (!(X == other.X && Y == other.Y)) return true;
	return false;
}

Vec2I& Vec2I::operator=(const Vec2I& other)
{
	X = other.X;
	Y = other.Y;
	return *this;
}

const Vec2I Vec2I::operator+(const Vec2I& other) const
{
	return Vec2I(X + other.X, Y + other.Y);
}

Vec2I& Vec2I::operator+=(const Vec2I& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

const Vec2I Vec2I::operator-(const Vec2I& other) const
{
	return Vec2I(X - other.X, Y - other.Y);
}

Vec2I& Vec2I::operator-=(const Vec2I& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}



const Vec2I Vec2I::operator*(const int& other) const
{
	return Vec2I(X * other, Y * other);
}

Vec2I& Vec2I::operator*=(const  int& other)
{
	X *= other;
	Y *= other;
	return *this;
}

const Vec2I Vec2I::operator-() const
{
	return Vec2I(-X, -Y);
}



