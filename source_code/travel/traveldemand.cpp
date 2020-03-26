#include "TravelDemand.h"
#include "ui_TravelDemand.h"
#include "myschedule.h"
#include<windows.h>
#include <QDebug>
#include <QButtonGroup>
#include <QDateEdit>
#include<QFile>
#include<QTextStream>
#define num_city 15
#define road_size 45

TravelDemand::TravelDemand(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TravelDemand)
{
    ui->setupUi(this);

    //设置窗口标题
    this->setWindowTitle("查询窗口");
    //设置窗口Icon
    this->setWindowIcon(QPixmap(":/clock2.jpg"));
    //设置widget窗口背景颜色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(palette);

    sche = new MySchedule;

    pass=new int[num_city];
    //初始化途经城市信息 函数调用
    for(int i=0;i<num_city;i++)
    {
        pass[i]=0;
    }
    pass_place_init();

    //默认选中策略1
    ui->strategy1->setChecked(true);
    ui->strategy3_hour->setEnabled(false);
    ui->strategy3_day->setEnabled(false);

    ui->strategy3_hour->setMaximum(23);

    CreateConnect();
}

TravelDemand::~TravelDemand()
{
    delete ui;
}
void TravelDemand::CreateConnect()
{
    ui->pass_A->setEnabled(false);
    ui->btn_travel_ok->setEnabled(false);
    //只有选中策略三时，截止时间才能编辑
    connect(ui->strategy3,&QRadioButton::clicked,[=](){
       ui->strategy3_hour->setEnabled(true);
       ui->strategy3_day->setEnabled(true);
    });
    connect(ui->strategy1,&QRadioButton::clicked,[=](){
       ui->strategy3_hour->setEnabled(false);
       ui->strategy3_day->setEnabled(false);
    });
    connect(ui->strategy2,&QRadioButton::clicked,[=](){
       ui->strategy3_hour->setEnabled(false);
       ui->strategy3_day->setEnabled(false);
    });

    connect(ui->btn_travel_ok,&QPushButton::clicked,this,[=](){
        emit this->GetCTime();
        qDebug()<<"2";
        //得到旅客设置的信息，出发地、目的地、时间和策略选择等
        get_travel_info();
        //获得旅行建议输出
        get_advice();
//        emit this->OpenTimer();
        emit this->MoveTraveler();
        this->close();
    });

    //取消按钮关闭窗口
    connect(ui->btn_travel_quit,&QPushButton::clicked,this,[=](){
       this->close();
//       emit this->OpenTimer();
    });

    connect(ui->departure,static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),[=](){
            ui->pass_A->setEnabled((CityToNum(ui->departure->currentText())^0)*(CityToNum(ui->destination->currentText())^0));
            ui->pass_B->setEnabled((CityToNum(ui->departure->currentText())^1)*(CityToNum(ui->destination->currentText())^1));
            ui->pass_C->setEnabled((CityToNum(ui->departure->currentText())^2)*(CityToNum(ui->destination->currentText())^2));
            ui->pass_D->setEnabled((CityToNum(ui->departure->currentText())^3)*(CityToNum(ui->destination->currentText())^3));
            ui->pass_E->setEnabled((CityToNum(ui->departure->currentText())^4)*(CityToNum(ui->destination->currentText())^4));
            ui->pass_F->setEnabled((CityToNum(ui->departure->currentText())^5)*(CityToNum(ui->destination->currentText())^5));
            ui->pass_G->setEnabled((CityToNum(ui->departure->currentText())^6)*(CityToNum(ui->destination->currentText())^6));
            ui->pass_H->setEnabled((CityToNum(ui->departure->currentText())^7)*(CityToNum(ui->destination->currentText())^7));
            ui->pass_I->setEnabled((CityToNum(ui->departure->currentText())^8)*(CityToNum(ui->destination->currentText())^8));
            ui->pass_J->setEnabled((CityToNum(ui->departure->currentText())^9)*(CityToNum(ui->destination->currentText())^9));
            ui->pass_K->setEnabled((CityToNum(ui->departure->currentText())^10)*(CityToNum(ui->destination->currentText())^10));
            ui->pass_L->setEnabled((CityToNum(ui->departure->currentText())^11)*(CityToNum(ui->destination->currentText())^11));
            ui->pass_M->setEnabled((CityToNum(ui->departure->currentText())^12)*(CityToNum(ui->destination->currentText())^12));
            ui->pass_N->setEnabled((CityToNum(ui->departure->currentText())^13)*(CityToNum(ui->destination->currentText())^13));
            ui->pass_P->setEnabled((CityToNum(ui->departure->currentText())^14)*(CityToNum(ui->destination->currentText())^14));
            ui->btn_travel_ok->setEnabled(!(ui->departure->currentIndex()==ui->destination->currentIndex()));
        });

    connect(ui->destination,static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),[=](){
        ui->pass_A->setEnabled((CityToNum(ui->departure->currentText())^0)*(CityToNum(ui->destination->currentText())^0));
        ui->pass_B->setEnabled((CityToNum(ui->departure->currentText())^1)*(CityToNum(ui->destination->currentText())^1));
        ui->pass_C->setEnabled((CityToNum(ui->departure->currentText())^2)*(CityToNum(ui->destination->currentText())^2));
        ui->pass_D->setEnabled((CityToNum(ui->departure->currentText())^3)*(CityToNum(ui->destination->currentText())^3));
        ui->pass_E->setEnabled((CityToNum(ui->departure->currentText())^4)*(CityToNum(ui->destination->currentText())^4));
        ui->pass_F->setEnabled((CityToNum(ui->departure->currentText())^5)*(CityToNum(ui->destination->currentText())^5));
        ui->pass_G->setEnabled((CityToNum(ui->departure->currentText())^6)*(CityToNum(ui->destination->currentText())^6));
        ui->pass_H->setEnabled((CityToNum(ui->departure->currentText())^7)*(CityToNum(ui->destination->currentText())^7));
        ui->pass_I->setEnabled((CityToNum(ui->departure->currentText())^8)*(CityToNum(ui->destination->currentText())^8));
        ui->pass_J->setEnabled((CityToNum(ui->departure->currentText())^9)*(CityToNum(ui->destination->currentText())^9));
        ui->pass_K->setEnabled((CityToNum(ui->departure->currentText())^10)*(CityToNum(ui->destination->currentText())^10));
        ui->pass_L->setEnabled((CityToNum(ui->departure->currentText())^11)*(CityToNum(ui->destination->currentText())^11));
        ui->pass_M->setEnabled((CityToNum(ui->departure->currentText())^12)*(CityToNum(ui->destination->currentText())^12));
        ui->pass_N->setEnabled((CityToNum(ui->departure->currentText())^13)*(CityToNum(ui->destination->currentText())^13));
        ui->pass_P->setEnabled((CityToNum(ui->departure->currentText())^14)*(CityToNum(ui->destination->currentText())^14));
        ui->btn_travel_ok->setEnabled(!(ui->departure->currentIndex()==ui->destination->currentIndex()));
    });

    //出发地等于目的地，确定按钮无法点击

}

