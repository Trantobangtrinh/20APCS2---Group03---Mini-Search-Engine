#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <mmsystem.h>

#define SIZE			16  
#define Black			0
#define DarkBlue		1
#define DarkGreen		2
#define DarkCyan		3
#define DarkRed			4
#define DarkPink		5
#define DarkYellow		6
#define DarkWhite		7
#define Grey			8
#define Blue			9
#define Green			10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15
#define defaultColor	7 

// Function to set the size of the console
void setConsoleWindow(int w, int h);

// Function to lock the size of the console
void fixConsoleWindow();

// Function to coloring text
void Textcolor(int color);

// Function to move cursor 
void gotoXY(int x, int y);

// Function to hide the cursor
void AnTroChuot();
#endif