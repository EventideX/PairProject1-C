// Core.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Core.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
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

constexpr bool isSeperator(const char c) {
	return (isCr(c) || isLf(c) || c == ' ' || c == '\t');
}

constexpr bool isCharacter(const char c) {
	return (isSeperator(c) || isLetter(c));
}

// to be fixed
typedef std::pair<std::string, size_t> WordCountPair;

EXTERN WordCountResult CalculateWordCount(const char * fileName)
{
	auto ret = WordCountResult();
	bool runStateMachine = true;
	char prev = 0, c = 0;
	std::ifstream file(fileName);
	std::string word = ""; // 不想做动态分配内存，std::string省事 
	size_t wordLength = 0; // <= wordAtLeastCharacterCount，超过则不再计数
	bool isWord = false;
	bool hasNotBlankCharacter = false;
	auto map = std::map<std::string, size_t>();
	file >> std::noskipws;

	if (!file.good()) {
		ret.errorCode = WORDCOUNTRESULT_OPEN_FILE_FAILED;
		return ret;
	}

	while (runStateMachine) {
		prev = c;
		file >> c;
		if (file.eof()) {
			runStateMachine = false; // 文件读取结束，不立即退出，处理一下之前未整理干净的状态
			c = 0; 
		}
		else {
			ret.characters++;
		}

		if (c >= 'A' && c <= 'Z') {
			c = c - 'A' + 'a';
		}
		if (!isSeperator(c)) {
			hasNotBlankCharacter = true;
		}
		if (isCharacter(c)) {
			if (isLetter(c)) {
				word += c;
				if (!isLetter(prev)) { // 如果当前确定这个字符是单词的第一个字母，就确定它是单词
					isWord = true;
				}
				if (isWord && wordLength <= wordAtLeastCharacterCount) {
					if (!isAlphabet(c)) { // abc123不算单词
						isWord = false;
					}
					else {
						wordLength++;
					}
				}
			}
		}
		if ((isCharacter(c) && !isLetter(c)) || !runStateMachine) {
			if (wordLength >= wordAtLeastCharacterCount) {
				if (map.find(word) == map.end()) {
					map[word] = 0;
					ret.uniqueWords++;
				}
				map[word]++;
				ret.words++;
			}
			word = "";
			wordLength = 0;
			isWord = false;
		}
		if (isLf(c) || !runStateMachine) {
			if (hasNotBlankCharacter) { // 任何包含非空白字符的行，都需要统计。
				ret.lines++;
			}
			hasNotBlankCharacter = false;
		}
	}

	file.close();
	
	auto sortedMap = std::vector<WordCountPair>(map.begin(), map.end());
	std::sort(sortedMap.begin(), sortedMap.end(), [](const WordCountPair& lhs, const WordCountPair& rhs) {
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

	return ret;
}

EXTERN void ClearWordAppear(WordCountResult * resultStruct)
{
	for (size_t i = 0; i < resultStruct->uniqueWords; i++) {
		delete resultStruct->wordAppears[i].word;
	}
	delete resultStruct->wordAppears;
}
