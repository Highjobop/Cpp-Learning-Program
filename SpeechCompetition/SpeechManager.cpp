#include "SpeechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
    this->initSpeech();
}

//展示菜单
void SpeechManager::showMenu()
{
    cout << "********************************************" << endl;
    cout << "*************  欢迎参加演讲比赛 ************" << endl;
    cout << "*************  1.开始演讲比赛  *************" << endl;
    cout << "*************  2.查看往届记录  *************" << endl;
    cout << "*************  3.清空比赛记录  *************" << endl;
    cout << "*************  0.退出比赛程序  *************" << endl;
    cout << "********************************************" << endl;
    cout << endl;
}

//初始化比赛数据
void SpeechManager::initSpeech()
{
    this->m_Round = 0; //C++允许类的成员函数访问同一类任何对象的私有成员
    //清空容器
    this->m_vSpeaker.clear();
    this->m_vRound1Speaker.clear();
    this->m_vWinnerSpeaker.clear();
    this->m_mSpeaker.clear();
}

//创建选手
void SpeechManager::createSpeaker()
{
    //选手姓名赋值
    string nameTemp = "选手";
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < 12; i++)
    {
        //选手姓名
        nameTemp += nameSeed[i];
        Speaker sTemp(nameTemp);

        //选手分数，初始化
        sTemp.setScore(1, 0);
        sTemp.setScore(2, 0);
        
        //选手编号，插入到12人vector容器
        int idTemp = 10001 + i;
        this->m_vSpeaker.push_back(idTemp);

        //插入到map
        this->m_mSpeaker.insert(pair<int,Speaker> (idTemp, sTemp));
    }
}

//测试1
void SpeechManager::test1()
{
    for (int i = 0; i < 12; i++)
    {
        cout << this->m_vSpeaker[i] << " ";       
        cout << this->m_mSpeaker[i + 10001].getName() << " ";
        cout << endl;
    }
}

//退出系统
void SpeechManager::exitSystem()
{
    cout << "欢迎下次再来" << endl;
    system("pause");
    exit(0);
}

//析构函数
SpeechManager::~SpeechManager()
{

}