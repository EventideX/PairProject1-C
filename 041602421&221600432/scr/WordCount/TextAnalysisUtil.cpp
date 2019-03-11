#include "pch.h"
#include "TextAnalysisTool.h"
#include <fstream>
#include <iostream>
using namespace std;

TextAnalysisUtil::TextAnalysisUtil()
{
}


TextAnalysisUtil::~TextAnalysisUtil()
{
}

int TextAnalysisUtil::asciiCount()
{
	ifstream fin("temp.txt");
	if (!fin)
	{
		 cout<< "cuowu";
	}
	char ch;
	int count=0;
	while (fin.get(ch))
	{
		if(isAsascii(ch))
			count++;
	}
	
	return count;
}

bool TextAnalysisUtil::isAsascii(char c)
{
	return ((unsigned char)c & 0x80) == 0x80 ? false : true;
}
