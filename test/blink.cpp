#include "../include/bcmwrapper.h"
#include <stdio.h>

#define LED_PIN RPI_GPIO_P1_11

int main() {
    
    if (!bcm2835_init()) {
        printf("bcm2835 initialization failed. Are you running as root?\n");
        return 1;
    }

    gpio_pinset(LED_PIN, BCM2835_GPIO_FSEL_OUTP);
	
    while (1) {
        gpio_write(LED_PIN, HIGH);
        bcm2835_delay(500);

        gpio_write(LED_PIN, LOW);
		bcm2835_delay(500);
    }

    bcm2835_close();
    return 0;
}

