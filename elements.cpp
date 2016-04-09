#include "elements.h"

bool element::ReadFromFile(string& fileName) {
	f.open(fileName);
	int size;
	int bufInt;
	int bufMemory = 0;
	int bufMemoryDyn;
	bool flIF = true;
	int flMemoryNum = 1;
	int flMemoryNumCode = 1;
	string bufStr = "";
	if (f.is_open()) {
		number = 0;
		assumeInt(assume); //Init assume table
		while (!f.eof()) {
			getline(f, bufWord);
			istringstream is;
			is.str(bufWord);
			if (flIF) {
				list.push_back(vector<string>());
				listInfo.push_back(vector<int>());
				grammar.push_back(vector<int>());
				tableCommand.push_back(vector<int>());
			}
			else
				flIF = true;

			//lexems
			while (is >> bufWord) {
				if (inCharString(';', bufWord))
					break;
				else if ((bufWord[0] == '"') || (bufWord[0] == '\'')) {
					bufStr = "";
					bufStr += bufWord;
					while ((is >> bufWord) && (!inCharString(';', bufWord))) {
						bufStr += " ";
						bufStr += bufWord;
					}
					strokaBuf.push_back(bufStr);
				}
				else if (inString(bufWord, singleStringLexems))
					strChange(bufWord, strokaBuf);
				else
					strokaBuf.push_back(bufWord);
			}

			//analyze table
			bufWord = "";
			size = strokaBuf.size();
			for (int i = 0; i < size; ++i) {
				if ((strokaBuf[i][0] == '"') || (strokaBuf[i][0] == '\'')) {
					if ((strokaBuf[i][bufStr.length() - 1] == '"') || (strokaBuf[i][bufStr.length() - 1] == '\''))
						bufInt = 9;
				}
				else {
					convert(strokaBuf[i]);
					if (strokaBuf[i] != "ELSE")
						bufInt = findAnalyze(strokaBuf[i]);
					else {
						flIF = false;
						break;
					}
				}
				list[number].push_back(strokaBuf[i]);
				listInfo[number].push_back(bufInt);
			}

			//if else endif
			if (!flIF) {
				getline(f, bufWord);
				strokaBuf.clear();
				continue;
			}

			//syntax
			if (!syntax(listInfo[number], list[number], grammar[number]))
				grammar[number].push_back(-1);

			//memory 
			bufMemoryDyn = memoryVec(listInfo[number], list[number], grammar[number], number);
			if (bufMemoryDyn == -1) {
				memory.push_back(-1); //for equ "= <const>"
				bufMemoryDyn = 0;
			}
			else if (bufMemoryDyn == -2) { //segment || data
				bufMemory = 0;
				memory.push_back(bufMemory);
			}
			else if (bufMemoryDyn == -3) {
				memory.push_back(-3); // string is space
				bufMemoryDyn = 0;
			}
			else if (bufMemoryDyn == -4) {
				memory.push_back(-4); // directive if, endif, else, end ("\t\t")
				bufMemoryDyn = 0;
			}
			else {
				memory.push_back(bufMemory);
				bufMemory += bufMemoryDyn;
			}
			if (flMemoryNum == space.size()) {
				spaceNum.push_back(memory[number]);
				++flMemoryNum;
			}
			if (flMemoryNumCode == spaceCode.size()) {
				spaceNum.push_back(memory[number]);
				++flMemoryNumCode;
			}
			strokaBuf.clear();
			++number;
		}
		f.close();
		return true;
	}
	else
		return false;
}

