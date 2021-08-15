#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <chrono> 

using namespace std;
using namespace std::chrono;

// 0-9: number, 10-35: words, 36: :, 37: . (decimal), 38: $, 39: %, 40: #, 41:-
const int MAX = 43; 

struct Store {
    string fileName;
    vector <int> pos;
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


void start();
void drawConsole();
void endConsole();

void cleanData(string& word);
void removeInt(std::vector<int>& v);
void removeFloat(std::vector<float>& v);

void inputData(trieNode* &root, vector<float>& number, string word, string path, int i, bool isTit);
void read11kFile(trieNode*& root, trieNode*& rootTitle, vector<float>& number);

void getStopWord(unordered_set <string> &stopWord, string path);

void saveTrie(trieNode *&root, trieNode *&rootTitle, vector<float> &number, string path);

vector<Store> search(trieNode* root, string word);

bool cmp(pair<Store, int>& a, pair<Store, int>& b);

vector<Store> ORquery(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> intitleQuery(trieNode* rootTitle, trieNode* rootData, string query, unordered_set<string> stopWords);
vector<Store> filetypeQuery(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> searchWildcard(trieNode* root, string key, unordered_set<string> stopWords);
vector<pair<Store, int>> exactMatch(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> hastagOperator(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> signQuery(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> PLUSquery(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> MINUSquery(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> ANDquery(trieNode* root, string query, unordered_set<string> stopWords);
vector<Store> synonym(trieNode* root, vector<pair<string, vector<string>>> dict, string query);
vector<Store> inRange(trieNode* root, string query, unordered_set<string> stopWords, vector<float> number);

int searchMatch(int k, vector<int> a);
vector<Store> isNext(vector<Store> a, vector<pair<Store, int>> b);

int convertKey(char key);

void readFile(trieNode*& root, trieNode*& rootTitle, vector<float>& number);
void readDictionary(vector<pair<string, vector<string>>>& dict);
void readHistory(vector<string>& history);
void writeHistory(string s, vector<string>& history);
void clearHistory(vector<string>& history);
void ZFunction(string str, int* Z);
bool findHistory(string pattern, string text);
void inputQuery(string& input, vector<string> history);
void cleanSuggestion(int x, int y);

void highlighter(string path, vector<int> pos, int& y, bool title, int& h);
void printTopRes(vector<Store> a, bool title, string query);

