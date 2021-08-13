#include "Header.h"
#include "Console.h"

void hightlightLine(int x, int y, int h, int w, int color);
void box(int x, int y, int h, int w);
void cur(int x, int y, int h, int w, int color);


void box(int x, int y, int h, int w) {
	if (h < 2 || w < 2) return;
	for (int i = x; i <= x + w; i++) {
		gotoXY(i, y); cout << char(196);
		gotoXY(i, y + h); cout << char(196);
	}
	for(int i = y; i <= y + h; i++) {
		gotoXY(x, i); cout << char(179);
		gotoXY(x + w, i); cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + w, y); cout << char(191);
	gotoXY(x, y + h); cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);
}

void cur(int x, int y, int h, int w, int color) {
	bool check = true;
	int ycur = y;
	int ypre = ycur;	
	while (true) {
		if (check == true) {
			gotoXY(x, ypre);
			hightlightLine(x, ypre, h, w, 15);
			ypre = ycur;
			hightlightLine(x, ycur, h, w, color);
			check == false;
		}
		char c = _getch();
		if (_kbhit()) {
			if (c == -32) {
				c = _getch();
				if (c == 72) {
					if (ycur > 10) {
						ycur -= 9;
					}
				}
				else if (c == 80) {
					if (ycur < 46) {
						ycur += 9;
					}
					else ycur = 10;
				}
			}
		}
	}
}

void hightlightLine(int x, int y, int h, int w, int color) {
	Textcolor(color);
	if (h < 2 || w < 2) return;
	for (int i = x; i <= x + w; i++) {
		gotoXY(i, y); cout << char(196);
		gotoXY(i, y + h); cout << char(196);
	}
	for (int i = y; i <= y + h; i++) {
		gotoXY(x, i); cout << char(179);
		gotoXY(x + w, i); cout << char(179);
	}
	gotoXY(x, y); cout << char(218);
	gotoXY(x + w, y); cout << char(191);
	gotoXY(x, y + h); cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);
}

// small main to test
// int main() {
// 	gotoXY(37, 0); cout << "G O O G L E";
// 	box(20, 3, 3, 40);
// 	for (int i = 0; i < 5; i++) {
// 		box(10, 10 + 9*i, 8, 60);
// 	}

// 	cur(10, 10, 8, 60, 10);
// 	return 0;
// }