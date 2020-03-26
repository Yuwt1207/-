#ifndef TRAVELDEMAND_H
#define TRAVELDEMAND_H

#include <QDialog>
#include <QString>
#include "myschedule.h"

const int city_num=15;
const int road_size=45;
namespace Ui {
class TravelDemand;
}

class TravelDemand : public QDialog
{
    Q_OBJECT

public:
    explicit TravelDemand(QWidget *parent = nullptr);
    ~TravelDemand();

    QString StrInTra;

    int *pass;//pass中存放途径城市的信号 1为途径 0为不途径

    //从ui文件直接获取的参数，作为与算法兼容的接口，/滑稽
    int id;             //暂时不知道有啥卵用
    int current_time;   //从widget获得的当前的时间
    int depart;         //出发地代号
    int dest;           //目的地代号
    int num_pass;       //途径地数量
    int Strategy;       //采用的策略
    int max_hours;      //若采用策略三，规定的最长时间

    //存储时刻表对象
    MySchedule *sche;

    schedule ***head;//

    void pass_place_init();//建立途径地函数 存储途径地至数组pass中（int类型）
    void get_travel_info();//从鼠标获得上述信息

    QString output;
    QString output2;
    QVector<QString> output3;

    //切换旅客时对显示旅客位置有帮助的信息
    int isInitorNot = 0;
    QDateTime begintime;
//    QDateTime overtime;

signals:
    void Output();          //输出信号
    void MoveTraveler();    //
    void OutputToWidget();  //字符串输出信号
//    void OpenTimer();       //打开计时器信号
    void GetCTime();  //

private:
    Ui::TravelDemand *ui;

    void CreateConnect();

    QString NumToCity(int city);
    QString NumToVehical(int vehical);
    QString NumToStrategy(int Strategy);

    void resetsch(schedule ***sch);

    void get_advice();  //调用各算法，获得旅客最佳策略的函数
    int startcity;
    int endcity;
    int max_hour;
    int strategy;
    int passcity[city_num];
    int passcity_num;
    int road[road_size];
    int mintime[city_num];//存startcity到各个city最少时间或是限时钱最少的路径
    int mincost[city_num];//存startcity到各个city最少钱
    int CityToNum(QString);
    void dijcost(schedule ***sch);
    void dijtime(schedule ***sch,int nowtime);
    void findway(schedule ***sch);
    void copy(TravelDemand *another){
        startcity=another->startcity;
        endcity=another->endcity;
        strategy=another->strategy;
        passcity_num=another->passcity_num;
        for(int i=0;i<city_num;i++)
        {
            passcity[i]=another->passcity[i];
            road[i]=another->road[i];
            mintime[i]=another->mintime[i];
            mincost[i]=another->mincost[i];
        }
    }
    void DFS(schedule ***sch,int nowcity,int endcost[city_num],bool iscityvisit[city_num],int path[city_num],int endtime[city_num],int DFScount);
    void outputway(schedule ***sch);

    void closeEvent(QCloseEvent *event);
};

#endif // TRAVELDEMAND_H
