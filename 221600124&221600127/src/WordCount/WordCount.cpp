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

int countChar(FILE *file) {
	fseek(file, 0, SEEK_SET);
	int cnt = 0;
	char c;
	while (fscanf_s(file, "%c", &c, sizeof(char)) != EOF) {
		if (c < 0 || c>255) continue;
		cnt++;
	}
	return cnt;
}

int countWord(FILE *file) {
	fseek(file, 0, SEEK_SET);
	int cnt = 0;
	int alacnt = 0;
	char c;
	while (fscanf_s(file, "%c", &c, sizeof(char)) != EOF) {
		if (c < 0 || c>255) continue;
		if (isalpha(c) || isdigit(c) && alacnt >= 4) alacnt++;
		if (alacnt < 4 && !isalpha(c)) alacnt = 0;
		if (alacnt >= 4 && !(isalpha(c) || isdigit(c))) alacnt = 0;
		if (alacnt == 4) cnt++;
	}
	return cnt;
}

int countLine(FILE *file) {
	fseek(file, 0, SEEK_SET);
	int cnt = 0;
	char c;
	bool isline = false;
	while (fscanf_s(file, "%c", &c, sizeof(char)) != EOF) {
		if (c < 0 || c>255) continue;
		if (!(c >= 0 && c <= 32 || c == 127)&&!isline) {
			isline = true;
			cnt++;
		}
		if (c == '\n') isline = false;
	}
	return cnt;
}

int countFre(FILE *file) {
	fseek(file, 0, SEEK_SET);
	char c;
	string temp="";
	int alacnt = 0;
	int w_cnt = 0;
	while (fscanf_s(file, "%c", &c, sizeof(char)) != EOF) {
		if (c < 0 || c>255) continue;
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
			for (int i = 0; i < (int)temp.length(); i++)
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
	}
	if (alacnt >= 4) {
		bool found = false;
		for (int i = 0; i < (int)temp.length(); i++)
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
	return w_cnt;
}

int main(int argc,char* argv[])
{
	FILE *in,*out;
	errno_t err;
	if ((err = fopen_s(&in, argv[1], "r")) != 0) {
		printf("Open file failed!");
		exit(0);
	}
	if ((err = fopen_s(&out, "result.txt", "w")) != 0) {
		printf("Open file failed!");
		exit(0);
	}
	int w_cnt = countFre(in);
	fprintf(out,"characters: %d\n", countChar(in));
	fprintf(out,"words: %d\n", countWord(in));
	fprintf(out,"lines: %d\n", countLine(in));
	for (int i = w_cnt-1; i >=0; i--) {
		fprintf(out, "<%s>: %d\n", word[i].c_str(),times[i]);
		if (i == w_cnt - 10) break;
	}
	fclose(in);
    return 0;
}

