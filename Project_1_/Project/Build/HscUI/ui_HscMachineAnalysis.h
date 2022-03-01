/********************************************************************************
** Form generated from reading UI file 'HscMachineAnalysis.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSCMACHINEANALYSIS_H
#define UI_HSCMACHINEANALYSIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HscMachineAnalysis
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_5;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;

    void setupUi(QWidget *HscMachineAnalysis)
    {
        if (HscMachineAnalysis->objectName().isEmpty())
            HscMachineAnalysis->setObjectName(QString::fromUtf8("HscMachineAnalysis"));
        HscMachineAnalysis->resize(880, 597);
        gridLayout = new QGridLayout(HscMachineAnalysis);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(HscMachineAnalysis);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(200, 50000));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(16);
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(6, 12, 6, 6);
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("border\357\274\232transparent"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 184, 526));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_5);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(HscMachineAnalysis);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));

        gridLayout->addWidget(stackedWidget, 0, 1, 1, 1);


        retranslateUi(HscMachineAnalysis);

        QMetaObject::connectSlotsByName(HscMachineAnalysis);
    } // setupUi

    void retranslateUi(QWidget *HscMachineAnalysis)
    {
        HscMachineAnalysis->setWindowTitle(QApplication::translate("HscMachineAnalysis", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("HscMachineAnalysis", "\346\234\272\345\217\260\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HscMachineAnalysis: public Ui_HscMachineAnalysis {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSCMACHINEANALYSIS_H
