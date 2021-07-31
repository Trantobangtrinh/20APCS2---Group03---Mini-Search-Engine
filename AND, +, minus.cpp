#include "Header.h"

vector<string> ANDquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	map<string, int> myMap;
	vector<string> res;
	int turn = 1;
	stringstream ss;
	ss.str(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word == "+") return res;
			if (word == "AND" || word == "&") {
				turn = 2;
				continue;
			}
			if (turn == 1) {
				s1 = search(root, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (myMap.find(s1[i].fileName) == myMap.end()) {
						myMap.insert({ s1[i].fileName, 1 });
					}
					else
						myMap[s1[i].fileName]++;
				}
			}
			else {
				s2 = search(root, word);
				for (int i = 0; i < s2.size(); ++i) {
					if (myMap.find(s2[i].fileName) == myMap.end()) {
						myMap.insert({ s2[i].fileName, 1 });
					}
					else
						myMap[s2[i].fileName]++;
				}
			}
		}
	}

	map<string, int> storeMap;
	for (int i = 0; i < s1.size(); ++i) {
		for (int j = 0; j < s2.size(); j++) {
			if (myMap[s1[i].fileName] = myMap[s2[j].fileName]) {
				storeMap.insert({ s1[i].fileName, 1 });
			}
		}
	}

	//push map to vector to return
	vector<pair<string, int> > A;
	for (auto& it : storeMap) {
		A.push_back(it);
	}

	sort(A.begin(), A.end(), cmp);
	int i = 0;
	vector<pair<string, int>>::iterator itr;
	for (itr = A.begin(); itr != A.end(); ++itr) {
		if (i == 2)
			break;
		res.push_back(itr->first);
		i++;
	}
	return res;
}



vector<string> MINUSquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	map<string, int> myMap;
	bool turn = false;
	stringstream ss;
	int count = 0;
	ss.str(query);
	string word;
	stringstream store;
	while (ss >> word) {
		store >> word;
		if (stopWords.find(word) == stopWords.end()) {
			if (word == "-" || word == "NOT") {
				turn = true;
				continue;
			}
			if (turn == true) {
				s2 = search(root, word);
				for (int i = 0; i < s2.size(); ++i) {
					if (myMap.find(s2[i].fileName) == myMap.end()) {
						myMap.insert({ s2[i].fileName, 1 });
					}
					else
						myMap[s2[i].fileName]++;
				}
			}
			count++;
		}
	}
	while (count != 0) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word == "-" || word == "NOT") {
				turn = false;
				continue;
			}
			if (turn == true) {
				s1 = search(root, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (myMap.find(s1[i].fileName) == myMap.end()) {
						for (int j = 0; j < s2.size(); ++j) {
							if (myMap[s1[i].fileName] = myMap[s2[j].fileName]) continue;
							else myMap.insert({ s1[i].fileName, 1 });
						}
					}
					else
						myMap[s1[i].fileName]++;
				}
			}
			count--;
		}
	}

	//push map to vector to return
	vector<pair<string, int> > A;

	for (auto& it : myMap) {
		A.push_back(it);
	}

	// Sort using comparator function
	sort(A.begin(), A.end(), cmp);

	vector<string> res;
	int i = 0;
	vector<pair<string, int>>::iterator itr;
	for (itr = A.begin(); itr != A.end(); ++itr) {
		if (i == 2)
			break;
		res.push_back(itr->first);
		i++;
	}
	return res;
}


vector<string> PLUSquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	map<string, int> myMap;
	stringstream ss;
	ss.str(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word == "+") {
				break;
			}
			s1 = search(root, word);
			for (int i = 0; i < s1.size(); ++i) {
				if (myMap.find(s1[i].fileName) == myMap.end()) {
					myMap.insert({ s1[i].fileName, 1 });
				}
				else
					myMap[s1[i].fileName]++;
			}
		}
	}
	while (ss >> word) {
		s2 = search(root, word);
		for (int i = 0; i < s2.size(); ++i) {
			if (myMap.find(s2[i].fileName) == myMap.end()) {
				myMap.insert({ s2[i].fileName, 1 });
			}
			else
				myMap[s2[i].fileName]++;
		}
	}

	map<string, int> storeMap;

	for (int i = 0; i < s1.size(); ++i) {
		for (int j = 0; j < s2.size(); j++) {
			if (myMap[s1[i].fileName] = myMap[s2[j].fileName]) {
				storeMap.insert({ s1[i].fileName, 1 });
			}
		}
	}

	//push map to vector to return
	vector<pair<string, int> > A;
	for (auto& it : storeMap) {
		A.push_back(it);
	}

	sort(A.begin(), A.end(), cmp);
	vector<string> res;
	int i = 0;
	vector<pair<string, int>>::iterator itr;
	for (itr = A.begin(); itr != A.end(); ++itr) {
		if (i == 2)
			break;
		res.push_back(itr->first);
		i++;
	}
	return res;
}