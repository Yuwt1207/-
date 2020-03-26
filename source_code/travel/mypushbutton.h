#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg, QString pressImg = "");

    QString normalImgPath;
    QString pressedImgPath;

    //向下跳跃
    void zoom1();
    //向上跳跃
    void zoom2();
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