bool element::syntax(const vector<int> &listStroka, const vector<string> &listString, vector<int> &listGrammar) {
	int size = listStroka.size();
	int i = 0;
	int pos = 1;
	bool fl = true;
	while ((i < size) && (fl)) {
		switch (listStroka[i]) {
		case 1:
			if (listString[i][0] == '[') {
				++i;
				while ((i < size) && (listString[i][0] != ']')) {
					++i;
					++pos;
				};
			}
			if ((i == 0) && (i == size - 1)) {
				listGrammar.push_back(0);
				listGrammar.push_back(1);
			}
			else if (i == 0) {
				listGrammar.push_back(0);
				listGrammar.push_back(1);
			}
			else {
				listGrammar.push_back(i + 1);
			}
			listGrammar.push_back(pos);
			pos = 0;
			break;
		case 2:
			if ((i < size - 1) && (listString[i + 1][0] == ',')) {
				listGrammar.push_back(i + 1);
				listGrammar.push_back(pos);
				++i;
				pos = 0;
			}
			else if (i != 0) {
				listGrammar.push_back(i + 1);
				listGrammar.push_back(pos);
				pos = 0;
			}
			else {
				fl = false;
			}
			break;
		case 3:
			if (i != 0) {
				listGrammar.push_back(i + 1);
				while ((i < size) && (listString[i][0] != ']') && (listString[i][0] != ',')) {
					++i;
					++pos;
				};
				listGrammar.push_back(pos);
				pos = 0;
			}
			else {
				fl = false;
			}
			break;
		case 4:
			if (i != 0) {
				listGrammar.push_back(i + 1);
				listGrammar.push_back(pos);
				pos = 0;
			}
			else if ((i == 0) && (i == size - 1)) {
				listGrammar.push_back(0);
				listGrammar.push_back(1);
				listGrammar.push_back(pos);
			}
			else {
				listGrammar.push_back(0);
				listGrammar.push_back(1);
				listGrammar.push_back(1);
				pos = 0;
			}
			break;
		case 5:
		case 6:
			if (i != 0) {
				if ((regex_match(listString[i - 1], directives)) || (regex_match(listString[i - 1], directivesType)) || (inString(listString[i - 1], singleStringLexems))) {
					listGrammar.push_back(i + 1);
					listGrammar.push_back(pos);
					pos = 0;
				}
				else {
					fl = false;
				}
			}
			else {
				fl = false;
			}
			break;
		case 7:
			if (i == 0) {
				fl = false;
			}
			--pos;
			break;
		case 8:
			if ((i == 0) && (i < size - 1)) {
				if (listStroka[i + i] == ':')
					++i;
				listGrammar.push_back(1);
				pos = 0;
			}
			else {
				listGrammar.push_back(i + 1);
				if ((i < size - 1) && (listString[i + 1][0] == '[')) {
					while ((i < size) && (listString[i][0] != ']')) {
						++i;
						++pos;
					};
				}
				listGrammar.push_back(pos);
				pos = 0;
			}
			break;
		case 9:
		case 10:
			if (i != 0) {
				listGrammar.push_back(i + 1);
				listGrammar.push_back(pos);
				pos = 0;
			}
			else {
				fl = false;
			}
			break;
		case 11:
			if (i != 0) {
				listGrammar.push_back(i + 1);
				while ((i < size) && (listString[i][0] != ']')) {
					++i;
					++pos;
				};
				listGrammar.push_back(pos);
				pos = 0;
			}
			else {
				fl = false;
			}
			break;
		default:
			fl = false;
			break;
		}
		++i;
		++pos;
	}
	return fl;
}

