#include "SpeechManager.h"

int main()
{
	//随机数
	srand((unsigned int)time(nullptr));

	//创建管理类对象
	SpeechManager sm;

	while (true)
	{
		//展示菜单
		sm.showMenu();

		int choice; //用户输入
		cout << "请输入你的选择：";
		cin >> choice;

		switch (choice)
		{
		case 1:  //1.开始演讲比赛
			sm.startSpeech();
			break;
		case 2:  //2.查看往届记录
			sm.showRecord();
			break;
		case 3:  //3.清空比赛记录
			sm.clearRecord();
			break;
		case 0:  //0.退出比赛程序
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
}