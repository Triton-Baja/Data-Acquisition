#ifndef BCMWRAPPER
#define BCMWRAPPER

#include <bcm2835.h>
#include <cstdint>
#include <sys/types.h>

constexpr uint8_t OUTPUT	= BCM2835_GPIO_FSEL_OUTP;
constexpr uint8_t INPUT		= BCM2835_GPIO_FSEL_INPT;
constexpr uint8_t PULLUP	= BCM2835_GPIO_PUD_UP;
constexpr uint8_t PULLDOWN	= BCM2835_GPIO_PUD_DOWN;

inline void gpio_pinmode(uint8_t pin, uint8_t mode){
	bcm2835_gpio_fsel(pin, mode);
}

inline void gpio_write(uint8_t pin, uint8_t value){
	bcm2835_gpio_write(pin, value);
}

inline uint8_t gpio_read(uint8_t pin){
	return bcm2835_gpio_lev(pin);
}

inline void gpio_setpull(uint8_t pin, uint8_t pull){
	bcm2835_gpio_set_pud(pin, pull);
}


#endif
