#include <iostream>
#include "BackBuffer.h"

void BackBuffer::clearScreen() {
	fillBox(Rect(0, 0, ili9341::WIDTH, ili9341::HEIGHT), Colors::BLACK);
}

void BackBuffer::flush() {
	dirtyRects.clear();
	dirtyRects.emplace_back(Rect{0, 0, ili9341::WIDTH - 1, ili9341::HEIGHT - 1});

	for(const auto& e : dirtyRects) {
		//copy bb to wb
		auto index = 0;
		
		//build up write buffer
		//this is draw order dependent
		//x is reversed
		for (auto dx = e.width - 1; dx >= 0; --dx) {
			for (auto dy = 0; dy < e.height; ++dy) {

				const auto to = index * 2;  //two bytes per pixel

				//here we turn it around since i mounted it wrong
				if (const auto bx = e.x + dx, by = e.y + dy;
						bx >= 0 && bx < ili9341::WIDTH &&
						by >= 0 && by < ili9341::HEIGHT) {
						writeBuffer[to]     = backBuffer[bx][by][0];
						writeBuffer[to + 1] = backBuffer[bx][by][1];
				}
				++index;
			}
		}

		
		screen.writeToBuffer(e, writeBuffer);
	}
	
	std::cout << "drew " << dirtyRects.size() << std::endl;
	dirtyRects.clear();
}

void BackBuffer::fillBox(const Rect& screen, const Color& fill){
	const unsigned char bch = fill.get16bitHigh();
	const unsigned char bcl = fill.get16bitLow();

	const Rect onScreen = screen.crop(0, 0, ili9341::WIDTH, ili9341::HEIGHT);

	for (auto dx = onScreen.x; dx < onScreen.x + onScreen.width; ++dx) {
		for (auto dy = onScreen.y; dy < onScreen.y + onScreen.height; ++dy)
			backBuffer[dx][dy] = {bch, bcl};
	}

	for(auto& e : dirtyRects){
		if(e.intersect(onScreen)){
			e.merge(onScreen);
			return;
		}
	}

	dirtyRects.push_back(onScreen);
}
