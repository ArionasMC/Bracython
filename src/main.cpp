#include <cstdio>
#include <string>
#include <fstream>
#include <algorithm>
#include "headers/Parser.hpp"
#include "headers/ImportManager.hpp"
using namespace std;

bool isBryFileName(string name);
string getOutLoc(string name);
list<string> getFileLines(string fileName);

int main(int argc, char* argv[]) {

	printf("Bracython!!!\n");
	char *name = new char[30];

	if(argc <= 1) {
		printf("File to convert: ");
		scanf(" %s", name);
	} else {
		name = argv[1];
		printf("file name: %s\n", name);
	}

	string loc = string(name);
	ifstream file(loc.c_str());

	if(file.fail()) {
		printf("ERROR: Failed to open %s!\n", loc.c_str());
		return 0;
	}

	if(!isBryFileName(loc)) {
		printf("ERROR: %s is not a Bracython file!\n", loc.c_str());
		return 0;
	}

	string line;
	list<string> rawLines = getFileLines(name);
	file.close();

	// Search for imports
	ImportManager *man = new ImportManager(rawLines);
	list<string> filesToParse;
	filesToParse.push_back(string(name));

	for(string s : man->getFileNames())
		filesToParse.push_back(s);

	list<string>::iterator it = filesToParse.begin();
	it++;
	int counter = 1;

	while(counter < filesToParse.size()) {
		string f = *it;
		list<string> ls = getFileLines(f);

		ImportManager *im = new ImportManager(ls);
		for(string s : im->getFileNames())
			if(find(filesToParse.begin(), filesToParse.end(), s) == filesToParse.end())
				filesToParse.push_back(s);

		counter++;
		it++;
	}

	printf("Files to parse:\n");
	for(string s : filesToParse) {
		printf("Parsing %s...", s.c_str());

		Parser *parser = new Parser(getFileLines(s));
		parser->bry2py();

		string outLoc = getOutLoc(s);
		ofstream outFile(outLoc.c_str());

		for(string s : parser->getFinalLines())
			outFile << s.c_str() << '\n';
		outFile.close();

		printf("done!\n");
	}

	printf("\n");

	string toRun = getOutLoc(string(name));
	printf("Running python %s: \n\n", toRun.c_str());
	string cmd = "py "+toRun;
	system(cmd.c_str());

	return 0;
}

bool isBryFileName(string name) {
	string ext = ".bry";
	for(int i = name.size()-4; i < name.size(); i++)
		if(name[i] != ext[i-(name.size()-4)])
			return false;

	return true;
}

string getOutLoc(string name) {
	string outLoc(name);
	outLoc.erase(outLoc.end()-4, outLoc.end());
	outLoc.append(".py");

	return outLoc;
}

list<string> getFileLines(string fileName) {
	list<string> lines;
	string s;
	ifstream file(fileName.c_str());

	if(file.good())
		while(getline(file, s))
			lines.push_back(s);
	file.close();

	return lines;
}
