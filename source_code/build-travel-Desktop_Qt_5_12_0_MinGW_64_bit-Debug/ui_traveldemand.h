/********************************************************************************
** Form generated from reading UI file 'traveldemand.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAVELDEMAND_H
#define UI_TRAVELDEMAND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TravelDemand
{
public:
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *pass_A;
    QCheckBox *pass_B;
    QCheckBox *pass_C;
    QCheckBox *pass_D;
    QCheckBox *pass_E;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *pass_G;
    QCheckBox *pass_H;
    QCheckBox *pass_I;
    QCheckBox *pass_J;
    QCheckBox *pass_F;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *pass_K;
    QCheckBox *pass_L;
    QCheckBox *pass_M;
    QCheckBox *pass_N;
    QCheckBox *pass_P;
    QLabel *label_5;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btn_travel_ok;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_travel_quit;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_7;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *departure;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *destination;
    QLabel *label_6;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QSpinBox *strategy3_hour;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *strategy1;
    QRadioButton *strategy2;
    QRadioButton *strategy3;

    void setupUi(QDialog *TravelDemand)
    {
        if (TravelDemand->objectName().isEmpty())
            TravelDemand->setObjectName(QString::fromUtf8("TravelDemand"));
        TravelDemand->resize(612, 465);
        label_3 = new QLabel(TravelDemand);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 20, 72, 15));
        label_4 = new QLabel(TravelDemand);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 100, 91, 16));
        widget_6 = new QWidget(TravelDemand);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(40, 120, 527, 159));
        verticalLayout = new QVBoxLayout(widget_6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_3 = new QWidget(widget_6);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pass_A = new QCheckBox(widget_3);
        pass_A->setObjectName(QString::fromUtf8("pass_A"));

        horizontalLayout_3->addWidget(pass_A);

        pass_B = new QCheckBox(widget_3);
        pass_B->setObjectName(QString::fromUtf8("pass_B"));

        horizontalLayout_3->addWidget(pass_B);

        pass_C = new QCheckBox(widget_3);
        pass_C->setObjectName(QString::fromUtf8("pass_C"));

        horizontalLayout_3->addWidget(pass_C);

        pass_D = new QCheckBox(widget_3);
        pass_D->setObjectName(QString::fromUtf8("pass_D"));

        horizontalLayout_3->addWidget(pass_D);

        pass_E = new QCheckBox(widget_3);
        pass_E->setObjectName(QString::fromUtf8("pass_E"));

        horizontalLayout_3->addWidget(pass_E);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget_6);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pass_G = new QCheckBox(widget_4);
        pass_G->setObjectName(QString::fromUtf8("pass_G"));

        horizontalLayout_4->addWidget(pass_G);

        pass_H = new QCheckBox(widget_4);
        pass_H->setObjectName(QString::fromUtf8("pass_H"));

        horizontalLayout_4->addWidget(pass_H);

        pass_I = new QCheckBox(widget_4);
        pass_I->setObjectName(QString::fromUtf8("pass_I"));

        horizontalLayout_4->addWidget(pass_I);

        pass_J = new QCheckBox(widget_4);
        pass_J->setObjectName(QString::fromUtf8("pass_J"));

        horizontalLayout_4->addWidget(pass_J);

        pass_F = new QCheckBox(widget_4);
        pass_F->setObjectName(QString::fromUtf8("pass_F"));

        horizontalLayout_4->addWidget(pass_F);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(widget_6);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pass_K = new QCheckBox(widget_5);
        pass_K->setObjectName(QString::fromUtf8("pass_K"));

        horizontalLayout_5->addWidget(pass_K);

        pass_L = new QCheckBox(widget_5);
        pass_L->setObjectName(QString::fromUtf8("pass_L"));

        horizontalLayout_5->addWidget(pass_L);

        pass_M = new QCheckBox(widget_5);
        pass_M->setObjectName(QString::fromUtf8("pass_M"));

        horizontalLayout_5->addWidget(pass_M);

        pass_N = new QCheckBox(widget_5);
        pass_N->setObjectName(QString::fromUtf8("pass_N"));

        horizontalLayout_5->addWidget(pass_N);

        pass_P = new QCheckBox(widget_5);
        pass_P->setObjectName(QString::fromUtf8("pass_P"));

        horizontalLayout_5->addWidget(pass_P);


        verticalLayout->addWidget(widget_5);

        label_5 = new QLabel(TravelDemand);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 280, 91, 16));
        widget_8 = new QWidget(TravelDemand);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(170, 400, 271, 50));
        horizontalLayout_6 = new QHBoxLayout(widget_8);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btn_travel_ok = new QPushButton(widget_8);
        btn_travel_ok->setObjectName(QString::fromUtf8("btn_travel_ok"));

        horizontalLayout_6->addWidget(btn_travel_ok);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        btn_travel_quit = new QPushButton(widget_8);
        btn_travel_quit->setObjectName(QString::fromUtf8("btn_travel_quit"));

        horizontalLayout_6->addWidget(btn_travel_quit);

        widget_9 = new QWidget(TravelDemand);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setGeometry(QRect(40, 40, 253, 65));
        horizontalLayout_7 = new QHBoxLayout(widget_9);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        widget = new QWidget(widget_9);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        departure = new QComboBox(widget);
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->addItem(QString());
        departure->setObjectName(QString::fromUtf8("departure"));

        horizontalLayout->addWidget(departure);


        horizontalLayout_7->addWidget(widget);

        widget_2 = new QWidget(widget_9);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        destination = new QComboBox(widget_2);
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->addItem(QString());
        destination->setObjectName(QString::fromUtf8("destination"));

        horizontalLayout_2->addWidget(destination);


        horizontalLayout_7->addWidget(widget_2);

        label_6 = new QLabel(TravelDemand);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(240, 280, 91, 16));
        widget_10 = new QWidget(TravelDemand);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        widget_10->setGeometry(QRect(260, 300, 144, 43));
        horizontalLayout_8 = new QHBoxLayout(widget_10);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_7 = new QLabel(widget_10);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_8->addWidget(label_7);

        strategy3_hour = new QSpinBox(widget_10);
        strategy3_hour->setObjectName(QString::fromUtf8("strategy3_hour"));

        horizontalLayout_8->addWidget(strategy3_hour);

        groupBox = new QGroupBox(TravelDemand);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(40, 300, 156, 110));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        strategy1 = new QRadioButton(groupBox);
        strategy1->setObjectName(QString::fromUtf8("strategy1"));

        verticalLayout_2->addWidget(strategy1);

        strategy2 = new QRadioButton(groupBox);
        strategy2->setObjectName(QString::fromUtf8("strategy2"));

        verticalLayout_2->addWidget(strategy2);

        strategy3 = new QRadioButton(groupBox);
        strategy3->setObjectName(QString::fromUtf8("strategy3"));

        verticalLayout_2->addWidget(strategy3);

        QWidget::setTabOrder(destination, pass_F);
        QWidget::setTabOrder(pass_F, pass_A);
        QWidget::setTabOrder(pass_A, pass_B);
        QWidget::setTabOrder(pass_B, pass_C);
        QWidget::setTabOrder(pass_C, pass_D);
        QWidget::setTabOrder(pass_D, pass_E);
        QWidget::setTabOrder(pass_E, pass_G);
        QWidget::setTabOrder(pass_G, pass_H);
        QWidget::setTabOrder(pass_H, pass_I);
        QWidget::setTabOrder(pass_I, pass_J);
        QWidget::setTabOrder(pass_J, departure);
        QWidget::setTabOrder(departure, pass_K);
        QWidget::setTabOrder(pass_K, pass_L);
        QWidget::setTabOrder(pass_L, pass_M);
        QWidget::setTabOrder(pass_M, pass_N);

        retranslateUi(TravelDemand);

        QMetaObject::connectSlotsByName(TravelDemand);
    } // setupUi

    void retranslateUi(QDialog *TravelDemand)
    {
        TravelDemand->setWindowTitle(QApplication::translate("TravelDemand", "Dialog", nullptr));
        label_3->setText(QApplication::translate("TravelDemand", "\346\202\250\347\232\204\345\247\223\345\220\215\357\274\232", nullptr));
        label_4->setText(QApplication::translate("TravelDemand", "\351\200\224\347\273\217\345\237\216\345\270\202\351\200\211\346\213\251", nullptr));
        pass_A->setText(QApplication::translate("TravelDemand", "A", nullptr));
        pass_B->setText(QApplication::translate("TravelDemand", "B", nullptr));
        pass_C->setText(QApplication::translate("TravelDemand", "C", nullptr));
        pass_D->setText(QApplication::translate("TravelDemand", "D", nullptr));
        pass_E->setText(QApplication::translate("TravelDemand", "E", nullptr));
        pass_G->setText(QApplication::translate("TravelDemand", "F", nullptr));
        pass_H->setText(QApplication::translate("TravelDemand", "G", nullptr));
        pass_I->setText(QApplication::translate("TravelDemand", "H", nullptr));
        pass_J->setText(QApplication::translate("TravelDemand", "I", nullptr));
        pass_F->setText(QApplication::translate("TravelDemand", "J", nullptr));
        pass_K->setText(QApplication::translate("TravelDemand", "K", nullptr));
        pass_L->setText(QApplication::translate("TravelDemand", "L", nullptr));
        pass_M->setText(QApplication::translate("TravelDemand", "M", nullptr));
        pass_N->setText(QApplication::translate("TravelDemand", "N", nullptr));
        pass_P->setText(QApplication::translate("TravelDemand", "P", nullptr));
        label_5->setText(QApplication::translate("TravelDemand", "\346\227\205\350\241\214\347\255\226\347\225\245\351\200\211\346\213\251", nullptr));
        btn_travel_ok->setText(QApplication::translate("TravelDemand", "\347\241\256\345\256\232", nullptr));
        btn_travel_quit->setText(QApplication::translate("TravelDemand", "\345\217\226\346\266\210", nullptr));
        label->setText(QApplication::translate("TravelDemand", "\345\207\272\345\217\221\345\234\260", nullptr));
        departure->setItemText(0, QApplication::translate("TravelDemand", "A", nullptr));
        departure->setItemText(1, QApplication::translate("TravelDemand", "B", nullptr));
        departure->setItemText(2, QApplication::translate("TravelDemand", "C", nullptr));
        departure->setItemText(3, QApplication::translate("TravelDemand", "D", nullptr));
        departure->setItemText(4, QApplication::translate("TravelDemand", "E", nullptr));
        departure->setItemText(5, QApplication::translate("TravelDemand", "F", nullptr));
        departure->setItemText(6, QApplication::translate("TravelDemand", "G", nullptr));
        departure->setItemText(7, QApplication::translate("TravelDemand", "H", nullptr));
        departure->setItemText(8, QApplication::translate("TravelDemand", "I", nullptr));
        departure->setItemText(9, QApplication::translate("TravelDemand", "J", nullptr));
        departure->setItemText(10, QApplication::translate("TravelDemand", "K", nullptr));
        departure->setItemText(11, QApplication::translate("TravelDemand", "L", nullptr));
        departure->setItemText(12, QApplication::translate("TravelDemand", "M", nullptr));
        departure->setItemText(13, QApplication::translate("TravelDemand", "N", nullptr));
        departure->setItemText(14, QApplication::translate("TravelDemand", "P", nullptr));

        label_2->setText(QApplication::translate("TravelDemand", "\347\233\256\347\232\204\345\234\260", nullptr));
        destination->setItemText(0, QApplication::translate("TravelDemand", "A", nullptr));
        destination->setItemText(1, QApplication::translate("TravelDemand", "B", nullptr));
        destination->setItemText(2, QApplication::translate("TravelDemand", "C", nullptr));
        destination->setItemText(3, QApplication::translate("TravelDemand", "D", nullptr));
        destination->setItemText(4, QApplication::translate("TravelDemand", "E", nullptr));
        destination->setItemText(5, QApplication::translate("TravelDemand", "F", nullptr));
        destination->setItemText(6, QApplication::translate("TravelDemand", "G", nullptr));
        destination->setItemText(7, QApplication::translate("TravelDemand", "H", nullptr));
        destination->setItemText(8, QApplication::translate("TravelDemand", "I", nullptr));
        destination->setItemText(9, QApplication::translate("TravelDemand", "J", nullptr));
        destination->setItemText(10, QApplication::translate("TravelDemand", "K", nullptr));
        destination->setItemText(11, QApplication::translate("TravelDemand", "L", nullptr));
        destination->setItemText(12, QApplication::translate("TravelDemand", "M", nullptr));
        destination->setItemText(13, QApplication::translate("TravelDemand", "N", nullptr));
        destination->setItemText(14, QApplication::translate("TravelDemand", "P", nullptr));

        label_6->setText(QApplication::translate("TravelDemand", "\351\231\220\345\256\232\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        label_7->setText(QApplication::translate("TravelDemand", "\345\260\217\346\227\266(h)\357\274\232", nullptr));
        groupBox->setTitle(QString());
        strategy1->setText(QApplication::translate("TravelDemand", "\346\234\200\347\234\201\351\222\261", nullptr));
        strategy2->setText(QApplication::translate("TravelDemand", "\346\234\200\347\234\201\346\227\266\351\227\264", nullptr));
        strategy3->setText(QApplication::translate("TravelDemand", "\351\231\220\345\256\232\346\227\266\351\227\264\346\234\200\347\234\201\351\222\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TravelDemand: public Ui_TravelDemand {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAVELDEMAND_H
