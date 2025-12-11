#include "SpeechManager.h"
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>
#include <fstream>

//构造函数
SpeechManager::SpeechManager()
{
    this->initSpeech();

    this->m_Count = 0;  //之前写到initSpeech()里面了，导致每次比赛开始都清零

    this->loadRecord();
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
    //C++允许类的成员函数访问同一类任何对象的私有成员
    this->m_Round = 0;

    //清空容器
    this->m_vSpeaker.clear();
    this->m_vRound1Speaker.clear();
    this->m_vWinnerSpeaker.clear();
    this->m_mSpeaker.clear();
    this->m_mTotalRecord.clear();
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
    //轮数+1
    this->m_Round++;
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

    //临时容器存放小组成绩，每位选手的“平均分-编号”的键值对，注意是key值是平均分不是编号，方便降序排序筛选前三名；
    //注意定义时就要写排序方式 greater<double>
    multimap<double, int, greater<double>> mTemp; 

    cout << "------第 " << this->m_Round << " 轮的比赛开始------" << endl;
    cout << "正在进行激烈的比赛，结果马上出来！" << endl;
    system("pause");

    cout << "-----第 " << this->m_Round << " 轮的结果已产生-----" << endl;

    //对每个选手进行操作
    for (int i = 0; i < vTemp.size(); i++)
    {
        //1、打分
        deque<int> d; //存放每个选手的分数，每个评委打的分是 int，最后均分是 double
        //假设10个评委
        for (int j = 0; j < 10; j++)
        {
            int score = rand() % 16 + 80; //分数80~95之间
            d.push_back(score);
        }
        sort(d.begin(), d.end(), greater<int>()); //降序排列
        //去除最高分和最低分
        d.pop_back();
        d.pop_front();
        //计算均分
        double sum = accumulate(d.begin(), d.end(), 0.0); //需要包含numeric头文件
        double avg = sum / d.size();
        avg = round(avg * 100) / 100;  //保留2位小数
        //测试打印公示分数
        //cout << "编号为 " << vTemp[i] << " 的选手的得分为：" << avg << endl;
        

        //2、将均分存入multimap，和mScore数组中
        mTemp.insert({ avg,vTemp[i] });
        this->m_mSpeaker[vTemp[i]].setScore(this->m_Round, avg); //存入mScore数组，难想啊，正好有一个 map，存放了 编号-选手


        //3、晋级/出结果：比赛的共性——每组取前三
        //每6人为一组，进行判断
        if ((i + 1) % 6 == 0)  //注意是 i + 1，不是 i，从 0 开始计数
        {
            //sort(mTemp.begin(), mTemp.end(), greater<double>()); //根据分数降序排序multimap，错的，怎么能对multimap使用sort呢
            //第一轮
            if (this->m_Round == 1)
            {
                int rank = 1; //小组名次
                int groupNum = (i + 1) / 6; //第几组，可以直接计算出来
                cout << "第 " << groupNum << " 小组的晋级选手依次是：" << endl;

                //这里multimap的类型也要改，加上greater<double>
                //++++++mTemp.begin() 可以这么写吗，为了找到前三名?
                //不可以，map、set不可以这样连续给begin()多个++（写一个++可以），也不可以 + N；支持随机访问的容器可以v.begin()+3
                //现在把 rank 也放入，巧妙解决了只取 3 项的问题
                //注意 一个是 &&，一个是 ,  （若for循环有两个表达式，第二项（条件判断）里面用 && 或 ||，第一项和第三项用 ,）
                for (multimap<double, int, greater<double>>::iterator it = mTemp.begin(); it != mTemp.end() && rank <= 3; it++, rank++)
                {
                    cout << "第 " << rank << " 名选手：";
                    cout << "选手姓名：" << this->m_mSpeaker[it->second].getName() << " ";
                    cout << "选手编号：" << it->second << " ";
                    cout << "选手得分：" << it->first << endl;

                    //将结果存入对应容器中
                    this->m_vRound1Speaker.push_back(it->second);                    
                }
            }
            //第二轮
            else
            {
                cout << "最终获胜的选手依次是：" << endl;
                int rank = 1;
                for (multimap<double, int, greater<double>>::iterator it = mTemp.begin(); it != mTemp.end() && rank <= 3; it++, rank++)
                {
                    cout << "第 " << rank << " 名选手：";
                    cout << "选手姓名：" << this->m_mSpeaker[it->second].getName() << " ";
                    cout << "选手编号：" << it->second << " ";
                    cout << "选手得分：" << it->first << endl;

                    //将结果存入对应容器中
                    this->m_vWinnerSpeaker.push_back(it->second);                    
                }
            }
            //清空mTemp，否则第一轮第2组不是6个人比，是12个人比（mTemp存放的是临时6人小组的分数）
            mTemp.clear();
        }
    }
    //结尾
    if (this->m_Round == 1)
    {
        //衔接第二轮
        cout << "第一轮比赛已结束，让我们恭喜进入决赛的 6 位选手！" << endl;
        system("pause");
    }
    else
    {
        this->m_Count++; //场次+1（比赛完完整的一场）
        cout<< "-----第 " << this->m_Count << " 场比赛顺利结束-----" << endl;

        system("pause");
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

    //第二轮比赛
    //抽签
    this->SpeakerDraw();
    //比赛
    this->SpeechProcess();

    //保存到文件
    this->saveRecord();

    //重新初始化比赛数据
    this->initSpeech();

    //比赛结束
    cout << "第 " << this->m_Count << " 场比赛已顺利结束，感谢大家的参与，让我们下次比赛再会！" << endl;
    system("pause");
    system("cls");
}

//保存至文件
void SpeechManager::saveRecord()
{
    ofstream ofs("speech_competition_results.csv", ios::out | ios::app); //用追加的方式写.csv文件

    //保存前三名的数据，使用vWinnerSpeaker容器
    for (vector<int>::const_iterator it = this->m_vWinnerSpeaker.begin(); it != this->m_vWinnerSpeaker.end(); it++)
    {
        //逗号分隔，按分数降序写  编号,姓名,分数,  (分数后面也加上逗号，不然会有错，无法区分开前一个人的分数和后一个人的编号)
        ofs << *it << "," << this->m_mSpeaker[*it].getName() << "," << this->m_mSpeaker[*it].getScore(2) << ",";
    }
    //一场比赛写在一行里
    ofs << endl;

    ofs.close();
    cout << "文件记录保存完毕" << endl;

    this->fileIsEmpty = false; //更新文件不为空
}

//读取文件，获取往届记录
void SpeechManager::loadRecord()
{
    ifstream ifs;
    ifs.open("speech_competition_results.csv", ios::in);

    //判断文件是否为空 - 3 种情况
    //1 文件不存在
    if (!ifs.is_open())
    {
        //cout << "文件不存在" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }
    //2 文件存在但为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }

    //3 文件不为空
    ifs.putback(ch); //回退一个字符

    int tempRound = 0; //记录轮次

    vector<string> vTemp; //存放文件读取出的数据，放while外面，因为之后m_mTotalRecord还要用

    string data;
    while (getline(ifs, data)) //一行一行地读，每次处理一行（一场比赛）
    {
        //cout << data << endl;

        int start = 0; //开始操作的位置

        int tempIndex = 0; //逗号的索引位置（草。一开始初始化的值是-1，下面while循环的条件是tempIndex != -1，被拒在外面了，搞了半天都没while循环里进去）

        while (tempIndex != -1)
        {
            // find：从start位置开始查找逗号，未查到返回-1
            //注意！！！这里的tempIndex要写在里面，之前写在外面了，就是死循环！！！！！！！！
            //注意，又错了！写在这最后一次循环也不对，还是会多执行一次 ×  NO！NO！NO！NO！写在这里就是对的，最后一个字符串后面没有逗号！！！ ×  NO！NO！NO！NO！修改了一下，最后一个字符串后面也有逗号了
            tempIndex = data.find(",", start); 

            ////最后一次，此时在这个位置tempIndex = -1
            // 修改了，最后一个字符串后面也有逗号了，不需要这个了
            //if (tempIndex == -1)
            //{
            //    string tempString = data.substr(start);
            //    vTemp.push_back(tempString);

            //    break;
            //}

            string tempString = data.substr(start, tempIndex - start); //提取子串。tempIndex - start 一开始还写错了

            vTemp.push_back(tempString); //容器是一个一个字符串存的，编号、姓名、分数依次存在一起的 

            start = tempIndex + 1; //更新start位置

            //tempIndex = data.find(",", start);  写在这里不对
        }

        tempRound++;
        
        this->m_mTotalRecord.insert({ tempRound,vTemp });  //注意：这里tempRound是从1开始存的，不是0

        vTemp.clear(); //清空（每次就存这一行的数据，不累计存）
    }

    this->m_Count=this->m_mTotalRecord.size(); //更新已有场次数

    this->fileIsEmpty = false; //更新文件不为空

    ifs.close();
}

//显示所有比赛记录
void SpeechManager::showRecord()
{
    this->loadRecord(); //先加载文件，更新一下 m_mTotalRecord 容器

    // 文件的3种情况的提示

    if (this->fileIsEmpty)
    {       
        ifstream ifs;
        ifs.open("speech_competition_results.csv", ios::in);

        //文件不存在
        if (!ifs.is_open())
        {
            cout << "经查询，文件不存在。" << endl;
            ifs.close();
            system("pause");
            system("cls");
            return;
        }
        //文件存在但为空
        else
        {
            cout << "经查询，文件为空。" << endl;
            ifs.close();
            system("pause");
            system("cls");
            return;
        }
    }

    //文件存在且不为空
    cout << "经查询，已经进行了 " << this->m_Count << " 场比赛。" << endl;
    cout<<endl;

    string rankName[3] = { "冠军","亚军","季军" };

    for (int i = 0; i < this->m_mTotalRecord.size(); i++)  //总共的场次有两种表示方法都可以： m_Count  和  m_mTotalRecord.size()
    {
        cout << "第 " << i + 1 << " 届的结果如下：" << endl;
        /*cout << "冠军：" << " 编号：" << this->m_mTotalRecord[i][0] << " 姓名：" << this->m_mTotalRecord[i][1] << " 第二轮成绩：" << this->m_mTotalRecord[i][2] << endl;
        cout << "亚军：" << " 编号：" << this->m_mTotalRecord[i][3] << " 姓名：" << this->m_mTotalRecord[i][4] << " 第二轮成绩：" << this->m_mTotalRecord[i][5] << endl;
        cout << "季军：" << " 编号：" << this->m_mTotalRecord[i][6] << " 姓名：" << this->m_mTotalRecord[i][7] << " 第二轮成绩：" << this->m_mTotalRecord[i][8] << endl;*/

        for (int j = 0; j < 3; j++)
        {
            cout << rankName[j] << " | 编号：" << this->m_mTotalRecord[i + 1][j * 3] << " 姓名：" << this->m_mTotalRecord[i + 1][j * 3 + 1]
                 << " 第二轮成绩：" << this->m_mTotalRecord[i + 1][j * 3 + 2] << endl;
        }
    }

    system("pause");
    system("cls");
}

//清空比赛记录
void SpeechManager::clearRecord()
{
    int choice_clear;
    cout << "请输入您的选择，确认是否真的要清空文件。" << endl;
    cout << "1、确认清空；2、返回上一界面" << endl;
    cin >> choice_clear;
    
    if (choice_clear == 1)
    {
        ofstream ofs;
        ofs.open("speech_competition_results.csv", ios::trunc);
        ofs.close();
        cout << "文件已清空" << endl;

        //初始化所有的数据和容器
        this->initSpeech();

        //更新文件状态
        this->fileIsEmpty = true;
    }
   
    system("pause");
    system("cls");
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