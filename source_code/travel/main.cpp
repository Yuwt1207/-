#include "widget.h"
#include "myschedule.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySchedule schedule;

    Widget w;
    w.show();

    return a.exec();
}
