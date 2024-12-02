# Example Code
Collection of code examples using the bcmwrapper

## blink.cpp
Blink an LED. Half a second on, half a second off

```C++
#include "../../include/bcmwrapper/bcmwrapper.h"
#include <bcm2835.h>
#include <stdio.h>

constexpr uint8_t LED_PIN = 17;

int main(){
		
    if(!bcm2835_init()){
        printf("Failed to initialize\n");
        return 1;
    }

    gpio_pinmode(LED_PIN, OUTPUT);

    while(true){
        gpio_write(LED_PIN, HIGH);
        delay(500);

        gpio_write(LED_PIN, LOW);
		delay(500);
    }

    bcm2835_close();
    return 0;
}
```

## input.cpp
Print the state (1 or 0) of a button

```C++
#include "../../include/bcmwrapper/bcmwrapper.h"
#include <bcm2835.h>
#include <stdio.h>

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
```

## led_with_input.cpp
Turn LED on when button is pressed

```C++
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
```

## AND_OR.cpp
Depending on the switch state, use two buttons as AND/OR gates to turn on an LED

```C++
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
		if(gpio_read(SWITCH_PIN))
			gpio_write(LED_PIN, !gpio_read(BUTTON1_PIN) || !gpio_read(BUTTON2_PIN));

		else
			gpio_write(LED_PIN, !gpio_read(BUTTON1_PIN) && !gpio_read(BUTTON2_PIN));
	}

	bcm2835_close();
	return 0;
}
```

## knob.cpp
Track angular position of [rotatory encoder](https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/)

```C++
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
```
