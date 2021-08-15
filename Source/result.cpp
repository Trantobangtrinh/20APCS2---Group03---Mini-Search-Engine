#include "Header.h"
#include "Console.h"

void removeInt(std::vector<int>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}

void removeFloat(std::vector<float>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}

//input file name + vector posa
void highlighter(string path, vector<int> pos, int &y, bool title, int &h) {
	int tmp = y-3;
	ifstream fin;
	string word;
	int count = 0;
	fin.open(path);
	removeInt(pos);
	sort(pos.begin(), pos.end());
	int k = 0;
	int x = 10;
	int l = 135;
	gotoXY(x, y);
	Textcolor(DarkCyan);
	if (title == false) {
		getline(fin, word);
		stringstream ss(word);
		while (ss >> word) {
			count++;
			cout << word << " ";
		}
		y += 2;
		gotoXY(x, y);
		
	}
	if (title == true) {
		getline(fin, word);
		stringstream ss(word);
		while (ss >> word) {
			count++;
			if (k < pos.size() && count == pos[k]) {
				cout << "\033[1;32m" << word << "\033[0m" << " ";
				k++;
			}
			else {
				cout << word << " ";
			}
			
		}
		y += 2;
		gotoXY(x, y);
	}
	Textcolor(White);
	while (fin >> word) {
		count++;

		if (k < pos.size()) {
			if (count == pos[k]) {
				cout << "\033[1;32m" << word << "\033[0m" << " ";
				if (wherex() >= l - 10) {
					y++;
					gotoXY(x, y);
					h++;
				}
				k++;
				if (k < pos.size()) {
					while (count < pos[k - 1] + 10 && count != pos[k] - 1) {
						count++;
						if (fin >> word) {
							cout << word << " ";
							if (wherex() >= l - 10) {
								y++;
								gotoXY(x, y);
								h++;
							}
						}
						else
							break;
					}
					continue;
				}
				else {
					while (count < pos[k - 1] + 10) {
						count++;
						if (fin >> word) {
							cout << word << " ";
							if (wherex() >= l - 10) {
								y++;
								gotoXY(x, y);
								h++;
							}
						}
						else
							break;
					}
					break;
				}
			}
			else if (count == pos[k] - 10 || count == pos[k] + 10) {
				cout << "..." << " ";
				if (wherex() >= l - 10) {
					y++;
					gotoXY(x, y);
					h++;
				}
				continue;
			}
			else if (count > pos[k] - 10 && count < pos[k]) {
				cout << word << " ";
				if (wherex() >= l - 10) {
					y++;
					gotoXY(x, y);
					h++;
				}
				continue;
			}
		}
		else
			break;
	}
	x = 5;
	resultBox(x, tmp, h+5, l+5);

	fin.close();


}

void printTopRes(vector<Store> a, bool title, string query) {
	system("cls");
	int x = 20;
	int y = 2;
	gotoXY(x, y);
	box(x, y, 2, 110);
	gotoXY(x + 114, y + 1);
	cout << "Search";
	x = 25;
	y = 3;
	gotoXY(x, y);
	cout << query;
	gotoXY(25, y + 3);
	cout << "Top " << a.size() << " results: ";
	x = 10;
	y += 7;
	int l = 135;
	int xcur = x, ycur = y;
	vector<int> htotal;
	if (a.size() > 0) {
		for (int i = 0; i < a.size(); i++) {
			int h = 0;
			gotoXY(xcur, ycur);
			Textcolor(Grey);
			cout << "Filename: " << a[i].fileName << endl;
			Textcolor(White);
			ycur += 2;
			highlighter(a[i].fileName, a[i].pos, ycur, title, h);
			ycur += 5;
			h += 5;
			htotal.push_back(h);
		}
		cur(5, y-1, htotal, l+5, DarkYellow);
	}
	else {
		gotoXY(x, y);
		Textcolor(Red);
		cout << "NOT FOUND!";
	}
}

void readHistory(vector<string> &history) {
	ifstream fin;
	fin.open("history.txt");

	if (fin.is_open()) {
		string s;

		while (!fin.eof()) {
			getline(fin, s, '\n');
			history.push_back(s);
		}
	}

	fin.close();
}

void writeHistory(string s, vector<string>& history) {
	ofstream fout;
	fout.open("history.txt", ios::app);

	if (fout.is_open()) {
		fout << s << endl;
		history.push_back(s);
	}

	fout.close();
}

void clearHistory(vector<string>& history) {
	ofstream fout;

	fout.open("history.txt", ios::trunc);
	fout.close();

	history.clear();
}

//HISTORY SUGGESTION

void ZFunction(string str, int* Z) {
	int n = str.length();
	int L, R, k;

	L = R = 0;
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && str[R - L] == str[R])
				R++;
			Z[i] = R - L;
			R--;
		}
		else {
			k = i - L;
			if (Z[k] < R - i + 1)
				Z[i] = Z[k];
			else {
				L = i;
				while (R < n && str[R - L] == str[R])
					R++;
				Z[i] = R - L;
				R--;
			}
		}
	}
}

bool findHistory(string pattern, string text) {
	bool found = false;

	string concat = pattern + "$" + text;
	int l = concat.length();

	int* Z = new int[l];
	ZFunction(concat, Z);

	int size = pattern.length();
	if (Z[size + 1] == size)
		found = true;

	delete[] Z;
	return found;
}

void cleanSuggestion(int x, int y) {
	gotoXY(x+1, y);
	for (int i = 0; i < 100; ++i)
		cout << " ";
}

void inputQuery(string& input, vector<string> history) {
	Textcolor(White);
	string res = "";
	int d = 45;
	int y = 15;
	while (true) {
		if (_kbhit()) {
			gotoXY(input.size() + d + 2, y);

			char key = _getch();

			if (int(key) == 13)
				break;
			else if (int(key) == 8) {
				//backspace
				if (input.size()) {
					input.erase(input.size() - 1, y);
					gotoXY(input.size() + d + 2, y);
					cout << " ";
				}
			}
			else if (int(key) == 9) {
				//keyTab
				//auto fulfill the suggestion
				if (res.size()) {
					input = res;
					gotoXY(d + 2, 11);
					for (int i = 0; i < 65; ++i)
						cout << " ";
					gotoXY(d + 2, y);
					cout << input;
				}
			}
			else if (int(key) >= 21)
				input += key;

			if (int(key) >= 21)
				cout << key;

			//cleanSuggestion(wherex(), wherey());
			
			if (input.size()) {
				for (int i = 0; i < history.size(); ++i) {
					if (findHistory(input, history[i])) {
						Textcolor(Pink);
						gotoXY(d + 1, y + 3);
						cout << "\33[2K";
						cout << "Searched: " << history[i] << "\r";
						Textcolor(White);
						res = history[i];
						break;
					}
					else if (i == history.size() - 1) {
						gotoXY(d + 1, y + 3);
						cout << "\33[2K\r";
					}
				}
			}
			else {
				res = "";
			}
				
		}
	}
}




