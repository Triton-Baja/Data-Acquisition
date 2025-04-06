#include "../../../include/bcmwrapper/bcmwrapper.h"
#include "../../../include/TM1637/TM1637Display.h"
#include <bits/chrono.h>
#include <cstdint>
#include <cstdio>
#include <bcm2835.h>
#include <random>
#include <ctime>
#include <chrono>

constexpr uint8_t DIO_PIN = 27;
constexpr uint8_t CLK_PIN = 22;

void runDisplay(TM1637Display &display){
	display.setBrightness(0x0f);

	auto start = std::chrono::steady_clock::now();
	while(true){
		auto current = std::chrono::steady_clock::now();

		printf("Hey\n");

		if(std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count() > 1000){
			uint8_t data[4];
			data[0] = display.encodeDigit(4);
			data[1] = display.encodeDigit(5 + rand() % 2);
			data[2] = display.encodeDigit(2 + rand() % 6);
			data[3] = display.encodeDigit(1 + rand() % 7);

			display.setSegments(data);
			start = current;
		}
	}
}

int main(){

	srand(time(nullptr));

	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}


	TM1637Display display(CLK_PIN, DIO_PIN);

	runDisplay(display);

	bcm2835_close();

}