void TravelDemand::closeEvent(QCloseEvent *event)
{
    ui->pass_A->setCheckState(Qt::Unchecked);
    ui->pass_B->setCheckState(Qt::Unchecked);
    ui->pass_C->setCheckState(Qt::Unchecked);
    ui->pass_D->setCheckState(Qt::Unchecked);
    ui->pass_E->setCheckState(Qt::Unchecked);
    ui->pass_F->setCheckState(Qt::Unchecked);
    ui->pass_G->setCheckState(Qt::Unchecked);
    ui->pass_H->setCheckState(Qt::Unchecked);
    ui->pass_I->setCheckState(Qt::Unchecked);
    ui->pass_J->setCheckState(Qt::Unchecked);
    ui->pass_K->setCheckState(Qt::Unchecked);
    ui->pass_L->setCheckState(Qt::Unchecked);
    ui->pass_M->setCheckState(Qt::Unchecked);
    ui->pass_N->setCheckState(Qt::Unchecked);
    ui->pass_P->setCheckState(Qt::Unchecked);

    //默认选中策略1
    ui->strategy1->setChecked(true);
    ui->strategy3_hour->setEnabled(false);
    ui->strategy3_day->setEnabled(false);

    ui->strategy3_hour->setValue(0);
    ui->strategy3_day->setValue(0);
}