int element::memoryVec(const vector<int> &listStroka, const vector<string> &listString, vector<int> &listGrammar, int &listNumber) {
	int size = listStroka.size();
	int bufInt = 0;
	int i = 0;
	while (i < size) {
		switch (listStroka[i]) {
		case 1:
			if (listString[i] == "SEGMENT") {
				return -2;
			}
			else if (listString[i] == "ENDS") {
				//tableAssume(listString, i + 1, true); //add table assume (for proc .386)
				Active_seg = false;
				return 0;
			}
			else if (listString[i] == "ASSUME") {
				tableAssume(listString, i + 1, false);
				return -4;
			}
			else if ((listString[i] == "IF") || (listString[i] == "ELSE") || (listString[i] == "ENDIF")) {
				return -4; //tab and if else endif
			}
			else if (listString[i] == "END")
				return -4; //tab 
			break;
		case 4:
			if (listString[i] == "STI") {
				tableCommand[number].push_back(251);
				return 1;
			}
			else if (listString[i] == "DEC") {
				if (regex_match(listString[i + 1], typeRegisters)) {
					tableCommand[number].push_back(254);
					tableCommand[number].push_back(memR32(typeRegistersString(listString[i + 1]), "rg", 8) + 8);
					return 2;
				}
				tableCommand[number].push_back(memR32(listString[i + 1], "rg", 2) + 8);
				return 1;
			}
			else if (listString[i] == "INC") {
				int bufMemory = 0;
				int sizeMemoryBuf = sizeVarible(spaceMem, listString[i + 3], space, spaceCode);
				if (segmentRegisterInCommands(listString, number)) {
					if (sizeMemoryBuf == 1)
						tableCommand[number].push_back(254);
					else if (sizeMemoryBuf == 2) {
						tableCommand[number].push_back(102);
						tableCommand[number].push_back(255);
						++bufMemory;
					}
					else if (sizeMemoryBuf == 4)
						tableCommand[number].push_back(255);
					tableCommand[number].push_back(memR32("ESP", listString[i + 7], 4));
					tableCommand[number].push_back(memR32(listString[i + 5], listString[i + 7], stoi(listString[i + 9])));
				}
				else {
					if (sizeMemoryBuf == 1)
						tableCommand[number].push_back(254);
					else if (sizeMemoryBuf == 2) {
						tableCommand[number].push_back(102);
						tableCommand[number].push_back(255);
						++bufMemory;
					}
					else if (sizeMemoryBuf == 4)
						tableCommand[number].push_back(255);
					tableCommand[number].push_back(memR32("ESP", listString[i + 5], 4));
					tableCommand[number].push_back(memR32(listString[i+3], listString[i+5], stoi(listString[i+7])));
				}
				return (segmentSizeMem(listString, listStroka, i + 1) + bufMemory);
			}
			else if (listString[i] == "AND") {
				if (regex_match(listString[i+1], typeRegisters))
					tableCommand[number].push_back(34);
				else
					tableCommand[number].push_back(35);
				tableCommand[number].push_back(memR32(typeRegistersString(listString[i+3]), typeRegistersString(listString[i+1]), 8));
				return 2;
			}
			else if (listString[i] == "OR") {
				segmentRegisterInCommands(listString, number);
				int bufReg = 0;
				if (regex_match(listString[i + 1], typeRegisters)) {
					++bufReg;
				}
				tableCommand[number].push_back(11);
				tableCommand[number].push_back(memR32("ESP", listString[i + 1], 4));
				tableCommand[number].push_back(memR32(listString[i + 5], listString[i + 7], stoi(listString[i + 9])));
				return (bufReg + segmentSizeMem(listString, listStroka, i + 3));
			}
			else if (listString[i] == "CMP") {
				segmentRegisterInCommands(listString, number);
				return segmentSizeMem(listString, listStroka, i + 1);
			}
			else if (listString[i] == "MOV") {
				if (regex_match(listString[i + 1], typeRegisters))
					return 2;
				return 5;
			}
			else if (listString[i] == "ADD") {
				segmentRegisterInCommands(listString, number);
				return (segmentSizeMem(listString, listStroka, i + 1) + 1);
			}
			else if (listString[i] == "JNZ") {
				int sizeAssume = assume.size();
				for (int j = 0; j < sizeAssume; ++j) {
					if (assume[j][1] == listString[1])
						return 2;
				}
				return 6;
			}
			break;
		case 8:
			if (((space.size() == 0) || (!strInVec(listString[i], space))) && \
				(i < size - 2) && ((listStroka[i + 1] == 10) || (listString[i + 1] == "EQU")) && \
				(Active_seg)) {
				space.push_back(listString[i]);
			}
			else if ((i < size - 2) && (listString[i + 1] == "EQU")) {
				//spaceNum.push_back(-3);
				if (listStroka[i + 2] == 5)
					equConst.push_back(atoi(listString[i + 2].c_str()));
				else
					equConst.push_back(-1);
				return -1;
			}
			else if (((spaceCode.size() == 0) || (!strInVec(listString[i], spaceCode))) && \
				(i < size - 1) && (!Active_seg) && (listStroka[i + 1] == 10)) {
				spaceCode.push_back(listString[i]);
			}
			if ((i < size - 1) && (listStroka[i + 1] == 10)) {
				if (listString[i + 1] == "DB")
					spaceMem.push_back(1);
				else if (listString[i + 1] == "DW")
					spaceMem.push_back(2);
				else if (listString[i + 1] == "DD")
					spaceMem.push_back(4);
			}
			break;
		case 9:
			return (listString[i].size() - 2);
		case 10:
			if ((listString[i] == "DB") && (listStroka[i + 1] == 9)) {
				int sizeStr = listString[i + 1].size();
				for (int k = 1; k < sizeStr - 1; ++k) {
					tableCommand[number].push_back(ascii_cod(listString[i + 1][k]));
				}
				//tableCommand.push_back(atoi(listString[i + 1].c_str()));
				return (sizeStr - 2);
			}
			else if (listString[i] == "DB") {
				int ss = stoi(listString[i + 1], nullptr, 16);
				tableCommand[number].push_back(ss);
				return 1;
			}
			else if (listString[i] == "DW") {
				int ss = stoi(listString[i + 1], nullptr, 16);
				tableCommand[number].push_back(ss);
				return 2;
			}
			else if (listString[i] == "DD") {
				int ss = stoi(listString[i + 1], nullptr, 16);
				tableCommand[number].push_back(ss);
				return 4;
			}
			break;
		default:
			break;
		}
		++i;
	}
	if (i == 0)
		return -3; // string is space
	return bufInt;
}

