#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ifstream in;
    int countWord = 0;
    int countFile = 0;
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 100; ++j) {
            countWord = 0;
            if (j < 10) {
                in.open("Group0" + to_string(i) + "News0" + to_string(j) + ".txt");
                if (in.is_open()) {
                    // char word[300];
                    string word;
                    while (!in.eof()) {
                        in >> word;
                        // Search $
                        // char word2[300];
                        // in >> word2;
                        // if (word2[0] == '$') 
                        //     printf ("Group%dNews%d: %s %s\n", i, j, word, word2);

                        if (word[0] == '#')
                            countWord++;
                    }
                    in.close();
                }
            }
            else {
                in.open("Group0" + to_string(i) + "News" + to_string(j) + ".txt");
                if (in.is_open()) {
                    // char word[300];
                    string word;
                    while (!in.eof()) {
                        in >> word;
                        // Search $
                        // char word2[300];
                        // in >> word2;
                        // if (word2[0] == '$') 
                        //     printf ("Group%dNews%d: %s %s\n", i, j, word, word2);

                        if (word[0] == '#')
                            countWord++;
                    }
                    in.close();
                }
            }
            // if (countWord < 500) {
            //     printf ("Group%dNews%d: %d\n", i, j, countWord); 
            //     countFile++;
            // }
            if (countWord > 0)
                printf ("Group%dNews%d: %d\n", i, j, countWord); 
        }
    }
    cout << countFile << endl;
    system("pause");
    return 0;
}