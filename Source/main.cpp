#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include "Console.h"
#include "Header.h"

using namespace std;

int main() {
    setConsoleWindow(800, 600);
    trieNode *root = new trieNode();
    unordered_set <string> stopWord;

    getStopWord(stopWord, "stopWord.txt");
    saveTrie(root, stopWord, "Data1000.txt");

    // int level = 0;
    // char str[20];

    // display(root, str, level);

    char choice = '4';

    while (choice != '0') { 
        gotoXY(26, 5); cout << "=======================================================";
        Textcolor(3);
        gotoXY(44, 8); cout << "MINI SEARCH ENGINE";
        Textcolor(Blue);
        gotoXY(47, 11); cout << "B";
        Textcolor(Red);
        gotoXY(49, 11); cout << "O";
        Textcolor(Yellow);
        gotoXY(51, 11); cout << "O";
        Textcolor(Blue);
        gotoXY(53, 11); cout << "B";
        Textcolor(Green);
        gotoXY(55, 11); cout << "L";
        Textcolor(Red);
        gotoXY(57, 11); cout << "E";
        Textcolor(7);
        gotoXY(26, 14); cout << "=======================================================";

        gotoXY(40, 17); cout << "1. Search";
        gotoXY(40, 19); cout << "2. View history";
        gotoXY(40, 21); cout << "3. Exit";
        gotoXY(40, 23); cout << char(26) << " Enter your choice: ";

        string query;
        choice = getchar();
        cin.ignore(100, '\n');

        switch (choice) {

            case '1':
                gotoXY(40, 17); cout << "                            ";
                gotoXY(40, 19); cout << "                            ";
                gotoXY(40, 21); cout << "                            ";
                gotoXY(40, 23); cout << "                            ";
                gotoXY(43, 17); cout << "Enter query:\n";
                gotoXY(40, 19); getline(cin, query, '\n');

                // Put something here.... 
                gotoXY(40, 21); cout << "Searching for " << query << "....";

                // temp:
                cout << "\n\n\t\t\t\t\tUpdate soon..\n\n\t\t\t\t\tPress any key to return...";


                getch();
                system("cls");
                choice = '4';
                break;

            case '2':
                gotoXY(40, 17); cout << "                            ";
                gotoXY(40, 19); cout << "                            ";
                gotoXY(40, 21); cout << "                            ";
                gotoXY(40, 23); cout << "                            ";
                gotoXY(47, 17); cout << "History:\n";

                // Put something here.... 
                // temp:
                cout << "\n\n\t\t\t\t\tUpdate soon..\n\n\t\t\t\t\tPress any key to return...";

                
                getch();
                system("cls");
                choice = '4';
                break;
            
            case '3':
                gotoXY(40, 17); cout << "                            ";
                gotoXY(40, 19); cout << "                            ";
                gotoXY(40, 21); cout << "                            ";
                gotoXY(40, 23); cout << "                            ";
                gotoXY(35, 22); cout << "Thank you for using our search engine\n\n\t\t\t\t\t";
                Sleep(2500);
                choice = '0';
                break;
        }
    }

    system("pause");
    return 0;
}