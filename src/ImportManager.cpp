#include "headers/ImportManager.hpp"
#include <fstream>

ImportManager::ImportManager(list<string> lines) : lines(lines) {

	for(string s : lines)
		checkLineForImport(s);

}

list<string> ImportManager::getFileNames() {
	return this->fileNames;
}

void ImportManager::checkLineForImport(string line) {
	string prefix = "from ";
	int index = 0;
	for(int i = 0; i < line.size(); i++) {
		if(line[i] == prefix[index]) {
			index++;
		} else {
			index = 0;
		}

		if(index == prefix.size()) {
			index = i;
			break;
		}
	}

	string name = "";
	if(index > 0) {
		for(int i = index+1; i < line.size(); i++) {
			if(isspace(line[i])) break;
			name.push_back(line[i]);
		}
		name.append(".bry");

		ifstream file(name.c_str());
		if(file.good())
			this->fileNames.push_back(name);
		file.close();

	}
}
