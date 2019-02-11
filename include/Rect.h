#pragma once

struct Rect {
	int x, y, width, height;

	constexpr int left() const noexcept { return x; }
	constexpr int right() const noexcept { return x + width; }
	constexpr int bottom() const noexcept { return y; }
	constexpr int top() const noexcept { return y + height; }
	constexpr bool intersect(const Rect& other) const noexcept;
	constexpr void merge(const Rect& other) noexcept;

	constexpr Rect(int dx, int dy, int dw, int dh) noexcept : x(dx), y(dy), width(dw), height(dh) {}
	Rect crop(int minX, int minY, int maxX, int maxY) const;
};

constexpr bool Rect::intersect(const Rect& other) const noexcept {
	if (other.left() >= right())
		return false;
	if (left() >= other.right())
		return false;
	if (other.bottom() >= top())
		return false;
	return bottom() < top();
}

constexpr void Rect::merge(const Rect& other) noexcept {
	int nx = x;
	int ny = y;
	if ( other.left() < left())
		nx = left();
	if ( other.bottom() < bottom())
		ny = other.bottom();
	if (other.right() > right())
		width = other.right() - nx;
	else
		width = right() - nx;
	if (other.top() > top())
		height = other.top() - ny;
	else
		height = top() - ny;
	x = nx;
	y = ny;
}