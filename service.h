#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <sstream>
#include <regex> 

using namespace std;

const regex directives("END|SEGMENT|ENDS|PTR|EQU|ASSUME|IF|ELSE|ENDIF"); //1 directives
const regex registers("EAX|ECX|EDX|EBX|ESP|EBP|ESI|EDI|AL|CL|DL|BL|AH|CH|DH|BH"); //2 register
const regex segmentRegisters("CS|DS|SS|ES|FS|GS"); //3 segment registers
const regex commands("STI|DEC|INC|AND|OR|CMP|MOV|ADD|JNZ"); //4 commands
const regex numberChars16("[0-9ABCDEF]+H"); //5 16th number

const string numberChars("1234567890"); //6 number
const string singleStringLexems(",:()[]+-*"); //7 a one symbol
const string identifierChars("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@"); //8 identificator

//9 text constant

const regex directivesType("DB|DW|DD"); // 10 directive type
const regex directivesTypeChange("BYTE|WORD|DWORD"); // 11 directive type 

const regex codeCommands("000|001|010|011|101|110|111"); // code for commands
const regex typeRegisters("AL|CL|DL|BL|AH|CH|DH|BH"); // 8-bit registers