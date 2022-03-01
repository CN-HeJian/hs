/********************************************************************************
** Form generated from reading UI file 'allmachineWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLMACHINEWINDOW_H
#define UI_ALLMACHINEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_allMachineWindow
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButton;

    void setupUi(QWidget *allMachineWindow)
    {
        if (allMachineWindow->objectName().isEmpty())
            allMachineWindow->setObjectName(QString::fromUtf8("allMachineWindow"));
        allMachineWindow->resize(934, 561);
        gridLayout_2 = new QGridLayout(allMachineWindow);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(allMachineWindow);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 912, 453));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        tableWidget->setFont(font);
        tableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section { color: black; font-family: \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\"; font-weight: bold; font-size: 20px; height: 30px}\n"
"QTableWidget{selection-background-color:lightblue}\n"
"\n"
""));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        pushButton = new QPushButton(allMachineWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 80));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft New Tai Lue"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("background:lightblue"));

        verticalLayout->addWidget(pushButton);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(allMachineWindow);

        QMetaObject::connectSlotsByName(allMachineWindow);
    } // setupUi

    void retranslateUi(QWidget *allMachineWindow)
    {
        allMachineWindow->setWindowTitle(QApplication::translate("allMachineWindow", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("allMachineWindow", "\346\234\272\345\231\250\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("allMachineWindow", "\346\234\272\345\231\250\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("allMachineWindow", "\346\234\272\345\217\260\346\225\260\346\215\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("allMachineWindow", "\346\263\242\345\275\242\346\225\260\346\215\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("allMachineWindow", "\345\220\257\347\224\250/\347\246\201\347\224\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("allMachineWindow", "\347\243\201\347\233\230", nullptr));
        pushButton->setText(QApplication::translate("allMachineWindow", "\346\267\273\345\212\240\346\234\272\345\217\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class allMachineWindow: public Ui_allMachineWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLMACHINEWINDOW_H
