#include "../../../include/bcmwrapper/bcmwrapper.h"
#include "../../../include/TM1637/TM1637Display.h"
#include <bits/chrono.h>
#include <cstdint>
#include <cstdio>
#include <bcm2835.h>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <atomic>

constexpr uint8_t DIO_PIN = 27;
constexpr uint8_t CLK_PIN = 22;
constexpr uint8_t BUT_PIN = 26;

std::atomic<bool> running = true;

void runDisplay(){

	TM1637Display display(CLK_PIN, DIO_PIN);
	display.setBrightness(0x0f);

	while(running){
		uint8_t data[4];
		data[0] = display.encodeDigit(4);
		data[1] = display.encodeDigit(5 + rand() % 2);
		data[2] = display.encodeDigit(2 + rand() % 6);
		data[3] = display.encodeDigit(1 + rand() % 7);

		display.setSegments(data);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	std::this_thread::sleep_for(std::chrono::seconds(5));
	printf("runDisplay out of loop\n");
}

int main(){

	srand(time(nullptr));

	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}


	std::thread runDisplayThread(runDisplay);

	gpio_pinmode(BUT_PIN, INPUT);
	gpio_setpull(BUT_PIN, PULLUP);
	delay(200);

	while(gpio_read(BUT_PIN)){
		printf("Hey\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	running = false;
	runDisplayThread.join();


	printf("thread joined\n");

	bcm2835_close();

}
