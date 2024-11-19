#include "bcmwrapper.h"

void handle_signal(int signal){
	printf("\nTerminating due to signal %d\n", signal);
	bcm2835_close();
	printf("Closed bcm2835\n");
	exit(1);
}

void register_signals(){
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
}
