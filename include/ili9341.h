#pragma once

#include <vector>
#include <span> // TODO C++2a: remove include/impl/span
#include "utils.hpp"
#include "Rect.h"
#include "Color.h"

class ili9341 {
public:
	ili9341();
	~ili9341() noexcept;
	void test();
	void setBrightness(unsigned char lightLevel);

	void adressSet( int x, int y, int w, int h);
	void writeToBuffer(const Rect &rect, std::span<unsigned char> writeBuffer);
	void shutdown();
	static constexpr auto WIDTH  = 320;
	static constexpr auto HEIGHT = 240;

private:
	void LCD_Write_DATA(unsigned char data);
	void LCD_Write_COM(unsigned char com);


	static constexpr auto DC   = 4_uc;// # gpio pin 16 = wiringpi no. 4 (BCM 23)
	static constexpr auto RST  = 5_uc;// # gpio pin 18 = wiringpi no. 5 (BCM 24)
	static constexpr auto LED  = 1_uc;// # gpio pin 12 = wiringpi no. 1 (BCM 18)

	//# SPI connection, these are only for documentation...
	static constexpr auto SCE  = 10_uc;// # gpio pin 24 = wiringpi no. 10 (CE0 BCM 8)
	static constexpr auto SCLK = 14_uc;// # gpio pin 23 = wiringpi no. 14 (SCLK BCM 11)
	static constexpr auto DIN  = 12_uc;// # gpio pin 19 = wiringpi no. 12 (MOSI BCM 10)

	static constexpr auto spiChannel = 0;
	static constexpr auto spiSpeed = 32000000;


	int fileDescriptor;
};


