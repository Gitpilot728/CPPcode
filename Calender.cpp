#include <iostream>
#include <iomanip>
class Calendar {
private:
    int year;
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const char* months[12] = {"January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};
    bool isLeapYear() {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    int getFirstDayOfYear() {
        int day = 1;
        int month = 1;
        int y = year;
        int m = 13;
        y--;
        if (month < 3) {
            m = month + 12;
            y--;
        }
        int k = y % 100;
        int j = y / 100;
        int h = (day + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;
        return ((h + 5) % 7);
    }
public:
    Calendar(int y) : year(y) {
        if (isLeapYear()) {
            daysInMonth[1] = 29; // February has 29 days in a leap year
        }
    }

    void printCalendar() {
        std::cout << "\nCalendar for " << year << "\n\n";

        int firstDay = getFirstDayOfYear();
        for (int month = 0; month < 12; month++) {
            printMonth(month, firstDay);
            firstDay = (firstDay + daysInMonth[month]) % 7;
            std::cout << "\n";
        }
    }
private:
    void printMonth(int month, int firstDay) {
        std::cout << months[month] << " " << year << "\n";
        std::cout << "Su Mo Tu We Th Fr Sa\n";
        std::cout << "---------------------\n";
        for (int i = 0; i < firstDay; i++) {
            std::cout << "   ";
        }
        for (int day = 1; day <= daysInMonth[month]; day++) {
            std::cout << std::setw(2) << day << " ";
            firstDay = (firstDay + 1) % 7;
            if (firstDay == 0 && day != daysInMonth[month]) {
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
};
int main() {
    int year;
    std::cout << "Enter year: ";
    std::cin >> year;
    if (year < 1) {
        std::cout << "Please enter a valid year.\n";
        return 1;
    }
    Calendar cal(year);
    cal.printCalendar();
    return 0;
}
