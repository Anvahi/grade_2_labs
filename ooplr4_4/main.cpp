#include <iostream>
#include <ctime>
using namespace std;

//Дана дата. Вывести, сколько дней до нее осталось (или сколько
//дней прошло)

int main() {
    time_t now = time(nullptr);
    tm *loc = localtime(&now);
    tm find;
    int day = loc->tm_mday;
    int mon = loc->tm_mon+1;
    int year = loc->tm_year+1900;
    find.tm_wday = 0;
    find.tm_hour = 0;
    find.tm_isdst = 0;
    find.tm_min = 0;
    find.tm_sec = 0;
    find.tm_yday = 0;
    cout << "Enter the day:";
    cin >> find.tm_mday;
    cout << "Enter the month:";
    cin >> find.tm_mon;
    find.tm_mon -= 1;
    cout << "Enter the year:";
    cin >> find.tm_year;
    find.tm_year -= 1900;
    double rez = difftime(now, mktime(&find))/86400;
    cout << "Difference is equal " << abs(rez) << ".\n";
    return 0;
}