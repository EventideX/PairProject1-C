// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Core.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

#define EXTERN extern "C" __declspec(dllexport)

constexpr size_t wordAtLeastCharacterCount = 4;

constexpr bool isAlphabet(const char c) {
	return (c >= 'a' && c <= 'z');
}

constexpr bool isNumber(const char c) {
	return (c >= '0' && c <= '9');
}

constexpr bool isLetter(const char c) {
	return (isAlphabet(c) || isNumber(c));
}

constexpr bool isLf(const char c) {
	return (c == '\n');
}

constexpr bool isCr(const char c) {
	return (c == '\r');
}

constexpr bool isSeparator(const char c) {
	return !isLetter(c); // 空格是个冗余条件，删除
}

constexpr bool isEmptyChar(const char c) {
	return c <= 32 && c != 127;
}

constexpr bool isCharacter(const char c) {
	return !isEmptyChar(c) || c == ' ' || c == '\t' || c == '\n';
}

typedef std::pair<std::string, size_t> WordCountPair;

EXTERN WordCountResult CalculateWordCount(const char * fileName)
{
	auto ret = WordCountResult();
	bool runStateMachine = true;
	char c = 0;
	std::ifstream file(fileName);
	std::string word = ""; // 不想做动态分配内存，std::string省事 
	size_t wordLength = 0; // <= wordAtLeastCharacterCount，超过则不再计数
	bool isValidWordStart = true;
	bool hasNotBlankCharacter = false;
	auto map = std::unordered_map<std::string, size_t>();
	FILE* f;
	if (fopen_s(&f, fileName, "rb") != 0) {
		ret.errorCode = WORDCOUNTRESULT_OPEN_FILE_FAILED;
		return ret;
	}
	fseek(f, 0, SEEK_END);
	long fileLength = ftell(f);
	fseek(f, 0, SEEK_SET);
	char * string = (char*)malloc(fileLength + 1);
	fread(string, fileLength, 1, f);
	fclose(f);
	string[fileLength] = 0;

	size_t currentPosition = 0;
	while (runStateMachine) {
		c = string[currentPosition];
		if (currentPosition == fileLength) {
			runStateMachine = false; // 文件读取结束，不立即退出，处理一下之前未整理干净的状态
			c = 0;
		}
		else {
			currentPosition++;
			if (c == '\r') continue; // Thanks God
			ret.characters++;
		}

		if (c >= 'A' && c <= 'Z') {
			c = c - 'A' + 'a';
		}

		if (!isEmptyChar(c)) {
			hasNotBlankCharacter = true;
		}

		if (isCharacter(c)) {
			if (isLetter(c)) {
				// 判断一下首几个字母是不是字母，不是的话就不是单词
				if ((wordLength > 0 && wordLength < wordAtLeastCharacterCount) || (wordLength == 0 && isValidWordStart)) {
					if (isAlphabet(c)) {
						word += c;
						wordLength++;
					}
					else {
						isValidWordStart = false;
						word = "";
						wordLength = 0;
					}
				}
				else {
					word += c;
				}
			}
		}

		if (!isLetter(c)) {
			if (wordLength >= wordAtLeastCharacterCount) { // 不是数字字母了，就可能是个单词的结束
				if (map.find(word) == map.end()) {
					map[word] = 0;
					ret.uniqueWords++;
				}
				map[word]++;
				ret.words++;
			}
			word = "";
			wordLength = 0;

			if (isSeparator(c)) { // 只有有分隔符分割的，才是一个单词的开始
				isValidWordStart = true;
			}
		}

		if (isLf(c) || !runStateMachine) {
			if (hasNotBlankCharacter) { // 任何包含非空白字符的行，都需要统计。
				ret.lines++;
			}
			hasNotBlankCharacter = false;
		}
	}

	auto sortedMap = std::vector<WordCountPair>(map.begin(), map.end());
	std::sort(sortedMap.begin(), sortedMap.end(), [](const WordCountPair& lhs, const WordCountPair& rhs) noexcept {
		if (lhs.second == rhs.second) {
			return lhs.first < rhs.first;
		}
		return lhs.second > rhs.second;
	});
	ret.wordAppears = new WordCountWordAppear[ret.uniqueWords];
	size_t i = 0;
	for (auto &it : sortedMap) {
		ret.wordAppears[i].word = new char[it.first.length() + 1];
		strcpy_s(ret.wordAppears[i].word, it.first.length() + 1, it.first.c_str());
		ret.wordAppears[i].count = it.second;
		i++;
	}

	free(string);
	return ret;
}

EXTERN void ClearWordAppear(WordCountResult * resultStruct)
{
	for (size_t i = 0; i < resultStruct->uniqueWords; i++) {
		delete resultStruct->wordAppears[i].word;
	}
	delete resultStruct->wordAppears;
}
