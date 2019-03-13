#pragma once
class TextAnalysisUtil
{
public:
	
	TextAnalysisUtil();
	~TextAnalysisUtil();
	int asciiCount();
	bool isAsascii(char ch);
	int countLines(char * filename);
	void wordAnalysis();

};

