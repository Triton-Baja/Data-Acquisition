#include "../../include/bcmwrapper/bcmwrapper.h"
#include <bcm2835.h>
#include <stdio.h>
#include <signal.h>

constexpr uint8_t BUTTON_PIN = 17;

int main(){

	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}

	gpio_pinmode(BUTTON_PIN, INPUT);
	gpio_setpull(BUTTON_PIN, PULLUP);

	while(true){
		printf("%d\n", gpio_read(BUTTON_PIN));
		delay(250);
	}
	
	bcm2835_close();
	return 0;
}
