#include "pch.h"
#include "TextAnalysisUtil.h"
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
	WordInf()
	{
		count = 0;
	}
};
TextAnalysisUtil::TextAnalysisUtil()
{
}


TextAnalysisUtil::~TextAnalysisUtil()
{
}

bool isWordGreater(string str1, int n1, string str2, int n2)
{
	bool flag;
	if (n1 > n2)
	{
		flag = true;
	}
	else if(n1 < n2)
	{
		flag = false;
	}
	else
	{
		flag = strcmp(str1.c_str(), str2.c_str()) > 0 ? true : false;
	}
	return flag;
}

int TextAnalysisUtil::asciiCount()
{
	//调试用
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

int TextAnalysisUtil::countLines(char * filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename, ios::in);
	while (getline(ReadFile, tmp, '\n'))
	{
		if (tmp.length() == 0)
		{
			continue;

		}
		n++;


	}
	ReadFile.close();
	return n;
}

void TextAnalysisUtil::wordAnalysis()
{
	ifstream fin("D:\\搜狗高速下载\\测试样例\\测试样例\\input1.txt");
	if (!fin)
	{
		cout << "cuowu";
	}
	char ch;
	string str;
	int state = 0;
	int nflag;
	int wordCount = 0;
	WordInf tempArr[10];
	unordered_map<string, int> map;
	while (fin.get(ch))
	{
		switch (state)
		{
		case 0:
			//查找单词首的状态
			if (isdigit(ch))
			{
				//转入找到数字开头的过滤状态
				state = 1;
			}				
			else if (isalpha(ch))
			{
				//找到单词，转入爬取单词状态
				state = 2;
				str = ch;
				nflag = 1;//记录单词开头字母数
			}
			break;
		case 1:
			//转入找到数字开头或不符合单词开头有4个字母的过滤状态
			if (!(isdigit(ch)||isalpha(ch)))
			{
				state = 0;
			}
			break;
		case 2:
			//爬取单词状态
			if (isalpha(ch))
			{
				++nflag;
				str += ch;
				if (nflag >= 4)
					//进入爬取单词尾部状态
					state = 3;
			}
			else
			{
				//不满足单词开头有4个字母
				state = 1;
			}
			break;
		case 3:
			//爬取单词尾部状态
			if (isdigit(ch) || isalpha(ch))
			{
				str += ch;
			}
			else
			{
				//处理和存入字符串
				transform(str.begin(), str.end(), str.begin(), ::tolower);
				state = 0;
				if (map[str] == 0)
				{
					wordCount++;
				}
				map[str]++;
			}
			break;
		default:
			break;
		}
		
	}
	//遍历找出频率最高的top10单词
	for (auto iter = map.begin(); iter != map.end(); iter++)
	{
		if (isWordGreater(iter->first, iter->second, tempArr[9].word, tempArr[9].count))
		{
			tempArr[9].word = iter->first;
			tempArr[9].count = iter->second;
			for (int i = 9; i >= 1; i--)
			{
				if (isWordGreater(tempArr[i].word, tempArr[i].count, tempArr[i - 1].word, tempArr[i - 1].count))
				{
					swap(tempArr[i], tempArr[i - 1]);
				}
			}
		}
	}
}
