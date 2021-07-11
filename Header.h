#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>
#include<set>
#include<map>

using namespace std;

const int MAX = 26;

struct trieNode {
	int index;
	trieNode* child[MAX];
	trieNode() {
		for (int i = 0; i < MAX; i++) {
			child[i] = nullptr;
			index = -1;
		}
	}
};

struct node {
	int data;
	node* next;
};