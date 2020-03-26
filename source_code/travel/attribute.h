#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QTime>

class Attribute
{
public:
    Attribute();
    Attribute(int, int, QString, QString, QString, int, int);

    int from, to, cost, vehicle;
    QString num;
    QString begin, end;

};

#endif // ATTRIBUTE_H
