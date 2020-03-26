#ifndef SCHEDUELTREE_H
#define SCHEDUELTREE_H

#include <QDialog>
#include "myschedule.h"


namespace Ui {
class ScheduelTree;
}

class ScheduelTree : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduelTree(QWidget *parent = nullptr);
    ~ScheduelTree();

    //希望从这个函数得到父窗口的值
    void FromA(int num);
    //并把这个值赋给city
    int city;

//    void test(void);
    void VehicalTime(void);
    void print(int c);


private:
    Ui::ScheduelTree *ui;
};

#endif // SCHEDUELTREE_H
