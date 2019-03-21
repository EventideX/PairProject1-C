#include "pch.h"
#include "../Core/Core.h"
#include <iostream>
#include <fstream>

constexpr size_t exportWordLines = 10;

int main(int argc, const char** argv)
{
	using std::cout;
	using std::cerr;
	using std::endl;
	if (argc < 2) {
		cerr << "No filename";
		exit(255);
	}
	std::ofstream fout("result.txt");
	auto a = CalculateWordCount(argv[1]);
	if (a.errorCode == WORDCOUNTRESULT_SUCCEED) {
		fout << "characters: " << a.characters << endl;
		fout << "words: " << a.words << endl;
		fout << "lines: " << a.lines << endl;
		for (size_t i = 0; i < min(a.uniqueWords, exportWordLines); i++) {
			fout << "<" << a.wordAppears[i].word << ">: " << a.wordAppears[i].count << endl;
		}
	}
	else {
		switch (a.errorCode) {
		case WORDCOUNTRESULT_OPEN_FILE_FAILED:
			cerr << "Open file failed";
			exit(255);
			break;
		}
	}
	ClearWordAppear(&a);
}