//获得旅行者选定的项目，出发地、目的地、时间和策略等
void TravelDemand::get_travel_info()
{
    isInitorNot = 1;
    //获得出发地
    QString departure=ui->departure->currentText();
    depart = CityToNum(departure);

    //获得目的地
    QString destination=ui->destination->currentText();
    dest = CityToNum(destination);

    //获得选择的旅行策略
    QButtonGroup groupBox;
    groupBox.addButton(ui->strategy1,1);
    groupBox.addButton(ui->strategy2,2);
    groupBox.addButton(ui->strategy3,3);
    Strategy = groupBox.checkedId();

    //获得选择策略三时设置的最长时间
    max_hours = ui->strategy3_hour->value()+ui->strategy3_day->value()*24;

    QString str;
    for(int i = 0;i < num_city;i++)
    {
        str += QString::number( pass[i] );
        str += " ";
    }
}
//初始化pass数组 其中存放15个城市是否被选中途径的信息
void TravelDemand::pass_place_init()
{
    //捕捉勾选途径某城市的信号
    //过于丑陋 亟待简化
    connect(ui->pass_A,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[0]=1;}else if(state==0)pass[0]=0;});
    connect(ui->pass_B,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[1]=1;}else if(state==0)pass[1]=0;});
    connect(ui->pass_C,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[2]=1;}else if(state==0)pass[2]=0;});
    connect(ui->pass_D,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[3]=1;}else if(state==0)pass[3]=0;});
    connect(ui->pass_E,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[4]=1;}else if(state==0)pass[4]=0;});
    connect(ui->pass_F,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[5]=1;}else if(state==0)pass[5]=0;});
    connect(ui->pass_G,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[6]=1;}else if(state==0)pass[6]=0;});
    connect(ui->pass_H,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[7]=1;}else if(state==0)pass[7]=0;});
    connect(ui->pass_I,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[8]=1;}else if(state==0)pass[8]=0;});
    connect(ui->pass_J,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[9]=1;}else if(state==0)pass[9]=0;});
    connect(ui->pass_K,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[10]=1;}else if(state==0)pass[10]=0;});
    connect(ui->pass_L,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[11]=1;}else if(state==0)pass[11]=0;});
    connect(ui->pass_M,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[12]=1;}else if(state==0)pass[12]=0;});
    connect(ui->pass_N,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[13]=1;}else if(state==0)pass[13]=0;});
    connect(ui->pass_P,&QCheckBox::stateChanged,[=](int state){if(state==2){pass[14]=1;}else if(state==0)pass[14]=0;});
}
//输出旅行者的旅行建议
void TravelDemand::get_advice()
{
    startcity = depart;
    endcity = dest;
    strategy = Strategy-1;
//    passcity_num = num_pass;
    for(int i=0;i < num_city;i++)
    {
        passcity[i]=-1;
        mintime[i]=-1;
        mincost[i]=-1;
    }
    for(int i=0;i<road_size;i++)
    {
        road[i]=-1;
    }
    max_hour=max_hours + current_time;
    passcity_num = 0;
    for(int i=0;i<city_num;i++)
    {
        if(pass[i]==1)
        {
            passcity[passcity_num]=i;
            passcity_num++;
        }
    }

    for(int i=0;i<city_num;i++)
    {
        qDebug()<<pass[i];
    }

    for(int i=0;i<city_num;i++)
        pass[i] = 0;
    QString str ="";
    for(int i=0;i<city_num;i++)
    {
        str += QString::number(passcity[i]);
        str += " ";
    }
//    qDebug()<<str;

    head = sche->head;

//    for(int i = 0;output[i] != nullptr;i++)
//        output3.remove(i);
    output3.clear();

    findway(head);
    outputway(head);

    begintime = QDateTime::currentDateTime();
//    int total = 0;
//    for(int i = 1;StrInTra.section("-",i,i) != nullptr;i += 2)
//    {
//        total += StrInTra.section("-",i,i).toInt();
//    }
//    overtime = begintime.addSecs(total * 10);


    emit this->OutputToWidget();
    emit Output();
}
void TravelDemand::dijcost(schedule ***sch)
{
    const int max=200000;
    bool isfindbestway[city_num]={0};
    for(int i=0;i<city_num;i++)
    {
        mincost[i]=max;
    }

    int path[city_num];

    int cost[city_num][city_num];
    for(int i=0;i<city_num;i++)
    {
        for(int j=0;j<city_num;j++)
        {
            cost[i][j]=max;
        }
    }

//	for(int i=0;i<city_num;i++)
//	{
//		for(int j=0;j<city_num;j++)
//		{
//			qDebug()<<cost[i][j]<<" ";
//		}
//		qDebug()<<endl;
//	}
//
    for(int i=0;i<city_num;i++)
    {
        for(int j=0;j<city_num;j++)
        {
            if(sch[i][j]!=nullptr)
            {
                for(int k=0;k<6;k++)
                {
                    if(sch[i][j][k].vihecle!=0)
                    {
                        if(sch[i][j][k].cost<cost[i][j])
                        {
                            cost[i][j]=sch[i][j][k].cost;
                        }
                    }
                }
            }
        }
    }


    for(int i=0;i<city_num;i++)
    {
        mincost[i]=cost[startcity][i];
        if(mincost[i]<max)
        {
            path[i]=startcity;
        }
        else
        {
            path[i]=-1;
        }
    }
    isfindbestway[startcity]=true;
    mincost[startcity]=0;
//	for(int i=0;i<city_num;i++)
//	{
//		qDebug()<<mincost[i]<<" ";
//	}
//	qDebug()<<endl;


    for(int i=1;i<city_num;i++)
    {
        int min=max;
        int v;
        for(int j=0;j<city_num;j++)
        {
            if(!isfindbestway[j]&&mincost[j]<min)
            {
                v=j;
                min=mincost[j];
            }
        }
        isfindbestway[v]=true;
        for(int j=0;j<city_num;j++)
        {
            if(!isfindbestway[j]&&(mincost[v]+cost[v][j]<mincost[j]))
            {
                mincost[j]=mincost[v]+cost[v][j];
                path[j]=v;
            }
        }
    }
//		for(int i=0;i<city_num;i++)
//	{
//		qDebug()<<mincost[i]<<" ";
//	}
//	qDebug()<<endl;

//	for(int i=0;i<city_num;i++)
//	{
//		qDebug()<<path[i]<<" ";
//	}
    //复原路线
    int i=endcity;
    int j=city_num-1;
    int r[city_num];
    while(1)
    {
        if(i==startcity)
        {
            r[j]=i;
            break;
        }
        r[j]=i;
        j--;
        i=path[i];
    }
    i=0;
    for(;j<city_num;j++)
    {
        road[i]=r[j];
        i++;
    }
}
void TravelDemand::dijtime(schedule ***sch,int nowtime)
{
    const int max=200000;
    bool isfindbestway[city_num]={0};
    for(int i=0;i<city_num;i++)
    {
        mintime[i]=max;
    }
    int path[city_num];
    for(int i=0;i<city_num;i++)//初始化
    {
        if(sch[startcity][i]!=nullptr)
        {
            for(int j=0;j<6;j++)
            {
                if(sch[startcity][i][j].vihecle!=0)
                {
                    while(sch[startcity][i][j].starttime<nowtime)
                    {
                        sch[startcity][i][j].starttime+=24;
                        sch[startcity][i][j].endtime+=24;
                    }
                    if(sch[startcity][i][j].endtime<mintime[i])
                    {
                        mintime[i]=sch[startcity][i][j].endtime;
                    }
                    path[i]=startcity;
                }
            }
        }
        else
        {
            path[i]=-1;
        }
    }
//    for(int i=0;i<city_num;i++)
//    {
//        qDebug()<<mintime[i]<<" ";
//    }
//    qDebug()<<endl;
//初始化没问题
    isfindbestway[startcity]=true;
    mintime[startcity]=nowtime;
    /*初始化结束，开始循环，每次求startcity到i的最短路径*/
    for(int i=1;i<city_num;i++)
    {
        int v;
        int min=max;
        for(int j=0;j<city_num;j++)
        {
            if(!isfindbestway[j]&&mintime[j]<min)
            {
                v=j;
                min=mintime[j];
            }
        }
        isfindbestway[v]=true;
//		qDebug()<<min<<" "<<v<<endl;
        for(int j=0;j<city_num;j++)
        {
            if(!isfindbestway[j])
            {
                if(sch[v][j]!=nullptr)
                {
                    for(int k=0;k<6;k++)
                    {

                        if(sch[v][j][k].vihecle==0)
                        {
                            break;
                        }

                            while(sch[v][j][k].starttime<mintime[v])
                            {
                                sch[v][j][k].starttime+=24;
                                sch[v][j][k].endtime+=24;
                            }
                            if(sch[v][j][k].endtime<mintime[j])
                            {
                                mintime[j]=sch[v][j][k].endtime;
                                path[j]=v;
                            }

                    }
                }
            }
        }
    }
//	for(int i=0;i<city_num;i++)
//	{
//		qDebug()<<mintime[i]<<" ";
//	}
//	qDebug()<<endl;
//	for(int i=0;i<city_num;i++)
//	{
//		qDebug()<<path[i]<<" ";
//	}
//	qDebug()<<endl;
    //复原路线
    int i=endcity;
    int j=city_num-1;
    int r[city_num];
    while(1)
    {
        if(i==startcity)
        {
            r[j]=i;
            break;
        }
        r[j]=i;
        j--;
        i=path[i];
    }
    i=0;
    for(j;j<city_num;j++)
    {
        road[i]=r[j];
        i++;
    }
//	qDebug()<<"D"<<endl;
//	for(int i=0;i<city_num;i++)
//	{
//		qDebug()<<mintime[i]<<" ";
//	}
//	qDebug()<<endl;

}
void TravelDemand::DFS(schedule ***sch,int nowcity,int endcost[city_num],bool iscityvisit[city_num],int path[city_num],int endtime[city_num],int DFScount)
{

    if(endtime[DFScount]>max_hour)
    {
        return ;
    }
    int roadlen=0;
    while(road[roadlen+1]!=-1)
    {
        roadlen++;
    }
    if(nowcity==endcity)
    {
        bool isallpassed=true;
        for(int i=0;i<this->passcity_num;i++)
        {
            if(iscityvisit[this->passcity[i]]==false)
            {
                isallpassed=false;
                break;
            }
        }

        if(isallpassed&&(mincost[roadlen]>endcost[DFScount]||roadlen==0))
        {

            for(int i=0;i<city_num;i++)
            {
                if(i<=DFScount)
                {
                    mincost[i]=endcost[i];
                    mintime[i]=endtime[i];
                    this->road[i]=path[i];
                }
                else
                {
                    mincost[i]=0;
                    mintime[i]=0;
                    this->road[i]=-1;
                }
            }
        }

            //比较是否为目前最优，若最优则更新
        return;
    }

    if(endcost[DFScount]>mincost[roadlen]&&roadlen!=0)//剪枝，如果到现在这条路费用比最优的高且时间也更多则直接弃用
    {
        return;
    }
    DFScount++;
//	qDebug()<<nowcity<<" ";
//	system("pause");
//	for(int i=0;i<DFScount;i++)
//	{
//		qDebug()<<endcost[i]<<" ";
//	}
//	qDebug()<<endl;
    for(int i=0;i<city_num;i++)
    {
        if(sch[nowcity][i]!=nullptr&&iscityvisit[i]==false)
        {
            iscityvisit[i]=true;
            path[DFScount]=i;
            for(int j=0;j<6;j++)
            {
                if(sch[nowcity][i][j].vihecle==0)
                {
                    break;
                }
                endcost[DFScount]=endcost[DFScount-1]+sch[nowcity][i][j].cost;
//				qDebug()<<endcost[DFScount]<<" ";

                endtime[DFScount]=sch[nowcity][i][j].endtime;
                if(sch[nowcity][i][j].starttime<endtime[DFScount-1])
                {
                    endtime[DFScount]+=24*(((endtime[DFScount-1]-sch[nowcity][i][j].starttime)/24)+1);
                }

                DFS(sch,i,endcost,iscityvisit,path,endtime,DFScount);
//				DFScount--;
            }
            endcost[DFScount]=0;
            endtime[DFScount]=0;
            path[DFScount]=-1;
            iscityvisit[i]=false;
        }
    }
}
void TravelDemand::findway(schedule ***sch)
{
    if(this->strategy==0)//最少钱
    {
        int closestcity;
        if(passcity_num==0)
        {

            this->dijcost(sch);
        }
        else
        {

            const int max=200000;
            TravelDemand another;
            another.copy(this);
            bool ispasscityvisit[city_num]={0};
            int visit_num=0;
            while(1)
            {
                if(visit_num==this->passcity_num+1)
                {
                    another.dijcost(sch);
                    int i=0;
                    int j=0;
                    while(another.road[i+1]!=-1)
                    {
                        if(this->road[j]!=-1)
                        {
                            j++;
                            continue;
                        }
                        else
                        {
                            this->road[j]=another.road[i];
                            i++;
                            j++;
                        }
                    }
                    this->road[j]=this->endcity;
                    break;
                }

                another.dijcost(sch);
                int min=max;

                for(int i=0;i<another.passcity_num;i++)
                {
                    if(ispasscityvisit[another.passcity[i]]==true)
                    {
                        continue;
                    }
                    if(another.mincost[another.passcity[i]]<min)
                    {
                        closestcity=another.passcity[i];
                        min=another.mincost[another.passcity[i]];
                    }
                }
                ispasscityvisit[closestcity]=true;
                visit_num++;
                another.endcity=closestcity;
                for(int i=0;i<road_size;i++)
                {
                    another.road[i]=-1;
                }
                another.dijcost(sch);
                int i=0;
                int j=0;

//				for(int i=0;i<city_num;i++)
//				{
//					qDebug()<<this->road[i]<<" ";
//				}
//				system("pause");
                while(another.road[i+1]!=-1)
                {
                    if(this->road[j]!=-1)
                    {
                        j++;
                        continue;
                    }
                    else
                    {
                        this->road[j]=another.road[i];
                        i++;
                        j++;
                    }

                }
//				for(int i=0;i<city_num;i++)
//				{
//					qDebug()<<this->road[i]<<" ";
//				}
//				system("pause");
                another.startcity=another.endcity;
                another.endcity=this->endcity;
            }
        }
    }
    else if(strategy==1)//时间最短
    {
        int nowtime=current_time;
//        qDebug()<<"nowtime = "<<nowtime;
        if(passcity_num==0)
        {
            this->dijtime(sch,nowtime);
        }
        else
        {
            int closestcity;
            const int max=200000;
            TravelDemand another;
            another.copy(this);
            bool ispasscityvisit[city_num]={0};
            int visit_num=0;
            while(1)
            {
                if(visit_num==this->passcity_num+1)
                {
                    another.dijtime(sch,nowtime);
                    int i=0;
                    int j=0;
                    while(another.road[i+1]!=-1)
                    {
                        if(this->road[j]!=-1)
                        {
                            j++;
                            continue;
                        }
                        else
                        {
                            this->road[j]=another.road[i];
                            i++;
                            j++;
                        }
                    }
                    this->road[j]=this->endcity;
                    break;
                }

                another.dijtime(sch,nowtime);
                int min=max;

                for(int i=0;i<another.passcity_num;i++)
                {
                    if(ispasscityvisit[another.passcity[i]]==true)
                    {
                        continue;
                    }
                    if(another.mintime[another.passcity[i]]<min)
                    {
                        closestcity=another.passcity[i];
                        min=another.mintime[another.passcity[i]];
                    }
                }
                ispasscityvisit[closestcity]=true;
                visit_num++;
                another.endcity=closestcity;
                for(int i=0;i<city_num;i++)
                {
                    another.road[i]=-1;
                }
                another.dijtime(sch,nowtime);
                int i=0;
                int j=0;

//				for(int i=0;i<city_num;i++)
//				{
//					qDebug()<<this->road[i]<<" ";
//				}
//				system("pause");
                while(another.road[i+1]!=-1)
                {
                    if(this->road[j]!=-1)
                    {
                        j++;
                        continue;
                    }
                    else
                    {
                        this->road[j]=another.road[i];
                        i++;
                        j++;
                    }

                }
//				for(int i=0;i<city_num;i++)
//				{
//					qDebug()<<this->road[i]<<" ";
//				}
//				system("pause");
                another.startcity=another.endcity;
                another.endcity=this->endcity;
        }
    }
    }
    else if(this->strategy==2)//限定时间花钱最少
    {
        int endcost[city_num],endtime[city_num],path[city_num];
        bool iscityvisit[city_num];
        for(int i=0;i<city_num;i++)
        {
            endcost[i]=0;
            endtime[i]=0;
            path[i]=-1;
            iscityvisit[i]=false;
        }
        int DFScount=0;
        endtime[0]=current_time;//现在的时间
        DFS(sch,startcity,endcost,iscityvisit,path,endtime,DFScount);
        if(road[1]>=0&&road[1]<=14)
        {
            road[0]=startcity;
            int roadlen=0;
            while(road[roadlen]!=-1)
            {
                roadlen++;
            }

            qDebug()<<endl;
            for(int i=0;i<roadlen;i++)
            {
                qDebug()<<mintime[i]<<" ";
            }
            qDebug()<<endl;
        }
        else
        {
            qDebug()<<"no way!"<<endl;
        }

    }
    resetsch(sch);
}
void TravelDemand::outputway(schedule ***sch)
{
    QString Filename=QString("%1乘客.txt").arg(this->id);
    QFile file( Filename );
    if(!file.open( QIODevice::Append |QIODevice::Text))
        qDebug()<<"can not open file!";
    QTextStream in(&file);


    QString str="";
    for(int i=0;i<passcity_num;i++)
    {
        str+=NumToCity(passcity[i]);
        str+=" ";
    }
    str+="使用策略:";
    str+=NumToStrategy(strategy);
    output=QString("%1:00 乘客%2从%3去往%4,途径城市：%5").arg(current_time).arg(id).arg(NumToCity(this->depart)).arg(NumToCity(this->dest)).arg(str);
    output3.append(output);
//    emit Output();
    in<<QString("%1:00 乘客%2从%3去往%4,途径城市：%5").arg(current_time).arg(id).arg(NumToCity(this->depart)).arg(NumToCity(this->dest)).arg(str);

//    qDebug()<<id<<endl;
    if(this->strategy==0)
    {
        int totaltime;
        int totalcost = 0;

        int roadlen=0;
        while(road[roadlen]!=-1)
        {
            roadlen++;
        }
        int nowtime=current_time;
        for(int i=0;i<roadlen-1;i++)
        {
            int k=0;
            for(int j=0;sch[road[i]][road[i+1]][j].vihecle!=0;j++)
            {
                if(sch[road[i]][road[i+1]][j].cost<sch[road[i]][road[i+1]][k].cost)
                {
                    k=j;
                }
            }
            while(sch[road[i]][road[i+1]][k].starttime<nowtime)
            {
                sch[road[i]][road[i+1]][k].starttime+=24;
                sch[road[i]][road[i+1]][k].endtime+=24;
            }
            totalcost += sch[road[i]][road[i+1]][k].cost;
            in<<QString("%1--%2-->%3，第%4天%5：00出发，第%6天%7：00到达，车次：%8，费用：%9元")
                .arg(NumToCity(road[i])).arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle)).arg(NumToCity(road[i+1])).arg(sch[road[i]][road[i+1]][k].starttime/24+1)
                .arg(sch[road[i]][road[i+1]][k].starttime-(sch[road[i]][road[i+1]][k].starttime/24)*24).arg(sch[road[i]][road[i+1]][k].endtime/24+1)
                .arg(sch[road[i]][road[i+1]][k].endtime-(sch[road[i]][road[i+1]][k].endtime/24)*24)
                .arg(sch[road[i]][road[i+1]][k].trainnum).arg(sch[road[i]][road[i+1]][k].cost)<<endl;
            output = QString("%1--%2-->%3，第%4天%5：00出发，第%6天%7：00到达，车次：%8，费用：%9元")
                    .arg(NumToCity(road[i])).arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle)).arg(NumToCity(road[i+1])).arg(sch[road[i]][road[i+1]][k].starttime/24+1)
                    .arg(sch[road[i]][road[i+1]][k].starttime-(sch[road[i]][road[i+1]][k].starttime/24)*24).arg(sch[road[i]][road[i+1]][k].endtime/24+1)
                    .arg(sch[road[i]][road[i+1]][k].endtime-(sch[road[i]][road[i+1]][k].endtime/24)*24)
                    .arg(sch[road[i]][road[i+1]][k].trainnum).arg(sch[road[i]][road[i+1]][k].cost);
            output3.append(output);
            if(i == 0)
            {
                StrInTra += QString("%1-%2-%3-%4-%5")
                        .arg(NumToCity(road[i]))
                        .arg(sch[road[i]][road[i+1]][k].starttime - current_time)
                        .arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle))
                        .arg(sch[road[i]][road[i+1]][k].endtime - sch[road[i]][road[i+1]][k].starttime)
                        .arg(NumToCity(road[i+1]));
            }
            else {
                StrInTra += QString("-%1-%2-%3-%4")
                        .arg(sch[road[i]][road[i+1]][k].starttime - nowtime)
                        .arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle))
                        .arg(sch[road[i]][road[i+1]][k].endtime - sch[road[i]][road[i+1]][k].starttime)
                        .arg(NumToCity(road[i+1]));
            }
