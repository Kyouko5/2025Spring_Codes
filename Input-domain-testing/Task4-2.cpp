/*
 * @Author: Kyouko
 * @Date: 2025-03-27 08:29:23
 * @LastEditTime: 2025-03-27 09:07:54
 * @Description: 编写GTest程序读取RT_test_data.csv并测试。
 * @FilePath: /Code/Input-domain-testing/Task4-2.cpp
 */
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Task1.cpp"

TEST(NextDateTest, RandomTests) {
    std::ifstream infile("RT_test_data.csv");
    ASSERT_TRUE(infile.is_open()) << "无法打开 RT_test_data.csv";
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string field;
        std::vector<int> values;
        while (std::getline(ss, field, ',')) {
            values.push_back(std::stoi(field));
        }
        int year = values[0], month = values[1], day = values[2];
        int exp_year = values[3], exp_month = values[4], exp_day = values[5];
        NextDate(year, month, day);
        EXPECT_EQ(year, exp_year) << "Year mismatch for input: " << values[0] << "," << values[1] << "," << values[2];
        EXPECT_EQ(month, exp_month) << "Month mismatch for input: " << values[0] << "," << values[1] << "," << values[2];
        EXPECT_EQ(day, exp_day) << "Day mismatch for input: " << values[0] << "," << values[1] << "," << values[2];
    }
    infile.close();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}