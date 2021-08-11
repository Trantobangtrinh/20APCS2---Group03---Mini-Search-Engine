#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string word;
    ifstream in;
    ofstream out;
 
    string str1 = "“", str2 = "’", str3 = "”", str4 = "—", str5 = "‘", str6 = "…";
    for (int i = 21; i <= 100; ++i) {
        int countWord = 0;
        int count = 0;

	// Change the address corresponding to your directory.
        // string file_name = "C:\\Users\\phanv\\Documents\\Code\\Search engine test\\data\\" + to_string(i) + ".txt";
        // string des = "C:\\Users\\phanv\\Documents\\Code\\Search engine test\\data\\temp.txt";

	string file_name = "C:\\.........\\data\\" + to_string(i) + ".txt";
	string des = "C:\\........\\data\\temp.txt";
        in.open(file_name);
        out.open(des);
        if (in.is_open()) {
            while (!in.eof()) {

                // Convert unknown character to normal ascii character

                int count1 = 0;
                in >> word;
                size_t found1 = word.find(str1);
                while (found1 != string::npos) {
                    word.erase(found1, 2);
                    word[found1] = '\"';
                    found1 = word.find(str1);
                }
                size_t found2 = word.find(str2);
                while (found2 != string::npos) {
                    word.erase(found2, 2);
                    word[found2] = '\'';
                    found2 = word.find(str2);
                }
                size_t found3 = word.find(str3);
                while (found3 != string::npos) {
                    word.erase(found3, 2);
                    word[found3] = '\"';
                    found3 = word.find(str3);
                }
                size_t found4 = word.find(str4);
                while (found4 != string::npos) {
                    word.erase(found4, 2);
                    word[found4] = '-';
                    found4 = word.find(str4);
                }
                size_t found5 = word.find(str5);
                while (found5 != string::npos) {
                    word.erase(found5, 2);
                    word[found5] = '\'';
                    found5 = word.find(str5);
                }
                size_t found6 = word.find(str6);
                while (found6 != string::npos) { 
                    word.erase(found6, 3);
                    word.push_back('.');
                    word.push_back('.');
                    word.push_back('.');
                    found6 = word.find(str6);
                }
                out << word << " ";
            }
            in.close();
        }
        else cout << "Error opening file.\n";
        if (out.is_open()) 
            out.close();
        
        remove(file_name.c_str());
        rename(des.c_str(), file_name.c_str());
    }
    
    system("pause");
    return 0;
}

// Uncomment the code below if you are using this program to find any file has unknown character.

// #include <iostream>
// #include <string>
// #include <fstream>

// using namespace std;

// int main() {
//     string word;
//     ifstream in;
//     ofstream out;
 
//     string str1 = "“", str2 = "’", str3 = "”", str4 = "—", str5 = "‘", str6 = "…";
//     for (int i = 21; i <= 100; ++i) {
//         int countWord = 0;
//         int count = 0;

//        // Change the address corresponding to your directory.
//        // string file_name = "C:\\Users\\phanv\\Documents\\Code\\Search engine test\\data\\" + to_string(i) + ".txt";
//        // string des = "C:\\Users\\phanv\\Documents\\Code\\Search engine test\\data\\temp.txt";

//	   string file_name = "C:\\.........\\data\\" + to_string(i) + ".txt";
//	   string des = "C:\\........\\data\\temp.txt";
//         in.open(file_name);
//         out.open(des);
//         if (in.is_open()) {
//             while (!in.eof()) {
//                 in >> word;
//                 countWord++;
//                 if (word.find("\200") != string::npos)
//                     count++;
//             }
//             printf ("%d: %d\n", i, count); 
//             in.close();
//         }
//         else cout << "Error\n";
//         if (out.is_open()) 
//             out.close();
//     }

//     system("pause");
//     return 0;
// }