void element::convert(string& s) {
	int size = s.length();
	for (int i = 0; i < size; ++i)
		s[i] = toupper(s[i]);
}

void element::strChange(string& value, vector<std::string>& str) {
	string bufString = "";
	int sizeValue = value.size();
	int size = 0;
	while (size < sizeValue) {
		if (inCharString(value[size], singleStringLexems)) {
			if (bufString.length() != 0)
				str.push_back(bufString);
			bufString = value[size];
			str.push_back(bufString);
			bufString = "";
			++size;
		}
		else if (value[size] == 'H') {
			bufString += value[size];
			str.push_back(bufString);
			bufString = "";
		}
		bufString += value[size];
		++size;
	}
	if ((bufString.length() != 0) && (bufString[0] != '\0'))
		str.push_back(bufString);
}

bool element::inString(const string &value, const string &str) {
	int size = value.size();
	for (int i = 0; i < size; ++i)
		if (inCharString(value[i], str))
			return true;
	return false;
}

bool element::inStringInd(const string &value, const string &str) {
	int size = value.size();
	int k = 0;
	for (int i = 0; i < size; ++i) {
		if (inCharString(value[i], str))
			++k;
		else
			return false;
	}
	return (k == size);
}

bool element::strInStr(const string &value, const string &str) {
	int size = value.size();
	if (size != str.size())
		return false;
	for (int i = 0; i < size; ++i) {
		if (value[i] != str[i])
			return false;
	}
	return true;
}

bool element::strInVec(const string &value, const vector<string> &str) {
	int size = str.size();
	int k = 0;
	for (int i = 0; i < size; ++i) {
		if (strInStr(value, str[i]))
			return true;
	}
	return false;
}

bool element::inCharString(const char &value, const string &str) {
	return find(str.begin(), str.end(), value) != str.end();
}

int element::findAnalyze(const string &value) {
	if (regex_match(value, directives))
		return 1;
	else if (regex_match(value, directivesType))
		return 10;
	else if (regex_match(value, directivesTypeChange))
		return 11;
	else if (regex_match(value, registers))
		return 2;
	else if (regex_match(value, segmentRegisters))
		return 3;
	else if (regex_match(value, commands))
		return 4;
	else if (regex_search(value, numberChars16))
		return 5;
	else if (inStringInd(value, numberChars))
		return 6;
	else if (inString(value, singleStringLexems))
		return 7;
	else if (inString(value, identifierChars))
		if ((!inCharString(value[0], numberChars)) && (inStringInd(value, identifierChars)) && (value.size() < 9)) {
			return 8;
		}
	return 0;
	return 0;
}

int element::segmentSizeMem(const vector<string> &listString, const vector<int> &listStroka, const int &numb) {
	int number = numb;
	int sizeList = listString.size();
	int sizeSpace = space.size();
	for (; number < sizeList; ++number) {
		if ((listStroka[number] == 8) || (listStroka[number] == 3))
			break;
	}
	if (listStroka[number] == 3)
		return 8;
	for (int i = 0; i < sizeSpace; ++i) {
		if (space[i] == listString[number])
			return 7;
	}
	return 8;
}

void element::tableAssume(const vector<string> &listString, const int &number, bool nothingAssume) {
	int i = number;
	int j;
	int size = listString.size();
	int sizeVec;
	while (i < size - 2) {
		if (listString[i] == "CS")
			assume[0][1] = listString[i + 2];
		else if (listString[i] == "DS")
			assume[1][1] = listString[i + 2];
		else if (listString[i] == "SS")
			assume[2][1] = listString[i + 2];
		else if (listString[i] == "ES")
			assume[3][1] = listString[i + 2];
		else if (listString[i] == "GS")
			assume[4][1] = listString[i + 2];
		else if (listString[i] == "FS")
			assume[5][1] = listString[i + 2];
		i += 4;
	}
}

