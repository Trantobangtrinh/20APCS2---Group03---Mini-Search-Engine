#include "Header.h"
#include "Console.h"

bool cmp(pair<Store, int> &a, pair<Store, int> &b){
	return (a.second > b.second);
}

vector<Store> ORquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<pair<Store, int>> s1, s2;

	vector<pair<Store, int>> total;

	bool turn = false;

	//tách chữ query
	stringstream ss(query);
	string word;
	string str1;
	string str2;
	while (ss >> word) {
		//check stopWord
		if (stopWords.find(word) == stopWords.end()) {

			//nếu có OR thì đổi turn kiểu key1 với key2 tách ra 
			//query key1 OR key2
			if (word == "OR" || word == "|") {
				s1 = exactMatch(root, str1, stopWords);
				turn = true;
				continue;
			}
			if (turn == false) {
				str1 += word;
				str1 += " ";
				/*num++;
				//hàm search return vector<Store>
				s1 = search(root, word);
				if (num == 1) {
					for (int i = 0; i < s1.size(); ++i) {
						if (st1.size() == 0) {
							st1.push_back(make_pair(s1[i], s1[i].pos.size()));
						}
						else {
							for (int j = 0; j < st1.size(); ++j) {
								if (st1[j].first.fileName == s1[i].fileName) {
									st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
									removeInt(st1[j].first.pos);
									st1[j].second = st1[j].first.pos.size();
									break;
								}
								if (j == st1.size() - 1) {
									st1.push_back(make_pair(s1[i], s1[i].pos.size()));
									break;
								}

							}
						}
					}
				}
				else {
					vector<Store> a;
					if (num == 2) {
						a = isNext(s1, st1);
						st1.clear();
					}
					
				}*/
			}
			else {
				/*s2 = search(root, word);
				for (int i = 0; i < s2.size(); ++i) {
					if (total.size() == 0) {
						total.push_back(make_pair(s2[i], s2[i].pos.size()));
					}
					else {
						for (int j = 0; j < total.size(); ++j) {
							if (total[j].first.fileName == s2[i].fileName) {
								total[j].first.pos.insert(total[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
								removeInt(total[j].first.pos);
								total[j].second = total[j].first.pos.size();
								break;
							}
							if (j == total.size() - 1) {
								total.push_back(make_pair(s2[i], s2[i].pos.size()));
								break;
							}
								
						}
					}
					
				}*/
				str2 += word;
				str2 += " ";
			}
		}
	}
	s2 = exactMatch(root, str2, stopWords);

	for (int i = 0; i < s1.size(); ++i) {
		total.push_back(make_pair(s1[i].first, s1[i].first.pos.size()));
	}
	for (int i = 0; i < s2.size(); ++i) {
		if (total.size() == 0) {
			total.push_back(make_pair(s2[i].first, s2[i].first.pos.size()));
		}
		else {
			for (int j = 0; j < total.size(); ++j) {
				if (total[j].first.fileName == s2[i].first.fileName) {
					total[j].first.pos.insert(total[j].first.pos.end(), s2[i].first.pos.begin(), s2[i].first.pos.end());
					removeInt(total[j].first.pos);
					total[j].second = total[j].first.pos.size();
					break;
				}
				else if (j == total.size()-1){
					total.push_back(make_pair(s2[i].first, s2[i].first.pos.size()));
					break;
				}
			}
		}
	}
	vector<Store> res;

	sort(total.begin(), total.end(), cmp);

	for (int i = 0; i < total.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(total[i].first);
	}
	return res;
}

vector<Store> intitleQuery(trieNode* rootTitle, trieNode* rootData, string query, unordered_set<string> stopWords) {
	vector<pair<Store, int>> st1, st2;
	vector<pair<Store, int>> total;
	string str1, str2;
	//tách chữ query
	bool turn = false;
	string key = "intitle:";

	stringstream ss(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {

			//check filetype trong string
			size_t found = word.find(key);

			if (found != string::npos) {
				st1 = exactMatch(rootData, str1, stopWords);
				turn = true;

				//xóa chữ filetype: vì query là filetype:txt viết liền
				//word bây h là txt
				word.erase(0, key.size());
			}
			if (turn == false) {
				str1 += word;
				str1 += " ";
				/*
				s1 = search(rootData, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (st1.size() == 0)
						st1.push_back(make_pair(s1[i], s1[i].pos.size()));
					else {
						for (int j = 0; j < st1.size(); ++j) {
							if (st1[j].first.fileName == s1[i].fileName) {
								st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
								removeInt(st1[j].first.pos);
								st1[j].second = st1[j].first.pos.size();
							
							}
							if (j == st1.size() - 1) {
								st1.push_back(make_pair(s1[i], s1[i].pos.size()));
								break;
							}
								
						}
					}

				}*/
			}

			if (turn == true) {
				str2 += word;
				str2 += " ";
				/*s2 = search(rootTitle, word);

				for (int i = 0; i < s2.size(); ++i) {
					//check nếu là title thì thêm vào map, không thì bỏ qua
					if (st1.size() != 0) {
						for (int j = 0; j < st1.size(); ++j) {
							if (st1[j].first.fileName == s2[i].fileName) {
								st1[j].first.pos.insert(st1[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
								removeInt(st1[j].first.pos);
								total.push_back(make_pair(st1[j].first, st1[j].first.pos.size()));
							}
						}
					}
					else {
						total.push_back(make_pair(s2[i], 1));
					}
					
				}*/
			}
			
		}
	}
	st2 = exactMatch(rootTitle, str2, stopWords);
	for (int i = 0; i < st2.size(); ++i) {
		//check nếu là title thì thêm vào map, không thì bỏ qua
		if (st1.size() != 0) {
			for (int j = 0; j < st1.size(); ++j) {
				if (st1[j].first.fileName == st2[i].first.fileName) {
					st1[j].first.pos.insert(st1[j].first.pos.end(), st2[i].first.pos.begin(), st2[i].first.pos.end());
					removeInt(st1[j].first.pos);
					total.push_back(make_pair(st1[j].first, st1[j].first.pos.size()));
				}
			}
		}
		else {
			total.push_back(make_pair(st2[i].first, st2[i].first.pos.size()));
		}

	}

	vector<Store> res;

	sort(total.begin(), total.end(), cmp);

	for (int i = 0; i < total.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(total[i].first);
	}
	return res;
}

