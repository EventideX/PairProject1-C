// WordCount.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

int times[100005] = {};
string word[100005] = {};

int main(int argc,char* argv[])
{
	FILE *fp1,*fp2;
	errno_t err;
	if ((err = fopen_s(&fp1, argv[1], "r")) != 0) {
		printf("Open file failed!");
		exit(0);
	}
	if ((err = fopen_s(&fp2, "result.txt", "w")) != 0) {
		printf("Open file failed!");
		exit(0);
	}
	char c;
	int characters = 0;
	int words = 0;
	int lines = 0;
	int alacnt = 0;
	int w_cnt = 0;
	bool isline = false;
	string temp = "";
	while (fscanf_s(fp1, "%c", &c, sizeof(char)) != EOF) {
		characters++;
		if (isalpha(c) || isdigit(c) && alacnt >= 4) {
			temp += c;
			alacnt++;
		}
		if (alacnt < 4 && !isalpha(c)) {
			temp = "";
			alacnt = 0;
		}
		if (alacnt >= 4 && !(isalpha(c) || isdigit(c))) {
			bool found = false;
			for (int i = 0; i < temp.length(); i++)
				temp[i] = tolower(temp[i]);
			for (int i = 0; i < w_cnt; i++) {
				if (temp == word[i]) {
					times[i]++;
					found = true;
					break;
				}
			}
			if (!found) {
				word[w_cnt] = temp;
				times[w_cnt]++;
				w_cnt++;
			}
			temp = "";
			alacnt = 0;
		}
		if (alacnt == 4) words++;
		if (!(c >= 0 && c <= 32 || c == 127)) {
			if (!isline) {
				isline = true;
				lines++;
			}
		}
		if (c == '\n') {
			isline = false;
		}
	}
	for (int i = 0; i < w_cnt - 1; i++) {
		for (int j = 0; j < w_cnt - 1 - i; j++) {
			if (times[j] > times[j + 1] || times[j] == times[j + 1] && word[j] < word[j + 1]) {
				int temp;
				temp = times[j];
				times[j] = times[j + 1];
				times[j + 1] = temp;
				string s_temp;
				s_temp = word[j];
				word[j] = word[j + 1];
				word[j + 1] = s_temp;
			}
		}
	}
	fprintf(fp2,"characters: %d\n", characters);
	fprintf(fp2,"words: %d\n", words);
	fprintf(fp2,"lines: %d\n", lines);
	for (int i = w_cnt-1; i >=0; i--) {
		fprintf(fp2, "<%s>: %d\n", word[i].c_str(),times[i]);
		//cout << "<" << word[i] << ">: " << times[i]<<endl;
		if (i == w_cnt - 10) break;
	}
	fclose(fp1);
    return 0;
}

