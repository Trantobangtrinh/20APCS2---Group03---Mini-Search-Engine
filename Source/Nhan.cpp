#include"Header.h"
#include"Nhan.h"

//t moi lam dc 1 cai operator th :((

int convertKey(char key) {
	if (key >= 48 && key <= 57) return (key - '0');
	if (key >= 97 && key <= 122) return (int(key) - 87);
	if (key >= 65 && key <= 90) return (int(key) - 55);
	if (key == ' ') return 36;
	if (key == '.') return 37;
	if (key == '$') return 38;
	if (key == '%') return 39;
	if (key == '#') return 40;
	if (key == '-') return 41;
	return -1;
}

/*trieNode* searchWord(trieNode* root, string key) {
	trieNode* pCur = root;
	int index, length = key.length();
	for (int i = 0; i < length; ++i) {
		index = convertKey(key[i]);
		if (index == -1) continue;
		if (!pCur->child[index]) return NULL;
		pCur = pCur->child[index];
	}
	if (pCur) {
		if (title && !pCur->isTitle) return NULL;
		if (pCur->isLeaf) return pCur;
	}
	return NULL;
}
*/

int searchDelimLength(string key, string delim) {
	int count = 0;
	for (int i = 0;i < key.length();i++) {
		if (key[i] == delim) count++;
	}
	return count;
}


void splitKey(string key, string& a, string& b, string delim) {
	size_t pos = 0;
	string a, b;
	pos = key.find(delim);
	a = key.substr(0, pos);
	key.erase(0, pos + delim.length());
	b = key.substr(0, pos);
}

bool searchMatch(int k, vector<int> a) {
	int s = a.size();
	int mid ;
	int left = 0, right = s;
	while (true) {
		mid = (left + right) / 2;
		if (a[mid] == k) return true;
		else if (a[mid] > k) {
			right = mid;
			continue;
		}
		else {
			left = mid;
			continue;
		}
		if (left >= right) return false;
	}
	return false;
}

vector <string> seacrhWildcard(trieNode* root, string key, unordered_set<string> stopWords) {
	string a, b;
	string delim = "*";
	splitKey(key, a, b, delim);
	int l = searchDelimLength(key, delim);
	vector<Store> s1, s2;
	vector<string> res;

	stringstream ss(key);
	string word;

	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			s1 = search(root, a);
			s2 = search(root, b);

			for (int i = 0; i < s1.size(); ++i) {
				for (int j = 0; j < s2.size();j++) {
					if (s1[i].fileName == s2[i].fileName) {
						for (int k = 0;k < s2[i].pos.size();k++) {
							if (s1[i].pos[i] + l == s2[i].pos[k]) {
								res.push_back(s1[i].fileName);
								break;
							}
						}
					}
				}

			}
		}

	}
	return res;
}

void getRange(string key,vector<int> &range) {
	stringstream ss;
	ss << key;
	string tmp;
	int found;
	while (!ss.eof()) {
		ss >> tmp;
		if (stringstream(tmp) >> found) { 
			range.push_back(found); 
			tmp = "";
		}
	}
}

vector <string> seacrhRange(trieNode* root, string key,unordered_set<string> stopWords) {
	vector<int> range;
	getRange(key, range);
	string a, b;
	string delim = "..";
	splitKey(key, a, b, delim);

	vector<Store> s1;
	map<string, int> myMap;

	stringstream ss(key);
	string word;

	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
		
		
		}
	}
}









