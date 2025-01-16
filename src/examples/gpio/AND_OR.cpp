#include "../../include/bcmwrapper/bcmwrapper.h"

constexpr uint8_t SWITCH_PIN = 26;
constexpr uint8_t BUTTON1_PIN = 27;
constexpr uint8_t BUTTON2_PIN = 22;

constexpr uint8_t LED_PIN = 17;

int main(){
	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 0;
	}


	gpio_pinmode(SWITCH_PIN, INPUT);
	gpio_pinmode(BUTTON1_PIN, INPUT);
	gpio_pinmode(BUTTON2_PIN, INPUT);
	gpio_pinmode(LED_PIN, OUTPUT);


	gpio_setpull(SWITCH_PIN, PULLUP);
	gpio_setpull(BUTTON1_PIN, PULLUP);
	gpio_setpull(BUTTON2_PIN, PULLUP);


	while(true){
		if(gpio_read(SWITCH_PIN)){
			gpio_write(LED_PIN, !gpio_read(BUTTON1_PIN) || !gpio_read(BUTTON2_PIN));
		}

		else{
			gpio_write(LED_PIN, !gpio_read(BUTTON1_PIN) && !gpio_read(BUTTON2_PIN));
		}
	}

	bcm2835_close();
	return 0;
}
