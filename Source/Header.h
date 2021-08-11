#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

// 0-9: number, 10-35: words, 36: :, 37: . (decimal), 38: $, 39: %, 40: #, 41:-
const int MAX = 42; 

struct Store {
    string fileName;
    vector <int> pos;
    int score = 0;
    bool isTitle;
};

struct trieNode
{
    trieNode *child[MAX];
    bool isLeaf;
    vector <Store> file;
    trieNode()
    {
        for (int i = 0; i < MAX; i++)
        {
            child[i] = nullptr;
        }
        isLeaf = false;
    }
};

void inputData(trieNode* &root, unordered_set<string> stopWord, vector<float>&number, string word, string path, int position, bool isTit);

void getStopWord(unordered_set <string> &stopWord, string path);

void saveTrie(trieNode*& root, trieNode* &rootTitle, unordered_set<string> stopWord, vector<float> &number, string path);

void cleanData(string& word);

void display(struct trieNode* root, char str[], int level);

string numberToString(int num);

string floatToString(float num);

int convertKey(char key);

bool checkValid(char& key);

bool isNumber(char key);

bool isWord(char key);

vector<Store> search(trieNode* root, string word);

bool cmp(pair<string, int>& a, pair<string, int>& b);

vector<string> ORquery(trieNode* root, string query, unordered_set<string> stopWords);

vector<string> intitleQuery(trieNode* root, string query, unordered_set<string> stopWords);

vector<string> filetypeQuery(trieNode* root, string query, unordered_set<string> stopWords);