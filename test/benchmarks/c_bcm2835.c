// 6.95 MHz stable mostly-square wave

#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define GPIO_PIN RPI_V2_GPIO_P1_11

int main() {
    if (!bcm2835_init()) {
        printf("bcm2835_init failed. Are you running as root?\n");
        return 1;
    }

    bcm2835_gpio_fsel(GPIO_PIN, BCM2835_GPIO_FSEL_OUTP);

    while (1) {
        bcm2835_gpio_write(GPIO_PIN, HIGH);
        bcm2835_gpio_write(GPIO_PIN, LOW);
    }

    bcm2835_close();
    return 0;
}
