#include "Header.h"

int convertKey(char key) {
    if (key >= 48 && key <= 57) return (key - '0');
    if (key >= 97 && key <= 122) return (int(key) - 87);
    if (key >= 65 && key <= 90) return (int(key) - 55);

    if (key == '$') return 36;
    if (key == '.') return 37;
    if (key == '#') return 38;
    if (key == '-') return 39;
    if (key == '\'') return 40;
    if (key == ',') return 41;
    
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
        inputData(rootTitle, stopWord, number, word, path, i, isTit);
        i++;
    }

    while (in >> word) {
        isTit = false;
        inputData(root, stopWord,number, word, path, i, isTit);
        i++;
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
    vector<float>::iterator itr;
    // Check từ trong stop word
    // Nếu từ đó không phải stop word thì insert vào Trie
    if (isTit == true || stopWord.find(word) == stopWord.end()) {
        // Insert từ vào trie
        if (word[0] == '$') {
            size_t pos = word.length() - 1;
            string tmp = word.substr(1, pos);

            itr = find(number.begin(), number.end(), stof(tmp));
            if (itr == number.end())
                number.push_back(stof(tmp));
        }
        for (int i = 0; i < word.length(); ++i) {
            int index = convertKey(word[i]);
            if (index == -1)
                continue;
            if ((i == word.length() - 2) && convertKey(word[i + 1]) >= 36) {
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
        if (!cur->child[index] && !cur->isLeaf) {
            vector<Store> null;
            return null;
        }
        if (!cur->isLeaf)
            cur = cur->child[index];
    }

    return cur->file;
}

void readFile(trieNode*& root, trieNode* &rootTitle, unordered_set<string> stopWords, vector<float> &number) {
    for (int i = 96; i <=100; ++i) {
        string tmp = to_string(i) + ".txt";
        saveTrie(root, rootTitle, stopWords, number, tmp);
        cout << "\r" << i << " %";
        
    }
}