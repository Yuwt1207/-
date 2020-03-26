#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>
#include "mypushbutton.h"
#include "ScheduleTree.h"

//显示时间头文件
#include<QLabel>
#include<QDateTime>
#include<QTimer>
#include <QMouseEvent>

#define SPEED 50
#define ico_width 48

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置widget标题
    this->setWindowTitle("模拟旅行查询系统");
    //设置window Icon
    this->setWindowIcon(QPixmap(":/query.jpg"));

    //widget窗口美化模块
    //设置widget窗口背景颜色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background,QColor(129,216,207));
    this->setPalette(palette);
    palette.setColor (QPalette::Foreground, QColor (0,0,0,255));
    this->setPalette (palette);

    //所有控件圆角化
//    setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    //按钮控件圆角化
//    ui->ChooseTraveler->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
//    ui->AddNewTraveller->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
//    ui->QueryRequest_btn->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");

    //初始化时不允许mapwidget重绘
    tra.currenttraveler = -1;

    //没有乘客时不允许点击查询按钮
    ui->QueryRequest_btn->setEnabled(false);

    //创建信号与槽的链接
    CreateConnect();

    //创建15个城市按钮
    CreateButton();

    //启动定时器，刷新时间
    StartTimer();
}
Widget::~Widget()
{
    delete ui;
}
//链接信号与槽
void Widget::CreateConnect()
{
    //实现点击添加新乘客按钮，下拉框内成员数加一
    connect(ui->AddNewTraveller,&QPushButton::clicked,ui->ChooseTraveler,[=](){
       num_traveler++;
       QString Filename=QString("%1乘客.txt").arg(num_traveler);
       QFile file( Filename );
       if(!file.open( QIODevice::WriteOnly |QIODevice::Text))
           qDebug()<<"can not open file!";
       file.close();
       QString str;
       str = tr("乘客%1").arg(num_traveler);

       if(now_traveler == 0)
           now_traveler = 1;

       //创建新对象traveler_demand
       traveler_demand = new TravelDemand;
       map.insert(num_traveler,traveler_demand);
       map[num_traveler]->isInitorNot = 0;
       createListenSignal();

       ui->ChooseTraveler->addItem(str);
       ui->QueryRequest_btn->setEnabled(true);
    });

    //点击下拉框内的其他旅客
    connect(ui->ChooseTraveler,static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),[=](){
//        qDebug()<<ui->ChooseTraveler->currentIndex();
        now_traveler = ui->ChooseTraveler->currentIndex()+1;
        paint();
    });

    //按钮 发起查询请求 弹出新窗口
    connect(ui->QueryRequest_btn,&QPushButton::clicked,[=](){
        map[now_traveler]->id=now_traveler;
//        killTimer(id1);                 //打开查询请求窗口时，关闭定时器
//        WhenKillTimer = QDateTime::currentDateTime();
//        map[now_traveler]->current_time = current_hour2;
        map[now_traveler]->show();        //弹出非模态子窗口
        map[now_traveler]->StrInTra = "";
    });
}
//封装城市按钮创建
void Widget::CreateButton()
{
    //以下为15个城市的按钮创建，实现在widget窗口中点击城市对应按钮可以查看当前城市去往其他城市的交通时刻表
    //共占代码量 16*15=240行
    //第一次代码量缩减//   时间：2019/4/11  工作记录：行间缩进 紧挨着放置代码  变更为10*14+14=154行

    //成都按钮创建
    MyPushButton *Chengdu = new MyPushButton(":/city/Chengdu.png");
    Chengdu->setParent(this); Chengdu->move(100,280);
    connect(Chengdu,&QPushButton::clicked,[=](){
        //点击按钮，实现弹起特效
        Chengdu->zoom1();   Chengdu->zoom2();
        //点击按钮，弹出该城市时刻表
        city_clicked = 0;       //0代表成都
        tree = new ScheduelTree;//创建出新的窗口，显示时刻表信息
        tree->FromA(city_clicked);//调用该函数将点击的城市city_clicked值赋给tree中的city，将Map1中的***head给tree中的quote，并在此设置窗口标题
        //************注意此处*************
        //如何传递一个指针数组的头指针？将widget中的tmp1赋给FromA，FromA中以schedule ***tmp接收，并令那个类中声明的schedule ***quote接收tmp，才可以使用
        tree->VehicalTime();    //调用该函数显示窗口中的各种信息（时刻表等）
        tree->show();           //显示该窗口（模态）
    });

    //重庆按钮创建
    MyPushButton *Chongqing = new MyPushButton(":/city/Chongqing.png");
    Chongqing->setParent(this); Chongqing->move(210,350);
    connect(Chongqing,&QPushButton::clicked,[=](){
        Chongqing->zoom1(); Chongqing->zoom2();
        city_clicked = 1;           //1代表重庆
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //武汉按钮创建
    MyPushButton *Wuhan = new MyPushButton(":/city/Wuhan.png");
    Wuhan->setParent(this); Wuhan->move(500,305);
    connect(Wuhan,&QPushButton::clicked,[=](){
        Wuhan->zoom1(); Wuhan->zoom2();
        city_clicked = 2;           //2代表武汉
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //合肥按钮创建
    MyPushButton *Hefei = new MyPushButton(":/city/Hefei.png");
    Hefei->setParent(this); Hefei->move(650,265);
    connect(Hefei,&QPushButton::clicked,[=](){
        Hefei->zoom1(); Hefei->zoom2();
        city_clicked = 3;           //3代表合肥
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //南京按钮创建
    MyPushButton *Nanjing = new MyPushButton(":/city/Nanjing.png");
    Nanjing->setParent(this); Nanjing->move(750,240);
    connect(Nanjing,&QPushButton::clicked,[=](){
        Nanjing->zoom1(); Nanjing->zoom2();
        city_clicked = 4;           //4代表南京
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //昆明按钮创建
    MyPushButton *Kunming = new MyPushButton(":/city/Kunming.png");
    Kunming->setParent(this); Kunming->move(10,430);
    connect(Kunming,&QPushButton::clicked,[=](){
        Kunming->zoom1(); Kunming->zoom2();
        city_clicked = 5;           //5代表昆明
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //贵阳按钮创建
    MyPushButton *Guiyang = new MyPushButton(":/city/Guiyang.png");
    Guiyang->setParent(this); Guiyang->move(195,465);
    connect(Guiyang,&QPushButton::clicked,[=](){
        Guiyang->zoom1(); Guiyang->zoom2();
        city_clicked = 6;           //6代表贵阳
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //长沙按钮创建
    MyPushButton *Changsha = new MyPushButton(":/city/Changsha.png");
    Changsha->setParent(this); Changsha->move(480,425);
    connect(Changsha,&QPushButton::clicked,[=](){
        Changsha->zoom1(); Changsha->zoom2();
        city_clicked = 7;           //7代表长沙
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //南昌按钮创建
    MyPushButton *Nanchang = new MyPushButton(":/city/Nanchang.png");
    Nanchang->setParent(this); Nanchang->move(585,390);
    connect(Nanchang,&QPushButton::clicked,[=](){
        Nanchang->zoom1(); Nanchang->zoom2();
        city_clicked = 8;           //8代表长沙
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //杭州按钮创建
    MyPushButton *Hangzhou = new MyPushButton(":/city/Hangzhou.png");
    Hangzhou->setParent(this); Hangzhou->move(785,375);
    connect(Hangzhou,&QPushButton::clicked,[=](){
        Hangzhou->zoom1(); Hangzhou->zoom2();
        city_clicked = 9;           //9代表杭州
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //上海按钮创建
    MyPushButton *Shanghai = new MyPushButton(":/city/Shanghai.png");
    Shanghai->setParent(this); Shanghai->move(855,320);
    connect(Shanghai,&QPushButton::clicked,[=](){
        Shanghai->zoom1(); Shanghai->zoom2();
        city_clicked = 10;           //10代表上海
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //南宁按钮创建
    MyPushButton *Nanning = new MyPushButton(":/city/Nanning.png");
    Nanning->setParent(this); Nanning->move(285,635);
    connect(Nanning,&QPushButton::clicked,[=](){
        Nanning->zoom1(); Nanning->zoom2();
        city_clicked = 11;           //11代表南宁
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //广州按钮创建
    MyPushButton *Guangzhou = new MyPushButton(":/city/Guangzhou.png");
    Guangzhou->setParent(this); Guangzhou->move(455,570);
    connect(Guangzhou,&QPushButton::clicked,[=](){
        Guangzhou->zoom1(); Guangzhou->zoom2();
        city_clicked = 12;           //12代表广州
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //福州按钮创建
    MyPushButton *Fuzhou = new MyPushButton(":/city/Fuzhou.png");
    Fuzhou->setParent(this); Fuzhou->move(725,580);
    connect(Fuzhou,&QPushButton::clicked,[=](){
        Fuzhou->zoom1();
        Fuzhou->zoom2();
        city_clicked = 13;           //13代表福州
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });

    //香港按钮创建
    MyPushButton *Hongkong = new MyPushButton(":/city/Hongkong.png");
    Hongkong->setParent(this); Hongkong->move(480,670);
    connect(Hongkong,&QPushButton::clicked,[=](){
        Hongkong->zoom1(); Hongkong->zoom2();
        city_clicked = 14;           //14代表香港
        tree = new ScheduelTree;
        tree->FromA(city_clicked); tree->VehicalTime(); tree->show();
    });
}
//更新widget上的时间
void Widget::StartTimer()
{
    timecount = 0;
    id1 = startTimer(1000);//单位：毫秒,更新当前的时间
    current_date_time =QDateTime::currentDateTime();
    date_hour =current_date_time.toString("yyyy.MM.dd hh");//后可继续添加  :mm:ss
    current_hour = date_hour.mid(11,2);
    current_hour2 = current_hour.toInt();
    current_y = date_hour.mid(0,4);
    current_m = date_hour.mid(5,2);
    current_d = date_hour.mid(8,2);
    ui->hour->setText(QString("时间: %1:00").arg(current_hour));
    ui->date->setText(QString("日期: %1/%2/%3").arg(current_y).arg(QString::number(current_m.toInt())).arg(current_d));
}
//定时刷新时间
void Widget::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == id1)
    {
        timecount ++;
        timecount = timecount % 10;
//        qDebug()<<"timecount = "<<timecount;
        if(timecount == 0)               //第一个计时器脉冲来临，进行下列操作
        {
            //获取带日期的时间，使用QDateTime类
            //显示时间
            static int hour = current_hour.toInt()+1;
            static int hour2 = hour;

            static int day = current_d.toInt();
            static int day2 = day;

            static int month = current_m.toInt();
            static int month2 = month;

            static int year = current_y.toInt();
            static int year2 = year;

            ui->hour->setText(QString("时间: %1:00").arg(QString::number(hour2)));
            current_hour2 = hour2;
            hour2 = updateHour(hour2);

            ui->date->setText(QString("日期: %1/%2/%3").arg(QString::number(year2)).arg(QString::number(month2)).arg(QString::number(day2)));
            day2 = updateDay(day2,month2,year);
            month2 = updateMonth(month2);
            year2 = updateYear(year2);
        }
    }
}
//更新小时
int Widget::updateHour(int num)
{
    if(num==23)//当系统时间为23点时，不能正常工作
    {
        num = 0;
        co = 1;
    }
    else
    {
        num++;
    }
    return num;
}
//更新天
int Widget::updateDay(int num,int m,int y)
{
    if(co == 1)
    {
        num++;
        co = 0;
        switch (m) {
            case 1:case 3:case 5:case 7:case 8:case 10:case 12:
                if(num==32)
                {
                    num=1;
                    co1=1;
                }
            break;
            case 2:
                if((y%4==0&&y%100!=0)||y%400==0)
                {
                    if(num==30)
                    {
                        num=1;
                        co1=1;
                    }
                }
                else{
                    if(num==29)
                    {
                        num=1;
                        co1=1;
                }
            break;
            case 4:case 6:case 9:case 11:
                if(num==31)
                {
                    num=1;
                    co1=1;
                }
            break;
                }
        }
    }
    return num;
}
//更新月
int Widget::updateMonth(int num)
{
    if(co1==1)
    {

        num++;
        co1=0;
        if(num==13)
        {
            co2 = 1;
            num=1;
        }
    }
    return num;
}
//更新年
int Widget::updateYear(int num)
{
    if(co2==1)
    {
        num++;
        co2=0;
    }
    return num;
}
//给每个旅客对象链接信号与槽
void Widget::createListenSignal()
{
    //监听TravelDemand中的输出信号
    connect(map[num_traveler],&TravelDemand::Output,[=](){
//        ui->textBrowser->setText(map[now_traveler]->output2);
        ui->textBrowser->clear();
        QVector<QString>::iterator iter;
        for(iter = map[now_traveler]->output3.begin();iter != map[now_traveler]->output3.end();iter++)
            ui->textBrowser->append(*iter);
    });
//    //监听TravelDemand中的打开定时器信号
//    connect(map[num_traveler],&TravelDemand::OpenTimer,[=](){
//       id1 = startTimer(1000);
//       WhenStartTimer = QDateTime::currentDateTime();
//       AddBegintime();
//    });
    //监听TravelDemand中的移动旅客信号
    connect(map[num_traveler],&TravelDemand::MoveTraveler,[=](){
        paint();
    });
    //监听TravelDemand中的输出字符串信号
    connect(map[num_traveler],&TravelDemand::OutputToWidget,[=](){
       StrFromTra = map[now_traveler]->StrInTra;
    });
    //监听TravDemand中获取当前时间信号
    connect(map[num_traveler],&TravelDemand::GetCTime,[=](){
       map[num_traveler]->current_time = current_hour2;
       qDebug()<<current_hour2;
    });
}
//为mapwidget提供当前旅行者的信息，以便画出其当前状态
void Widget::paint()
{
//    ui->textBrowser->setText(map[now_traveler]->output2);
    ui->textBrowser->clear();
    QVector<QString>::iterator iter;
    for(iter = map[now_traveler]->output3.begin();iter != map[now_traveler]->output3.end();iter++)
        ui->textBrowser->append(*iter);

    QDateTime starttime = map[now_traveler]->begintime;
//    QDateTime totaltime = map[now_traveler]->overtime;
    QDateTime totaltime;
    int total = 0;
    StrFromTra = map[now_traveler]->StrInTra;
    for(int i = 1;StrFromTra.section("-",i,i) != nullptr;i += 2)
    {
        total += StrFromTra.section("-",i,i).toInt();
    }
    qDebug()<<"total = "<<total;
    totaltime = starttime.addSecs(total * 10);
    QString plan = StrFromTra;
    int currenttraveler;
    if(map[now_traveler]->isInitorNot == 0)
        currenttraveler = -1;
    else {
        currenttraveler = 1;
    }
    tra = {starttime,totaltime,plan,currenttraveler};
}
void Widget::initTimeThread()
{
    //计时功能及所需的线程
    mstimer = new QTimer;
    mstimer->setInterval(1);

    timethread = new QThread();
    timethread->start();

    mstimer->moveToThread(timethread);
}
