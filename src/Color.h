#pragma once


class Color {
	public:
		unsigned int r, g, b;
		Color(unsigned int dr, unsigned int dg, unsigned int db) {
			r = dr;
			g = dg;
			b = db;
		}

		// rrrrrggggggbbbbb
		unsigned char get16bitHigh() {
			return ((r & 248) | g >> 5);
		}
		// rrrrrggggggbbbbb
		unsigned char get16bitLow() {
			return ((g & 28) << 3 | b >> 3);
		}

		static Color BLACK;
};