bool element::segmentRegisterInCommands(const vector<string> &listString, const int &number) {
	int sizeList = listString.size();
	int j = 0;
	while (j < sizeList) {
		if (strInVec(listString[j], spaceCode)) {
			tableCommand[number].push_back(46);
			return true;
		}
		++j;
	}
	int size = listString.size();
	for (int i = 0; i < size; ++i) {
		if (listString[i] == "CS") {
			tableCommand[number].push_back(46);
			return true;
		}
		else if (listString[i] == "DS") {
			tableCommand[number].push_back(62);
			return true;
		}
		else if (listString[i] == "SS") {
			tableCommand[number].push_back(54);
			return true;
		}
		else if (listString[i] == "ES") {
			tableCommand[number].push_back(38);
			return true;
		}
		else if (listString[i] == "FS") {
			tableCommand[number].push_back(100);
			return true;
		}
		else if (listString[i] == "GS") {
			tableCommand[number].push_back(101);
			return true;
		}
	}
	return false;
}

int element::element::ascii_cod(char x) {
	int a;
	a = x;
	return a;
}

void element::assumeInt(vector<vector<string>> &assume) {
	for (int i = 0; i < 6; ++i) {
		assume.push_back(vector<string>(2));
		assume[i][1] = "Nothing";
	}
	assume[0][0] = "CS";
	assume[1][0] = "DS";
	assume[2][0] = "SS";
	assume[3][0] = "ES";
	assume[4][0] = "GS";
	assume[5][0] = "FS";
}

int element::memR32(const string& r32, const string& index, const int &scaled) {
	int scaledBuf = 0;
	switch (scaled) {
	case 2:
		scaledBuf = 1;
		break;
	case 4:
		scaledBuf = 2;
		break;
	case 8:
		scaledBuf = 3;
		break;
	default:
		break;
	}
	if (r32 == "EAX") 
		return (memIndex(index, scaledBuf));
	else if (r32 == "ECX")
		return (memIndex(index, scaledBuf) + 1);
	else if (r32 == "EDX")
		return (memIndex(index, scaledBuf) + 2);
	else if (r32 == "EBX")
		return (memIndex(index, scaledBuf) + 3);
	else if (r32 == "ESP")
		return (memIndex(index, scaledBuf) + 4);
	else if (r32 == "EBP")
		return (memIndex(index, scaledBuf) + 5);
	else if (r32 == "ESI")
		return (memIndex(index, scaledBuf) + 6);
	else if (r32 == "EDI")
		return (memIndex(index, scaledBuf) + 7);
	return 0;
}

int element::memIndex(const string& index, const int &scaled) {
	if (index == "EAX")
		return (scaled * 64);
	else if (index == "ECX")
		return (scaled * 64 + 8);
	else if (index == "EDX")
		return (scaled * 64 + 16);
	else if (index == "EBX")
		return (scaled * 64 + 24);
	else if (index == "ESP")
		return (scaled * 64 + 40);
	else if (index == "EBP")
		return (scaled * 64 + 40);
	else if (index == "ESI")
		return (scaled * 64 + 48);
	else if (index == "EDI")
		return (scaled * 64 + 56);
	return (scaled * 64);
}

string element::typeRegistersString(const string& type) {
	if ((type == "AL") || (type == "AX"))
		return "EAX";
	else if ((type == "CL") || (type == "CX"))
		return "ECX";
	else if ((type == "DL") || (type == "DX"))
		return "EDX";
	else if ((type == "BL") || (type == "BX"))
		return "EBX";
	else if ((type == "AH") || (type == "SP"))
		return "ESP";
	else if ((type == "CH") || (type == "BP"))
		return "EBP";
	else if ((type == "DH") || (type == "SI"))
		return "ESI";
	else if ((type == "BH") || (type == "DI"))
		return "EDI";
	return type;
}


int element::sizeVarible(const vector<int> &memory, const string& value, const vector<string> &space, const vector<string> &spaceCode) {
	int size = memory.size();
	for (int i = 0; i < size; ++i) {
		if ((i < space.size()) && (value == space[i]))
			return memory[i];
		else if ((i < spaceCode.size()) && (value == spaceCode[i]))
			return memory[i];
	}
	return 0;
}