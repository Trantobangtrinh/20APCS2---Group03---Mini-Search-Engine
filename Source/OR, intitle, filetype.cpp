#include "Header.h"

bool cmp(pair<string, int>& a, pair<string, int>& b){
	return a.second > b.second;
}

vector<string> ORquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	map<string, int> myMap;
	bool turn = false;

	//tách chữ query
	stringstream ss(query);
	string word;
	while (ss >> word) {
		//check stopWord
		if (stopWords.find(word) == stopWords.end()) {

			//nếu có OR thì đổi turn kiểu key1 với key2 tách ra 
			//query key1 OR key2
			if (word == "OR" || word == "|") {
				turn = true;
				continue;
			}
			if (turn == false) {

				//hàm search return vector<Store>
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

vector<string> intitleQuery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1;
	map<string, int> myMap;

	//tách chữ query
	
	string key = "intitle:";
	query.erase(0, key.length());
	stringstream ss(query);
	string word;
	while (ss >> word) {
		
		s1 = search(root, word);

		for (int i = 0; i < s1.size(); ++i) {
			//check nếu là title thì thêm vào map, không thì bỏ qua
			if (s1[i].isTitle) {
				if (myMap.find(s1[i].fileName) == myMap.end()) {
					myMap.insert({ s1[i].fileName, 1 });
				}
				else
					myMap[s1[i].fileName]++;
			}
		}
	}

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

vector<string> filetypeQuery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1;
	map<string, int> myMap;
	//check đã xong keyword chưa để bắt đầu check filetype
	bool turn = false;

	//tách chữ query
	string key = "filetype:";
	stringstream ss(query);
	string word;
	while (ss >> word) {
		//check stopWord
		if (stopWords.find(word) == stopWords.end()) {

			//check filetype trong string
			size_t found = word.find(key);

			if (found != string::npos) {
				turn = true;

				//xóa chữ filetype: vì query là filetype:txt viết liền
				//word bây h là txt
				word.erase(0, key.size());
			}

			if (turn == false) {

				//hàm search return vector<Store>
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
				map<string, int>::iterator itr;

				//chạy các object trong map để check filetype và xóa bớt
				for (itr = myMap.begin(); itr != myMap.end(); ++itr) {

					//biến để check đúng filetype chưa
					bool choose = true;

					//biến chạy trong word để so sánh với key trong map
					int j = 0;

					//itr->first.length() - word.length() là vị trí đếm ngược để lọc còn filetype
					//vd 01.txt, first.length() = 6, word.length() = 3, i = 6-3 = 3 
					//và i bắt đầu từ index 3, chạy tới hết first.length, tức txt. 
					for (int i = itr->first.length() - word.length(); i < itr->first.length(); ++i) {
						if (word[j++] != itr->first[i]) {
							choose = false;
							break;
						}
					}
					
					//nếu ko đúng filetype thì xóa ra khỏi map
					if (choose == false) {
						itr = myMap.erase(itr);
					}
				}
			}
		}
	}

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

