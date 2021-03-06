// a.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
map<string, int> word_count;
map<string, int>::iterator iter;
vector<pair<int, string> > vec;

int count_ch();
int count_word();
int count_line();
bool cmp(pair<int, string> a, pair<int, string> b);
void MapSortOfValue(vector<pair<int, string> >& vec, map<string, int>& m);
int main()
{
	ofstream out("result.txt");
	if (out.is_open())
	{
		out << "characters: " << count_ch() << endl;
		out << "words: " << count_word() << endl;
		out << "lines: " << count_line() << endl;
		MapSortOfValue(vec, word_count);
		for (int i = 0;i < vec.size() && i < 10;i++)
			out << "<" << vec[i].second.c_str() << ">:" << vec[i].first << endl;
		out.close();
	}
	return 0;
}
int count_ch()
{
	char ch;
	int num = 0;
	ifstream in("input.txt");
	if (!in.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	while (!in.eof())
	{
		in.get(ch);
		num++;
	}
	in.close();
	return num;
}
int count_word()
{
	int num = 0, flag = 0, count = 0;
	char ch, word[100];

	ifstream in("input.txt");
	if (!in.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	while (!in.eof())
	{
		in.get(ch);
		if (count < 4 && ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')))
		{
			if (ch >= 'A'&&ch <= 'Z')ch += 32;
			word[count++] = ch;
		}
		else if (count >= 4 && ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z') || (ch >= '0'&&ch <= '9')))
		{
			if (ch >= 'A'&&ch <= 'Z')ch += 32;
			word[count++] = ch;
		}
		else
		{
			if (count >= 4)
			{
				num++;
				++word_count[word];
			}
			count = 0;
			for (int i = 0;i < 30;i++)
				word[i] = '\0';
		}
	}
	if (count >= 4)
	{
		word[count - 1] = '\0';
		num++;
		++word_count[word];
	}
	in.close();
	return num;
}
int count_line()
{
	char ch[10000];
	int num = 0;
	ifstream in("input.txt");
	if (!in.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	while (!in.eof())
	{
		in.getline(ch, 10000);
		if (ch[0] != '\0')
			num++;
	}
	in.close();
	return num;
}
bool cmp(pair<int, string> a, pair<int, string> b)
{
	return (a.first != b.first) ? a.first > b.first:a.second < b.second;
}
void MapSortOfValue(vector<pair<int, string> >& vec, map<string, int>& m)
{
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++)
		vec.push_back(make_pair(it->second, it->first));
	sort(vec.begin(), vec.end(), cmp);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
