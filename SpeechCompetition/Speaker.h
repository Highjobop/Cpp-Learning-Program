#pragma once
#include <iostream>
using namespace std;

class Speaker
{
	string m_Name; //姓名
	double m_Score[2]; //分数 最多两轮
	// double m_Score[2] = {0.0, 0.0};  类内初始化，C++11起支持
public:
	//构造函数
	Speaker();
	Speaker(string name);
	//析构函数
	~Speaker();
	//获取成员变量
	string getName();
	double getScore(int round);
	//设置成员变量
	void setName(string name);
	void setScore(int round, double score);
};