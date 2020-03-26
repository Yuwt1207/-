#include "myschedule.h"
//#include "log.h"
#include <QDebug>

#define CityNum 15

std::multimap<int, Attribute> MySchedule::database;

MySchedule::MySchedule()
{
    for(int i = 0;i < CityNum;i++)
    {
        database.erase(i);
    }

    QFile file(":/test.txt");
    if(!file.open(QIODevice::ReadOnly))//只读方式打开文件，打开失败时输出失败
    {
        qDebug() << "Can't open the file";
        return;
    }
    QTextStream in(&file);
    QString from, to, number, begin, end, cost, vechile; //分别为出发地、目的地、班次、开始时间、结束时间、费用、交通方式

    //将时刻表信息读入database数据结构
    while(!in.atEnd())
    {
        in >> from >> to >> number >> begin >> end >> cost >> vechile >> endl;//读取一组时刻信息
        if(from != "")                                                        //from没有读到信息时不进入分支
        {
//            qDebug() << from << to << number << begin;
            Attribute line(CityToNum(from), CityToNum(to), number, begin,     //声明对象line将一组信息保存到其中
                           end, cost.toInt(), vechile.toInt());
            database.insert(std::make_pair(CityToNum(from), line));           //insert函数为database插入pair数据，由于键值与元素是多对多对应关系，
        }                                                                     //multimap称为多重映照容器，后期学习vector、list容器，相比map容器multimap
    }                                                                         //允许键值重复插入元素，后期学习multimap的元素搜索
    store_in_schedule();
}
MySchedule::~MySchedule()
{
}

//根据字符串转换为相应的序号
int MySchedule::CityToNum(QString city)
{
    int num = -1;

    if(city == "成都")
        num = 0;
    else if(city == "重庆")
        num = 1;
    else if(city == "武汉")
        num = 2;
    else if(city == "合肥")
        num = 3;
    else if(city == "南京")
        num = 4;
    else if(city == "昆明")
        num = 5;
    else if(city == "贵阳")
        num = 6;
    else if(city == "长沙")
        num = 7;
    else if(city == "南昌")
        num = 8;
    else if(city == "杭州")
        num = 9;
    else if(city == "上海")
        num = 10;
    else if(city == "南宁")
        num = 11;
    else if(city == "广州")
        num = 12;
    else if(city == "福州")
        num = 13;
    else if(city == "香港")
        num = 14;

    return num;
}

void MySchedule::store_in_schedule()
{
    head = new schedule**[CityNum];
    for(int i=0;i<CityNum;i++)
    {
        head[i] = new schedule*[CityNum];
    }

    for(int i=0;i<CityNum;i++)
    {
        for(int j=0;j<CityNum;j++)
        {
            head[i][j]=nullptr;
        }
    }

    for(int i=0;i<CityNum;i++)
    {
        typedef std::multimap<int, Attribute>::size_type sz_type;
        sz_type entries = MySchedule::database.count(i);
        std::multimap<int, Attribute>::iterator iter = MySchedule::database.find(i);
        for(sz_type j=0;j<entries;j++,iter++)
        {
            head[i][iter->second.to] = new schedule[6];
            for(int k = 0;k < 6;k++)
            {
                head[i][iter->second.to][k].vihecle = 0;
            }
        }
    }

    for(int i=0;i<CityNum;i++)
    {
        typedef std::multimap<int, Attribute>::size_type sz_type;
        sz_type entries = MySchedule::database.count(i);
        std::multimap<int, Attribute>::iterator iter = MySchedule::database.find(i);
        for(int j=0;j<CityNum;j++)
        {
            if(head[i][j]!=nullptr)
            {
                sz_type num = 0;
                int k = 0;
                for(;num < entries;num++,iter++)
                {
                    if(iter->second.to == j)
                    {
                        head[i][j][k].trainnum = iter->second.num;
                        head[i][j][k].starttime = iter->second.begin.toInt();
                        head[i][j][k].endtime = iter->second.end.toInt();
                        head[i][j][k].cost = iter->second.cost;
                        head[i][j][k].vihecle = iter->second.vehicle;
                        k++;
                    }
                }
                k = 0;
            }
            iter = MySchedule::database.find(i);
        }
    }
}
