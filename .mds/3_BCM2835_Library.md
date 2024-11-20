# BCM2835 Library
Every Raspberry Pi model has a diffferent version of the [Broadcom chip](https://www.raspberrypi.com/documentation/computers/processors.html), 
BCM2XXX. The Raspberry Pi 4B specifically has the BCM2711 chip. However, the [BCM2835 library](https://www.airspayce.com/mikem/bcm2835/) 
is compatible with all of the different Broadcom chip versions.

## Pinout
<div align="center>
  img<src=../.assets/reference/pinout-corrected-1024x605.jpg width="600" />
</div>

## Basic bcm2835 functions
Note that we'll be showing you the [function prototypes](https://cplusplus.com/articles/yAqpX9L8/) and that the `pin`s are as numbered on the BCM<br><br>

```C++
void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode);
```
This function is used to set a pin to an `BCM2835_GPIO_FSEL_OUTP` (output) or `BCM2835_GPIO_FSEL_INPT` (input) 
