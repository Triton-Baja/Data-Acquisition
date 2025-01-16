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
