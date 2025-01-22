#include <fstream>
#include <cstdio>
#include <string>

void binToCSV(std::fstream &file, std::string filename){
	file.open(filename, std::ios::in);

	file.seekg(0, std::ios::end);
	size_t len = file.tellg();
	size_t numFloats = len / sizeof(float);

	float readBuffer[numFloats];

	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(readBuffer), sizeof(readBuffer));
	file.close();

	printf("Inside binToCSV\n");
	for(int i = 0; i < numFloats; i++)
		printf("%f ", readBuffer[i]);

	printf("\n");

	file.open("data_floats.txt", std::ios::out | std::ios::trunc);
	
	for(int i = 0; i < numFloats; i++){
		file << std::to_string(readBuffer[i]);
		file << ',';
	}

	file.close();
}


void workingWithStrings(std::fstream &file){

	// Writing
	file.open("data_strings.bin", std::ios::out | std::ios::trunc);

	if(!file.is_open())
		return;

	char buffer[] = "This is a test for binary files";

	file.seekp(0, std::ios::end);
	size_t fileSize = file.tellp();

	printf("%ld\n", fileSize);

	file.seekp(0, std::ios::beg);
	file.write(buffer, sizeof(buffer));
	file.close();

	// Reading
	
	file.open("data_strings.bin", std::ios::in);

	char readBuffer [1024] = {};

	file.seekg(0, std::ios::beg);
	file.read(readBuffer, sizeof(readBuffer));
	file.close();

	printf("%s\n", readBuffer);

}

void workingWithFloats(std::fstream &file){

	// Writing
	
	file.open("data_floats.bin", std::ios::out | std::ios::trunc);

	if(!file.is_open())
		return;

	float buffer[] = {12.34, 56.29, 56.98, 0.0001};

	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(buffer), sizeof(buffer));
	file.close();

	// Reading
	
	file.open("data_floats.bin", std::ios::in);

	float readBuffer[4];

	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(readBuffer), sizeof(readBuffer));
	file.close();

	for(int i = 0; i < 4; i++)
		printf("%f ", readBuffer[i]);

	printf("\n");
	binToCSV(file, "data_floats.bin");

}

int main(){

	std::fstream file;
	workingWithStrings(file);
	workingWithFloats(file);

	file.close();

	return 0;
}
