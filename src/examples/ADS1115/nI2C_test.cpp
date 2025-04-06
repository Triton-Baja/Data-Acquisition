#include <bcm2835.h>
#include <iostream>

#define I2C_ADDR  0x20  // Replace with your device's I2C address

int main() {
    if (!bcm2835_init()) {
        std::cerr << "bcm2835_init failed. Are you running as root?\n";
        return 1;
    }

    if (!bcm2835_i2c_begin()) {
        std::cerr << "bcm2835_i2c_begin failed.\n";
        return 1;
    }

    bcm2835_i2c_setSlaveAddress(I2C_ADDR);
    bcm2835_i2c_set_baudrate(100000);  // 100 kHz

    // --- Write one byte to register 0x00 ---
    char write_buffer[2] = {0x00, 0x01};  // register 0x00, value 0x01
    if (bcm2835_i2c_write(write_buffer, 2) != BCM2835_I2C_REASON_OK) {
        std::cerr << "I2C write failed\n";
    }

    bcm2835_delay(10); // Optional short delay

    // --- Read one byte from register 0x00 ---
    char reg = 0x00;
    bcm2835_i2c_write(&reg, 1); // Tell device which register to read
    char read_buffer[1];
    if (bcm2835_i2c_read(read_buffer, 1) != BCM2835_I2C_REASON_OK) {
        std::cerr << "I2C read failed\n";
    } else {
        std::cout << "Read value: 0x" << std::hex << (int)read_buffer[0] << "\n";
    }

    bcm2835_i2c_end();
    bcm2835_close();

    return 0;
}
