## Shutdown Button
As we are aware, just like with any other computer, we need to shutdown the Pi before we can unplug it and cut the power off. This is fairly easy given that we have access to its terminal. 
However, as it might be the case with the driver, there might not be a terminal. In this case a physical button would be more useful. We can easily set this up

```
sudo nano /boot/firmware/config.txt
```

Let's jump to the end of the file and add
```
dtoverlay=gpio-shutdown, gpio_pin=X,
```

For instance, here we would connect the button between GND and GPIO 17
```
dtoverlay=gpio-shutdown, gpio_pin=17,
```
