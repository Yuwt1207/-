#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//封装一个自己的按钮，该按钮能实现点击图片弹出对话框
//传入两个参数，第一个是正常的图片，第二个是按下后显示的图片
//因为需求的按钮只需要实现动画效果即可，不需要第二张图片，仅传入一个参数即可
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    //保存正常图片路径和 选中后显示的路径
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressImg;

    QPixmap pix;

    bool ret = pix.load(this->normalImgPath);
    if(!ret)
    {
        //此行代码实现几个Qstring之间 的拼接
        QString str = QString("1%图片加载失败").arg(this->normalImgPath);
        qDebug()<<str;

        return;
    }
    //设定大小为正常的0.5倍
    this->setFixedSize(pix.width()*0.5,pix.height()*0.5);

    //设置图片
    this->setIcon(pix);

    //设置图片大小为正常的0.5倍
    this->setIconSize(QSize(pix.width()*0.5,pix.height()*0.5));
}

//向下跳跃
void MyPushButton::zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");

    //设定时间间隔
    animation->setDuration(100);
    //设置动画对象起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()  ));
    //设置动画对象结束位置
    animation->setEndValue(QRect(this->x(),this->y()+8 ,this->width(),this->height()  ));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::Linear);
    //执行动画
    animation->start();
}
//向上跳跃
void MyPushButton::zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");

    //设定时间间隔
    animation->setDuration(100);
    //设置动画对象起始位置
    animation->setStartValue(QRect(this->x(),this->y()+8,this->width(),this->height()  ));
    //设置动画对象结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()  ));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::Linear);
    //执行动画
    animation->start();
}
