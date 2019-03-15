#pragma once
#include<string.h>
#include <string>
#include<vector>
#include<list>
using namespace std;
struct words {
	int times;//出现次数
	string s;//单词	
	words(string b, int a) {
		times = a;
		s = b;
	};//存放单词和出现次数的结构
};
__declspec(dllexport) int countAscii(string);
__declspec(dllexport) list<words> sortWord(string);
__declspec(dllexport) int countLines(string);
__declspec(dllexport) int countWordNumbers(string);