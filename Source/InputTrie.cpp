#include "Header.h"

void saveTrie(trieNode*& root, unordered_set<string> stopWord, string path) {
    fstream in;
    in.open(path);
    string word;
    int i = 0;
    bool isTit = true;
    if (in.is_open()) {
        while (in >> word) {
            for (int j = 0; j < word.length(); ++j) {
                if (word[j] < 'A' || word[j] > 'Z') {
                    isTit = false;
                    break;
                }
            }
            inputData(root, stopWord, word, path, i, isTit);
            i++;
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

void inputData(trieNode* &root, unordered_set<string> stopWord, string word, string path, int position, bool isTit) {
    trieNode* cur = root;

    // Check từ trong stop word
    // Nếu từ đó không phải stop word thì insert vào Trie
    if (isTit == false) {
        word[0] = tolower(word[0]);
    }
    if (isTit == true || stopWord.find(word) == stopWord.end()) {
        // Insert từ vào trie
        for (int i = 0; i < word.length(); ++i) {
            word[i] = tolower(word[i]);
            int index = word[i] - 'a';
            if (word[i] < 'a' || word[i] > 'z')
                continue;
            if (cur->child[index] == nullptr)
                cur->child[index] = new trieNode();
            cur = cur->child[index];
        }

        cur->isLeaf = true;

        // Check đã có giá trị trước đó chưa, nếu chưa thì thêm, nếu đã có thì insert vào đầu 
    }
    
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