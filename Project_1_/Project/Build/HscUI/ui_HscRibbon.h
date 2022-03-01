/********************************************************************************
** Form generated from reading UI file 'HscRibbon.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSCRIBBON_H
#define UI_HSCRIBBON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HscRibbon
{
public:
    QHBoxLayout *horizontalLayout_3;
    QWidget *widgetContainer;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QTabWidget *tabWidgetMenuBar;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QWidget *tab_5;
    QGridLayout *gridLayout_7;
    QWidget *tab_6;
    QGridLayout *gridLayout_8;

    void setupUi(QMenuBar *HscRibbon)
    {
        if (HscRibbon->objectName().isEmpty())
            HscRibbon->setObjectName(QString::fromUtf8("HscRibbon"));
        HscRibbon->resize(798, 90);
        HscRibbon->setMinimumSize(QSize(0, 90));
        HscRibbon->setMaximumSize(QSize(16777215, 90));
        HscRibbon->setWindowOpacity(1.000000000000000);
        HscRibbon->setLayoutDirection(Qt::LeftToRight);
        HscRibbon->setAutoFillBackground(false);
        HscRibbon->setStyleSheet(QString::fromUtf8(""));
        HscRibbon->setDefaultUp(false);
        HscRibbon->setNativeMenuBar(false);
        horizontalLayout_3 = new QHBoxLayout(HscRibbon);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetContainer = new QWidget(HscRibbon);
        widgetContainer->setObjectName(QString::fromUtf8("widgetContainer"));
        widgetContainer->setMinimumSize(QSize(0, 90));
        widgetContainer->setMaximumSize(QSize(16777215, 90));
        widgetContainer->setAutoFillBackground(false);
        widgetContainer->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(widgetContainer);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidgetMenuBar = new QTabWidget(widgetContainer);
        tabWidgetMenuBar->setObjectName(QString::fromUtf8("tabWidgetMenuBar"));
        tabWidgetMenuBar->setMinimumSize(QSize(0, 90));
        tabWidgetMenuBar->setMaximumSize(QSize(16777215, 90));
        tabWidgetMenuBar->setStyleSheet(QString::fromUtf8(""));
        tabWidgetMenuBar->setElideMode(Qt::ElideNone);
        tabWidgetMenuBar->setTabBarAutoHide(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 3, -1, 2);
        tabWidgetMenuBar->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_7 = new QGridLayout(tab_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(-1, 3, -1, 2);
        tabWidgetMenuBar->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        gridLayout_8 = new QGridLayout(tab_6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(-1, 3, -1, 2);
        tabWidgetMenuBar->addTab(tab_6, QString());

        gridLayout->addWidget(tabWidgetMenuBar, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalLayout->setStretch(0, 10);

        horizontalLayout_3->addWidget(widgetContainer);


        retranslateUi(HscRibbon);

        tabWidgetMenuBar->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(HscRibbon);
    } // setupUi

    void retranslateUi(QMenuBar *HscRibbon)
    {
        HscRibbon->setWindowTitle(QApplication::translate("HscRibbon", "Form", nullptr));
        tabWidgetMenuBar->setTabText(tabWidgetMenuBar->indexOf(tab), QApplication::translate("HscRibbon", "\345\234\250\347\272\277\347\233\221\346\216\247", nullptr));
        tabWidgetMenuBar->setTabText(tabWidgetMenuBar->indexOf(tab_5), QApplication::translate("HscRibbon", "\346\234\272\345\217\260\345\210\206\346\236\220", nullptr));
        tabWidgetMenuBar->setTabText(tabWidgetMenuBar->indexOf(tab_6), QApplication::translate("HscRibbon", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HscRibbon: public Ui_HscRibbon {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSCRIBBON_H
