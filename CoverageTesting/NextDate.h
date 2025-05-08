/*
 * @Author: Kyouko
 * @Date: 2025-05-08 10:05:31
 * @LastEditTime: 2025-05-08 10:05:36
 * @Description: 请输入文件描述
 * @FilePath: /Code/CoverageTesting/NextDate.h
 */
#ifndef NEXTDATE_H
#define NEXTDATE_H

bool LeapYear(int year);
bool ValidDate(int year, int month, int day);
void NextDate(int &year, int &month, int &day);

#endif