vector<Store> filetypeQuery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<pair<Store, int>> st1;
	//check đã xong keyword chưa để bắt đầu check filetype
	bool turn = false;
	string str1, str2;
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
				st1 = exactMatch(root, str1, stopWords);
				turn = true;

				//xóa chữ filetype: vì query là filetype:txt viết liền
				//word bây h là txt
				word.erase(0, key.size());
			}

			if (turn == false) {
				str1 += word;
				str1 += " ";
				/*
				//hàm search return vector<Store>
				s1 = search(root, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (total.size() == 0)
						total.push_back(make_pair(s1[i], s1[i].pos.size()));
					else {
						for (int j = 0; j < total.size(); ++j) {
							if (total[j].first.fileName == s1[i].fileName) {
								total[j].first.pos.insert(total[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
								removeInt(total[j].first.pos);
								total[j].second = total[j].first.pos.size();
								break;
							}
							if (j == total.size() - 1) {
								total.push_back(make_pair(s1[i], s1[i].pos.size()));
								break;
							}
						}
					}
					
				}*/
			}
			else {
				//chạy các object trong map để check filetype và xóa bớt
				for (int k = 0; k < st1.size(); ++k) {

					//biến để check đúng filetype chưa
					bool choose = true;

					//biến chạy trong word để so sánh với key trong map
					int j = 0;
					int ind = 0;
					//itr->first.length() - word.length() là vị trí đếm ngược để lọc còn filetype
					//vd 01.txt, first.length() = 6, word.length() = 3, i = 6-3 = 3 
					//và i bắt đầu từ index 3, chạy tới hết first.length, tức txt. 
					for (int i = st1[k].first.fileName.length() - word.length(); i < st1[k].first.fileName.length(); ++i) {
						if (word[j++] != st1[k].first.fileName[i]) {
							choose = false;
							ind = k;
							break;
						}
					}

					//nếu ko đúng filetype thì xóa ra khỏi map
					if (choose == false) {
						st1.erase(st1.begin() + ind);
					}
				}
			}
		}
	}

	vector<Store> res;

	sort(st1.begin(), st1.end(), cmp);

	for (int i = 0; i < st1.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(st1[i].first);
	}
	return res;
}

