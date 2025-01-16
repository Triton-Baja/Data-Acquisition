#include "../../include/bcmwrapper/bcmwrapper.h"
#include <bcm2835.h>
#include <stdio.h>

constexpr uint8_t LED_PIN = 17;
constexpr uint8_t BUTTON_PIN = 22;

int main(){

	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}

	gpio_pinmode(LED_PIN, OUTPUT);
	gpio_pinmode(BUTTON_PIN, INPUT);
	
	gpio_setpull(BUTTON_PIN, PULLUP);

	while(true){
		uint8_t button_status = !gpio_read(BUTTON_PIN);
		gpio_write(LED_PIN, button_status);

		printf("The LED is %d\n", button_status);
	}
	
	bcm2835_close();
	return 0;
}
