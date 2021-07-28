#include "Header.h"

// For both $ and #
vector<string> specialOperator(trieNode* root, string query, unordered_set<string> stopWords) {
    vector<Store> s;
    map<string, int> myMap;
    // bool check$ = false, checkS = false;
    // bool end$ = false;

    // int price, lwrBound, upBound;

    stringstream ss(query);
    string word;
    while (ss >> word) {
        if (stopWords.find(word) == stopWords.end()) {
            s = search(root, word);
            for (int i = 0; i < s.size(); ++i) {
                if (myMap.find(s[i].fileName) == myMap.end()) {
                    myMap.insert({ s[i].fileName, 1 });
                }
                else
                    myMap[s[i].fileName]++;
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

vector<string> exactMatch(trieNode* root, string query, unordered_set<string> stopWords) {
    vector<Store> s, exactWord;
    map<string, int> myMap;
    bool exact = false;

    stringstream ss(query);
    string word;
    while (ss >> word) {
        if (stopWords.find(word) == stopWords.end()) {

            // Delete the quotation mark at the start and end of the word
            if (word[0] == '\"') {
                exact = true;
                word.erase(0, 1);
                word.erase(word.size() - 1, 1);
            }
            
            if (exact) {
                exactWord = search(root, word);

                // Let the frequency as 500 as higher priority
                for (int i = 0; i < exactWord.size(); ++i) {
                    if (myMap.find(exactWord[i].fileName) == myMap.end()) {
                        myMap.insert({ exactWord[i].fileName, 500 });
                    }
                    else
                        myMap[exactWord[i].fileName]++;
                }
                exact = false;
            }
            else {
                s = search(root, word);
                for (int i = 0; i < s.size(); ++i) {
                    if (myMap.find(s[i].fileName) == myMap.end()) {
                        myMap.insert({ s[i].fileName, 1 });
                    }
                    else
                        myMap[s[i].fileName]++;
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

// vector<string> searchPrice(trieNode *root, string query, vector <int> &pos, int &score) {
//     stringstream ss(query);
//     string temp;

//     if (ss >> temp) { 
//         if (isNumber(temp[0]) || temp[0] == '$') {
//             double lowBound, upBound;
//             if (getRange(temp, lowBound, upBound)) {
//                 string number;
//                 vector <int> res;
//                 if (temp[0] == '$') {
//                     if (!root->child[38])
//                         continue;
//                     findNumber(root->child[38], number, lowBound, upBound, res);
//                     if (res.empty()) continue;
//                 }
//                 else findNumber(root, number, lowBound, upBound, res);
//                 if (res.empty()) continue;
//                 pos = getUnion(pos, res);
//             }
//         }
//     }
//     vector<pair<string, int> > A;

//     for (auto& it : res) {
//         A.push_back(it);
//     }

//     // Sort using comparator function
//     sort(A.begin(), A.end(), cmp);

//     vector<string> res;
//     int i = 0;
//     vector<pair<string, int>>::iterator itr;
//     for (itr = A.begin(); itr != A.end(); ++itr) {
//         if (i == 2)
//             break;
//         res.push_back(itr->first);
//         i++;
//     }
//     return res;
//     return true;
// }

// bool getRange(string tmp, double& lowbound, double& upbound) {//Khanh
// 	string low, up;
// 	int length = tmp.length();
// 	bool check = false;

// 	for (int i = 1; i <= length - 3; ++i) {
// 		if (tmp[i] == '.' && tmp[i + 1] == '.') { 
//             check = true; 
//             break; 
//         }
// 	}
// 	if (!check) return false;
// 	int i;

// 	for (i = 0; i < length; ++i) {
// 		if (tmp[i] == '.' && tmp[i + 1] == '.') break;
// 		low += tmp[i];
// 	}
// 	i += 2;
// 	for (i; i < length; ++i) {
// 		up += tmp[i];
// 	}
// 	if (tmp[0] == '$') {
// 		low = low.substr(1);
// 		up = up.substr(1);
// 	}
// 	lowbound = atof(low.c_str());
// 	upbound = atof(up.c_str());
//     return true;
// }

// vector <int> getUnion(vector<int>& v1, vector<int>& v2) {
// 	if (v1.empty()) return v2;
// 	if (v2.empty()) return v1;
// 	vector<int> res;
// 	int i = 0, j = 0, size1 = v1.size(), size2 = v2.size();
// 	while (i < size1 && j < size2) {
// 		if (v1[i] < v2[j]) 
//             res.push_back(v1[i++]);
// 		else if (v2[j] < v1[i]) 
//             res.push_back(v2[j++]);
// 		else 
// 			res.push_back(v2[j++]); ++i;
// 	}
// 	while (i < size1) res.push_back(v1[i++]);
// 	while (j < size2) res.push_back(v2[j++]);
// 	return res;
// }

// void findNumber(trieNode *root, string number, double lowbound, double upbound, vector <int> &pos) {
//     if (root->isLeaf) {
//         double num = atof(number.c_str());
//         if (num >= lowbound && num <= upbound)
//             pos = getUnion();
//     }
//     for (int i = 0; i <= 37; ++i) {
//         if (i == 10) {
//             i += 26;
//             continue;
//         }
//         if (root->child[i]) {
//             char append;
//             if (i != 37) append = i + '0';
//             else append = '.';
//             findNumber(root->child[i], number + append, lowbound, upbound, pos);
//         }
//     }
//}