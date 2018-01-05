#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
void trim(std::string& str) {
	while (!str.empty() && str[0] == ' ') {
		str.erase(0, 1); 
	}
	while (!str.empty() && str[str.size() - 1] == ' ') {
		str.erase(str.size() - 1, 1); 
	}
}
void csvRead(std::string& fileName, char seperator, std::vector< std::vector<string> > &csvData) {
	std::fstream is(fileName, std::ios::in);
	if (!is.is_open()) {
		throw std::string("Cannot open file '") + fileName + "'";
	}
	std::string line;
	while (getline(is, line)) {
		auto cr = line.find('\r');
		if (cr != string::npos) {
			line.erase(cr);
		}
		size_t index = 0;
		std::string field;
		std::vector<string> fields;
		while (index < line.size()) {
			while (index < line.size() && line[index] != seperator) {
				field += line[index];
				index++;
			}
			index++; 
			trim(field);
			fields.push_back(std::move(field));
		}
		csvData.push_back(std::move(fields));
	}
	is.close();
}
void csvPrint(std::vector< std::vector<string> > &csvData) {
	std::cout << std::endl;
	for (auto row : csvData) {
		for (auto column : row) {
			std::cout << "(" << column << ") ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (size_t row = 0; row < csvData.size(); row++) {
		for (size_t column = 0; column < csvData[row].size(); column++) {
			std::cout << "--" << csvData[row][column] << "-- ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (auto row = csvData.begin(); row != csvData.end(); row++) {
		for (auto column = row->begin(); column != row->end(); column++) {
			std::cout << "[" << *column << "] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
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

