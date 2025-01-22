# Files
We know we can store program data in the form of variables. However, these only exist on the computer's RAM while the program is running. After execution ends, the OS performs a cleanup of all the resources allocated by the program.
This poses a challenge when there is data that we want to save permanently. This is where files come in hand, as in, the files stored in your computer drive. Unlike variables, this data is stored on the computer's Hard Drive, or more recently, SSD.

## fstream
C++ does a great job at facilitating working with files through the use of [streams](https://cplusplus.com/reference/iolibrary/), more precisely [file streams](https://cplusplus.com/doc/tutorial/files/). 
The [cplusplus.com](cplusplus.com) website already does a great job at explaining how these streams work, so I won't be discussing that here. Please make sure to [read this](https://cplusplus.com/doc/tutorial/files/) extensively.

## non-binary mode
As you learned from the [cplusplus.com](cplusplus.com) documentation, the default mode to write/read to/from a file is by using the `<<` operator and the `getline` function when it comes to C++ strings ([std::string](https://cplusplus.com/reference/string/string/)) or [string literals](https://en.wikipedia.org/wiki/String_literal). 
Here are some examples from [src/examples/files](https://github.com/Triton-Baja/Data-Acquisition/tree/main/src/examples/files).

Writing something to a file

```C++
#include <iostream>
#include <fstream>

int main(){
	std::ofstream ofile;
	ofile.open("data.txt", std::ios::out | std::ios::app);

	if(!ofile.is_open())
		return 1;

	ofile << "Nevermind\n";
	ofile.close();
	return 0;
}
```

Writing CSV to a file containing names
```C++
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
```

Reading from the `names.txt` file and loading the names into memory
```C++
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

  	// Manually extracting the names by looking for the comma separator	
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

	for(int i = 0; i < 4; i++)
		printf("%s\n", names[i].c_str());

  	// Using getline's delimiter argument to read until we find a comma
	std::string name;
	j = 0;
	while(getline(file, name, ','))
		names[j] = name;

	for(int i = 0; i < 4; i++)
		printf("%s\n", names[i].c_str());

	file.close();
	return 0;
}
```

## Binary files
While writing/reading to/from files open in default (non-binary) mode is very easy, it's not very fast, specially if we want to read from multiple sensors multiple times per second and store all the data. 
Thankfully, writing and reading in binary mode is much faster, although just a bit more complicated. 

### C Strings
Here I have a function that, given a `file` object, it will write and read a C String (character array) into the file
```C++
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
```

### Primitives
Working with primitives is exactly the same as working with C Strings, except for a small detail. We must `reinterpret_cast<char*>` our primitive array. 
That is, we need to reinterpret the decayed pointer to the first element of the primitive array into type `char`, `char*` so that the write and read functions can write them to the files. 
Here I have a function that, given a `file` object, it will write and read a float array into the file.
```C++
void workingWithFloats(std::fstream &file){

	// Writing
	float buffer[] = {12.34, 56.29, 56.98, 0.0001};
	file.open("data_floats.bin", std::ios::out | std::ios::trunc);

	if(!file.is_open())
		return;

	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(buffer), sizeof(buffer));
	file.close();

	// Reading
  	float readBuffer[4];
	file.open("data_floats.bin", std::ios::in);
	
	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(readBuffer), sizeof(readBuffer));
	file.close();

	for(int i = 0; i < 4; i++)
		printf("%f ", readBuffer[i]);

	printf("\n");
}
```
