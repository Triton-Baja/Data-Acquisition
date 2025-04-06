#include <bcm2835.h>
#include <cstdio>

int main(){

	if(!bcm2835_init()){
		printf("Failed to initialize\n");
		return 1;
	}

	//bcm2835_i2c_setSlaveAddress(8);

	bcm2835_i2c_begin();

	bcm2835_i2c_end();
	bcm2835_close();

	return 0;
}
