#include "Header.h"

void saveTrie(trieNode*& root, unordered_set<string> stopWord, string path) {
    fstream in;
    in.open(path);
    string word;
    if (in.is_open()) {
        while (in >> word) {
            inputData(root, stopWord, word, path);
        }
        in.close();
    }
    else cout << "\nUnable to open " << path << " directory.\n";
}

void getStopWord(unordered_set <string> &stopWord, string path) {
    ifstream in;
    in.open(path);

    string word;

    if (in.is_open()) {
        while (in >> word)
            stopWord.insert(word);
        in.close();
    }
    else cout << "\nUnable to open " << path << " directory.\n";
    return;
}

void inputData(trieNode* &root, unordered_set<string> stopWord, string word, string path) {
    trieNode* cur = root;

    // Check từ trong stop word
    // Nếu từ đó không phải stop word thì insert vào Trie
    if (stopWord.find(word) == stopWord.end()) {

        // Insert từ vào trie
        for (int i = 0; i < word.length(); ++i) {
            int index = tolower(word[i]) - 'a';
            if (index < 0 || index >= 26) {
                continue;
            }
            if (cur->child[index] == nullptr)
                cur->child[index] = new trieNode();
            cur = cur->child[index];
        }

        cur->isLeaf = true;

        // Check đã có giá trị trước đó chưa, nếu chưa thì thêm, nếu đã có thì insert vào đầu
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

void display(struct trieNode* root, char str[], int level)
{
    // Nếu là leaf node, thì đã tạo thành một từ rồi
    // Thêm \0 ở cuối để cout ra
    if (root->isLeaf) 
    {
        str[level] = '\0';
        cout << str << " ";
    }
  
    for (int i = 0; i < MAX; i++) 
    {
        if (root->child[i]) 
        {
            str[level] = i + 'a';
            display(root->child[i], str, level + 1);
        }
    }
}