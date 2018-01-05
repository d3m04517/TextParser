#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

class Task {
    string name, slots, pass, fail;
public:
    Task(vector<string>& fields): slots("1") {
        switch(fields.size()) {
            case 4: 
                if (validTaskName(fields[3])) {
                    fail = fields[3];
                } else {
                    throw string("Syntax error in " + fields[3]);
                }
            case 3:
                if (validTaskName(fields[2])) {
                    pass = fields[2];
                } else {
                    throw string("Syntax error in " + fields[2]);
                }
            case 2:
                if (validSlotName(fields[1])) {
                    slots = fields[1];
                } else {
                    throw string("Syntax error in " + fields[1]);
                }
            case 1:
                if (validTaskName(fields[0])) {
                    name = fields[0];
                } else {
                    throw string("Syntax error in " + fields[0]);
                }
                break;
            default:
                throw string("syntax error - not 1, 2, 3, or 4 fields");
        }
    }
    void TaskPrint() {
        cout << name << "|" << slots << "|" << pass << "|" << fail << endl;
    }
    void TaskGraph(fstream& os){
		if (!fail.empty()) {
			os << '"' << name << '"' << "->" << '"' << fail << '"' << "[color=red]" << ";\n";
		}

		if (!pass.empty()) {
			os << '"' << name << '"' << "->" << '"' << pass << '"' << "[color=green]" << ";\n";
		}

		if (fail.empty() && pass.empty()) {
			os << '"' << name << '"' << ";\n";
		}
	}
    ~Task() {

	}
};




class TaskManager {
    vector<Task> tasks;
public:
    TaskManager(vector< vector<string> >& csvdata) {
        for (auto row: csvdata) {
            try {
                tasks.push_back(std::move(Task(row)));
            } 
            catch (string& s) {
                cerr << s << endl;
            }
        }
    }
    
    void TaskPrint() {
		
		int lineNumber = 0;
		for (auto t : tasks) {
			lineNumber++;
			cout << "Task " << lineNumber << ":";
			t.TaskPrint();
		}
	}
    
    void TaskGraph(string& filename) {
		fstream os(filename + ".gv", ios::out);
		os << "diagraph taskGraph {\n";
		for (auto t : tasks){
			t.TaskGraph(os);
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
	~TaskManager() {

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

		TaskManager tm(csvTaskData);
		tm.TaskPrint();
		tm.TaskGraph(filename);
	}
	catch (string& e) {
		cerr << e << "\n";
	}

	return 0;
}
