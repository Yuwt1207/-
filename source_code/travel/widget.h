#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStatusBar>
#include "TravelDemand.h"
#include "ScheduleTree.h"
#include "mapwidget.h"

#include <QDateTime>
#include <QMap>

struct travelers{
    QDateTime starttime;
    QDateTime totaltime;
    QString plan;
    int currenttraveler;
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    int num_traveler = 0;           //当前用户数量（旅行者的数量）
    TravelDemand *traveler_demand;  //旅客对象
    ScheduelTree *tree;             //新建城市时刻表窗口对象

    int city_clicked;               //用户点击的城市

    //与mapwidget交互的接口
    QMap<int,TravelDemand*> map;    //存放各个旅行者的容器
    int now_traveler = 0;
    travelers tra;
    void paint();

private:
    Ui::Widget *ui;

    void CreateConnect();
    void CreateButton();
    void StartTimer();
    void initTimeThread();
    void createListenSignal();

    QString StrFromTra;

    //实现时间更新
    int timecount;
    void timerEvent(QTimerEvent *e); //定时器事件,刷新时间
    int updateHour(int num);//更新小时
    int updateDay(int num,int m,int y);//更新天
    int updateMonth(int num);//更新月
    int updateYear(int num);//更新年
    int co;//小时进位标志
    int co1;//天进位标志
    int co2;//月进位标志
    int id1;//定时器1的Id
    int id2;//定时器2的Id
    int id3;//定时器3的Id
    QDateTime current_date_time;
    QString date_hour;
    QString current_hour;
    int current_hour2;              //获取当前的小时
    QString current_y;
    QString current_m;
    QString current_d;

    //参与时间进程的变量
    QTimer *mstimer;
    QThread *timethread;
};

#endif // WIDGET_H
