#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

class Order {
    string custName, prodName;
    vector<string> itemList;
public:
    Order(vector<string>& fields) {
        if (fields.size() < 3) {
            throw string("syntax error - not 3 or more fields");
        }
        if (validCustName(fields[0])) {
            custName = fields[0];
        } else {
            throw string("Syntax error in " + fields[0]);
        }
        if (validProductName(fields[1])) {
            prodName = fields[1];
        } else {
            throw string("Syntax error in " + fields[1]);
        }
        for (size_t i = 2; i < fields.size(); i++) {
            if (validItemName(fields[i])) {
                itemList.push_back(move(fields[i]));
            } else {
                throw string("Syntax error in " + fields[i]);
            }
        }
    }
    void OrderPrint() {
        cout << "[" << custName << "] " << "[" << prodName << "] " << "\n";
		for (auto i : itemList) {
			cout << "[" << i << "] ";
		}
		cout << "\n";
    }
    void OrderGraph(fstream& os) {
		for (auto i : itemList) {
			os << '"' << custName << "\n" << prodName << '"' << "->" << '"' << i << '"' << "[color=blue]" << ";\n";
		}
	}
    ~Order() {

	}
};




class OrderManager {
    vector<Order> orders;
public:
    OrderManager(vector< vector<string> >& csvdata) {
        for (auto row: csvdata) {
            try {
                orders.push_back(std::move(Order(row)));
            } 
            catch (string& s) {
                cerr << s << endl;
            }
        }
    }
    
    void OrderPrint() {
		
		int lineNumber = 0;
		for (auto o : orders) {
			lineNumber++;
			cout << "Task " << lineNumber << ":";
			o.OrderPrint();
		}
	}
    
    void OrderGraph(string& filename) {
		fstream os(filename + ".gv", ios::out);
		os << "diagraph order {\n";
		for (auto o : orders){
			o.OrderGraph(os);
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
	~OrderManager() {

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

		OrderManager om(csvTaskData);
		om.OrderPrint();
		om.OrderGraph(filename);
	}
	catch (string& e) {
		cerr << e << "\n";
	}

	return 0;
}
