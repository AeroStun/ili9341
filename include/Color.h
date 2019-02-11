#pragma once


struct Color {
	unsigned int r, g, b;

	constexpr unsigned char get16bitHigh() const noexcept;
	constexpr auto get16bitLow() const noexcept;
};

constexpr unsigned char Color::get16bitHigh() const noexcept {
  return static_cast<unsigned char>((r & 248u) | g >> 5u);
}
constexpr auto Color::get16bitLow() const noexcept {
  return static_cast<unsigned char>((g & 28u) << 3u | b >> 3u);
}


namespace Colors {
	constexpr Color BLACK = {0x00, 0x00, 0x00};
	constexpr Color WHITE = {0xFF, 0xFF, 0xFF};
	constexpr Color RED   = {0xFF, 0x00, 0x00};
	constexpr Color GREEN = {0x00, 0xFF, 0x00};
  constexpr Color BLUE  = {0x00, 0x00, 0xFF};
};
