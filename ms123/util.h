/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   util.h
 * Author: Lkim
 *
 * Created on December 21, 2017, 1:27 PM
 */

#include <iostream>
#include <vector>
#include <fstream>

void trim(std::string& str);
void csvRead(std::string& fileName, char seperator, std::vector< std::vector<std::string> > &csvData);
void csvPrint(std::vector< std::vector<std::string> > &csvData);
bool validTaskName(std::string&);
bool validSlotName(std::string&);
bool validItemSequence(std::string&);
bool validItemName(std::string&);
bool validCustName(std::string&);
bool validProductName(std::string&);
bool validOrderName(std::string);
bool validOrderSequence(std::string&);

