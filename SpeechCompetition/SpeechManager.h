#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Speaker.h"
using namespace std;

//管理类
class SpeechManager
{
	//选手容器
	vector<int> m_vSpeaker; //初始12人数组
	vector<int> m_vRound1Speaker; //第一轮赛后6人晋级者
	vector<int> m_vWinnerSpeaker; //第二轮赛后3人获胜者
	map<int, Speaker> m_mSpeaker; //编号-选手 键值对

	//比赛情况
	int m_Round; //轮次
	int m_Count; //场次

	//文件读取相关
	bool fileIsEmpty; //文件是否为空，false不为空
	map<int, vector<string>> m_mTotalRecord; //存放所有比赛记录，  场次数 - vector 键值对

public:
	//构造函数
	SpeechManager();

	//展示菜单
	void showMenu();

	//开始比赛
	void startSpeech();

	//初始化比赛
	void initSpeech();

	//创建选手
	void createSpeaker();

	//抽签
	void SpeakerDraw();

	//正式比赛
	void SpeechProcess();

	//保存至文件
	void saveRecord();

	//读取文件，从文件中获取往届记录
	void loadRecord();

	//显示所有比赛记录
	void showRecord();

	//清空比赛记录
	void clearRecord();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();

	//测试函数
	//void test1();
};