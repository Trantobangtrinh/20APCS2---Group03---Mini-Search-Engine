#include "Header.h"
#include <sstream>

string numberToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

string floatToString(float num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

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

bool checkValid(char& key) {
	if (key >= 65 && key <= 90) {
		key = int(key) + 32;
		return true;
	}
	if ((key >= 48 && key <= 57) || (key >= 97 && key <= 122)) return true;
	if (key == '\n'){
		key = ' '; return true;
	}
	if (key == '') {
		key = '-'; return true;
	}
	if (key == ' ' || key == '$' || key == '%' || key == '#'|| key == '-') return true;
	return false;
}

bool isNumber(char key) {
    if (key >= 48 && key <= 57)
        return true;
    return false;
}

bool isWord(char key){
	if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) return true;
	return false;
} 