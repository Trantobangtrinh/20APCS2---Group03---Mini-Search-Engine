#include "Header.h"

int convertKey(char key) {
    if (key >= 48 && key <= 57) return (key - '0');
    if (key >= 97 && key <= 122) return (int(key) - 87);
    if (key >= 65 && key <= 90) return (int(key) - 55);

    if (key == '#') return 36;
    if (key == '$') return 37;
    if (key == '%') return 38;
    if (key == '.') return 39;
    if (key == ',') return 40;
    if (key == '\'') return 41;
    if (key == '-') return 42;

    return -1;
}

void saveTrie(trieNode*& root, trieNode* &rootTitle, unordered_set<string> stopWord, vector<float> &number, string path) {
    fstream in;
    in.open(path);
    string word;
    int i = 0;
    bool isTit;
    getline(in, word);
    stringstream ss(word);
    while (ss >> word) {
        isTit = true;
        i++;
        inputData(rootTitle, stopWord, number, word, path, i, isTit);
    }

    while (in >> word) {
        isTit = false;
        i++;
        inputData(root, stopWord,number, word, path, i, isTit);
        
    }
    in.close();

}

void getStopWord(unordered_set <string> &stopWord, string path) {
    ifstream in;
    in.open(path);

    string word;
    while (in >> word)
        stopWord.insert(word);
    in.close();
    
    return;
}

void inputData(trieNode* &root, unordered_set<string> stopWord, vector<float>&number, string word, string path, int position, bool isTit) {
    trieNode* cur = root;
    bool check = false;
    // Check từ trong stop word
    // Nếu từ đó không phải stop word thì insert vào Trie
    if (isTit == true || stopWord.find(word) == stopWord.end()) {
        // Insert từ vào trie
        if (word[0] == '$') {
            size_t pos = word.length() - 1;
            string tmp = word.substr(1, pos);
            number.push_back(stof(tmp));
        }

        for (int i = 0; i < word.length(); ++i) {
            cleanData(word);
            int index = convertKey(word[i]);
            if (index == -1)
                continue;
            if ((i == word.length() - 2) && convertKey(word[i + 1]) >= 36) {
                cur->child[index] = new trieNode();
                cur = cur->child[index];
                break;
            }
            if (cur->child[index] == nullptr)
                cur->child[index] = new trieNode();

            cur = cur->child[index];
        }

        cur->isLeaf = true;
        check = true;

        // Check đã có giá trị trước đó chưa, nếu chưa thì thêm, nếu đã có thì insert vào đầu 
    }
    
    if (check) {
        for (int i = 0; i < cur->file.size(); ++i) {
            if (cur->file[i].fileName == path) {
                cur->file[i].score++;
                cur->file[i].pos.push_back(position);
                cur->file[i].isTitle = isTit;
                return;
            }
        }
        Store a;
        a.fileName = path;
        a.score++;
        a.pos.push_back(position);
        a.isTitle = isTit;
        cur->file.push_back(a);
    }
    return;
}

vector<Store> search(trieNode* root, string word) {
    trieNode* cur = root;
    for (int i = 0; i < word.length(); ++i) {
        int index = convertKey(word[i]);
        if (index == -1)
            continue;
        if (!cur->child[index]) {
            vector<Store> null;
            return null;
        }
        cur = cur->child[index];
    }
    if (cur->isLeaf) {
        return cur->file;
    }
        
    else {
        vector<Store> null;
        return null;
    }
}

void readFile(trieNode*& root, trieNode* &rootTitle, unordered_set<string> stopWords, vector<float> &number) {
    for (int i = 96; i <= 100; ++i) {
        string tmp = to_string(i) + ".txt";
        saveTrie(root, rootTitle, stopWords, number, tmp);
        cout << "\r" << i << " %";
        
    }
}

void cleanData(string& word) {
    for (int i = 0; i < word.size(); i++) {
        int idx = convertKey(word[i]);
        if (idx == -1 || (idx >= 36 && idx <= 37 && i != 0)) {
            word.erase(i, 1);
            --i;
        }
    }

    if (word.size() == 1 && convertKey(word[0]) >= 36)
        word.erase(0, 1);

    int i = word.size() - 1;
    if (i >= 0 && (convertKey(word[i]) >= 38 && convertKey(word[i]) <= 40)) {
        word.erase(i, 1);
        //i = word.size() - 1;
    }
}