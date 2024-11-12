#ifndef BCMWRAPPER
#define BCMWRAPPER

#include <bcm2835.h>
#include <cstdint>
#include <sys/types.h>

inline void gpio_pinset(uint8_t pin, uint8_t mode){
	bcm2835_gpio_fsel(pin, mode);
}

inline void gpio_write(uint8_t pin, uint8_t value){
	bcm2835_gpio_write(pin, value);
}


#endif
