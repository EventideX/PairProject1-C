#pragma once
#include<string.h>
#include <string>
#include<vector>
#include<list>
using namespace std;
struct words {
	int times;//���ִ���
	string s;//����	
	words(string b, int a) {
		times = a;
		s = b;
	};//��ŵ��ʺͳ��ִ����Ľṹ
};
__declspec(dllexport) int countAscii(string);
__declspec(dllexport) list<words> sortWord(string);
__declspec(dllexport) int countLines(string);
__declspec(dllexport) int countWordNumbers(string);