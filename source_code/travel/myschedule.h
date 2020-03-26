#ifndef MYSCHEDULE_H
#define MYSCHEDULE_H

#include "attribute.h"

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <QString>
#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

struct schedule{
    QString trainnum;
    int starttime;
    int endtime;
    int cost;
    int vihecle;
};

class MySchedule
{
public:
    MySchedule();
    ~MySchedule();
    static int CityToNum(QString);
    static std::multimap<int, Attribute> database;

    schedule ***head;
private:
    void store_in_schedule();
};

#endif // SCHEDULE_H
