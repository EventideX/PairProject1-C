#pragma once
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;
struct WordInf
{
		string word;
		int count;
		WordInf() {
			word = "";
			count = 0;
		}
		
	
};
class TextAnalysisUtil
{
public:
	
	TextAnalysisUtil();
	~TextAnalysisUtil();
	int asciiCount(char * fileName);
	bool isAsascii(char ch);
	int countLines(char * filename);
	int wordAnalysis(char * fileName,WordInf * tempArr);
	

};

