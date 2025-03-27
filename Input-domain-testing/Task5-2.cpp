/*
 * @Author: Kyouko
 * @Date: 2025-03-27 09:06:11
 * @LastEditTime: 2025-03-28 01:18:53
 * @Description: 将Task5-1.txt转换为CT_test_data.txt，映射Leap为2020、NonLeap为2021，并计算预期结果。
 * @FilePath: /Code/Input-domain-testing/Task5-2.cpp
 */
#include <fstream>
#include <sstream>
#include <vector>

bool LeapYear(int year);
bool ValidDate(int year, int month, int day);
extern std::tuple<int, int, int> computeNextDate(int year, int month, int day);

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::ifstream infile("Task5-1.txt");
    std::ofstream outfile("CT_test_data.txt");
    std::string line;
    std::getline(infile, line); // 跳过表头
    while (std::getline(infile, line)) {
        auto fields = split(line, '\t');
        std::string year_str = fields[0];
        int month = std::stoi(fields[1]);
        int day = std::stoi(fields[2]);
        int year = (year_str == "Leap") ? 2020 : 2021;
        auto [exp_year, exp_month, exp_day] = computeNextDate(year, month, day);
        outfile << year << "," << month << "," << day << "," 
                << exp_year << "," << exp_month << "," << exp_day << "\n";
    }
    infile.close();
    outfile.close();
    return 0;
}