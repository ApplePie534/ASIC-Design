#include <stdio.h>
#include <string.h>

// Function to check if a year is a leap year
int isLeapYear(int year) {
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

// Function to get the number of days in a month
int getDaysInMonth(int month, int year) {
    switch (month) {
        case 1:  return 31;
        case 2:  return isLeapYear(year) ? 29 : 28;
        case 3:  return 31;
        case 4:  return 30;
        case 5:  return 31;
        case 6:  return 30;
        case 7:  return 31;
        case 8:  return 31;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;  // Invalid month
    }
}

// Function to calculate the day of the week for the 1st of a given month and year
int getStartDay(int month, int year) {
    int day = 1;  // 1st day of the month
    int y = year - (month < 3);  // Adjust year if month is January or February
    int m = month + (month < 3 ? 12 : 0);  // Adjust month
    return (day + 2*m + 3*(m+1)/5 + y + y/4 - y/100 + y/400) % 7;
}

// Function to print the calendar for a given month and year
void printCalendar(int month, int year) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    const char *daysOfWeek = "Sun Mon Tue Wed Thu Fri Sat";

    char title[20];
    snprintf(title, sizeof(title), "%s %d", months[month-1], year);

    // Calculate the total width of the calendar
    int calendarWidth = 28;  // 7 days * 4 spaces (3 for numbers, 1 for space) = 28 characters
    int titlePadding = (calendarWidth - (int)strlen(title)) / 2;

    // Center the title
    printf("\n%*s%s%*s\n", titlePadding, "", title, calendarWidth - titlePadding - (int)strlen(title), "");
    printf("%s\n", daysOfWeek);

    int startDay = getStartDay(month, year);
    int daysInMonth = getDaysInMonth(month, year);

    // Print leading spaces for the first week
    for (int i = 0; i < startDay; i++) {
        printf("    ");
    }

    // Print the days of the month
    for (int day = 1; day <= daysInMonth; day++) {
        printf("%3d ", day);
        if ((startDay + day) % 7 == 0) {
            printf("\n");  // Start a new line after Saturday
        }
    }
    printf("\n");
}

int main() {
    int month, year;

    printf("Enter month (1-12): ");
    scanf("%d", &month);

    printf("Enter year: ");
    scanf("%d", &year);

    if (month < 1 || month > 12 || year < 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printCalendar(month, year);

    return 0;
}
