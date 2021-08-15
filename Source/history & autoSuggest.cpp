#include "Header.h"
#include <queue>

bool all_null(trieNode* root) {
	if (root == nullptr) return true;
	for (int i = 0; i < 42; i++) {
		if (root->child[i] != nullptr)
			return false;
	}
	return true;
}

int numberOfLine(string filename) {
	ifstream in;
	in.open(filename);
	string s;
	int count = 0;
	while (!in.eof()) {
		getline(in, s, '\n');
		if (s != "") {
			count++;
		}
	}
	in.close();
	return count;
}

trieNode* getNode()
{
	trieNode* temp = new trieNode;
	for (int i = 0; i < 42; i++)
	{
		temp->child[i] = NULL;
	}
	return temp;
}

void saveHistory(trieNode* root) {
	ofstream out;
	if (root == nullptr) return;
	trieNode* cur = root;
	out.open("history.txt", ios::app);
	if (out) {
		while ((all_null(cur) == false)) {
			for (int i = 0; i < 42; i++)
			{
				if (cur->child[i] != nullptr) {
					out << cur->child[i];
					saveHistory(cur->child[i]);
				}
			}
		}
	}
	else {
		cout << "Can not open file";
		return;
	}
	out.close();
}

void insert(trieNode* root, string key)
{
	trieNode* temp = root;
	for (int i = 0; i < (int)key.length(); i++)
	{
		//tui nhớ trước mình có hàm đổi mã ascii mà kiếm không thấy nữa nên xài code mẫu nha
		int ind = convertKey(key[i]);
		if (temp->child[ind] == NULL)
		{
			temp->child[ind] = getNode();
		}
		temp = temp->child[ind];
	}
}

void getHistory(trieNode* root) {
	ifstream in;
	string str;
	in.open("history.txt");
	if (in) {
		for (int i = 1; i <= numberOfLine("history.txt"); i++) {
			in >> str;
			insert(root, str);
		}
		in.close();
	}
}

void findWordSuggest(trieNode* root, string key, vector<string>& suggestions) {
	if (root == NULL) return;
	trieNode* temp = root;
	for (int i = 0; i < (int)key.length(); i++)
	{
		int ind = convertKey(key[i]);
		if (temp->child[ind] == NULL) return;
		temp = temp->child[ind];
	}

	queue<pair<trieNode*, string> > q;
	q.push(make_pair(temp, key));
	string this_word;

	while (!q.empty())
	{
		temp = q.front().first;
		this_word = q.front().second;
		suggestions.push_back(this_word);
		q.pop();
		for (int i = 10; i < 36; i++)
		{
			if (temp->child[i] != NULL)
			{
				q.push(make_pair(temp->child[i], this_word + char(i + 87)));
			}
		}
	}
}

void auto_complete(trieNode* root, string key)
{
	if (key.length() == 0) return;
	vector<string> suggestions;

	findWordSuggest(root, key, suggestions);

	if (suggestions.size() == 0)
	{
		cout << "There is no suggestion '\n'";
		return;
	}
	else{
		for (int i = key.size(); i<suggestion[0].size(); ++i){
			cout << suggestion[0][i];
		}
		cout << "There are " << suggestions.size() << " suggestions for " << key << '\n';
		for (int i = 1; i < suggestion.size(); i++) {
			cout << suggestions[i] << ' ';
	}
	}
	

	return;
}