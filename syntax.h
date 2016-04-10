#pragma once
#include "elements.h"

class syntax : element {
public:
	void vivodSentence(element& list, ofstream& fileRecord) {
		cout << "\n    Field Tag\t\t" << "field mnemokod\t\t\t" << "1st operand\t\t\t" << "2st operand\n";
		cout << "    ¹ field\t" << "¹1st field\t" << "number fields\t" << "¹1st operand\t" << "number operands\t " << "¹1st operand\t" << "number operands\n";
		fileRecord << "\n    Field Tag\t\t" << "field mnemokod\t\t\t" << "1st operand\t\t\t" << "2st operand\n";
		fileRecord << "    ¹ field\t" << "¹1st field\t" << "number fields\t" << "¹1st operand\t" << "number operands\t " << "¹1st operand\t" << "number operands\n";
		int size = list.listInfo.size();
		int sizeVec;
		int i = 0;
		int j = 0;
		bool fl = true;
		int sizeAnal;
		while ((fl) && (i < size)) {
			fileRecord << " " << i + 1;
			cout << " " << i + 1;
			sizeVec = list.grammar[i].size();
			j = 0;
			while ((fl) && (j < sizeVec)) {
				if (list.grammar[i][j] != -1) {
					if (j == 0) {
						fileRecord << "\t" << list.grammar[i][j];
						cout << "\t" << list.grammar[i][j];
					}
					else {
						fileRecord << setw(15) << list.grammar[i][j];
						cout << setw(15) << list.grammar[i][j];
					}
				}
				else {
					fileRecord << "\nERROR\n";
					cout << "\nERROR\n";
					fl = false;
				}
				++j;
			}
			fileRecord << '\n';
			cout << '\n';
			++i;
		}
	}

private:
	ofstream fr;
};