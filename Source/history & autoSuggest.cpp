#include "Header.h"

struct Node {
    string word;
    int count;
    Node* pNext;
};

void history(Node* historyR) {
	ofstream out;
	out.open("history.txt", ios::app);
	if (out) {
		out << historyR->word << endl;
	}
	else {
		cout << "Can not open file";
		return;
	}
	out.close();
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

void getHistory(Node* historyR) {
	ifstream in;
	Node* pCur = historyR;
	in.open("history.txt");
	if (in) {
		for (int i = 1; i <= numberOfLine("history.txt"); i++) {
			if (historyR == nullptr) {
				historyR = new Node;
				pCur = historyR;
			}
			else {
				pCur->pNext = new Node;
				pCur = pCur->pNext;
			}
			getline(in, pCur->word);
			pCur->pNext = nullptr;
		}
		in.close();
	}
}

bool stringcmp(string input, string data) {
    if (input == " ") return true;
 	if (input == data) return true;
 	else return false;
    //dang lam tiep
    //khuc nay dang chua biet compare sao
    //compare the nao de in ra may tu da nhap roi?
}

void autoSuggest(Node* historyR, string word) {
	int appear;
	if (stringcmp(word, historyR->word) == true && appear < 4) {
		cout << historyR->word;
		historyR = historyR->pNext;
		appear++;
	}
	else if (stringcmp(word, historyR->word) == false && appear < 4) {
		historyR = historyR->pNext;
	}
}