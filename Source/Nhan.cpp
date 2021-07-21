#include"Header.h"
#include"Nhan.h"



int convertKey(char key) {
	if (key >= 48 && key <= 57) return (key - '0');
	if (key >= 97 && key <= 122) return (int(key) - 87);
	if (key >= 65 && key <= 90) return (int(key) - 55);
	if (key == ' ') return 36;
	if (key == '.') return 37;
	if (key == '$') return 38;
	if (key == '%') return 39;
	if (key == '#') return 40;
	if (key == '-') return 41;
	return -1;
}

trieNode* searchWord(trieNode* root, string key) {
	trieNode* pCur = root;
	int index, length = key.length();
	for (int i = 0; i < length; ++i) {
		index = convert(key[i]);
		if (index == -1) continue;
		if (!pCur->children[index]) return NULL;
		pCur = pCur->children[index];
	}
	if (pCur) {
		if (title && !pCur->isTitle) return NULL;
		if (pCur->isLeaf) return pCur;
	}
	return NULL;
}


