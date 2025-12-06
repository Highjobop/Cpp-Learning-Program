#include "SpeechManager.h"
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>

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
    string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < 12; i++)
    {
        //选手姓名
        string nameTemp = "选手";
        nameTemp += nameSeed[i]; //名字格式：选手A
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
//void SpeechManager::test1()
//{
//    for (int i = 0; i < 12; i++)
//    {
//        cout << this->m_vSpeaker[i] << " ";   
//        cout << (this->m_mSpeaker.find(i + 10001))->second.getName() << " ";
//        cout << endl;
//    }
//}

//抽签
void SpeechManager::SpeakerDraw()
{
    this->m_Round++; //轮数+1
    //第一轮
    if (this->m_Round == 1)
    {
        random_shuffle(this->m_vSpeaker.begin(), this->m_vSpeaker.end()); //洗牌打乱
        cout << "开始进行第 " << this->m_Round << " 轮的抽签" << endl;
        cout << "-----------------------------" << endl;
        cout << "抽签结果如下：" << endl;
        cout << "第 1 小组的选手编号依次为：" << endl;
        for (int i = 0; i < 6; i++)
        {
            cout << this->m_vSpeaker[i] << " ";
        }
        cout << endl;
        cout << "第 2 小组的选手编号依次为：" << endl;
        for (int i = 6; i < 12; i++)
        {
            cout << this->m_vSpeaker[i] << " ";
        }
        cout << endl;
        system("pause");
    }
    //第二轮
    else
    {
        random_shuffle(this->m_vRound1Speaker.begin(), this->m_vRound1Speaker.end()); //洗牌打乱
        cout << "开始进行第 " << this->m_Round << " 轮的抽签" << endl;
        cout << "-----------------------------" << endl;
        cout << "抽签结果如下：" << endl;
        cout << "选手编号依次为：" << endl;
        for (int i = 0; i < 6; i++)
        {
            cout << this->m_vRound1Speaker[i] << " ";
        }
        cout << endl;       
        system("pause");
    }
}

//正式比赛
void SpeechManager::SpeechProcess()
{
    vector<int> vTemp; //比赛过程专用的临时容器
    if (this->m_Round == 1)
    {
        vTemp = this->m_vSpeaker;
    }
    else
    {
        vTemp = this->m_vRound1Speaker;
    }

    multimap<double, int, greater<double>> mTemp; //每位选手的“平均分-编号”的键值对，注意是key值是平均分不是编号，方便降序排序筛选前三名

    cout << "------第 " << this->m_Round << " 轮的比赛开始------" << endl;

    //对每个选手进行操作
    for (int i = 0; i < vTemp.size(); i++)
    {
        //1、打分
        deque<double> d; //存放每个选手的分数
        //假设10个评委
        for (int j = 0; j < 10; j++)
        {
            double score = rand() % 16 + 80; //分数80~95之间
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<double>()); //降序排列
        //去除最高分和最低分
        d.pop_back();
        d.pop_front();
        //计算均分
        double sum = accumulate(d.begin(), d.end(), 0); //需要包含numeric头文件
        double avg = sum / d.size();
        //测试打印公示分数
        //cout << "编号为 " << vTemp[i] << " 的选手的得分为：" << avg << endl;
        

        //2、将均分存入multimap，和mScore数组中
        mTemp.insert({ avg,vTemp[i] });
        this->m_mSpeaker[vTemp[i]].setScore(this->m_Round, avg); //存入mScore数组，难想啊


        //3、晋级：比赛的共性——每组取前三
        //每6人为一组，进行判断
        if (i % 6 == 0)
        {
            //sort(mTemp.begin(), mTemp.end(), greater<double>()); //根据分数降序排序multimap，错的，怎么能对multimap使用sort呢
            //第一轮
            if (this->m_Round == 1)
            {
                int groupNum = 1; //第几组
                int rank = 1; //小组名次
                cout << "第 " << groupNum << " 组的晋级选手依次是：" << endl;
                for (multimap<double, int, greater<double>()>::iterator it = mTemp.begin(); it != ++++++mTemp.begin(); it++) //这里multimap的类型也要改，加上排序方式
                {
                    cout << "第 " << rank << " 名选手：";
                    cout << "选手姓名：" << this->m_mSpeaker[it->second].getName() << " ";
                    cout << "选手编号：" << it->second << " ";
                    cout << "选手得分：" << it->first << endl;

                    groupNum++;
                    rank++;
                }
            }
            //第二轮
            else
            {
                cout << "最终获胜的选手依次是：" << endl;
                int rank = 1;
                for (multimap<double, int, greater<double>>::iterator it = mTemp.begin(); it != ++++++mTemp.begin(); it++) //这里multimap的类型也要改，加上排序方式
                {
                    cout << "第 " << rank << " 名选手：";
                    cout << "选手姓名：" << this->m_mSpeaker[it->second].getName() << " ";
                    cout << "选手编号：" << it->second << " ";
                    cout << "选手得分：" << it->first << endl;
                }
            }
        }
    }
}

//开始比赛
void SpeechManager::startSpeech()
{
    //准备
    this->initSpeech();
    this->createSpeaker();

    //第一轮比赛
    //抽签
    this->SpeakerDraw();
    //比赛
    this->SpeechProcess();

    //结果


    //第二轮比赛
    //抽签
    //this->SpeakerDraw();
    //比赛
    //this->SpeechProcess();

    //结果


    //分数


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