#include "pch.h"
#include "../Core/Core.h"
#include <iostream>

constexpr size_t exportWordLines = 10;

int main()
{
	using std::cout;
	using std::endl;
	auto a = CalculateWordCount("Z:\\11.txt");
	cout << "characters: " << a.characters << endl;
	cout << "words: " << a.words << endl;
	cout << "lines: " << a.lines << endl;
	for (size_t i = 0; i < min(a.uniqueWords, exportWordLines); i++) {
		cout << a.wordAppears[i].word << ": " << a.wordAppears[i].count << endl;
	}
	ClearWordAppear(&a);
}