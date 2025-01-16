#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <random>

int rollDice(int faces = 6){

	return (rand() % faces) + 1;

}

int main(){

	srand(time(nullptr));


	for(int i = 0; i < 10; i++){
		printf("%f\n", 23 + 2.0 * (float)rand() / RAND_MAX -1);
	}

	for(int i = 0; i < 100; i++)
		if(i % 2 == 0)
			printf("%d is even\n", i);

		else
		 printf("%d is not even\n", i);

	constexpr int faces = 10;
	int count[faces] = {};
	int numberOfRolls = 4778327;

	for(int i = 0; i < numberOfRolls; i++){
		int value = rollDice();

		count[value - 1]++;
		//printf("%d\n", value);
	}

	for(int i = 0; i < faces; i++){
		printf("%d was printed %f%%\n", i + 1, 100.0 * float(count[i]) / numberOfRolls);
	}

	
}
