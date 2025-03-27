/*
 * @Author: Kyouko
 * @Date: 2025-03-27 08:28:11
 * @LastEditTime: 2025-03-28 01:09:20
 * @Description: 生成100条随机测试用例，保存到RT_test_data.csv，每行格式为year,month,day,exp_year,exp_month,exp_day。预期结果使用标准库计算。
 * @FilePath: /Code/Input-domain-testing/Task4-1.cpp
 */
#include <fstream>
#include <random>
#include <ctime>
#include <tuple>
#include <utility>
#include "Task1.cpp"    // 使用LeapYear() 和ValidDate()

/**
 * @description: 计算下一天的日期，作为预期结果。使用std::tm结构体，
 * @return {std::tuple<int, int, int>} 返回tuple打包调整后的年月日。若日期不合法，返回原日期。
 */
std::tuple<int, int, int> computeNextDate(int year, int month, int day) {
    if (!ValidDate(year, month, day)) {
        return std::make_tuple(year, month, day);
    }
    std::tm time = {};
    time.tm_year = year - 1900;
    time.tm_mon = month - 1;
    time.tm_mday = day + 1;
    time.tm_isdst = -1;     // 系统自动判断夏令时
    std::mktime(&time);     // 规范化时间结构体，自动处理日期溢出
    return std::make_tuple(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);     // 注意还原偏移量
}

/**
 * @description: 生成测试数据
 */
void generateTestData() {
    std::ofstream outfile("RT_test_data.csv");
    std::random_device rd;      // 随机种子生成
    std::mt19937 gen(rd());     // 看到别人说可以生成高质量伪随机数
    std::uniform_int_distribution<> year_dist(1, 9999);
    std::uniform_int_distribution<> month_dist(1, 12);
    std::uniform_int_distribution<> day_dist(1, 31);

    for (int i = 0; i < 100; ++i) {
        int year = year_dist(gen);
        int month = month_dist(gen);
        int day = day_dist(gen);
        auto [exp_year, exp_month, exp_day] = computeNextDate(year, month, day);
        outfile << year << "," << month << "," << day << "," 
                << exp_year << "," << exp_month << "," << exp_day << "\n";      // 将预期和预期结果写入文件，每个字段之间使用逗号分隔。
    }
    outfile.close();
}

int main() {
    generateTestData();
    return 0;
}