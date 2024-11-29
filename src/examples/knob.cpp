#include "../../include/bcmwrapper/bcmwrapper.h"
#include <cstdio>

constexpr uint8_t CLK_PIN = 27;
constexpr uint8_t DT_PIN = 17;

int main(){
	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}

	gpio_pinmode(CLK_PIN, INPUT);
	gpio_pinmode(DT_PIN, INPUT);

	uint8_t previousCLK = gpio_read(CLK_PIN);
	uint8_t currentCLK;

	int position = 0;

	while(true){

		currentCLK = gpio_read(CLK_PIN);

		if(currentCLK && !previousCLK){
			if(!gpio_read(DT_PIN))
				position++;

			else 
				position--;
		}

		previousCLK = currentCLK;
		printf("Position: %d\n", position);
		delay(1);
	}

	bcm2835_close();
}
