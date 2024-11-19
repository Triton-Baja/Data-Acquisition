#include "../../include/bcmwrapper/bcmwrapper.h"
#include <bcm2835.h>
#include <stdio.h>
#include <signal.h>

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