vector<Store> ANDquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	//vector tổng lưu s1 và s2
	vector<pair<Store, int>> st1, st2;
	string str1, str2;
	int turn = 1;
	stringstream ss;
	ss.str(query);
	string word;
	int num = 0;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word == "AND" || word == "&") {
				st1 = exactMatch(root, str1, stopWords);
				turn = 2;
				continue;
			}
			if (turn == 1) {
				str1 += word;
				str1 += " ";
				/*s1 = search(root, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (st1.size() == 0) {
						st1.push_back(make_pair(s1[i], s1[i].pos.size()));
						
					}
						
					else {
						for (int j = 0; j < st1.size(); ++j) {
							if (st1[j].first.fileName == s1[i].fileName) {
								
								st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
								removeInt(st1[j].first.pos);
								st1[j].second = st1[i].first.pos.size();
								break;
							}
							if (j == st1.size() - 1) {
								st1.push_back(make_pair(s1[i], s1[i].pos.size()));
								
								break;
							}
						}
					}
				}*/
			}
			else {
				str2 += word;
				str2 += " ";
				/*num++;
				s2 = search(root, word);
				if (num < 2) {
					for (int i = 0; i < s2.size(); ++i) {
						if (st2.size() == 0)
							st2.push_back(make_pair(s2[i], s2[i].pos.size()));
						else {
							for (int j = 0; j < st2.size(); ++j) {
								if (st2[j].first.fileName == s2[i].fileName) {
									st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
									removeInt(st2[j].first.pos);
									st2[j].second = st2[j].first.pos.size();
									break;
								}
								if (j == st2.size() - 1) {
									st2.push_back(make_pair(s2[i], s2[i].pos.size()));
									break;
								}
							}

						}
					}
				}
				else {
					vector<pair<Store, int>> tmp;
					for (int i = 0; i < s2.size(); ++i) {
						for (int j = 0; j < st2.size(); ++j) {
							if (st2[j].first.fileName == s2[i].fileName) {
								st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
								removeInt(st2[j].first.pos);
								st2[j].second = st2[j].first.pos.size();
								tmp.push_back(make_pair(st2[j].first, st2[j].second));
								break;
							}
						}
					}
					st2.clear();
					st2 = tmp;
					tmp.clear();
				}*/

			}
		}
	}
	st2 = exactMatch(root, str2, stopWords);
	// check file trùng giữa 2 vế nếu có thì lưu vào map
	vector<pair<Store, int>> storeMap;
	/*
	for (int i = 0; i<st1.size(); ++i) {
		for (int j = i; j<st2.size(); ++j) {
			if (st1[i].first.fileName == st2[j].first.fileName) {
				int c1 = st1[i].second;
				int c2 = st2[j].second;
				if (storeMap.size() == 0) {
					st1[i].first.pos.insert(st1[i].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
					removeInt(st1[i].first.pos);
					storeMap.push_back(make_pair(st1[i].first, c1 + c2));
				}
				else {
					for (int k = 0; k < storeMap.size(); ++k) {
						if (storeMap[k].first.fileName == st1[i].first.fileName) {
							storeMap[k].first.pos.insert(storeMap[k].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
							removeInt(storeMap[k].first.pos);
							break;
						}
						if (k == storeMap.size() - 1 && storeMap[k].first.fileName != st1[i].first.fileName) {
							st1[i].first.pos.insert(st1[i].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
							removeInt(st1[i].first.pos);
							storeMap.push_back(make_pair(st1[i].first, c1 + c2));
							break;
						}
						
					}
				}
			}
		}
	}*/

	for (int i = 0; i < st1.size(); ++i) {
		for (int j = 0; j < st2.size(); ++j) {
			if (st1[i].first.fileName == st2[j].first.fileName) {
				if (storeMap.size() == 0) {
					st1[i].first.pos.insert(st1[i].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
					removeInt(st1[i].first.pos);
					storeMap.push_back(make_pair(st1[i].first, st1[i].first.pos.size()));
				}
				else {
					for (int k = 0; k < storeMap.size(); ++k) {
						if (storeMap[k].first.fileName == st1[i].first.fileName) {
							st1[i].first.pos.insert(st1[i].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
							storeMap[k].first.pos.insert(storeMap[k].first.pos.end(), st1[i].first.pos.begin(), st1[i].first.pos.end());
							removeInt(storeMap[k].first.pos);
							storeMap[k].second = storeMap[k].first.pos.size();
							break;
						}
						else if (k == storeMap.size() - 1){
							st1[i].first.pos.insert(st1[i].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
							removeInt(st1[i].first.pos);
							storeMap.push_back(make_pair(st1[i].first, st1[i].first.pos.size()));
							break;
						}
					}
				}
				
				
			}
		}
	}

	vector<Store> res;

	sort(storeMap.begin(), storeMap.end(), cmp);

	for (int i = 0; i < storeMap.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(storeMap[i].first);
	}
	return res;
}

vector<Store> signQuery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	//vector tổng kết cho s1, s2 sau mỗi lần search để so tiếp position
	vector<pair<Store, int>> st1, st2;
	string str1, str2;
	int turn = 1;
	stringstream ss;
	ss.str(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word[0] == '$') {
				st1 = exactMatch(root, str1, stopWords);
				turn = 2;
			}
			if (turn == 1) {
				str1 += word;
				str1 += " ";
				/*s1 = search(root, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (st1.size() != 0) {
						for (int j = 0; j<st1.size(); ++j){
							if (st1[j].first.fileName == s1[i].fileName) {
								st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
								removeInt(st1[j].first.pos);
								st1[j].second = st1[j].first.pos.size();
								break;
							}
							if (j == st1.size() - 1) {
								st1.push_back(make_pair(s1[i], s1[i].pos.size()));
								break;
							}
						}
					}
					else
						st1.push_back(make_pair(s1[i],s1[i].pos.size()));
						
				}*/
			}
			else {
				/*str2 += word;
				str2 += " ";
				*/
				s2 = search(root, word);
				for (int i = 0; i < s2.size(); ++i) {
					if (st2.size() != 0) {
						for (int j = 0; j<st2.size(); ++j) {
							if (st2[j].first.fileName == s2[i].fileName) {
								st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
								removeInt(st2[j].first.pos);
								st2[j].second = st2[j].first.pos.size();
								break;
							}
							if (j == st2.size() - 1) {
								st2.push_back(make_pair(s2[i], s2[i].pos.size()));
								break;
							}
						}
					}
					else
						st2.push_back(make_pair(s2[i], s2[i].pos.size()));
					
				}
			}
		}
	}
	//st2 = exactMatch(root, str2, stopWords);
	vector<pair<Store, int>> storeMap;

	//2 dòng for đầu để so sánh số file trùng của st1 và st2
	if (st1.size() != 0) {
		for (int i = 0; i < st1.size(); ++i) {
			for (int j = 0; j < st2.size(); ++j) {
				//check xem tên file có trùng ko
				if (st1[i].first.fileName == st2[j].first.fileName) {

					//2 dòng for kế tiếp là để check position, nếu position của số tiền - position của vế trước = 1 (kề nhau)
					//thì lưu vào map
					for (int k = 0; k < st1[i].first.pos.size(); ++k) {
						for (int l = 0; l < st2[j].first.pos.size(); ++l) {
							if (st2[j].first.pos[l] - st1[i].first.pos[k] <= 7 && st2[j].first.pos[l] - st1[i].first.pos[k] > 0) {
								Store tmp;
								if (storeMap.size() != 0) {
									for (int m = 0; m < storeMap.size(); ++m) {
										if (storeMap[m].first.fileName == st1[i].first.fileName) {
											storeMap[m].first.pos.push_back(st1[i].first.pos[k]);
											storeMap[m].first.pos.push_back(st2[j].first.pos[l]);
											removeInt(storeMap[m].first.pos);
											storeMap[m].second = storeMap[m].first.pos.size();
											break;
										}
										if (m == storeMap.size() - 1) {
											tmp.fileName = st1[i].first.fileName;
											tmp.pos.push_back(st1[i].first.pos[k]);
											tmp.pos.push_back(st2[j].first.pos[l]);
											storeMap.push_back(make_pair(tmp, tmp.pos.size()));
											break;
										}
									}
								}
								else {
									tmp.fileName = st1[i].first.fileName;
									tmp.pos.push_back(st1[i].first.pos[k]);
									tmp.pos.push_back(st2[j].first.pos[l]);
									storeMap.push_back(make_pair(tmp, tmp.pos.size()));
								}
							}

						}
					}

				}
			}
		}
	}
	else {
		for (int i = 0; i < st2.size(); ++i) {
			if (storeMap.size() != 0) {
				for (int j = 0; j < storeMap.size(); ++j) {
					if (storeMap[j].first.fileName == st2[i].first.fileName) {
						storeMap[j].first.pos.insert(storeMap[j].first.pos.end(), st2[i].first.pos.begin(), st2[i].first.pos.end());
						removeInt(storeMap[i].first.pos);
						storeMap[j].second = storeMap[i].first.pos.size();
						break;
					}
						
					else if (j == storeMap.size()-1){
						storeMap.push_back(make_pair(st2[i].first, st2[i].first.pos.size()));
						break;
					}
				}
			}
			else
				storeMap.push_back(make_pair(st2[i].first, st2[i].first.pos.size()));
		}
	}

	//push map to vector to return
	vector<Store> res;

	sort(storeMap.begin(), storeMap.end(), cmp);

	for (int i = 0; i < storeMap.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(storeMap[i].first);
	}
	return res;
}

