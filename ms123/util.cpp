#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
using namespace std;
void trim(std::string& str) {
	while (!str.empty() && str[0] == ' ') {
		str.erase(0, 1); 
	}
	while (!str.empty() && str[str.size() - 1] == ' ') {
		str.erase(str.size() - 1, 1); 
	}
}

void csvRead(std::string& fileName, char seperator, std::vector< std::vector<std::string> > &csvData) {
	std::fstream is(fileName, std::ios::in);
	if (!is.is_open()) {
		throw std::string("Cannot open file '") + fileName + "'";
	}
	std::string line;
	while (getline(is, line)) {
		//Handling an CR '\r' in data
		auto cr = line.find('\r');
		if (cr != std::string::npos) {
			line.erase(cr);
		}
		size_t index = 0;
		std::string field;
		std::vector<std::string> fields;
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
void csvPrint(std::vector< std::vector<std::string> > &csvData) {
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

bool validTaskName(string& s) {
    for (auto c : s) {
        if (!((isalnum(c)) || c != ' ' || c != '_')) {
            return false;
        }
    }
	return true;
}

bool validSlotName(string& s) {
    for (auto c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
	return true;
}

bool validItemSequence(string& s) {
    if (s.empty())
	{
		return false;
	}
	for (auto c : s) {
		if (isdigit(c))
		{
			continue;
		} else {
		cout << c << endl;
		return false;
		}
	}
	return true;
}

bool validItemName(string& s) {
	if (s.empty())
	{
		return false;
	}
	for (auto c : s) {
		if (isspace(c) || isalnum(c) || c == '_')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool validCustName(string& s) {
	if (s.empty())
	{
		return false;
	}
	for (auto c : s) {
		if (isspace(c) || isalnum(c) || c == '\'')
		{
			continue;
		}
		return false;
	}
	return true;
}
bool validProductName(string& s) {
	if (s.empty())
	{
		return false;
	}
	for (auto c : s) {
		if (isspace(c) || isalnum(c) || c == '\'' || c == '#' || c == '$')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool validOrderName(string& s) {
	if (s.empty())
	{
		return false;
	}
	for (auto c : s) {
		if (isspace(c) || isalnum(c) || c == '_')
		{
			continue;
		}
		return false;
	}
	return true;
}

bool validOrderSequence(string& s) {
	if (s.empty())
	{
		return false;
	}
	for (auto c : s) {
		if (isdigit(c))
		{
			continue;
		}
		return false;
	}
	return true;
}
