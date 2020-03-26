#include "attribute.h"
//#include "log.h"//暂时不太清楚这个

Attribute::Attribute()
{
    this->from = -1;
}
//这个类用来保存时刻表txt文件的一组内容，由myschedule类中读取并调用
Attribute::Attribute(int from, int to, QString num, QString begin, QString end, int cost, int vehicle)
{
    this->from = from;
    this->to = to;
    this->num = num;
    this->begin = begin;
    this->end = end;
    this->cost = cost;
    this->vehicle = vehicle;
}
