#include <iostream>
#include <fstream>
#include <string>

int main(){


	std::string names[] = {"Giovanni", "Brandon", "Guilian", "Andres"};
	std::ofstream file;
	file.open("names.txt", std::ios::out | std::ios::trunc);

	if(!file.is_open())
		return 1;

	int size = sizeof(names) / sizeof(names[0]);

	for(int i = 0; i < size; i++){
		file << names[i];
		file << ",";
	}

	file.close();

	return 0;
}
