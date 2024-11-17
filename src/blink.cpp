#include "../include/bcmwrapper/bcmwrapper.h"
#include <stdio.h>
#include <signal.h>

#define LED_PIN RPI_GPIO_P1_11

void handle_signal(int signal){
	printf("\nTerminating from signal %d\n", signal);

	bcm2835_close();
	printf("bcm2835 closed\n");

	exit(0);
}

int main() {

	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
    
		
    if (!bcm2835_init()) {
        printf("bcm2835 initialization failed. Are you running as root?\n");
        return 1;
    }

    gpio_pinmode(LED_PIN, BCM2835_GPIO_FSEL_OUTP);

    while (1) {
	//	printf("blinking...\n");
        gpio_write(LED_PIN, HIGH);
        bcm2835_delay(500);

        gpio_write(LED_PIN, LOW);
		bcm2835_delay(500);
    }

    bcm2835_close();
    return 0;
}

