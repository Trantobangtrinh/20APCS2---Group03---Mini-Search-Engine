#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

const int MAX = 26;

struct node {
	string data;
	node* next;
};

struct trieNode {
	trieNode* child[MAX];
	node* list;
	trieNode() {
		for (int i = 0; i < MAX; i++) {
			child[i] = nullptr;
			list = nullptr;
		}
	}
};
void inputData(trieNode*& root, unordered_set<string> stopWord, string word, string path);
void saveTrie(trieNode*& root, unordered_set<string> stopWord, string path);