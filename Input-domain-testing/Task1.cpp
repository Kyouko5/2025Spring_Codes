/**
 * @description: 判断是否为闰年。闰年规则为：能被4整除但不能被100整除，或能被400整除。
 */
bool LeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


/**
 * @description: 检查日期是否合法，包括年份为正整数，月份在1-12之间，日期在该月有效范围内（考虑闰年）
 */
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

/**
 * @description: 如果日期合法，计算下一天；否则，不修改参数。处理逻辑包括：
 * 31天月份（1、3、5、7、8、10）：日期31变为下月1日，否则日期+1。
 * 30天月份（4、6、9、11）：日期30变为下月1日，否则日期+1。
 * 12月：31日变为下一年1月1日，否则日期+1。
 * 2月：闰年29日或平年28日变为3月1日，否则日期+1。
 */
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
    // 如果日期不合法，不修改参数
}