// core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "core.h"
#include<iostream>
#include<stdio.h>
#include<string.h>
#include <string>
#include<stdlib.h>
#include<vector>
#include<list>
#include<fstream>
using namespace std;
void sortWord(list<words> &a) {//对单词出现次数排序
	a.sort([](words x, words y) {
		if (x.times != y.times)
			return x.times > y.times;
		else {
			if (x.s[0] > 90 && y.s[0] < 91)
				return (x.s[0] - 32) < y.s[0];
			else if (x.s[0] < 91 && y.s[0] > 91)
				return x.s[0] < (y.s[0] - 32);
			else
				return x.s[0] < y.s[0];
		}
	});
}
int isRightWord(string s)//判断是否是符合定义的单词 
{
	if (s.size() < 4)
		return 0;
	int i;	int x = 0;
	for (i = 0; i < 4; i++)
	{
		if (s[i] <= 'z' && s[i] >= 'a')
			x++;
		else if (s[i] <= 'Z' && s[i] >= 'A')
			x++;
	}
	if (x != 4 || sizeof(s) < 4)
		return 0;
	else
		return 1;
}
int isLlegal(char a)        //判断是否为单词的组成部分
{
	if (a <= 'z' && a >= 'a')
	{
		return 1;
	}
	else if (a <= 'Z' && a >= 'A')
	{
		return 1;
	}
	else if ('0' <= a && a <= '9') {
		return 1;
	}
	else
		return 0;
}
void addToList(list<words> &a, string s)
{

	int i = 1;
	for (auto &x : a) {
		if (s == x.s)
		{
			x.times++;
			i = 0;
			break;
		}
		else {
		}
	}
	if (i == 1) {
		a.push_back(words(s, 1));

	}

}
void IsWord(string s, list<words>&a)    //统计单词
{
	int i = 0, j = 0;
	string word;

	for (int k = 0; k < s.size(); k++)
	{
		if (!isLlegal(s[k]))
		{
			if (isRightWord(word))
			{
				addToList(a, word);
			}
			//j = 0;
			word = "";
		}
		else
		{
			word.push_back(s[k]);
		}

	}
}
int countLines(string s) {
	ifstream pFile;
	string buffer;
	pFile.open(s); // 打开文件
	int count = 0;
	for (string temp; getline(pFile, temp);) {
		if (temp != "") {
			buffer += temp;
			count++;
		}
	}
	//cout << "lines：" << count << endl;
	pFile.close();
	return count;
}
list<words> sortWord(string s) {
	list<words> v;
	ifstream pFile;
	string buffer;
	pFile.open(s); // 打开文件
	for (string temp; getline(pFile, temp);) {

		if (temp != "") {
			buffer += temp;
			buffer += '\n';
		}
	}
	IsWord(buffer, v);
	sortWord(v);
	int i = 0;
	list<words> f;
	for (auto &x : v) {
		//cout << x.s <<":"<< x.times << endl;
		f.push_back(words(x.s, x.times));
		i++;
		if (i >= 10)
			break;
	}
	pFile.close();
	return f;
}
int countAscii(string s) {
	ifstream pFile;
	string buffer;
	int count = 0;
	pFile.open(s); // 打开文件
	for (string temp; getline(pFile, temp);) {
		buffer += temp;
	}
	for (int i = 0; i < buffer.size(); i++)
	{
		if (buffer[i] >= 0 && buffer[i] <= 127)//判断是否是ASCII码
			count++;
	}
	//cout << "character:" << count << endl;
	pFile.close();
	return count;
}
int countWordNumbers(string s) {//计数单词个数
	list<words> v;
	ifstream pFile;
	string buffer;
	pFile.open(s); // 打开文件
	for (string temp; getline(pFile, temp);) {
		//cout << temp<<endl;
		if (temp != "") {
			buffer += temp;
			buffer += '\n';
		}
	}
	IsWord(buffer, v);
	int count = 0;
	for (auto &x : v) {
		count += x.times;
	}
	//cout << "words:" << count << endl;
	return count;
}


