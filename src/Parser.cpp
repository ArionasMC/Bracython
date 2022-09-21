#include "headers/Parser.hpp"
#include<cstdio>
#include<algorithm>
#include<fstream>
#include<cmath>

Parser::Parser(list<string> rawLines) : rawLines(rawLines) { }

list<string> Parser::getRawLines() {
	return this->rawLines;
}

list<string> Parser::getFinalLines() {
	return this->finalLines;
}

bool Parser::isDictionaryLine(string line) {
	bool search = false;
	for(int i = 0; i < line.size(); i++) {
		if(search) {
			if(line[i] == ' ')
				continue;
			else if(line[i] == '{')
				return true;
			else
				return false;
		}

		if(line[i] == '=')
			search = true;
	}
	return false;
}

// Returns how many spaces where removed
int Parser::replaceOpeningAt(string &line, int index) {
	line[index] = ':';

	for(int i = index-1; i >= 0; i--) {
		if(isspace(line[i]))
			line.erase(line.begin()+i);
		else
			return abs(i-index+1);
	}
}

void Parser::addIndentation(string &line, int times) {
	for(int i = 0; i < line.size(); i++) {
		if(isspace(line[i]))
			line.erase(line.begin()+i);
		else
			break;
	}
	for(int i = 0; i < times; i++) line.insert(line.begin(), '\t');
}

void Parser::removeAllSpacesAtBeginning(string &line) {
	for(int i = 0; i < line.size(); i++) {
		if(line[i] == '{' || line[i] == '}')
			continue;
		if(isspace(line[i]))
			line.erase(line.begin()+i);
		else
			break;
	}
}

void Parser::bry2py() {
	finalLines.clear();
	list<string>::iterator it;
	int change = 0;

	/* Check for and deal with the following scenario:
	 * <python command like if, def,...>
	 * {
	 *   commands
	 * }
	 */
	for(it = rawLines.begin(); it != rawLines.end(); it++) {
		string str(*it);

		removeAllSpace(str);

		if(str.size() == 1 && str[0] == '{') {
			auto prevElement = it;
			prevElement--;
			(*prevElement).push_back('{');
			rawLines.erase(it);
		}
	}

	// Convert rawLines to finalLines
	bool nextLine = false;
	for(it = rawLines.begin(); it != rawLines.end(); it++) {
		string str(*it);
		int prevLoc = 0;
		int closing = 0;

		this->removeAllSpacesAtBeginning(str);

		for(int i = 0; i < str.size(); i++) {
			if(str[i] == '{' && !isDictionaryLine(str)) {
				change++;
				prevLoc = i - this->replaceOpeningAt(str, i);

				if(!isLastNoSpace(str, prevLoc)) {
					string str2 = str.substr(prevLoc+1);
					str.erase(str.begin()+prevLoc+1, str.end());
					auto nextElement = it;
					nextElement++;
					rawLines.insert(nextElement, str2);
				}

				nextLine = true;
				break;
			}

			if(str[i] == '}') {
				if(change > 0) {
					if(firstNoSpace(str)!= '}') closing++;

					str.erase(str.begin()+i);
					i--;
					change--;
				}
			}
		}

		this->addIndentation(str, max(change-nextLine+closing, 0));
		nextLine = false;

		//printf("%s\n", change, str.c_str());
		finalLines.push_back(str);

	}
}

char Parser::firstNoSpace(string line) {
	for(int i = 0; i < line.size(); i++)
		if(!isspace(line[i]))
			return line[i];
	return '!';
}

bool Parser::isLastNoSpace(string line, int index) {
	for(int i = index+1; i < line.size(); i++)
		if(!isspace(line[i]))
			return false;
	return true;
}

void Parser::removeAllSpace(string &line) {
	for(int i = 0; i < line.size(); i++) {
		if(isspace(line[i])) {
			line.erase(line.begin()+i);
			i--;
		}
	}
}
