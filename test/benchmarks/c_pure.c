// 17/35 MHz unstable non-square wave

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

#define GPIO_BASE       0xFE200000  // Base address for GPIO on Pi 4
#define BLOCK_SIZE      4096        // Memory block size

#define INP_GPIO(g) *(gpio + ((g)/10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g)/10)) |=  (1 << (((g) % 10) * 3))

#define GPIO_SET *(gpio + 7)    // Set GPIO pin high
#define GPIO_CLR *(gpio + 10)   // Clear GPIO pin (set low)

#define GPIO_PIN 17

volatile unsigned int *gpio;

void setup_gpio() {
    int mem_fd;
    void *gpio_map;

    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        perror("open");
        exit(-1);
    }

    // Map GPIO memory
    gpio_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        GPIO_BASE
    );

    close(mem_fd);

    if (gpio_map == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }

    gpio = (volatile unsigned int *)gpio_map;
}

int main() {
    setup_gpio();

    INP_GPIO(GPIO_PIN);
    OUT_GPIO(GPIO_PIN);

    while (1) {
        GPIO_SET = 1 << GPIO_PIN;
        GPIO_CLR = 1 << GPIO_PIN;
    }

    return 0;
}