//            qDebug()<<StrInTra;
//            emit Output();
            nowtime=sch[road[i]][road[i+1]][k].endtime;
            totaltime = nowtime - current_time;
        }
        output = QString("total cost %1 totaltime %2").arg(totalcost).arg(totaltime);
        output3.append(output);
        in<<QString("total cost %1 totaltime %2").arg(totalcost).arg(totaltime);
//        emit Output();
    }
    else if(this->strategy==1)
    {
        int totaltime;
        int totalcost = 0;

        int roadlen=0;
        while(road[roadlen]!=-1)
        {
            roadlen++;
        }
        int nowtime=current_time;
        for(int i=0;i<roadlen-1;i++)
        {
            int k=0;
            for(int j=0;sch[road[i]][road[i+1]][j].vihecle!=0;j++)
            {
                while(sch[road[i]][road[i+1]][j].starttime<nowtime)
                {
                    sch[road[i]][road[i+1]][j].starttime+=24;
                    sch[road[i]][road[i+1]][j].endtime+=24;
                }
                if(sch[road[i]][road[i+1]][j].endtime<sch[road[i]][road[i+1]][k].endtime)
                {
                    k=j;
                }
            }
            totalcost += sch[road[i]][road[i+1]][k].cost;
            in<<QString("%1--%2-->%3，第%4天%5：00出发，第%6天%7：00到达，车次：%8，费用：%9元")
                .arg(NumToCity(road[i])).arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle)).arg(NumToCity(road[i+1])).arg(sch[road[i]][road[i+1]][k].starttime/24+1)
                .arg(sch[road[i]][road[i+1]][k].starttime-(sch[road[i]][road[i+1]][k].starttime/24)*24).arg(sch[road[i]][road[i+1]][k].endtime/24+1)
                .arg(sch[road[i]][road[i+1]][k].endtime-(sch[road[i]][road[i+1]][k].endtime/24)*24)
                .arg(sch[road[i]][road[i+1]][k].trainnum).arg(sch[road[i]][road[i+1]][k].cost)<<endl;
            output = QString("%1--%2-->%3，第%4天%5：00出发，第%6天%7：00到达，车次：%8，费用：%9元")
                    .arg(NumToCity(road[i])).arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle)).arg(NumToCity(road[i+1])).arg(sch[road[i]][road[i+1]][k].starttime/24+1)
                    .arg(sch[road[i]][road[i+1]][k].starttime-(sch[road[i]][road[i+1]][k].starttime/24)*24).arg(sch[road[i]][road[i+1]][k].endtime/24+1)
                    .arg(sch[road[i]][road[i+1]][k].endtime-(sch[road[i]][road[i+1]][k].endtime/24)*24)
                    .arg(sch[road[i]][road[i+1]][k].trainnum).arg(sch[road[i]][road[i+1]][k].cost);
            output3.append(output);
            if(i == 0)
            {
                StrInTra += QString("%1-%2-%3-%4-%5")
                        .arg(NumToCity(road[i]))
                        .arg(sch[road[i]][road[i+1]][k].starttime - current_time)
                        .arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle))
                        .arg(sch[road[i]][road[i+1]][k].endtime - sch[road[i]][road[i+1]][k].starttime)
                        .arg(NumToCity(road[i+1]));
            }
            else {
                StrInTra += QString("-%1-%2-%3-%4")
                        .arg(sch[road[i]][road[i+1]][k].starttime - nowtime)
                        .arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle))
                        .arg(sch[road[i]][road[i+1]][k].endtime - sch[road[i]][road[i+1]][k].starttime)
                        .arg(NumToCity(road[i+1]));
            }
            qDebug()<<StrInTra;
            nowtime=sch[road[i]][road[i+1]][k].endtime;
