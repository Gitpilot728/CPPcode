#include <iostream>
#include <string>
using namespace std;

string repited_ltr(string str) {
    if (str.empty()) return "-1"; /
    int max_repeats = 0;
    int start = 0, word_start = 0, word_end = 0;
    string result = "-1";
    str += " ";
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || i == str.length() - 1) {
            if (i > start) {
                string word = str.substr(start, i - start);
                int letter_count[26] = {0};
                int repeats = 0;
                for (char c : word) {
                    if (isalpha(c)) {
                        letter_count[tolower(c) - 'a']++;
                        if (letter_count[tolower(c) - 'a'] == 2) {
                            repeats++;
                        }
                    }
                }
                if (repeats > max_repeats) {
                    max_repeats = repeats;
                    result = word;
                    word_start = start;
                    word_end = i;
                }
            }
            start = i + 1;
        }
    }

    return result;
}
int main() {
    string input;
    cout << "Enter a string (or 'quit' to exit): ";
    while (getline(cin, input) && input != "quit") {
        if (input.empty()) {
            cout << "Word with the highest number of repeated letters: -1\n";
        } else {
            cout << "Original string: " << input << "\n";
            cout << "Word with the highest number of repeated letters: " << repited_ltr(input) << "\n";
        }
        cout << "\nEnter a string (or 'quit' to exit): ";
    }
    cout << "Program terminated.\n";
    return 0;
}
