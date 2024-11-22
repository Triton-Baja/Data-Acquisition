# bcmwrapper library
While the bcm2835 library works perfectly, some of the function names and constants are unnecessary long and hard to remember. Let's not do that. We'll use a [wrapper library]([https://github.com/Triton-Baja/Data-Acquisition/blob/main/include/bcmwrapper/bcmwrapper.h](https://en.wikipedia.org/wiki/Wrapper_library)).

## bcmwrapper.h
```C++
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
```
As you can see, the wrapper isn't really doing much. Mostly just "renaming" the original bcm2835 functions to shorter, and more comprehensible names. It does this by directly calling the original bcm2835 functions and direclty passing its parameters.

## Pinout
<img align="center" src="../.assets/reference/pinout-corrected-1024x605.jpg" width="600" />

As shown in the diagram, the Raspberry Pi 4 has 40 pins, which have two different ways for being numbered, the physical pin number, and the bcm number. The bcm2835 library uses the latter when refering to `pin` in their functions.

## Basic bcmwrapper functions
Note that we'll be showing you the [function prototypes](https://cplusplus.com/articles/yAqpX9L8/).<br><br>

```C++
int bcm2835_init()
```
This function initializes the library by loading the bcm 2835 device registers. It returns a `0` if it fails and a `1` if it succeeds. It must be called before any other bcm functions.<br><br>

```C++
int bcm2835_close();
```
This function closes the library by deallocating resources. It returns a `0` if it fails and a `1` if it succeeds. It must be called at the end of the code.<br><br>

```C++
void gpio_pinmode(uint8_t pin, uint8_t mode);
```
This function is used to set a `pin` to an `OUTPUT` or `INPUT`. In other words, we need to tell the Pi if this pin will be "writing" or "reading". This has to be set before we can use the `pin`<br><br>

```C++
void gpio_write(uint8_t pin, uint8_t value);
```
This function is used to write a `HIGH` or `LOW` value to a `pin`. Here a `HIGH` value represents 3.3v and a `LOW` valueɛrepresents 0v.<br><br>

```C++
uint8_t gpio_read(uint8_t pin);
```
This function reads `pin` and returns its value, either `HIGH` or `LOW`. Here `HIGH` represents 3.3v and `LOW` represents 0v. **The maximum GPIO input voltage is 3.3v, it cannot handle 5v**.<br><br>

```C++
void gpio_setpull(uint8_t pin, uint8_t pull);
```
This function sets either a `PULLUP` or `PULLDOWN` resistor at `pin`. Read more about pull resistors [here](https://eepower.com/resistor-guide/resistor-applications/pull-up-resistor-pull-down-resistor/).<br><br>

## Skeleton code
This is a template of how the code might look like

```C++
#include <bcmwrapper.h>
#include <cstdio>

int main(){

    if(!bcm2835_init()){
        printf("Failed to initialize"\n);
        return 1;
    }


    // your code


    bcm2835_close();
    return 0;
}
```
