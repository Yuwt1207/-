#include "ScheduleTree.h"
#include "ui_schedueltree.h"
#include "widget.h"
#include <QStringList>
#include <QDebug>

#include <QBitmap>
#include <QPainter>

ScheduelTree::ScheduelTree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduelTree)
{
    ui->setupUi(this);

    //设置窗口固定大小
    this->setFixedSize(500,400);

    //设置应用图片
    this->setWindowIcon(QPixmap(":/clock.jpg"));

    //由于需求窗口名称带参数，而构造函数在声明对象时即调用，无法获得父窗口传来的参数
    //因此改该窗口名称放在FromA中实现
}

ScheduelTree::~ScheduelTree()
{
    delete ui;
}
void ScheduelTree::FromA(int num)
{
    city = num;
    //详见widget.cpp构造函数创建封装的按钮时调用该函数的注释


    //cityA等中存放城市名称
    QString cityA;  cityA = "成都";
    QString cityB;  cityB = "重庆";
    QString cityC;  cityC = "武汉";
    QString cityD;  cityD = "合肥";
    QString cityE;  cityE = "南京";
    QString cityF;  cityF = "昆明";
    QString cityG;  cityG = "贵阳";
    QString cityH;  cityH = "长沙";
    QString cityI;  cityI = "南昌";
    QString cityJ;  cityJ = "杭州";
    QString cityK;  cityK = "上海";
    QString cityL;  cityL = "南宁";
    QString cityM;  cityM = "广州";
    QString cityN;  cityN = "福州";
    QString cityP;  cityP = "香港";

    int num_city = 15;

    //动态申请一维数组，存放Qstring城市
    QString *name;
    name = new QString[num_city];

    name[0] = cityA;
    name[1] = cityB;
    name[2] = cityC;
    name[3] = cityD;
    name[4] = cityE;
    name[5] = cityF;
    name[6] = cityG;
    name[7] = cityH;
    name[8] = cityI;
    name[9] = cityJ;
    name[10] = cityK;
    name[11] = cityL;
    name[12] = cityM;
    name[13] = cityN;
    name[14] = cityP;

    //实现Qstring拼接
    QString title = QString("%1时刻表").arg(name[city]);

    //设置窗口标题
    this->setWindowTitle(title);
}

//类似上面的test函数 写一个真正的显示时刻表树的函数
void ScheduelTree::VehicalTime(void)
{
    int num_city=15;

    //设置treeWidget标题
    ui->treeWidget->setFixedSize(500,400);
    ui->treeWidget->setHeaderLabels(QStringList()<<"交通工具"<<"车次"<<"出站/到站时刻"<<"票价");

    typedef std::multimap<int, Attribute>::size_type sz_type;
    sz_type entries = MySchedule::database.count(city);

    std::multimap<int, Attribute>::iterator iter = MySchedule::database.find(city);

    for(int i=0;i<num_city;i++)
    {
        for(sz_type j=0;j!=entries;j++,iter++)
        {
            //进入函数打印城市city和城市i之间的时刻信息，传入参数i即可
            if(iter->second.to == i)
            {
                print(i);
                break;
            }
        }
        iter = MySchedule::database.find(city);
    }
}
void ScheduelTree::print(int c)
{
    QString vehical1;   vehical1 = "汽车";
    QString vehical2;   vehical2 = "火车";
    QString vehical3;   vehical3 = "飞机";

    QString cityA;  cityA = "成都";
    QString cityB;  cityB = "重庆"; QString cityC;  cityC = "武汉";
    QString cityD;  cityD = "合肥"; QString cityE;  cityE = "南京";
    QString cityF;  cityF = "昆明"; QString cityG;  cityG = "贵阳";
    QString cityH;  cityH = "长沙"; QString cityI;  cityI = "南昌";
    QString cityJ;  cityJ = "杭州"; QString cityK;  cityK = "上海";
    QString cityL;  cityL = "南宁"; QString cityM;  cityM = "广州";
    QString cityN;  cityN = "福州"; QString cityP;  cityP = "香港";

//    int max_vehical = 6;
    int num_city = 15;
    int num_vehicle = 3;

    QString *name;
    name = new QString[num_city];
    QString *mold;
    mold = new QString[num_vehicle];

    mold[0] = vehical1;
    mold[1] = vehical2;
    mold[2] = vehical3;

    name[0] = cityA;
    name[1] = cityB; name[2] = cityC;
    name[3] = cityD;name[4] = cityE;
    name[5] = cityF; name[6] = cityG;
    name[7] = cityH; name[8] = cityI;
    name[9] = cityJ;name[10] = cityK;
    name[11] = cityL; name[12] = cityM;
    name[13] = cityN; name[14] = cityP;
    //同FromA函数

    typedef std::multimap<int, Attribute>::size_type sz_type;
    sz_type entries = MySchedule::database.count(city);

    std::multimap<int, Attribute>::iterator iter = MySchedule::database.find(city);

    //将信息打印在treewidget上分为以下几步：
    //1、设置treewidget标题 在外层函数中实现 ：ui->treeWidget->setHeaderLabels(QStringList()<<"交通工具"<<"出站/到站时刻"<<"票价");
    //2、声明QTreeWidgetItem类型的对象并为其赋Qstring类型值，表示城市
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<name[c]);
    //3、将该item放在表中，如下
    ui->treeWidget->addTopLevelItem(item);
    //4、在该item下添加几行信息，实现于下面的for循环中，用QstringList实现，注意当**<<**<<**的长度多于标题长度，只按标题的数量对应显示前几个
    for(sz_type j=0;j!=entries;j++,iter++)
    {
        if(iter->second.to == c)
        {
            QStringList info;
            QString ti = tr("%1:00~%2:00").arg(iter->second.begin).arg(iter->second.end);
            //注意该行，强制转换实现Qstring拼接
            info<<mold[iter->second.vehicle-1]<<iter->second.num<<ti<<QString::number(iter->second.cost);
            //5、声明QTreeWidgetItem类型，将Qstringlist放入其中
            QTreeWidgetItem *l = new QTreeWidgetItem(info);
            //6、将l放入item中
            item->addChild(l);
        }
    }
}
