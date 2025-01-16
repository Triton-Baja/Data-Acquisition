#include <iostream>
#include <fstream>
#include <cstdio>

int main(){

	std::ifstream file;
	file.open("names.txt", std::ios::in);

	std::string names[4];
	std::string line;

	getline(file, line);

	printf("%s\n", line.c_str());
	
	int i = 0;
	int j = 0;

	while(i < line.length() - 1){
		while(line[i] != ','){
			names[j] += line[i];
			i++;
		}
		i++;
		j++;
	}

	for(int i = 0; i < 4; i++){
		printf("%s\n", names[i].c_str());
	}

	std::string name;
	j = 0;
	while(getline(file, name, ',')){
		names[j] = name;
	}

	for(int i = 0; i < 4; i++){
		printf("%s\n", names[i].c_str());
	}


	file.close();
	return 0;
}
