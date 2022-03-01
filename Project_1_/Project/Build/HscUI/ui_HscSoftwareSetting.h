/********************************************************************************
** Form generated from reading UI file 'HscSoftwareSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSCSOFTWARESETTING_H
#define UI_HSCSOFTWARESETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HscSoftwareSetting
{
public:

    void setupUi(QWidget *HscSoftwareSetting)
    {
        if (HscSoftwareSetting->objectName().isEmpty())
            HscSoftwareSetting->setObjectName(QString::fromUtf8("HscSoftwareSetting"));
        HscSoftwareSetting->resize(400, 300);

        retranslateUi(HscSoftwareSetting);

        QMetaObject::connectSlotsByName(HscSoftwareSetting);
    } // setupUi

    void retranslateUi(QWidget *HscSoftwareSetting)
    {
        HscSoftwareSetting->setWindowTitle(QApplication::translate("HscSoftwareSetting", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HscSoftwareSetting: public Ui_HscSoftwareSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSCSOFTWARESETTING_H