vector<Store> MINUSquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s2;
	vector<pair<Store, int>> st1;
	string str1, str2;
	bool turn = false;
	stringstream ss;
	int count = 0;
	ss.str(query);
	string word;
	stringstream store;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word[0] == '-') {
				st1 = exactMatch(root, str1, stopWords);
				word = word.erase(0, 1);
				break;
			}
			str1 += word;
			str1 += " ";
			/*
			s1 = search(root, word);
			for (int i = 0; i < s1.size(); ++i) {
				if (total.size() == 0)
					total.push_back(make_pair(s1[i], s1[i].pos.size()));
				else {
					for (int j = 0; j < total.size(); ++j) {
						if (total[j].first.fileName == s1[i].fileName) {
							total[j].first.pos.insert(total[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
							removeInt(total[j].first.pos);
							total[j].second = total[j].first.pos.size();
							break;
						}
						if (j == total.size() - 1) {
							total.push_back(make_pair(s1[i], s1[i].pos.size()));
							break;
						}
					}
				}
				
			}*/
		}
	}
	do {
		s2 = search(root, word);
		for (int i = 0; i < s2.size(); ++i) {
			//nếu tìm thấy file name của s2 thì xóa khỏi map vì ko được có chữ sau dấu - trong file
			for (int j = 0; j < st1.size(); ++j) {
				if (st1[j].first.fileName == s2[i].fileName) {
					st1.erase(st1.begin() + j);
				}
			}
		}
	} while (ss >> word);

	vector<Store> res;

	sort(st1.begin(), st1.end(), cmp);

	for (int i = 0; i < st1.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(st1[i].first);
	}
	return res;
}

vector<Store> PLUSquery(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	vector<pair<Store, int>> st1, st2, total;
	string str1, str2;
	stringstream ss;
	bool turn = false;
	ss.str(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word[0] == '+') {
				st1 = exactMatch(root, str1, stopWords);
				word = word.erase(0, 1);
				turn = true;
			}
			if (turn == false) {
				str1 += word;
				str1 += " ";
				
			}
			else {
				str2 += word;
				str2 += " ";
			}
			/*
			s1 = search(root, word);
			for (int i = 0; i < s1.size(); ++i) {
				s1 = search(root, word);

				if (st1.size() == 0)
					st1.push_back(make_pair(s1[i], 1));
				else {
					for (int j = 0; j < st1.size(); ++j) {
						if (st1[j].first.fileName == s1[i].fileName) {
							st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
							st1[j].second++;
							break;
						}
						if (j == st1.size() - 1) {
							st1.push_back(make_pair(s1[i], 1));
							break;
						}
					}
				}
			}*/
		}
	}
	st2 = exactMatch(root, str2, stopWords);
	//đếm số chữ sau dấu +
	/*int num = 0;
	do {
		num++;
		s2 = search(root, word);
		if (num < 2) {
			for (int i = 0; i < s2.size(); ++i) {
				if (st2.size() == 0)
					st2.push_back(make_pair(s2[i], 1));
				else {
					for (int j = 0; j < st2.size(); ++j) {
						if (st2[j].first.fileName == s2[i].fileName) {
							st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
							st2[j].second = st2[j].first.pos.size();
							break;
						}
						if (j == st2.size() - 1) {
							st2.push_back(make_pair(s2[i], 1));
							break;
						}
					}
					
				}
			}
		}
		else {
			vector<pair<Store, int>> tmp;
			for (int i = 0; i < s2.size(); ++i) {
				for (int j = 0; j < st2.size(); ++j) {
					if (st2[j].first.fileName == s2[i].fileName) {
						st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
						st2[j].second = st2[j].first.pos.size();
						tmp.push_back(make_pair(st2[j].first, st2[j].second));
						break;
					}
				}
			}
			st2.clear();
			st2 = tmp;
			tmp.clear();
		}
		
	} while (ss >> word);
	*/
	//so sánh số file trùng của phần trước dấu + và sau dấu + để lọc file đúng nhất
	for (int i = 0; i<st1.size(); ++i) {
		for (int j = 0; j<st2.size(); ++j) {
			if (st1[i].first.fileName == st2[j].first.fileName) {
				int c1 = st1[i].second;
				int c2 = st2[j].second;
				st1[i].first.pos.insert(st1[i].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
				if (total.size() == 0) {
					total.push_back(make_pair(st1[i].first, min(c1, c2)));
				}
				else {
					for (int k = 0; k < total.size(); ++k) {
						if (total[k].first.fileName == st1[i].first.fileName) {
							total[k].first.pos.insert(total[k].first.pos.end(), st2[j].first.pos.begin(), st2[j].first.pos.end());
							total[k].second = total[k].first.pos.size();
							break;
						}
						else if (k == total.size() - 1) {
							total.push_back(make_pair(st1[i].first, min(c1, c2)));
							break;
						}
						
					}
				}
			}
		}
	}

	//push map to vector to return
	vector<Store> res;

	sort(total.begin(), total.end(), cmp);

	for (int i = 0; i < total.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(total[i].first);
	}
	return res;
}

