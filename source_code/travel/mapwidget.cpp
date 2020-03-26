#include "mapwidget.h"

#include <QApplication>
#include <QStateMachine>
#include <QPushButton>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QState>
#include <QLabel>

//添加新的timer，使得绘图准确
mapwidget::mapwidget(QWidget *parent) :
    QWidget(parent),state(-1)
{
    this->setAutoFillBackground(true);

    qDebug()<<"come mapwidget";

    paintmstimer = new QTimer;
    paintmstimer->start(1000/60);
    QObject::connect(paintmstimer, SIGNAL(timeout()), this, SLOT(update()));
}

//绘图实践，绘制旅行过程
void mapwidget::paintEvent(QPaintEvent *)
{
    //设置一个画家 叫painter1
    QPainter painter1(this);

    //绘制地图map2
    QPixmap pix;
    pix.load(":/map2.png");
    pix = pix.scaled(pix.width()*0.55,pix.height()*0.55);
    painter1.drawPixmap(0,150,pix);
    QPainter painter(this);
    Widget *fatherPtr = (Widget *)parentWidget();
    if (fatherPtr->tra.currenttraveler != -1)
    {
        painter.drawPixmap((setPointPos()), setPointGraph());
    }
}

//根据当前状态、交通方式决定图标
QPixmap mapwidget::setPointGraph()
{
    QPixmap pointGraph;
    switch(state)
    {
    case -2://arrived destination
        pointGraph = QPixmap(":/vehicles/arrive.ico");
        break;
    case -1://pause waiting
        pointGraph = QPixmap(":/vehicles/pause.ico");
        break;
    case 0:
        pointGraph = QPixmap(":/vehicles/car.ico");
        break;
    case 1:
        pointGraph = QPixmap(":/vehicles/train.ico");
        break;
    case 2:
        pointGraph = QPixmap(":/vehicles/plane.ico");
        break;
    }

    return pointGraph;
}

//设置当前图标所处位置
QPointF mapwidget::setPointPos()
{
    Widget *fatherPtr = (Widget *)parentWidget();
    static QPointF pointPos;
//    std::vector<Attribute> path = fatherPtr->travelers[fatherPtr->currentTraveler].getPlan();
    QDateTime spenttime = QDateTime::currentDateTime();
    QDateTime starttime = fatherPtr->tra.starttime;
    QDateTime totaltime = fatherPtr->tra.totaltime;
    QString plan = fatherPtr->tra.plan;

    //将字符串Plan剪短为需要的串
    int sub = (int)getTimeDifference(starttime,spenttime);
    int sum = 0;
    for(int i = 0;;i++) {
        int timebetween2city = plan.section("-",1,1).toInt()+plan.section("-",3,3).toInt();
       if(timebetween2city * 10000 < sub && timebetween2city != 0)
       {
//           qDebug()<<plan.section("-",1,1).toInt()+plan.section("-",3,3).toInt();
           sum += plan.section("-",1,1).toInt()+plan.section("-",3,3).toInt();
           int num = 0;
           for(int j = 0;j < 4;j++)
               num += plan.section("-",j,j).length() + 1;
           plan = plan.mid(num);
           sub -= timebetween2city * 10000;
       }
       else {
           break;
       }
    }
    //已用时间不小于总时间，当前位置为目的地
    if(spenttime >= totaltime)
    {
            for(int j = 0;plan.section("-",1,1) != nullptr;j++)
            {
                int num = plan.section("-",0,0).length() + 1;
                plan = plan.mid(num);
            }
         pointPos = getCityCor(CityToNum(plan));
         state = -2;
    }
    else
        while(1)
        {
            QDateTime departuredatetime = starttime.addSecs(sum * 10 + plan.section("-",1,1).toInt()* 10);
            QDateTime cityarrivaltime = departuredatetime.addSecs(plan.section("-",3,3).toInt() * 10);
            QDateTime start2Begin = getSplitTime(starttime, departuredatetime);
            QDateTime start2End = getSplitTime(starttime, cityarrivaltime);
            //已用时间不超过一段路径发车时间，状态为等待
            if (getSplitTime(starttime,spenttime) <= start2Begin)
            {
                pointPos = getCityCor(CityToNum(plan.section("-",0,0)));
                state = -1;
                break;
            }
            //已用时间不超过一段路径的到站时间，状态为运动中
            else if (getSplitTime(starttime,spenttime) <= start2End)
            {
                pointPos = getCityCor(CityToNum(plan.section("-",0,0)));
                pointPos += getMoveDistance(starttime,spenttime, start2Begin, start2End, CityToNum(plan.section("-",0,0)), CityToNum(plan.section("-",4,4)));
                state = VehicleToNum(plan.section("-",2,2));
                if (spenttime == start2End)
                {
                    qDebug() << "Arriving at " << plan.section("-",4,4);
                }
                break;
            }
        }
    return pointPos;
}

