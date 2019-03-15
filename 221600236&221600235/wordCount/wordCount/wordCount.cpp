#include "pch.h"
#include <iostream>
#include<fstream>
#include"core.h"

int main(int argc, char* argv[])
{
	list<words> a;
	string b = "result.txt";
	//	string c = "input.txt";
	ofstream pFile;
	pFile.open(b); // 打开文件
	pFile << "character:" << countAscii(argv[1]) << endl;
	pFile << "words:" << countWordNumbers(argv[1]) << endl;
	pFile << "lines:" << countLines(argv[1]) << endl;
	a = sortWord(argv[1]);
	for (auto x : a)
		pFile << x.s << ":" << x.times << endl;
}