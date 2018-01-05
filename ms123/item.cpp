#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

class Item {
    string itemName, installerTask, removerTask, sequentialCode, desc;
public:
    Item(vector<string>& fields) {
        switch(fields.size()) {
            case 5: 
                desc = fields[4];
            case 4:
                if (validItemSequence(fields[3])) {
                    sequentialCode = fields[3];
                } else {
                    throw string("Syntax error in " + fields[3]);
                }
                if (validTaskName(fields[2])) {
                    removerTask = fields[2];
                } else {
                    throw string("Syntax error in " + fields[2]);
                }
                if (validTaskName(fields[1])) {
                    installerTask = fields[1];
                } else {
                    throw string("Syntax error in " + fields[1]);
                }
                if (validItemName(fields[0])) {
                    itemName = fields[0];
                } else {
                    throw string("Syntax error in " + fields[0]);
                }
                break;
            default:
                throw string("syntax error - not 4 or 5 fields");
        }
    }
    void ItemPrint() {
        cout << "[" << itemName << "] "
	<< "[" << installerTask << "] "
	<< "[" << removerTask << "] "
	<< "[" << sequentialCode << "] "
	<< "[" << desc << "] " << "\n";
    }
    void ItemGraph(fstream& os) {
		os << '"' << "Item\n" << itemName << '"' << "->" << '"' << "Installer\n" << installerTask << '"' << "[color=green]" << ";\n";

		os << '"' << "Item\n" << itemName << '"' << "->" << '"' << "Remover\n" << removerTask << '"' << "[color=red]" << ";\n";
	}
    ~Item() {

	}
};




class ItemManager {
    vector<Item> items;
public:
    ItemManager(vector< vector<string> >& csvdata) {
        for (auto row: csvdata) {
            try {
                items.push_back(std::move(Item(row)));
            } 
            catch (string& s) {
                cerr << s << endl;
            }
        }
    }
    
    void ItemPrint() {
		
		int lineNumber = 0;
		for (auto i : items) {
			lineNumber++;
			cout << "Task " << lineNumber << ":";
			i.ItemPrint();
		}
	}
    
    void ItemGraph(string& filename) {
		fstream os(filename + ".gv", ios::out);
		os << "diagraph item {\n";
		for (auto i : items){
			i.ItemGraph(os);
		}
		os << "}\n";
		os.close();
		string cmd;
#ifdef _MSVC
	cmd += "C:\Program File(x86)\Graphviz2.38\bin\dot.exe"
#else
cmd = "dot";
#endif
		cmd += string("dot - Tpng") + filename + ".gv >" + filename + ".gv.png";
		cout << "running" << cmd << "\n";
		//system(cmd.c_str());
	}
	~ItemManager() {

	}
};

int main(int argc, char* argv[]) {
	try {
		if (argc != 3)
			throw string("usage:") + argv[0] + "file.csv delimeter-char";
		string filename = argv[1]; 
		char delim = argv[2][0]; 

		vector< vector <string> > csvTaskData;
		csvRead(filename, delim, csvTaskData);
		
		csvPrint(csvTaskData);

		ItemManager im(csvTaskData);
		im.ItemPrint();
		im.ItemGraph(filename);
	}
	catch (string& e) {
		cerr << e << "\n";
	}

	return 0;
}
