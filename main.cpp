#pragma once
#include "analyze.h"
#include "syntax.h"
#include "grammar.h"

int main() {
	setlocale(LC_ALL, "");
	element list;
	analyze sp;
	syntax sn;
	grammar gr;
	string fileName = "test.asm";
	string fileRecord = "info.txt";
	ofstream fr;
	fr.open(fileRecord);
	list.ReadFromFile(fileName);
	gr.vivodGrammar(list, fr);
	//sp.vivod(list, fr);
	//sn.vivodSentence(list, fr);
	fr.close();
	return 0;
}