//            emit Output();
            totaltime = nowtime - current_time;
        }
        output = QString("total cost %1 totaltime %2").arg(totalcost).arg(totaltime);
        output3.append(output);
        in<<QString("total cost %1 totaltime %2").arg(totalcost).arg(totaltime)<<endl;
//        emit Output();
    }
    else if(this->strategy==2)
    {
        int totaltime;
        int totalcost = 0;

        int roadlen=0;
        while(road[roadlen]!=-1)
        {
            roadlen++;
        }
        if(road[1] >= 0 && road[1] <= 14)
        {
            int nowtime=current_time;
            for(int i=0;i<roadlen-1;i++)
            {
                int k=0;
                for(int j=0;sch[road[i]][road[i+1]][j].vihecle!=0;j++)
                {
                    while(sch[road[i]][road[i+1]][j].starttime<nowtime)
                    {
                        sch[road[i]][road[i+1]][j].starttime+=24;
                        sch[road[i]][road[i+1]][j].endtime+=24;
                    }
                    if(sch[road[i]][road[i+1]][j].endtime==this->mintime[i+1])
                    {
                        k=j;
                    }
                }
                totalcost += sch[road[i]][road[i+1]][k].cost;
                in<<QString("%1--%2-->%3，第%4天%5：00出发，第%6天%7：00到达，车次：%8，费用：%9元")
                    .arg(NumToCity(road[i])).arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle)).arg(NumToCity(road[i+1])).arg(sch[road[i]][road[i+1]][k].starttime/24+1)
                    .arg(sch[road[i]][road[i+1]][k].starttime-(sch[road[i]][road[i+1]][k].starttime/24)*24).arg(sch[road[i]][road[i+1]][k].endtime/24+1)
                    .arg(sch[road[i]][road[i+1]][k].endtime-(sch[road[i]][road[i+1]][k].endtime/24)*24)
                    .arg(sch[road[i]][road[i+1]][k].trainnum).arg(sch[road[i]][road[i+1]][k].cost)<<endl;
                output = QString("%1--%2-->%3，第%4天%5：00出发，第%6天%7：00到达，车次：%8，费用：%9元")
                        .arg(NumToCity(road[i])).arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle)).arg(NumToCity(road[i+1])).arg(sch[road[i]][road[i+1]][k].starttime/24+1)
                        .arg(sch[road[i]][road[i+1]][k].starttime-(sch[road[i]][road[i+1]][k].starttime/24)*24).arg(sch[road[i]][road[i+1]][k].endtime/24+1)
                        .arg(sch[road[i]][road[i+1]][k].endtime-(sch[road[i]][road[i+1]][k].endtime/24)*24)
                        .arg(sch[road[i]][road[i+1]][k].trainnum).arg(sch[road[i]][road[i+1]][k].cost);
                output3.append(output);
                if(i == 0)
                {
                    StrInTra += QString("%1-%2-%3-%4-%5")
                            .arg(NumToCity(road[i]))
                            .arg(sch[road[i]][road[i+1]][k].starttime - current_time)
                            .arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle))
                            .arg(sch[road[i]][road[i+1]][k].endtime - sch[road[i]][road[i+1]][k].starttime)
                            .arg(NumToCity(road[i+1]));
                }
                else {
                    StrInTra += QString("-%1-%2-%3-%4")
                            .arg(sch[road[i]][road[i+1]][k].starttime - nowtime)
                            .arg(NumToVehical(sch[road[i]][road[i+1]][k].vihecle))
                            .arg(sch[road[i]][road[i+1]][k].endtime - sch[road[i]][road[i+1]][k].starttime)
                            .arg(NumToCity(road[i+1]));
                }
    //            qDebug()<<StrInTra;
                nowtime=sch[road[i]][road[i+1]][k].endtime;
