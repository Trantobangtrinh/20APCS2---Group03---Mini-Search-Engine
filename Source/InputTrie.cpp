#include "Header.h"

void saveTrie(trieNode*& root, unordered_set<string> stopWord, string path) {
    fstream in;
    in.open(path);
    string word;
    while (in >> word) {
        inputData(root, stopWord, word, path);
    }
    in.close();
}

void inputData(trieNode* &root, unordered_set<string> stopWord, string word, string path) {
    trieNode* cur = root;

    //check từ trong stop word
    if (stopWord.find(word) == stopWord.end()) {
        //insert từ vào trie
        for (int i = 0; i < word.length(); ++i) {
            int index = tolower(word[i]) - 'a';
            if (index < 0 || index >= 26) {
                continue;
            }
            if (cur->child[index] == nullptr)
                cur->child[index] = new trieNode();
            cur = cur->child[index];
        }
        //check đã có giá trị trước đó chưa, nếu chưa thì thêm, nếu đã có thì insert vào đầu
        if (cur->list == nullptr) {
            cur->list = new node;
            cur->list->data = path;
            cur->list->next = nullptr;
        }
        else {
            node* tmp = new node;
            tmp->data = path;
            tmp->next = cur->list;
            cur->list = tmp;
        }
    }
    
}