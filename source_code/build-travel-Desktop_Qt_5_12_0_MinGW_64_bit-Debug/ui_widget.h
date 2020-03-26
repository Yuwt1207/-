/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *AddNewTraveller;
    QPushButton *QueryRequest_btn;
    QLabel *label_3;
    QLabel *label;
    QTextEdit *textEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(1000, 800);
        Widget->setMinimumSize(QSize(1000, 800));
        Widget->setMaximumSize(QSize(1000, 800));
        AddNewTraveller = new QPushButton(Widget);
        AddNewTraveller->setObjectName(QString::fromUtf8("AddNewTraveller"));
        AddNewTraveller->setGeometry(QRect(10, 20, 93, 28));
        QueryRequest_btn = new QPushButton(Widget);
        QueryRequest_btn->setObjectName(QString::fromUtf8("QueryRequest_btn"));
        QueryRequest_btn->setGeometry(QRect(10, 80, 101, 28));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 770, 131, 31));
        label_3->setFrameShape(QFrame::NoFrame);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 10, 72, 15));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(230, 10, 641, 121));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        AddNewTraveller->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\346\226\260\346\227\205\345\256\242", nullptr));
        QueryRequest_btn->setText(QApplication::translate("Widget", "\345\217\221\350\265\267\346\237\245\350\257\242\350\257\267\346\261\202", nullptr));
        label_3->setText(QApplication::translate("Widget", "\346\227\266\351\227\264\357\274\232", nullptr));
        label->setText(QApplication::translate("Widget", "\346\227\205\350\241\214\345\273\272\350\256\256\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
