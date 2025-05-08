#include <gtest/gtest.h>
#include "NextDate.h"

// 任务1：语句覆盖率和分支覆盖率
TEST(NextDateTest, StatementAndBranchCoverage) {
    // 测试用例 1: 无效日期（语句：ValidDate 返回 false）
    // 覆盖分支：if (!ValidDate) 的 true 分支
    {
        int year = 2023, month = 13, day = 1;  // 无效月份
        int orig_year = year, orig_month = month, orig_day = day;
        NextDate(year, month, day);
        EXPECT_EQ(year, orig_year) << "Invalid date should not change year";
        EXPECT_EQ(month, orig_month) << "Invalid date should not change month";
        EXPECT_EQ(day, orig_day) << "Invalid date should not change day";
    }

    // 测试用例 2: 31 天月份，day == 31（语句：month++, day = 1）
    // 覆盖分支：month == 1||3||5||7||8||10 且 day == 31
    {
        int year = 2023, month = 10, day = 31;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 11);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 3: 31 天月份，day < 31（语句：day++）
    // 覆盖分支：month == 1||3||5||7||8||10 且 day != 31
    {
        int year = 2023, month = 10, day = 15;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 10);
        EXPECT_EQ(day, 16);
    }

    // 测试用例 4: 30 天月份，day == 30（语句：month++, day = 1）
    // 覆盖分支：month == 4||6||9||11 且 day == 30
    {
        int year = 2023, month = 4, day = 30;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 5);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 5: 30 天月份，day < 30（语句：day++）
    // 覆盖分支：month == 4||6||9||11 且 day != 30
    {
        int year = 2023, month = 4, day = 29;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 4);
        EXPECT_EQ(day, 30);
    }

    // 测试用例 6: 12 月，day == 31（语句：year++, month = 1, day = 1）
    // 覆盖分支：month == 12 且 day == 31
    {
        int year = 2023, month = 12, day = 31;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 1);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 7: 12 月，day < 31（语句：day++）
    // 覆盖分支：month == 12 且 day != 31
    {
        int year = 2023, month = 12, day = 30;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 12);
        EXPECT_EQ(day, 31);
    }

    // 测试用例 8: 2 月，闰年，day == 29（语句：month = 3, day = 1）
    // 覆盖分支：month == 2 且 LeapYear(year) && day == 29
    {
        int year = 2024, month = 2, day = 29;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 3);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 9: 2 月，闰年，day < 29（语句：day++）
    // 覆盖分支：month == 2 且 !(LeapYear(year) && day == 29)
    {
        int year = 2024, month = 2, day = 28;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 2);
        EXPECT_EQ(day, 29);
    }

    // 测试用例 10: 2 月，非闰年，day == 28（语句：month = 3, day = 1）
    // 覆盖分支：month == 2 且 !LeapYear(year) && day == 28
    {
        int year = 2023, month = 2, day = 28;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 3);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 11: 2 月，非闰年，day < 28（语句：day++）
    // 覆盖分支：month == 2 且 !(!LeapYear(year) && day == 28)
    {
        int year = 2023, month = 2, day = 27;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 2);
        EXPECT_EQ(day, 28);
    }
}