#include "util.h"

using namespace std;
int main(int argc, char* argv[]) {
	try {
		if (argc != 3) {
			throw std::string("Usage: ") + argv[0] + " csv-data-file-name csv-data-seperator";
		}
		std::string fileName = argv[1];
		char seperator = argv[2][0];
		std::vector< std::vector<string> > csvData;
		csvRead(fileName, seperator, csvData);
		csvPrint(csvData);
	}
	catch (const string& e) {
		std::cerr << e << std::endl;
	}
	std::cout << "Press any key to continue ... ";
	std::cin.get();
}