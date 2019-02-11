#include <cstdlib>
#include <iostream>
#include <random>
#include <unistd.h>
#include <wiringPi.h>
#include "BackBuffer.h"

constexpr auto CE1 = 11;

int main(){
	std::ios::sync_with_stdio(false);
	std::cout << "Started up" << std::endl;
	pinMode(CE1, OUTPUT);
	digitalWrite(CE1, 0);


	ili9341 lcd{};
	BackBuffer inst{lcd};

	lcd.setBrightness(255);

	lcd.test();
	sleep(3);

	inst.clearScreen();
	std::cout << "Before flush" << std::endl;
	inst.flush();
	std::cout << "After flush" << std::endl;
	sleep(1);




	//inst.test();
	inst.fillBox(Rect{ili9341::WIDTH / 2 - 5, ili9341::HEIGHT / 2 - 5, 30, 12}, Colors::WHITE);

	inst.fillBox(Rect{0, 0, 25, 50}, Color{255, 	0, 		0});
	inst.fillBox(Rect{ili9341::WIDTH - 25, 0, 25, 50}, 	Color{0, 		255, 	0});
	inst.fillBox(Rect{0, ili9341::HEIGHT - 50, 25, 50}, 	Color{0, 		0, 		255});
	inst.fillBox(Rect{ili9341::WIDTH - 25, ili9341::HEIGHT - 50, 25, 50}, Color{255, 	0, 		255});



	inst.fillBox(Rect{-25, ili9341::HEIGHT / 2 - 25, 50, 50}, Colors::WHITE);
	inst.fillBox(Rect(ili9341::WIDTH - 25, ili9341::HEIGHT / 2 - 25, 50, 50), Colors::WHITE);
	inst.fillBox(Rect(ili9341::WIDTH / 2 - 25, -25, 50, 50), Colors::WHITE);
	inst.fillBox(Rect(ili9341::WIDTH / 2 - 25, ili9341::HEIGHT - 25, 50, 50), Colors::WHITE);

	inst.flush();
	sleep(1);
	std::cout << "Before \n";
	std::default_random_engine eng{std::random_device{}()};
	std::uniform_int_distribution random_320{0, 320};
	std::uniform_int_distribution random_byte{0, 255};
	std::uniform_int_distribution random_240{0, 240};
	const auto rand_320 = [&] () -> int {return random_320(eng);};
	const auto rand_byte = [&] () -> unsigned {return static_cast<unsigned>(random_byte(eng));};
	const auto rand_240 = [&] () -> int {return random_240(eng);};

	inst.clearScreen();
	for (auto i = 0u; i < 60; ++i) {
		const Color col{rand_byte(), rand_byte(), rand_byte()};
		for (auto j = 0u; j < 16; ++j)
			inst.fillBox({rand_320(), rand_240(), rand_320(), rand_240()}, col);

		inst.flush();

		//sleep(1);
		//inst.clearScreen();
		//inst.flush();
		//sleep(1);
		//std::cout << "Flushed Some pixels\n";
	}

	sleep(3);
	std::cout << "Sleep" << std::endl;

	lcd.shutdown();
	std::cout << "no brightp" << std::endl;
	lcd.setBrightness(0);

}
