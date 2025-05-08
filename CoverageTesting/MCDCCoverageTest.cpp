

#include <gtest/gtest.h>
#include "NextDate.h"

// 任务3：MCDC 覆盖
TEST(NextDateTest, MCDCCoverage) {
    // 测试用例 1: (LeapYear(year) && day == 29) = true
    // MCDC: C1 = true, C2 = true, 判定 = true
    // 改变 C1 或 C2 使判定变为 false
    {
        int year = 2024, month = 2, day = 29;  // 闰年，2月29日
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 3);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 2: (LeapYear(year) && day == 29) = false, (!LeapYear(year) && day == 28) = true
    // MCDC: C3 = true, C4 = true, 判定 = true
    // 改变 C3 或 C4 使判定变为 false
    {
        int year = 2023, month = 2, day = 28;  // 非闰年，2月28日
        NextDate(year, month, day);
        EXPECT_EQ(year, 2023);
        EXPECT_EQ(month, 3);
        EXPECT_EQ(day, 1);
    }

    // 测试用例 3: (LeapYear(year) && day == 29) = false, (!LeapYear(year) && day == 28) = false
    // MCDC: C1 = true, C2 = false, 判定 = false
    // 改变 C1 使判定变为 true
    {
        int year = 2024, month = 2, day = 28;  // 闰年，2月28日
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 2);
        EXPECT_EQ(day, 29);
    }

    // 测试用例 4: (LeapYear(year) && day == 29) = false, (!LeapYear(year) && day == 28) = false
    // MCDC: C3 = false, C4 = false, 判定 = false
    // 改变 C3 使判定变为 true
    {
        int year = 2024, month = 2, day = 27;  // 闰年，2月27日
        NextDate(year, month, day);
        EXPECT_EQ(year, 2024);
        EXPECT_EQ(month, 2);
        EXPECT_EQ(day, 28);
    }
}