#include "Header.h"
#include "Console.h"


void start() {
	setFontSize(0, 20);
	stringstream ss;

	unordered_set<string> stopWords;
	getStopWord(stopWords, "stopWord.txt");

	vector<pair<string, vector<string>>> dict;
	readDictionary(dict);

	trieNode* rootData = new trieNode();
	trieNode* rootTitle = new trieNode();
	vector<float> number;
	vector<string> history;

	auto start = high_resolution_clock::now();
	read11kFile(rootData, rootTitle, number);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count() << endl;

	system("pause");
	readHistory(history);
	removeFloat(number);
	sort(number.begin(), number.end());

	char key;
	bool check = false;


	string query;
	string a[12] = { "AND", "OR", "intitle:", "filetype:", "+", "-", "#", "..", "\"", "*", "~", "$" };
	while (true) {
		drawConsole();
		string query;
		box(40, 14, 2, 85);

		inputQuery(query, history);
		writeHistory(query, history);

		int choice = -1;

		for (int i = 0; i < 12; ++i) {
			string key = a[i];
			size_t found = query.find(key);

			if (found != string::npos && query.size() > a[i].size()) {
				choice = i;
				break;
			}
		}

		vector<Store> res;
		vector<pair<Store, int>> exact;
		int title = false;
		switch (choice) {
		case 0:
			res = ANDquery(rootData, query, stopWords); //done
			break;
		case 1:
			res = ORquery(rootData, query, stopWords); //done
			break;
		case 2:
			res = intitleQuery(rootTitle, rootData, query, stopWords); //done
			title = true;
			break;
		case 3:
			res = filetypeQuery(rootData, query, stopWords); //done
			break;
		case 4:
			res = PLUSquery(rootData, query, stopWords); //done
			break;
		case 5:
			res = MINUSquery(rootData, query, stopWords); //done
			break;
		case 6:
			res = hastagOperator(rootData, query, stopWords); //done
			break;
		case 7:
			res = inRange(rootData, query, stopWords, number); //done
			break;
		case 8:
			exact = exactMatch(rootData, query, stopWords); //done
			check = true;
			break;
		case 9:
			res = searchWildcard(rootData, query, stopWords); //done
			break;
		case 10:
			res = synonym(rootData, dict, query); //done
			break;
		case 11:
			res = signQuery(rootData, query, stopWords); //done
			break;
		case -1:
			res = hastagOperator(rootData, query, stopWords); //done

		}
		if (check == true) {
			vector <Store> ans;
			for (int i = 0; i < exact.size(); ++i) {
				if (i == 5)
					break;
				ans.push_back(exact[i].first);
			}
			printTopRes(ans, title, query);
			ans.clear();
		}
		else {
			printTopRes(res, title, query);			
			res.clear();
		}
		key = _getch();
		if (key == 27)
			break;
	}

	endConsole();
	delete rootData;
	delete rootTitle;

	return;
}

void drawConsole() {
	system("cls");
	srand((unsigned)time(NULL));
	int x = 40, y = 5;
	
	int size = 8;
	while (!_kbhit()) {
		Textcolor(rand() % 15 + 1);
		gotoXY(x, y);
		cout << "     _______. _______      ___.      ______        ______  __    __   __   _______ ";
		y += 1;
		gotoXY(x, y);
		cout << "    /       ||   ____|    /   \\     |   _  \\      /      ||  |  |  | |  | |   ____|";
		y += 1;
		gotoXY(x, y);
		cout << "   |  (----` |  |__      /  ^  \\    |  |_)  |    |, ----' |  |__|  | |  | |  |__   ";
		y += 1;
		gotoXY(x, y);
		cout << "    \\   \\    |   __|    /  /_\\  \\   |      /     |  |     |   __   | |  | |   __| ";
		y += 1;
		gotoXY(x, y);
		cout << ".----)   |   |  |____  /  _____  \\  |  |\\  \\----.|  `----.|  |  |  | |  | |  |____ ";
		y += 1;
		gotoXY(x, y);
		cout << "|_______/    |_______|/__/     \\__\\ | _| `._____| \\______||__|  |__| |__| |_______|";
		y = 5;
		Sleep(1000);
	}
	char c = _getch();
	if (c == 27) {
		endConsole();
	}
}

void endConsole() {
	system("cls");
	srand((unsigned)time(NULL));
	int x = 35, y = 15;

	int size = 8;
	while (!_kbhit()) {
		Textcolor(rand() % 15 + 1);
		gotoXY(x, y);
		cout << " _________  ____  ____       _       ____  _____  ___  ____    ____  ____   ___   _____  _____  ";
		y += 1;
		gotoXY(x, y);
		cout << "|  _   _  ||_   ||   _|     / \\     |_   \\|_   _||_  ||_  _|  |_  _||_  _|.'   `.|_   _||_   _| ";
		y += 1;
		gotoXY(x, y);
		cout << "|_/ | |  \\|  | |__| |      / _ \\      |   \\ | |    | |_/ /      \\ \\  / / /  .-.  \\ | |    | |   ";
		y += 1;
		gotoXY(x, y);
		cout << "    | |      |  __  |     / ___ \\     | |\\ \\| |    |  __'.       \\ \\/ /  | |   | | | '    ' |   ";
		y += 1;
		gotoXY(x, y);
		cout << "   _| |_    _| |  | |_  _/ /   \\ \\_  _| |_\\   |_  _| |  \\ \\_     _|  |_  \\  `-'  /  \\ \\__/ /    ";
		y += 1;
		gotoXY(x, y);
		cout << "  |_____|  |____||____||____| |____||_____|\\____||____||____|   |______|  `.___.'    `.__.'     ";
		y = 15;
		Sleep(1000);
	}
	exit(1);
}