//获得两时间点之间的时间差，判断当前所处的状态
QDateTime mapwidget::getSplitTime(QDateTime former, QDateTime later)
{
    int durationMsec = (later.time().msec() -  former.time().msec());
    int durationSec = (later.time().second() - former.time().second() - (int)((durationMsec >= 0)?0:1));
    int durationMin = (later.time().minute() - former.time().minute() - (int)((durationSec >= 0)?0:1));
    int durationHour = (later.time().hour() - former.time().hour() - (int)((durationMin >= 0)?0:1));
    int durationDay = (later.date().day() - former.date().day() - (int)((durationHour >= 0)?0:1) + former.date().daysInMonth())
            % former.date().daysInMonth();
    durationMsec = (durationMsec + 1000) % 1000;
    durationSec = (durationSec + 60) % 60;
    durationMin = (durationMin + 60) % 60;
    durationHour = (durationHour + 24) % 24;

    return QDateTime(QDate(1, 1, durationDay+1), QTime(durationHour, durationMin, durationSec, durationMsec));
}

//获得图形中各个城市的位置
QPointF mapwidget::getCityCor(int city)
{
    int x, y;
    switch (city)
    {
    case 0:
        x = 134-24;
        y = 311-24;
        break;
    case 1:
        x = 209 - 24;
        y = 373 - 24;
        break;
    case 2:
        x = 521 -24;
        y = 328 -24;
        break;
    case 3:
        x = 687 - 24;
        y = 285 - 24;
        break;
    case 4:
        x = 768 - 24;
        y = 261 - 24;
        break;
    case 5:
        x = 27 - 24;
        y = 471 - 24;
        break;
    case 6:
        x = 215 - 24;
        y = 453 - 24;
        break;
    case 7:
        x = 474 - 24;
        y = 418 - 24;
        break;
    case 8:
        x = 624 - 24;
        y = 415 - 24;
        break;
    case 9:
        x = 782 - 24;
        y = 370 - 24;
        break;
    case 10:
        x = 853 - 24;
        y = 321 - 24;
        break;
    case 11:
        x = 304 - 24;
        y = 625 - 24;
        break;
    case 12:
        x = 500 - 24;
        y = 595 - 24;
        break;
    case 13:
        x = 716 - 24;
        y = 587 - 24;
        break;
    case 14:
        x = 500 - 24;
        y = 661 - 24;
        break;
    }
    return QPointF(x, y);
}

//获得两个时间段的时间差，用于计算坐标增量
double mapwidget::getTimeDifference(QDateTime former, QDateTime later)
{
    int durationMsec = (later.time().msec() - former.time().msec());
    int durationSec = (later.time().second() - former.time().second() - (int)((durationMsec >= 0)?0:1));
    int durationMin = (later.time().minute() - former.time().minute() - (int)((durationSec >= 0)?0:1));
    int durationHour = (later.time().hour() - former.time().hour() - (int)((durationMin >= 0)?0:1));
    int durationDay = (later.date().day() - former.date().day() - (int)((durationHour >= 0)?0:1) + former.date().daysInMonth())
            % former.date().daysInMonth();
    durationMsec = (durationMsec + 1000) % 1000;
    durationSec = (durationSec + 60) % 60;
    durationMin = (durationMin + 60) % 60;
    durationHour = (durationHour + 24) % 24;

    return (double)(1000 * (durationDay * 86400 + durationHour * 3600 + durationMin * 60 + durationSec) +durationMsec);
}

//计算坐标增量
QPointF mapwidget::getMoveDistance(QDateTime starttime, QDateTime spentTime, QDateTime start2Begin, QDateTime start2End,
                                   int from, int to)
{
//    qDebug()<<start2Begin<<start2End<<spentTime;
    double increaseRatio = getTimeDifference(start2Begin, getSplitTime(starttime,spentTime))/getTimeDifference(start2Begin, start2End);
    double xIncrease = (getCityCor(to) - getCityCor(from)).x() * increaseRatio;
    double yIncrease = (getCityCor(to) - getCityCor(from)).y() * increaseRatio;

    return QPointF(xIncrease, yIncrease);
}
int mapwidget::CityToNum(QString city)
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

int mapwidget::VehicleToNum(QString vehicle)
{
    if(vehicle == "汽车")
        return 0;
    else if(vehicle == "火车")
        return 1;
    else {
        return 2;
    }
}
