#include <stdio.h>
#include <time.h>

// Function to check leap year
int isLeap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

// Days in each month
int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

// Function to count total days till given date
int countDays(int d, int m, int y) {
    int days = d;

    for (int i = 0; i < m - 1; i++) {
        days += monthDays[i];
    }

    if (m > 2 && isLeap(y)) {
        days += 1;
    }

    days += y * 365 + y / 4 - y / 100 + y / 400;

    return days;
}

// Function to get name of day
const char* getDayName(int day, int month, int year) {
    static const char* days[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    struct tm timeStruct = {0};
    timeStruct.tm_mday = day;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_year = year - 1900;
    mktime(&timeStruct);
    return days[timeStruct.tm_wday];
}

int main() {
    int b_day, b_month, b_year;
    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    int c_day = today.tm_mday;
    int c_month = today.tm_mon + 1;
    int c_year = today.tm_year + 1900;

    printf("Enter your Date of Birth (DD MM YYYY): ");
    scanf("%d %d %d", &b_day, &b_month, &b_year);

    int birthDays = countDays(b_day, b_month, b_year);
    int currentDays = countDays(c_day, c_month, c_year);

    int total = currentDays - birthDays;

    int years = total / 365;
    total %= 365;
    int months = total / 30;
    int days = total % 30;

    printf("\nYou are %d years, %d months, and %d days old.\n", years, months, days);
    printf("You were born on a %s.\n", getDayName(b_day, b_month, b_year));

    return 0;
}
