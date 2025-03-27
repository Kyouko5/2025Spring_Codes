/*
 * @Author: Kyouko
 * @Date: 2025-03-27 08:52:46
 * @LastEditTime: 2025-03-27 09:02:18
 * @Description: 使用GTest框架测试NextDate函数，确保所有代码行至少执行一次（依据PIE模型，不考虑if语句的短路计算）。
 * @FilePath: /Code/Input-domain-testing/Task2.cpp
 */

 /**
  * 为覆盖所有分支，测试用例包括：
    31天月份：普通日期（如10月15日→16日）、月末（如10月31日→11月1日）。
    30天月份：普通日期（如4月29日→30日）、月末（如4月30日→5月1日）。
    12月：普通日期（如12月30日→31日）、年末（如12月31日→下一年1月1日）。
    2月：平年28日（如2023-2-28→3-1）、闰年28日（如2024-2-28→2-29）、闰年29日（如2024-2-29→3-1）、平年27日（如2023-2-27→2-28）。
    无效日期：月份超范围（如13月1日）、日期超范围（如4月31日），参数应保持不变。
  */
#include <gtest/gtest.h>
#include "Task1.cpp"

TEST(NextDateTest, Normal31DayMonth) {
    int year = 2023, month = 10, day = 15;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 10);
    EXPECT_EQ(day, 16);
}

TEST(NextDateTest, EndOf31DayMonth) {
    int year = 2023, month = 10, day = 31;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 11);
    EXPECT_EQ(day, 1);
}

TEST(NextDateTest, Normal30DayMonth) {
    int year = 2023, month = 4, day = 29;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 4);
    EXPECT_EQ(day, 30);
}

TEST(NextDateTest, EndOf30DayMonth) {
    int year = 2023, month = 4, day = 30;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 5);
    EXPECT_EQ(day, 1);
}

TEST(NextDateTest, NormalDecember) {
    int year = 2023, month = 12, day = 30;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 12);
    EXPECT_EQ(day, 31);
}

TEST(NextDateTest, EndOfYear) {
    int year = 2023, month = 12, day = 31;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2024);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
}

TEST(NextDateTest, FebruaryNonLeapYearNormal) {
    int year = 2023, month = 2, day = 27;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 2);
    EXPECT_EQ(day, 28);
}

TEST(NextDateTest, FebruaryNonLeapYearEnd) {
    int year = 2023, month = 2, day = 28;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(month, 3);
    EXPECT_EQ(day, 1);
}

TEST(NextDateTest, FebruaryLeapYearNormal) {
    int year = 2024, month = 2, day = 28;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2024);
    EXPECT_EQ(month, 2);
    EXPECT_EQ(day, 29);
}

TEST(NextDateTest, FebruaryLeapYearEnd) {
    int year = 2024, month = 2, day = 29;
    NextDate(year, month, day);
    EXPECT_EQ(year, 2024);
    EXPECT_EQ(month, 3);
    EXPECT_EQ(day, 1);
}

TEST(NextDateTest, InvalidMonth) {
    int year = 2023, month = 13, day = 1;
    int orig_year = year, orig_month = month, orig_day = day;
    NextDate(year, month, day);
    EXPECT_EQ(year, orig_year);
    EXPECT_EQ(month, orig_month);
    EXPECT_EQ(day, orig_day);
}

TEST(NextDateTest, InvalidDay) {
    int year = 2023, month = 4, day = 31;
    int orig_year = year, orig_month = month, orig_day = day;
    NextDate(year, month, day);
    EXPECT_EQ(year, orig_year);
    EXPECT_EQ(month, orig_month);
    EXPECT_EQ(day, orig_day);
}