/*
 * @Author: Kyouko
 * @Date: 2025-03-27 08:28:11
 * @LastEditTime: 2025-03-27 09:08:00
 * @Description: 生成100条随机测试用例，保存到RT_test_data.csv，每行格式为year,month,day,exp_year,exp_month,exp_day。预期结果使用标准库计算。
 * @FilePath: /Code/Input-domain-testing/Task4-1.cpp
 */
#include <fstream>
#include <random>
#include <ctime>
#include <tuple>
#include <utility>
#include "Task1.cpp"

std::tuple<int, int, int> computeNextDate(int year, int month, int day) {
    if (!ValidDate(year, month, day)) {
        return std::make_tuple(year, month, day);
    }
    std::tm time = {};
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day + 1;
    time.tm_isdst = -1;
    std::mktime(&time);
    return std::make_tuple(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
}

void generateTestData() {
    std::ofstream outfile("RT_test_data.csv");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> year_dist(1, 9999);
    std::uniform_int_distribution<> month_dist(1, 12);
    std::uniform_int_distribution<> day_dist(1, 31);

    for (int i = 0; i < 100; ++i) {
        int year = year_dist(gen);
        int month = month_dist(gen);
        int day = day_dist(gen);
        auto [exp_year, exp_month, exp_day] = computeNextDate(year, month, day);
        outfile << year << "," << month << "," << day << "," 
                << exp_year << "," << exp_month << "," << exp_day << "\n";
    }
    outfile.close();
}

int main() {
    generateTestData();
    return 0;
}