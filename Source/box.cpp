#include "Header.h"
#include "Console.h"


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

void cur(int x, int y, vector<int> h, int w, int color) {
	bool check = true;
	int ymax;
	int ycur = y;
	int ypre = ycur;	
	int i = 0;
	int pre = i;
	while (true) {
		if (check == true) {
			gotoXY(x, ypre);
			hightlightLine(x, ypre, h[pre], w, 15);
			gotoXY(x, ycur);
			hightlightLine(x, ycur, h[i], w, color);
			ypre = ycur;
		}
		char c = _getch();
		if (c!=8) {
			c = _getch();
			if (c == 72) {
				if (i > 0) {
					pre = i;
					ycur -= h[i-1];
					i--;
					ycur -= 4;
				}
				else {
					ycur = ymax;
					pre = i;
					i = h.size()-1;
				}
			}
			else if (c == 80) {
				if (i < h.size()-1) {
					pre = i;
					ycur += h[pre];
					i++;
					ycur += 4;
				}
				else {
					ymax = ycur;
					ycur = y;
					pre = i;
					i = 0;
				}
			}
		}
		else if (c==8)
			break;

	}
}

void hightlightLine(int x, int y, int h, int w, int color) {
	Textcolor(color);
	resultBox(x, y, h, w);
}

void resultBox(int x, int y, int h, int w) {
	box(x, y, 2, w);
	y += 2;
	box(x, y, h, w);

}
