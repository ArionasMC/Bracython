#ifndef HEADER_IMPORT_MANAGER
#define HEADER_IMPORT_MANAGER

#include<string>
#include<list>

using namespace std;

class ImportManager {

	public:
		ImportManager(list<string> lines);
		list<string> getFileNames(); // Get the files that should be converted to py

	private:
		list<string> lines;
		list<string> fileNames;
		void checkLineForImport(string line);

};

#endif
