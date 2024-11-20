#include <bcm2835.h>
#include <stdio.h>

constexpr uint8_t LED_PIN = 17;

int main(){
		
    if(!bcm2835_init()){
        printf("Failed to initialize\n");
        return 1;
    }

    bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_OUTP);

    while(true){
        bcm2835_gpio_write(LED_PIN, HIGH);
        delay(500);

        bcm2835_gpio_write(LED_PIN, LOW);
		delay(500);
    }

    bcm2835_close();
    return 0;
}

