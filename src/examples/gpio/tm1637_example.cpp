#include "../../include/TM1637/TM1637Display.h"
#include "../../include/bcmwrapper/bcmwrapper.h"
#include <bcm2835.h>

constexpr uint8_t CLK_PIN = 16;
constexpr uint8_t DIO_PIN = 20;
constexpr uint8_t pos = 21;

int main(){

	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}

	gpio_pinmode(pos, OUTPUT);
	gpio_write(pos, HIGH);

	TM1637Display display(CLK_PIN, DIO_PIN);


	while(true){
		uint8_t data[4];
		display.setBrightness(0x0f);

		data[0] = display.encodeDigit(0);
		data[1] = display.encodeDigit(1);
		data[2] = display.encodeDigit(2);
		data[3] = display.encodeDigit(3);
		display.setSegments(data);

		data[0] = display.encodeDigit(4);
		data[1] = display.encodeDigit(5);
		data[2] = display.encodeDigit(6);
		data[3] = display.encodeDigit(7);
		display.setSegments(data);
	}

	bcm2835_close();

}
