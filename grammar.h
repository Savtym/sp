#pragma once
#include "elements.h"

class grammar : element {
public:
	void vivodGrammar(element& list, ofstream& fileRecord) {
		int size = list.listInfo.size();
		int sizeList;
		int sizeCom;
		int sizeStr;
		int equ = 0;
		bool flNumb;
		for (int i = 0; i < size; ++i) {
			sizeStr = list.list[i].size();
			//equ (=<memory>)
			if (list.memory[i] == -1) {
				if (list.equConst[equ] != -1) {
					printf(" =%04X\t", list.equConst[equ]);
					fileRecord << " = " << hex << list.equConst[equ];
				}
				else
					printf(" = ");
				++equ;
			}
			//the string without memory 
			else if (list.memory[i] == -4) {
				printf(" \t");
				fileRecord << " \t";
			}
			//without space of string
			else if (list.memory[i] != -3) {
				printf("  %04X \t", list.memory[i]);
				fileRecord << "  " << setfill('0') << setw(4) << hex << uppercase << toupper(list.memory[i]) << "  ";
			}
			sizeList = list.listInfo[i].size();
			for (int k = 0; k < sizeList; ++k) {
				//directive type const
				if ((list.listInfo[i][k] == 10) && (list.listInfo[i][k+1] != 9)) {
					if (list.list[i][k] == "DB") {
						cout << " " << setfill('0') << setw(2) << hex << uppercase << toupper(list.tableCommand[i][0]) << "  ";
						fileRecord << " " << setfill('0') << setw(2) << hex << uppercase << list.tableCommand[i][0] << "  ";
					}
					else if (list.list[i][k] == "DW") {
						cout << " " << setfill('0') << setw(4) << hex << uppercase << list.tableCommand[i][0] << "  ";
						fileRecord << " " << setfill('0') << setw(4) << hex << uppercase << list.tableCommand[i][0] << "  ";
					}
					else if (list.list[i][k] == "DD") {
						cout << " " << setfill('0') << setw(8) << hex << uppercase << list.tableCommand[i][0] << "  ";
						fileRecord << " " << setfill('0') << setw(8) << hex << uppercase << list.tableCommand[i][0] << "  ";
					}
					break;
				}
				//text constant
				else if (list.listInfo[i][k] == 9) {
					sizeCom = list.tableCommand[i].size();
					int j = 0;
					while (j < sizeCom) {
						cout << " " << hex << uppercase << list.tableCommand[i][j];
						fileRecord << " " << hex << uppercase << list.tableCommand[i][j];
						++j;
					}
					break;
				}
				//for segment reigister ":"
				else if (list.listInfo[i][k] == 4) {
					sizeCom = list.tableCommand[i].size();
					int sizeListInfo = list.listInfo[i].size();
					int j = 0;
					for (int l = k + 1; l < sizeList; ++l) {
						if ((k < sizeListInfo - 1) && ((list.listInfo[i][k + 1] == 3) || (strInVec(list.list[i][l], list.spaceCode)))) {
							cout << " " << hex << uppercase << list.tableCommand[i][j] << ":";
							fileRecord << " " << hex << uppercase << list.tableCommand[i][j] << ":";
							++j;
							break;
						}
					}
					while (j < sizeCom) {
						cout << " " << hex << uppercase << list.tableCommand[i][j];
						fileRecord << " " << hex << uppercase << list.tableCommand[i][j];
						++j;
					}
					break;
				}
			}
			for (int j = 0; j < sizeStr; ++j) {
				cout << ' ' << list.list[i][j];
				fileRecord << ' ' << list.list[i][j];
			}
			cout << '\n';
			fileRecord << '\n';
		}
	}


private:
};