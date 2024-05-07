#pragma once
//通用的排序重载，防止其他文件重定义了
class Person;
bool Compare(const int& a, const int& b);

bool Compare(const Person& p1, const Person& p2);