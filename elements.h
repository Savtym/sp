#pragma once
#include <set>
#include <fstream>
#include <vector>
#include <string> 
#include "service.h"

class element {
public:
	vector<vector<string>> list;
	vector<vector<string>> assume;
	vector<vector<int>> listInfo;
	vector<vector<int>> grammar;
	vector<vector<int>> tableCommand;
	vector<string> space;
	vector<string> spaceCode;
	vector<bool> ERROR;
	vector<int> equConst;
	vector<int> spaceNum;
	vector<int> spaceMem;
	vector<int> memory;
	bool end = false;

	element() {};
	~element() {};

	//download with file.asm
	bool ReadFromFile(string& fileName);
	//syntax analyze
	bool syntax(const vector<int> &listStroka, const vector<string> &listString, vector<int> &listGrammar);
	//memory and grammar analyze
	int memoryVec(const vector<int> &listStroka, const vector<string> &listString, vector<int> &listGrammar, int &listNumber);

	//toupper string
	void convert(string& s);
	//splits the string
	void strChange(string& value, vector<std::string>& str);
	//find in the string
	bool inString(const string &value, const string &str);
	//find number in the string
	bool inStringInd(const string &value, const string &str);
	//string comparison
	bool strInStr(const string &value, const string &str);
	//find the string in the vector<string>
	bool strInVec(const string &value, const vector<string> &str);
	//find the char in the string
	bool inCharString(const char &value, const string &str);
	//analyze of vector<string>
	int findAnalyze(const string &value);
	//memory in the segment
	int segmentSizeMem(const vector<string> &listString, const vector<int> &listStroka, const int &numb);
	//table assume
	void tableAssume(const vector<string> &listString, const int &number, bool nothingAssume);
	//segment register in commands
	bool segmentRegisterInCommands(const vector<string> &listString, const int &number);
	//ascii cod the char
	int ascii_cod(char x);
	//contain table assume
	void assumeInt(vector<vector<string>> &assume);
	//mem Register 32
	int memR32(const string& r32, const string& index, const int &scaled);
	//add function mem Register 32
	int memIndex(const string& index, const int &scaled);
	//type register 8 bit and 32 bit
	string typeRegistersString(const string& type);
	//size variable DB DW DD
	int sizeVarible(const vector<int> &memory, const string& value, const vector<string> &space, const vector<string> &spaceCode);
	//if memory error
	bool memoryError(const vector<string> &listString, const vector<int> &listStroka);


private:
	int number;
	bool Active_seg = true;
	string segmentData;
	ifstream f;
	vector<char> st;
	vector<std::string> strokaBuf;
	string buf;
	string bufWord;
};