#pragma once
#include <iostream>
using namespace std;

class Speaker
{
	string m_Name; //姓名
	double m_Score[2]; //分数 最多两轮
public:
	//构造函数
	Speaker(string name);
	//析构函数
	~Speaker();
	//获取成员变量
	string getName();
	double getScore();
	//设置成员变量
	void setName(string name);
	void setScore(int round, double score);
};