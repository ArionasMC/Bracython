#ifndef HEADER_PARSER
#define HEADER_PARSER

#include <list>
#include <string>

using namespace std;

class Parser {

	public:
		Parser(list<string> rawLines);
		list<string> getRawLines();
		list<string> getFinalLines();
		void bry2py(); // Convert Raw (Bracython) Lines to Final (Python) Lines
		bool isDictionaryLine(string line); // Check if line containing '{' is for Python's dictionary
		int replaceOpeningAt(string &line, int index); // Replace '{' with ':'
		void addIndentation(string &line, int times); // Add indentation to line
		void removeAllSpacesAtBeginning(string &line); // Remove all whitespace at beginning of line

	private:
		list<string> rawLines;
		list<string> finalLines;
		char firstNoSpace(string line);
		bool isLastNoSpace(string line, int index);
		void removeAllSpace(string &line);
};

#endif
