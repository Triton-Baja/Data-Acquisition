#include <stdio.h>
#include <bcm2835.h>

#define ADS1115_ADDRESS 0X48

#define CONFIG_OS_NO_EFFECT     (0 << 15)
#define CONFIG_OS_SINGLE        (1 << 15)

#define CONFIG_MUX_AIN0_AIN1    (0 << 12)
#define CONFIG_MUX_AIN1_AIN3    (1 << 12)
#define CONFIG_MUX_AIN2_AIN3    (2 << 12)
#define CONFIG_MUX_AIN3_AIN3    (3 << 12)

#define CONFIG_MUX_AIN0_GND     (4 << 12)
#define CONFIG_MUX_AIN1_GND     (5 << 12)
#define CONFIG_MUX_AIN2_GND     (6 << 12)
#define CONFIG_MUX_AIN3_GND     (7 << 12)

#define CONFIG_PGA_6_144V       (0 << 9)
#define CONFIG_PGA_4_096V       (1 << 9)
#define CONFIG_PGA_2_048V       (2 << 9)
#define CONFIG_PGA_1_024V       (3 << 9)
#define CONFIG_PGA_0_512V       (4 << 9)
#define CONFIG_PGA_0_256V       (5 << 9)
// #define CONFIG_PGA_0_256V   (6 << 9) repeated for some reason
// #define CONFIG_PGA_0_256V   (7 << 9)

#define CONFIG_MODE_CONTINUOUS  (0 << 8)
#define CONFIG_MODE_SINGLE      (1 << 8)

#define CONFIG_DR_8SPS          (0 << 5)
#define CONFIG_DR_16SPS         (1 << 5)
#define CONFIG_DR_32SPS         (2 << 5)
#define CONFIG_DR_64SPS         (3 << 5)
#define CONFIG_DR_128SPS        (4 << 5)
#define CONFIG_DR_250SPS        (5 << 5)
#define CONFIG_DR_475SPS        (6 << 5)
#define CONFIG_DR_860SPS        (7 << 5)

#define CONFIG_COMP_MODE_TRAD   (0 << 4)
#define CONFIG_COMP_MODE_WINDOW (1 << 4)

#define CONFIG_COMP_POL_LOW     (0 << 3)
#define CONFIG_COMP_POL_HIGH    (1 << 3)

#define CONFIG_COMP_NON_LAT     (0 << 2)
#define CONFIG_COMP_LAT         (1 << 2)

#define CONFIG_COMP_QUE_ASRT1   (0 << 0)
#define CONFIG_COMP_QUE_ASRT2   (1 << 0)
#define CONFIG_COMP_QUE_ASRT3   (2 << 0)
#define CONFIG_COMP_QUE_DIS     (3 << 0)


double readVoltage(const uint16_t config){
    char configData[4];

    configData[0] = 0x01;
    configData[1] = static_cast<char>(config >> 8);
    configData[2] = static_cast<char>(config);
    configData[3] = 0x00;

    bcm2835_i2c_write(configData, 3);
    delay(10);

    bcm2835_i2c_write(&configData[3], 1);

    char readingSplit[2];
    bcm2835_i2c_read(readingSplit, 2);

    // 1010111000000000
    // 0000000001010101

    // 1010111001010101

    int16_t reading = static_cast<int16_t>((readingSplit[0] << 8) | readingSplit[1]);
    double voltage = -1;
    uint16_t voltageBits = config & (7 << 9);

    if(voltageBits == CONFIG_PGA_6_144V)
        voltage = 32768.0 * 6.144 / reading;

    else if(voltageBits == CONFIG_PGA_4_096V)
        voltage = 32768.0 * 4.096 / reading;

    else if(voltageBits == CONFIG_PGA_6_144V)
        voltage = 32768.0 * 6.144 / reading;

    return static_cast<double>(reading);

}

int main(){

    if(!bcm2835_init()){
        printf("Failed to initialize\n");
        return 1;
    }

	if(!bcm2835_i2c_begin()){
		printf("Failed to initialize I2C\nAre you running as root (sudo)?\n");
		return 2;
	}

    bcm2835_i2c_setSlaveAddress(ADS1115_ADDRESS);
    bcm2835_i2c_set_baudrate(100000);

    while(true){
        double voltage = readVoltage(CONFIG_OS_SINGLE | CONFIG_MUX_AIN2_GND | CONFIG_PGA_6_144V | CONFIG_MODE_CONTINUOUS |
            CONFIG_DR_128SPS | CONFIG_COMP_POL_LOW | CONFIG_COMP_NON_LAT | CONFIG_COMP_QUE_DIS);
        printf("%f\n", voltage);
        delay(200);
    }

    bcm2835_i2c_end();
    bcm2835_close();
    return 0;
}
