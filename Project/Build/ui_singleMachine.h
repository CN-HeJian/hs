/********************************************************************************
** Form generated from reading UI file 'singleMachine.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEMACHINE_H
#define UI_SINGLEMACHINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleMachine
{
public:

    void setupUi(QWidget *SingleMachine)
    {
        if (SingleMachine->objectName().isEmpty())
            SingleMachine->setObjectName(QString::fromUtf8("SingleMachine"));
        SingleMachine->resize(648, 416);

        retranslateUi(SingleMachine);

        QMetaObject::connectSlotsByName(SingleMachine);
    } // setupUi

    void retranslateUi(QWidget *SingleMachine)
    {
        SingleMachine->setWindowTitle(QApplication::translate("SingleMachine", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleMachine: public Ui_SingleMachine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEMACHINE_H
