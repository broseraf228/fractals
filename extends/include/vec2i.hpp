#pragma once

inline int inr(int p, int s);

struct Vec2 {
public:
	Vec2(int scallar = 0);
	Vec2(int x, int y);

	int x, y;

	Vec2 operator+(const Vec2&);
	Vec2& operator+=(const Vec2&);
	Vec2 operator-(const Vec2&);
	Vec2 operator*(float);
	Vec2 operator/(float);
	bool operator==(const Vec2&);

	static Vec2* viev_directions_8;
	static Vec2* viev_directions_4;
};