#include"Header.h"
#include"Nhan.h"


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
	int mid;
	int left = 0, right = s - 1;
	while (left < right) {
		mid = (left + right) / 2;
		if (a[mid] == k) return true;
		if (a[mid] > k) {
			right = mid - 1;
		}
		else if (a[mid] < k) {
			left = mid + 1;
		}

	}
	return false;
}

vector <string> seacrhWildcard(trieNode* root, string key, unordered_set<string> stopWords) {
	string a, b;
	string delim = "*";
	splitKey(key, a, b, delim);

	vector<Store> s1, s2;
	vector<string> res;

	//stringstream ss(key);
	//string word;
	s1 = search(root, a);
	s2 = search(root, b);
	for (int i = 0; i < s1.size();i++) {
		for (int j = 0; j < s2.size();j++) {
			if (s1[i].fileName == s2[j].fileName) {
				for (int k = 0; k < s1[i].pos.size();k++) {
					if (searchMatch(s1[i].pos[k] + 2, s2[j].pos)) {
						res.push_back(s1[i].fileName);
					}
				}
			}
			else continue;
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

//input file name + vector posa
void highlighter(string path,vector<int> pos) {
	ifstream fin;
	string ss;
	int count = 0, i = 0, k = 0;
	fin.open(path);
	while (!fin.eof()) {
		fin >> ss;
		k = i;
		if (i < pos.size() && count == pos[i]) {
			cout << "\033[31m" << ss << "\033[m" << " ";
			i++;
		}
		else if (i == pos.size()) k = i - 1;
		else if (count >= pos[k] - 3 && count <= pos[k] + 7) {
			cout << ss << " ";
		}
		if (count == pos[k] - 4 || count == pos[k] + 8) {
			cout << "...";
		}
		count++;
	}
	fin.close();


}

void printTopRes(vector<Store> a) {
	for (int i = 0; i < a.size();i++) {
		cout << endl;
		cout << "Filename: " << a[i].fileName << endl;
		highlighter(a[i].fileName, a[i].pos);
		cout << endl;

	}
}