//                emit Output();
                totaltime = nowtime - current_time;
            }
            output = QString("total cost %1 totaltime %2").arg(totalcost).arg(totaltime);
            output3.append(output);
            in<<QString("total cost %1 totaltime %2").arg(totalcost).arg(totaltime)<<endl;
//            emit Output();
        }
        else{
            output = QString("no way!");
            output3.append(output);
//            emit Output();
            in<<"no way!"<<endl;
        }
    }
    file.close();
    resetsch(sch);
}
void TravelDemand::resetsch(schedule ***sch)
{
    for(int i=0;i<city_num;i++)
    {
        for(int j=0;j<city_num;j++)
        {
            if(sch[i][j]!=NULL)
            {
                for(int k=0;k<6;k++)
                {
                    if(sch[i][j][k].vihecle!=0)
                    {
                        while(sch[i][j][k].starttime>=24)
                        {
                            sch[i][j][k].starttime=sch[i][j][k].starttime-24;
                            sch[i][j][k].endtime=sch[i][j][k].endtime-24;
                        }
                    }
                }
            }
        }
    }
}
QString TravelDemand::NumToCity(int city)
{
    QString str;
    switch (city) {
    case 0: str = "成都";break;
    case 1: str = "重庆";break;
    case 2: str = "武汉";break;
    case 3: str = "合肥";break;
    case 4: str = "南京";break;
    case 5: str = "昆明";break;
    case 6: str = "贵阳";break;
    case 7: str = "长沙";break;
    case 8: str = "南昌";break;
    case 9: str = "杭州";break;
    case 10:    str = "上海";break;
    case 11:    str = "南宁";break;
    case 12:    str = "广州";break;
    case 13:    str = "福州";break;
    case 14:    str = "香港";break;
    }
    return str;
}
QString TravelDemand::NumToVehical(int vehical)
{
    QString str;
    switch (vehical) {
    case 1:
        str = "汽车";break;
    case 2:
        str = "火车";break;
    case 3:
        str = "飞机";break;
    }
    return str;
}
int TravelDemand::CityToNum(QString city)
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
QString TravelDemand::NumToStrategy(int Strategy)
{
    QString str;
    switch (Strategy) {
    case 0:
        str = "花费最少";break;
    case 1:
        str = "时间最少";break;
    case 2:
        str = "限定时间花费最少";break;
    }
    return str;
}
