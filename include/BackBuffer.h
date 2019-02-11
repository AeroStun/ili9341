#pragma once

#include <array>
#include <vector>
#include "Rect.h"
#include "Color.h"
#include "ili9341.h"

using FBuffer = std::array<std::array<unsigned char, ili9341::WIDTH>, ili9341::HEIGHT>;

class BackBuffer {
public:
	inline explicit BackBuffer(ili9341& lcd) noexcept : screen(lcd){} //TODO C++2a: use constexpr instead of inline
	void clearScreen();
	void fillBox(const Rect& screen, const Color& fill);
	void flush();
private:
	static constexpr auto buffer_size = ili9341::WIDTH * ili9341::HEIGHT * 2; //two bytes per pixel
	std::vector<Rect> dirtyRects{};
	std::array<FBuffer, 2> backBuffer{};
	std::array<unsigned char, buffer_size> writeBuffer{0};
	ili9341& screen;
};
