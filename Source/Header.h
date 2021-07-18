#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// 0-9: number, 10-35: words, 36: :, 37: . (decimal), 38: $, 39: %, 40: #, 41:-
const int MAX = 42; 

struct Store {
    string fileName;
    vector <int> pos;
    int score;
};

struct trieNode
{
    trieNode *child[MAX];
    bool isLeaf, isTitle;
    vector <int> order;

    trieNode()
    {
        for (int i = 0; i < MAX; i++)
        {
            child[i] = nullptr;
        }
        isLeaf = false;
        isTitle = false;
    }
};

void inputData(trieNode *&root, unordered_set<string> stopWord, string word, string path);

void getStopWord(unordered_set <string> &stopWord, string path);

void saveTrie(trieNode *&root, unordered_set<string> stopWord, string path);

void display(struct trieNode* root, char str[], int level);