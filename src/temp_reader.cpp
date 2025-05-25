#include <stdio.h>
#include <bcm2835.h>
#include <cmath>
#include <fstream>
#include <chrono>
#include "../include/bcmwrapper/bcmwrapper.h"

constexpr uint8_t BUTTON_PIN = 16;

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

void binToCSV(std::fstream &file, std::string filename){
	file.open(filename, std::ios::in);

	file.seekg(0, std::ios::end);
	size_t len = file.tellg();
	size_t numFloats = len / sizeof(double);

	double readBuffer[numFloats];

	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(readBuffer), sizeof(readBuffer));
	file.close();

	printf("Converting .bin to .csv...\n");

	file.open("temp.csv", std::ios::out | std::ios::trunc);
	
	for(int i = 0; i < numFloats / 2; i++){
		file << std::to_string(readBuffer[2 * i]);
		file << ',';
		file << std::to_string(readBuffer[2 * i + 1]);
		file << '\n';
		
	}

	file.close();

	printf("Converted .bin to .csv\n");

}

void uploadToDrive(){
	system("bash -c 'cd GoogleDriveAPI && source venv/bin/activate && python3 upload.py'");
}


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
        voltage = reading * 6.144 / 32768.0;

    else if(voltageBits == CONFIG_PGA_4_096V)
        voltage = reading * 4.096 / 32768;

    else if(voltageBits == CONFIG_PGA_6_144V)
        voltage = reading * 6.144 / 32768.0;

    return static_cast<double>(voltage);

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

	gpio_pinmode(BUTTON_PIN, INPUT);
	gpio_setpull(BUTTON_PIN, PULLUP);

    bcm2835_i2c_setSlaveAddress(ADS1115_ADDRESS);
    bcm2835_i2c_set_baudrate(100000);

	std::fstream file;
	file.open("temp.bin", std::ios::out | std::ios::trunc);

	if(!file.is_open()){
		printf("File failed to open\n");
		return 3;
	}

	file.seekp(0, std::ios::beg);
	
	auto start_time = std::chrono::steady_clock::now();

    while(gpio_read(BUTTON_PIN)){
        double voltage = readVoltage(CONFIG_OS_SINGLE | CONFIG_MUX_AIN2_GND | CONFIG_PGA_6_144V | CONFIG_MODE_CONTINUOUS |
            CONFIG_DR_128SPS | CONFIG_COMP_POL_LOW | CONFIG_COMP_NON_LAT | CONFIG_COMP_QUE_DIS);
        double bit_10 = voltage * 1024.0 / 5.25;

		double r2 = (bit_10 * 100000) / (1024 - bit_10);
		r2 /= 1000;
		double temp = 0.0018 * pow(r2, 2) - 0.6001 * r2 + 66.5213;

		double elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count();

		file.write(reinterpret_cast<const char*>(&elapsed), sizeof(double));
		file.write(reinterpret_cast<const char*>(&temp), sizeof(double));
		printf("%f\n", temp);
        delay(200);
    }

	file.close();

	binToCSV(file, "temp.bin");

    bcm2835_i2c_end();
    bcm2835_close();

	uploadToDrive();

    return 0;
}
