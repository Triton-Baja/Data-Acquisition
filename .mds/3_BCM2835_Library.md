# BCM2835 Library
Every Raspberry Pi model has a diffferent version of the [Broadcom chip](https://www.raspberrypi.com/documentation/computers/processors.html), 
BCM2XXX. The Raspberry Pi 4B specifically has the BCM2711 chip. However, the [BCM2835 library](https://www.airspayce.com/mikem/bcm2835/) 
is compatible with all of the different Broadcom chip versions.

## Pinout
<img align="center" src="../.assets/reference/pinout-corrected-1024x605.jpg" width="600" />

As you can see, the Raspberry Pi 4 has 40 pins, which have two different ways for being numbered, the physical pin number, and the bcm number. The bcm2835 library uses the latter when refering to `pin` in their functions.

## Basic bcm2835 functions
Note that we'll be showing you the [function prototypes](https://cplusplus.com/articles/yAqpX9L8/).<br><br>

```C++
int bcm2835_init()
```
This function initializes the library by loading the bcm 2835 device registers. It returns a `0` if it fails and a `1` if it succeeds. It must be called before any other bcm functions.<br><br>

```C++
int bcm2835_close();
```
This function closes the library by deallocating resources. It mist be called at the end of the code.<br><br>

```C++
void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode);
```
This function is used to set a `pin` to an `BCM2835_GPIO_FSEL_OUTP` (output) or `BCM2835_GPIO_FSEL_INPT` (input). In other words, we need to tell the Pi if this pin will be "writing" or "reading". This has to be set before we can use the `pin`<br><br>

```C++
void bcm2835_gpio_write(uint8_t pin, uint8_t on);
```
This function is used to write a `HIGH` or `LOW` value to a `pin`. Here a `HIGH` value represents 3.3v and a `LOW` valueɛrepresents 0v.<br><br>

```C++
uint8_t bcm2835_gpio_lev(uint8_t pin);
```
This function reads `pin` and returns its value, either `HIGH` or `LOW`. Here `HIGH` represents 3.3v and `LOW` represents 0v. **The maximum GPIO input voltage is 3.3v, it cannot handle 5v**.<br><br>

```C++
void bcm2835_gpio_set_pud(uint8_t pin, uint8_t pud);
```
This function sets either a `BCM2835_GPIO_PUD_UP` (pullup) or `BCM2835_GPIO_PUD_DOWN` (pulldown) resistor at `pin`. Read more about pull resistors [here](https://eepower.com/resistor-guide/resistor-applications/pull-up-resistor-pull-down-resistor/).<br><br>

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
