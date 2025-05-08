#include <gtest/gtest.h>
#include "NextDate.h"

//任务2：判定覆盖率和条件覆盖率
TEST(NextDateTest, DecisionAndConditionCoverage) {
    // 测试用例 1: ValidDate 返回 false（判定：!ValidDate 为 true）
    // 条件：year <= 0, month < 1, month > 12, day < 1
    {
        int year = 2023, month = 13, day = 1;
        int orig_year = year, orig_month = month, orig_day = day;
        NextDate(year, month, day);
        EXPECT_EQ(year, orig_year);
        EXPECT_EQ(month, orig_month);
        EXPECT_EQ(day, orig_day);
    }

    // 测试用例 2: ValidDate 返回 true（判定：!ValidDate 为 false）
    // 条件：year > 0, 1 <= month <= 12, day >= 1
    {
        int year = 2023, month = 10, day = 15;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 10);
        EXPECT_EQ(day, 16);
    }

    // 测试用例 3: 31 天月份，day == 31（判定：month == 1||3||5||7||8||10 为 true, day == 31 为 true）
    // 条件：month == 1, month == 3, ..., day == 31
    {
        int year = 2023, month = 10, day = 31;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 11);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 4: 非 31 天月份（判定：month == 1||3||5||7||8||10 为 false）
    // 条件：month != 1, 3, 5, 7, 8, 10
    {
        int year = 2023, month = 4, day = 29;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 4);
        EXPECT_EQ(day, 30);
    }

    // 测试用例 5: 30 天月份，day == 30（判定：month == 4||6||9||11 为 true, day == 30 为 true）
    // 条件：month == 4, 6, 9, 11, day == 30
    {
        int year = 2023, month = 4, day = 30;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 5);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 6: 12 月，day == 31（判定：month == 12 为 true, day == 31 为 true）
    // 条件：month == 12, day == 31
    {
        int year = 2023, month = 12, day = 31;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 1);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 7: 2 月，闰年，day == 29（判定：(LeapYear(year) && day == 29) 为 true）
    // 条件：LeapYear(year) = true, day == 29
    {
        int year = 2024, month = 2, day = 29;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 3);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 8: 2 月，非闰年，day == 28（判定：(!LeapYear(year) && day == 28) 为 true）
    // 条件：LeapYear(year) = false, day == 28
    {
        int year = 2023, month = 2, day = 28;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 3);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 9: 2 月，判定为 false（判定：(LeapYear(year) && day == 29) || (!LeapYear(year) && day == 28) 为 false）
    // 条件：LeapYear(year) = true, day != 29 或 LeapYear(year) = false, day != 28
    {
        int year = 2024, month = 2, day = 28;
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 2);
        EXPECT_EQ(day, 29);
    }
}