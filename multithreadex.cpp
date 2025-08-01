#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <cctype>
#include <mutex>
#include <sstream>

std::mutex m; 
bool isP(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}
// Print even numbers
void pE(const std::vector<int>& a) {
    std::lock_guard<std::mutex> l(m);
    std::cout << "Even: ";
    for (int n : a) {
        if (n % 2 == 0) std::cout << n << " ";
    }
    std::cout << "\n";
}
// Print odd numbers
void pO(const std::vector<int>& a) {
    std::lock_guard<std::mutex> l(m);
    std::cout << "Odd: ";
    for (int n : a) {
        if (n % 2 != 0) std::cout << n << " ";
    }
    std::cout << "\n";
}
// Print prime numbers
void pP(const std::vector<int>& a) {
    std::lock_guard<std::mutex> l(m);
    std::cout << "Prime: ";
    for (int n : a) {
        if (isP(n)) std::cout << n << " ";
    }
    std::cout << "\n";
}
// Check vowels/consonants
void cVC(const std::string& s) {
    std::lock_guard<std::mutex> l(m);
    std::cout << "Chars:\n";
    for (char c : s) {
        char lc = std::tolower(c);
        if (std::isalpha(lc)) {
            if (lc == 'a' || lc == 'e' || lc == 'i' || 
                lc == 'o' || lc == 'u') {
                std::cout << c << ": vowel\n";
            } else {
                std::cout << c << ": consonant\n";
            }
        }
    }
}

int main() {
    std::vector<int> a;
    std::string s, line;
    // Get numbers input
    std::cout << "Enter numbers (space-separated): ";
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int n;
    while (ss >> n) a.push_back(n);
    std::sort(a.begin(), a.end()); /
    std::cout << "Enter string: ";
    std::getline(std::cin, s);
    // Create threads
    std::thread t1(pE, std::ref(a));
    std::thread t2(pO, std::ref(a));
    std::thread t3(pP, std::ref(a));
    std::thread t4(cVC, std::ref(s));
    // Join threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