vector<Store> hastagOperator(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s;
	vector<pair<Store, int>> total;

	// bool check$ = false, checkS = false;
	// bool end$ = false;

	// int price, lwrBound, upBound;

	stringstream ss(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			s = search(root, word);
			for (int i = 0; i < s.size(); ++i) {
				if (total.size() == 0)
					total.push_back(make_pair(s[i], s[i].pos.size()));
				else {
					for (int j = 0; j < total.size(); ++j) {
						if (total[j].first.fileName == s[i].fileName) {
							total[j].first.pos.insert(total[j].first.pos.end(), s[i].pos.begin(), s[i].pos.end());
							removeInt(total[j].first.pos);
							total[j].second = total[j].first.pos.size();
							break;
						}
						if (j == total.size() - 1) {
							total.push_back(make_pair(s[i], s[i].pos.size()));
							break;
						}
					}
				}
				
			}
		}
	}
	vector<Store> res;

	sort(total.begin(), total.end(), cmp);

	for (int i = 0; i < total.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(total[i].first);
	}
	return res;
	
}

vector<Store> isNext(vector<Store> a, vector<pair<Store, int>> b) {
	vector<Store> res;
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			if (a[i].fileName == b[j].first.fileName) {
				for (int k = 0; k < a[i].pos.size(); ++k) {
					for (int l = 0; l < b[j].first.pos.size(); ++l) {
						if (a[i].pos[k] - b[j].first.pos[l] == 1) {
							Store tmp;
							if (res.size() == 0) {
								tmp.fileName = b[j].first.fileName;
								tmp.pos.push_back(b[j].first.pos[l]);
								tmp.pos.push_back(a[i].pos[k]);
								res.push_back(tmp);
							}
							else {
								for (int x = 0; x < res.size(); ++x) {
									if (res[x].fileName == b[j].first.fileName) {
										res[x].pos.push_back(b[j].first.pos[l]);
										res[x].pos.push_back(a[i].pos[k]);
									}
									else if (x == res.size() - 1) {
										tmp.fileName = b[j].first.fileName;
										tmp.pos.push_back(b[j].first.pos[l]);
										tmp.pos.push_back(a[i].pos[k]);
										res.push_back(tmp);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return res;
}

vector<pair<Store, int>> exactMatch(trieNode* root, string query, unordered_set<string> stopWords) {
	vector<Store> s1;
	//vector tổng kết cho s1, s2 sau mỗi lần search để so tiếp position
	vector<pair<Store, int>> st1, tmp;

	stringstream ss;
	ss.str(query);
	string word;
	int num = 0;
	while (ss >> word) {
		num++;
		if (stopWords.find(word) == stopWords.end()) {
			if (word[0] == '\"') {
				word = word.erase(0, 1);
			}
			if (word[word.size() - 1] == '\"') {
				word = word.erase(word.size() - 1, 1);
			}
			
 			s1 = search(root, word);
			if (num == 1) {
				for (int i = 0; i < s1.size(); ++i) {
					if (st1.size() != 0) {
						for (int j = 0; j < st1.size(); ++j) {
							if (st1[j].first.fileName == s1[i].fileName) {
								st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
								st1[j].second++;
								break;
							}
							if (j == st1.size() - 1) {
								st1.push_back(make_pair(s1[i], 1));
								break;
							}

						}
					}
					else
						st1.push_back(make_pair(s1[i], 1));
				}
			}

			if (num > 1){
				vector<Store> a;
				if (num == 2) {
					a = isNext(s1, st1);
					st1.clear();
				}
				else
					a = isNext(s1, tmp);
				if (a.size() != 0) {
					for (int i = 0; i < a.size(); ++i) {
						if (tmp.size() == 0) {
							tmp.push_back(make_pair(a[i], a[i].pos.size()));
						}
						else {
							for (int j = 0; j < tmp.size(); ++j) {
								if (tmp[j].first.fileName == a[i].fileName) {
									tmp[j].first.pos.insert(tmp[j].first.pos.end(), a[i].pos.begin(), a[i].pos.end());
									removeInt(tmp[j].first.pos);
									tmp[j].second = tmp[j].first.pos.size();
									
									break;
								}
								if (j == tmp.size() - 1) {
									tmp.push_back(make_pair(a[i], a[i].pos.size()));
									break;
								}
									
							}
						}
					}
				}
			}
		}
	}

	vector<pair<Store, int>> storeMap;

	if (num > 1) {
		for (int i = 0; i < tmp.size(); ++i) {
			if (tmp[i].second >= num) {
				storeMap.push_back(make_pair(tmp[i].first, tmp[i].second));
			}
		}
	}
	else {
		for (int i = 0; i < st1.size(); ++i) {
			storeMap.push_back(make_pair(st1[i].first, st1[i].second));
		}
	}

	//push map to vector to return
	sort(storeMap.begin(), storeMap.end(), cmp);
	return storeMap;
}

int searchMatch(int k, vector<int> a) {
	//binary search
	int s = a.size();
	int mid;
	int left = 0, right = s - 1;
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (a[mid] == k) 
			return mid;
		if (a[mid] > k) {
			right = mid - 1;
		}
		else if (a[mid] < k) {
			left = mid + 1;
		}

	}
	return -1;
}

vector <Store> searchWildcard(trieNode* root, string key, unordered_set<string> stopWords) {
	vector<Store> s1, s2;
	vector<pair<Store, int>> st1, st2;
	vector<pair<Store, int>> total;

	bool turn = false;

	//tách chữ query
	stringstream ss(key);
	string word;
	//count tạm định là 2, là khoảng cách giữa a * b
	int count = 2;
	while (ss >> word) {
		//nếu có một từ nào trong query thuộc stopWords thì tăng count lên
		if (word == "*") {
			turn = true;
			continue;
		}
		if (turn == false) {
			s1 = search(root, word);
			for (int i = 0; i < s1.size(); ++i) {
				if (st1.size() != 0) {
					for (int j = 0; j < st1.size(); ++j) {
						if (st1[j].first.fileName == s1[i].fileName) {
							st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());
							st1[j].second++;
							removeInt(st1[j].first.pos);
							sort(st1[j].first.pos.begin(), st1[j].first.pos.end());
							break;
						}
						if (j == st1.size() - 1) {
							st1.push_back(make_pair(s1[i], 1));
							break;
						}
					}
				}
				else
					st1.push_back(make_pair(s1[i], 1));
			}
		}
		else {
			s2 = search(root, word);
			for (int i = 0; i < s2.size(); ++i) {
				if (st2.size() != 0) {
					for (int j = 0; j<st2.size(); ++j) {
						if (st2[j].first.fileName == s2[i].fileName) {
							st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
							st2[j].second++;
							removeInt(st2[j].first.pos);
							sort(st2[j].first.pos.begin(), st2[j].first.pos.end());
							break;
						}
						if (j == st2.size()-1) {
							st2.push_back(make_pair(s2[i], 1));
							break;
						}
					}
				}
				else {
					st2.push_back(make_pair(s2[i], 1));
				}

			}
		}
	}
	if (st1.size() > 0 && st2.size() > 0) {
		for (int i = 0; i < st1.size(); ++i) {
			for (int j = 0; j < st2.size(); ++j) {
				//nếu trùng file name
				if (st1[i].first.fileName == st2[j].first.fileName) {
					for (int k = 0; k < st1[i].first.pos.size(); k++) {
						//pos[k] + count là khoảng cách giữa 2 chữ ko là stopWords trong query
						//res.size() <= 5 để giới hạn tối đa 5 top results
						for (int x = 0; x < 7; ++x) {
							int find = searchMatch(st1[i].first.pos[k] + count + x, st2[j].first.pos);
							if (find != -1) {
								Store tmp;
								if (total.size() != 0) {
									for (int l = 0; l < total.size(); ++l) {
										if (total[l].first.fileName == st1[i].first.fileName) {
											tmp.pos.push_back(st1[i].first.pos[k]);
											for (int m = st1[i].first.pos[k] + 1; m <= st2[j].first.pos[find]; ++m) {
												tmp.pos.push_back(m);
											}
											total[l].first.pos.insert(total[l].first.pos.end(), tmp.pos.begin(), tmp.pos.end());

											total[l].second = total[l].first.pos.size();
											removeInt(total[l].first.pos);
											break;
										}
										else if (l == total.size() - 1) {
											tmp.fileName = st1[i].first.fileName;
											tmp.pos.push_back(st1[i].first.pos[k]);
											for (int m = st1[i].first.pos[k] + 1; m <= st2[j].first.pos[find]; ++m) {
												tmp.pos.push_back(m);
											}

											total.push_back(make_pair(tmp, tmp.pos.size()));
											removeInt(total[l].first.pos);
											break;
										}
									}
								}
								else {
									tmp.fileName = st1[i].first.fileName;
									tmp.pos.push_back(st1[i].first.pos[k]);
									for (int m = st1[i].first.pos[k] + 1; m <= st2[j].first.pos[find]; ++m) {
										tmp.pos.push_back(m);
									}
									total.push_back(make_pair(tmp, tmp.pos.size()));
									break;
								}
							}
						}

					}
				}
			}
		}
	}

	else if (st1.size() == 0) {
		for (int i = 0; i < st2.size(); ++i) {
			Store tmp;
			if (total.size() == 0) {
				tmp.fileName = st2[i].first.fileName;
				for (int j = 0; j < st2[i].first.pos.size(); ++j) {
					tmp.pos.push_back(st2[i].first.pos[j] - 1);
					tmp.pos.push_back(st2[i].first.pos[j]);
				}
				total.push_back(make_pair(tmp, tmp.pos.size()));
			}
			else {
				for (int k = 0; k < total.size(); ++k) {
					if (total[k].first.fileName == st2[i].first.fileName) {
						for (int j = 0; j < st2[i].first.pos.size(); ++j) {
							tmp.pos.push_back(st2[i].first.pos[j] - 1);
							tmp.pos.push_back(st2[i].first.pos[j]);
						}
						removeInt(tmp.pos);
						total[k].first.pos.insert(total[k].first.pos.end(), tmp.pos.begin(), tmp.pos.end());
						total[k].second = total[k].first.pos.size();
						break;
					}
					else if (k == total.size() - 1) {
						tmp.fileName = st2[i].first.fileName;
						for (int j = 0; j < st2[i].first.pos.size(); ++j) {
							tmp.pos.push_back(st2[i].first.pos[j] - 1);
							tmp.pos.push_back(st2[i].first.pos[j]);
						}
						total.push_back(make_pair(tmp, tmp.pos.size()));
						break;
					}
				}
			}
		}
	}

	else {
		for (int i = 0; i < st1.size(); ++i) {
			Store tmp;
			if (total.size() == 0) {
				tmp.fileName = st1[i].first.fileName;
				for (int j = 0; j < st1[i].first.pos.size(); ++j) {
					tmp.pos.push_back(st1[i].first.pos[j]);
					tmp.pos.push_back(st1[i].first.pos[j] + 1);
				}
				total.push_back(make_pair(tmp, tmp.pos.size()));
			}
			else {
				for (int k = 0; k < total.size(); ++k) {
					if (total[k].first.fileName == st1[i].first.fileName) {
						for (int j = 0; j < st1[i].first.pos.size(); ++j) {
							tmp.pos.push_back(st1[i].first.pos[j]);
							tmp.pos.push_back(st1[i].first.pos[j] + 1);
						}
						
						total[k].first.pos.insert(total[k].first.pos.end(), tmp.pos.begin(), tmp.pos.end());
						removeInt(total[k].first.pos);
						total[k].second = total[k].first.pos.size();
						break;
					}
					else if (k == total.size() - 1) {
						tmp.fileName = st1[i].first.fileName;
						for (int j = 0; j < st1[i].first.pos.size(); ++j) {
							tmp.pos.push_back(st1[i].first.pos[j]);
							tmp.pos.push_back(st1[i].first.pos[j] + 1);
						}
						removeInt(tmp.pos);
						total.push_back(make_pair(tmp, tmp.pos.size()));
						break;
					}
				}
			}
		}
	}

	vector<Store> res;

	sort(total.begin(), total.end(), cmp);

	for (int i = 0; i < total.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(total[i].first);
	}
	return res;
}

void readDictionary(vector<pair<string, vector<string>>>& dict) {
	ifstream in;
	in.open("dict.txt");
	string str;
	string word;
	string key;
	vector<string> sym;
	while (!in.eof()) {
		getline(in, str);
		string key1 = "KEY:";
		string key2 = "SYN:";
		size_t pos1 = str.find(key1);
		size_t pos2 = str.find(key2);

		if (pos1 != string::npos || pos2 != string::npos) {
			stringstream ss(str);
			ss >> word;

			if (word == "KEY:") {
				while (ss >> word) {
					if (word[0] == '[' || word[0] == '{' || word[0] == '\\' || word[word.length() - 1] == ']')
						continue;

					word[0] = tolower(word[0]);
					if (word[word.length() - 1] < 'a' || word[word.length() - 1] > 'z')
						word = word.erase(word.length() - 1);
					key = word;
					break;
				}
			}
			else if (word == "SYN:") {


				while (ss >> word) {
					if (word[0] == '[' || word[0] == '{' || word[0] == '\\' || word[word.length() - 1] == ']' || word[word.length() - 2] == ']')
						continue;
					word[0] = tolower(word[0]);
					if (word[word.length() - 1] < 'a' || word[word.length() - 1] > 'z')
						word = word.erase(word.length() - 1);
					sym.push_back(word);
				}
				if (dict.size() == 0) {
					dict.push_back(make_pair(key, sym));
				}
				else {
					for (int i = 0; i < dict.size(); ++i) {
						if (key == dict[i].first) {
							dict[i].second.insert(dict[i].second.end(), sym.begin(), sym.end());
							break;
						}
						else if (i == dict.size() - 1) {
							dict.push_back(make_pair(key, sym));
							break;
						}
					}
				}
				sym.clear();
			}
		}


	}
	in.close();
}

vector<Store> synonym(trieNode* root, vector<pair<string, vector<string>>> dict, string query) {
	query = query.erase(0, 1);
	vector<string> sym;
	for (int i = 0; i<dict.size(); ++i) {
		if (dict[i].first == query)
			sym = dict[i].second;
	}
	vector<Store> s;
	vector<pair<Store, int>> total;

	s = search(root, query);
	for (int i = 0; i < s.size(); ++i) {
		if (total.size() == 0)
			total.push_back(make_pair(s[i], s[i].pos.size()));

		else {
			for (int j = 0; j < total.size(); ++j) {
				if (total[j].first.fileName == s[i].fileName) {
					total[j].first.pos.insert(total[j].first.pos.end(), s[i].pos.begin(), s[i].pos.end());
					total[j].second++;
					break;
				}
				if (j == total.size() - 1) {
					total.push_back(make_pair(s[i], s[i].pos.size()));
					break;
				}
			}
		}
	}

	for (int j = 0; j < sym.size(); ++j) {
		s = search(root, sym[j]);
		for (int i = 0; i < s.size(); ++i) {
			if (total.size() == 0)
				total.push_back(make_pair(s[i], s[i].pos.size()));

			else {
				for (int j = 0; j < total.size(); ++j) {
					if (total[j].first.fileName == s[i].fileName) {
						total[j].first.pos.insert(total[j].first.pos.end(), s[i].pos.begin(), s[i].pos.end());
						total[j].second = total[j].first.pos.size();
						break;
					}
					if (j == total.size() - 1) {
						total.push_back(make_pair(s[i], s[i].pos.size()));
						break;
					}
				}
			}
			
		}
	}

	vector<Store> res;

	sort(total.begin(), total.end(), cmp);

	for (int i = 0; i < total.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(total[i].first);
	}
	return res;
}

vector<Store> inRange(trieNode* root, string query, unordered_set<string> stopWords, vector<float> number) {
	vector<Store> s1, s2;
	vector<pair<Store, int>> st1, st2;
	vector<float>::iterator low, high;
	string str1;
	int turn = 1;
	stringstream ss;
	ss.str(query);
	string word;
	while (ss >> word) {
		if (stopWords.find(word) == stopWords.end()) {
			if (word[0] == '$') {
				st1 = exactMatch(root, str1, stopWords);
				turn = 2;
			}
			if (turn == 1) {
				str1 += word;
				str1 += " ";
				/*s1 = search(root, word);
				for (int i = 0; i < s1.size(); ++i) {
					if (st1.size() != 0) {
						for (int j = 0; j < st1.size(); ++j) {
							if (st1[j].first.fileName == s1[i].fileName) {
								st1[j].first.pos.insert(st1[j].first.pos.end(), s1[i].pos.begin(), s1[i].pos.end());

								st1[j].second = st1[j].first.pos.size();
								break;
							}
							if (j == st1.size() - 1) {
								st1.push_back(make_pair(s1[i], s1[i].pos.size()));
								break;
							}
						}
					}
					else
						st1.push_back(make_pair(s1[i], s1[i].pos.size()));
				}*/
			}
			else {
				
				string token1, token2;
				float val1, val2;
				string key = "..";
				size_t pos = word.find(key);
				if (pos != string::npos) {
					token1 = word.substr(1, pos-1);
					val1 = stof(token1);

					pos += 3;

					token2 = word.substr(pos, word.length() - 1);
					val2 = stof(token2);
				}

				low = lower_bound(number.begin(), number.end(), val1);
				high = upper_bound(number.begin(), number.end(), val2);

				int l = low - number.begin();
				int h = high - number.begin();

				for (int i = l; i < h; ++i) {
					string word = "$" + to_string(number[i]);
					pos = word.find(".");
					pos += 3;
					word = word.erase(pos, word.length()-pos);
					s2 = search(root, word);
					for (int i = 0; i < s2.size(); ++i) {
						if (st2.size() != 0) {
							for (int j = 0; j < st2.size(); ++j) {
								if (st2[j].first.fileName == s2[i].fileName) {
									st2[j].first.pos.insert(st2[j].first.pos.end(), s2[i].pos.begin(), s2[i].pos.end());
									st2[j].second = st2[j].first.pos.size();
									break;
								}
								if (j == st2.size() - 1) {
									st2.push_back(make_pair(s2[i], s2[i].pos.size()));
									break;
								}
							}
						}
						else
							st2.push_back(make_pair(s2[i], s2[i].pos.size()));

					}
				}
			}
		}
	}

	vector<pair<Store, int>> storeMap;
	if (st1.size() != 0) {
		//2 dòng for đầu để so sánh số file trùng của st1 và st2
		for (int i = 0; i < st1.size(); ++i) {
			for (int j = 0; j < st2.size(); ++j) {
				//check xem tên file có trùng ko
				if (st1[i].first.fileName.compare(st2[j].first.fileName) == 0) {

					//2 dòng for kế tiếp là để check position, nếu position của số tiền - position của vế trước = 1 (kề nhau)
					//thì lưu vào map
					for (int k = 0; k < st1[i].first.pos.size(); ++k) {
						for (int l = 0; l < st2[j].first.pos.size(); ++l) {
							if (st2[j].first.pos[l] - st1[i].first.pos[k] <= 7 && st2[j].first.pos[l] - st1[i].first.pos[k] > 0) {
								Store tmp;
								if (storeMap.size() != 0) {
									for (int m = 0; m < storeMap.size(); ++m) {
										if (storeMap[m].first.fileName == st1[i].first.fileName) {
											storeMap[m].first.pos.push_back(st1[i].first.pos[k]);
											storeMap[m].first.pos.push_back(st2[j].first.pos[l]);
											storeMap[m].second = storeMap[m].first.pos.size();
											break;
										}
										if (m == storeMap.size() - 1) {
											tmp.fileName = st1[i].first.fileName;
											tmp.pos.push_back(st1[i].first.pos[k]);
											tmp.pos.push_back(st2[j].first.pos[l]);
											storeMap.push_back(make_pair(tmp, tmp.pos.size()));
											break;
										}
									}
								}
								else {
									tmp.fileName = st1[i].first.fileName;
									tmp.pos.push_back(st1[i].first.pos[k]);
									tmp.pos.push_back(st2[j].first.pos[l]);
									storeMap.push_back(make_pair(tmp, tmp.pos.size()));
								}
									
							}

						}
					}

				}
			}
		}
	}
	else {
		for (int i = 0; i < st2.size(); ++i) {
			if (storeMap.size() != 0) {
				for (int j = 0; j < storeMap.size(); ++j) {
					if (storeMap[j].first.fileName == st2[i].first.fileName) {
						storeMap[j].first.pos.insert(storeMap[j].first.pos.end(), st2[i].first.pos.begin(), st2[i].first.pos.end());
						storeMap[j].second = storeMap[j].first.pos.size();
						break;
					}

					else {
						storeMap.push_back(make_pair(st2[i].first, st2[i].first.pos.size()));
						break;
					}
				}
			}
			else
				storeMap.push_back(make_pair(st2[i].first, st2[i].first.pos.size()));
		}
	}

	//push map to vector to return
	vector<Store> res;

	sort(storeMap.begin(), storeMap.end(), cmp);

	for (int i = 0; i < storeMap.size(); ++i) {
		if (i == 5)
			break;
		res.push_back(storeMap[i].first);
	}
	return res;
}