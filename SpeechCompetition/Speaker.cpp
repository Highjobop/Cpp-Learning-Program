#include "Speaker.h"

//构造函数
Speaker::Speaker() //默认构造都初始化为默认值，最好不要为空
{
	this->m_Name = "";
	this->m_Score[0] = 0;
	this->m_Score[1] = 0;
}
Speaker::Speaker(string name)
{
	this->m_Name = name;

	// 数组不需要传参啊，直接元素=0就行了
	// 这种初始化列表的形式这里不可以用，因为C风格数组在初始化之后，不能直接用 ={...} 语法进行整体赋值，
	// 例如，double arr4[2];  arr4 = { 0, 0 };   这种不行，只能 double arr4[2] = { 0, 0 };
	// 想要这种初始化列表的方式赋值，只能在类内初始化的时候赋值
	// 且 double 类型的 0 最好写成 0.0
	// this->m_Score[] = { 0.0,0.0 };  典型错误
	this->m_Score[0] = 0.0;
	this->m_Score[1] = 0.0;
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
double Speaker::getScore(int round)
{
	return this->m_Score[round - 1];
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