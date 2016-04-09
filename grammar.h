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
		int iCur = 0;
		bool flNumb;
		for (int i = 0; i < size; ++i) {
			sizeStr = list.list[i].size();
			//equ (=<memory>)
			if (list.memory[i] == -1) {
				if (list.equConst[equ] != -1) {
					cout << " =" << setfill('0') << setw(4) << hex << list.equConst[equ];
					fileRecord << " =" << setfill('0') << setw(4) << hex << list.equConst[equ];
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
				else if ((k < sizeList - 1) && ((list.listInfo[i][k] == 4) && (list.listInfo[i][k + 1] == 3)) || \
					(list.listInfo[i][k] == 8) && (strInVec(list.list[i][k], list.spaceCode)) && ((list.listInfo[i][k + 1] != 10))) {
					iCur = 0;
					cout << " " << hex << uppercase << list.tableCommand[i][0] << ":";
					fileRecord << " " << hex << uppercase << list.tableCommand[i][0] << ":";
					++iCur;
				}
				//logical segment commands and register
				else if ((list.listInfo[i][k] == 8) && (k < sizeList - 1) && (list.listInfo[i][k+1] != 10)) {
					sizeCom = list.tableCommand[i].size();
					for (; iCur < sizeCom; ++iCur) {
						cout << " " << hex << uppercase << list.tableCommand[i][iCur];
						fileRecord << " " << hex << uppercase << list.tableCommand[i][iCur];
					}
					iCur = 0;
					sizeCom = list.spaceNum.size();
					for (int j = 0; j < sizeCom; ++j) {
						if ((j < list.space.size()) && (list.list[i][k] == list.space[j])) {
							cout << " " << setfill('0') << setw(8) << hex << uppercase << list.spaceNum[j] << " R";
							fileRecord << " " << setfill('0') << setw(8) << hex << uppercase << list.spaceNum[j] << " R";
							break;
						}
						else if ((j < list.spaceCode.size()) && (list.list[i][k] == list.spaceCode[j])) {
							cout << " " << setfill('0') << setw(8) << hex << uppercase << list.spaceNum[list.space.size()-j] << " R";
							fileRecord << " " << setfill('0') << setw(8) << hex << uppercase << list.spaceNum[list.space.size()-j] << " R";
							break;
						}
					}
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