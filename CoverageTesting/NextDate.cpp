/*
 * @Author: Kyouko
 * @Date: 2025-05-08 10:05:42
 * @LastEditTime: 2025-05-08 10:05:49
 * @Description: 请输入文件描述
 * @FilePath: /Code/CoverageTesting/NextDate.cpp
 */
#include "NextDate.h"

bool LeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool ValidDate(int year, int month, int day) {
    if (year <= 0 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    if (month == 2) {
        if (LeapYear(year)) {
            return day <= 29;
        } else {
            return day <= 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    } else {
        return day <= 31;
    }
}

void NextDate(int &year, int &month, int &day) {
    if (ValidDate(year, month, day)) {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10) {
            if (day == 31) {
                month++;
                day = 1;
            } else {
                day++;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            if (day == 30) {
                month++;
                day = 1;
            } else {
                day++;
            }
        } else if (month == 12) {
            if (day == 31) {
                year++;
                month = 1;
                day = 1;
            } else {
                day++;
            }
        } else { // month == 2
            if ((LeapYear(year) && day == 29) || (!LeapYear(year) && day == 28)) {
                month = 3;
                day = 1;
            } else {
                day++;
            }
        }
    }
}