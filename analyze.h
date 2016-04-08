#pragma once
#include "elements.h"

class analyze : public element {
public:
	void vivod(element& list, ofstream& fileRecord) {
		int size = list.list.size();
		for (int i = 0; i < size; ++i) {
			if (list.listInfo[i].size() != 0)
				table(i + 1, list.list[i], list.listInfo[i], fileRecord);
		}
	}

	void table(int list, const vector<string> &array, const vector<int>& listStroka, ofstream& fr) {
		fr << "<";
		cout << "<";
		for (int i = 0; i < 70; ++i) {
			if (i == 35) {
				fr << " string " << list << " ";
				cout << " string " << list << " ";
			}
			fr << "-";
			cout << "-";
		}
		fr << ">\n Num" << "Leksema\t\t" << "lenght\t\t\t" << "type leksema\n";
		cout << ">\n Num \t" << "Leksema\t\t" << "lenght\t\t\t" << "type leksema\n";
		
		int size = array.size();
		for (int i = 0; i < size; ++i) {
			fr << "  " << i + 1 << "\t" << array[i] << "\t\t  " << array[i].size() << "\t   ";
			cout << "  " << i + 1 << "\t" << array[i] << "\t\t  " << array[i].size() << "\t   ";
			switch (listStroka[i]) {
			case 1:
			case 10:
			case 11:
				fr << "Data Identifier directive\n";
				cout << "Data Identifier directive\n";
				break;
			case 2:
				fr << "Identifier 32-bit address register\n";
				cout << "Identifier 32-bit address register\n";
				break;
			case 3:
				fr << "Identifier segment registers\n";
				cout << "Identifier segment registers\n";
				break;
			case 4:
				fr << "Identifier mnemokods machine instructions\n";
				cout << "Identifier mnemokods machine instructions\n";
				break;
			case 5:
				fr << "Sixteenth constant\n";
				cout << "Sixteenth constant\n";
				break;
			case 6:
				fr << "Tenth constant\n";
				cout << "Tenth constant\n";
				break;
			case 7:
				fr << "A one-character\n";
				cout << "A one-character\n";
				break;
			case 8:
				fr << "Identifier or user defined\n";
				cout << "Identifier or user defined\n";
				break;
			case 9:
				fr << "Text constant\n";
				cout << "Text constant\n";
				break;
			default:
				fr << "Error\n";
				cout << "Error\n";
				break;
			}
		}
		fr << "<";
		cout << "<";
		for (int i = 0; i < 66; ++i) {
			if (i == 33) {
				fr << " end string " << list << " ";
				cout << " end string " << list << " ";
			}
			fr << "-";
			cout << "-";
		}
		fr << ">\n\n";
		cout << ">\n\n";
	}
private:
	int i;
	int size;
	int sizeInt;
	ofstream fr;
};