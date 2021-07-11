#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>
#include<set>
#include<map>

using namespace std;

const int MAX = 26;

struct trieNode {
	string value;
	trieNode* child[MAX];
	node* list;
	trieNode() {
		for (int i = 0; i < MAX; i++) {
			child[i] = nullptr;
			index = NULL;
		}
	}
};

struct node {
	int data;
	node* next;
};