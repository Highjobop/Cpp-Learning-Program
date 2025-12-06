#include "Speaker.h"

//构造函数
Speaker::Speaker(string name)
{
	this->m_Name = "";
	//数组不需要传参啊，直接元素=0就行了
	//this->m_Score[] = { 0.0,0.0 }; 这种初始化列表的形式这里不可以用。但是还是要注意数组要 []，且 double 类型的 0 也要写成 0.0
	this->m_Score[0] = 0;
	this->m_Score[1] = 0;
}

//析构函数
Speaker::~Speaker()
{

}

//获取成员变量
string Speaker::getName()
{
	return this->m_Name;
}
double Speaker::getScore()
{
	return this->m_Score[0];
}

//设置姓名
void Speaker::setName(string name)
{
	this->m_Name = name;
}

//设置分数 赋值
void Speaker::setScore(int round,double score)
{
	this->m_Score[round - 1] = score;
}