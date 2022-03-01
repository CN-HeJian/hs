/********************************************************************************
** Form generated from reading UI file 'SingleMachine.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEMACHINE_H
#define UI_SINGLEMACHINE_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <machineparaplot.h>

QT_BEGIN_NAMESPACE

class Ui_SingleMachine
{
public:
    QGridLayout *gridLayout_5;
    QWidget *widget;
    QGridLayout *gridLayout;
    MachineParaPlot *plotWidget;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QDateTimeEdit *dateTimeEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_1;
    QHBoxLayout *horizontalLayout_29;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_21;
    QSpinBox *spinBox_5;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_22;
    QSpinBox *spinBox_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_10;
    QDateTimeEdit *dateTimeEdit_3;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_11;
    QDateTimeEdit *dateTimeEdit_4;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_14;
    QSpinBox *spinBox_8;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_7;
    QHBoxLayout *horizontalLayout_21;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_16;
    QDoubleSpinBox *doubleSpinBox_10;
    QToolButton *toolButton_5;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_26;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBox_12;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_20;
    QDoubleSpinBox *doubleSpinBox_13;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_3;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *toolButton_4;

    void setupUi(QWidget *SingleMachine)
    {
        if (SingleMachine->objectName().isEmpty())
            SingleMachine->setObjectName(QString::fromUtf8("SingleMachine"));
        SingleMachine->resize(960, 858);
        QFont font;
        font.setPointSize(12);
        SingleMachine->setFont(font);
        gridLayout_5 = new QGridLayout(SingleMachine);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(SingleMachine);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 12, 0, 0);
        plotWidget = new MachineParaPlot(widget);
        plotWidget->setObjectName(QString::fromUtf8("plotWidget"));

        gridLayout->addWidget(plotWidget, 0, 0, 1, 1);


        gridLayout_5->addWidget(widget, 0, 0, 1, 1);

        groupBox = new QGroupBox(SingleMachine);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(260, 0));
        groupBox->setMaximumSize(QSize(250, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(16);
        groupBox->setFont(font1);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 40, 235, 189));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(235, 0));
        groupBox_2->setMaximumSize(QSize(230, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial Black"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(true);
        font2.setStyleStrategy(QFont::PreferAntialias);
        groupBox_2->setFont(font2);
        groupBox_2->setFocusPolicy(Qt::NoFocus);
        groupBox_2->setContextMenuPolicy(Qt::NoContextMenu);
#ifndef QT_NO_STATUSTIP
        groupBox_2->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
        groupBox_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        gridLayout_7 = new QGridLayout(groupBox_2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        checkBox_3 = new QCheckBox(groupBox_2);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setMinimumSize(QSize(90, 30));
        checkBox_3->setMaximumSize(QSize(90, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setWeight(50);
        font3.setKerning(true);
        font3.setStyleStrategy(QFont::PreferAntialias);
        checkBox_3->setFont(font3);
        checkBox_3->setChecked(false);

        horizontalLayout_7->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(groupBox_2);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setMinimumSize(QSize(90, 30));
        checkBox_4->setMaximumSize(QSize(90, 30));
        checkBox_4->setFont(font3);
        checkBox_4->setChecked(true);

        horizontalLayout_7->addWidget(checkBox_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setMaximumSize(QSize(16777215, 30));
        label_3->setFont(font3);

        horizontalLayout_4->addWidget(label_3);

        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(150, 30));
        comboBox->setMaximumSize(QSize(150, 30));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font4.setPointSize(12);
        font4.setBold(false);
        font4.setWeight(50);
        font4.setKerning(true);
        font4.setStyleStrategy(QFont::PreferAntialias);
        comboBox->setFont(font4);
        comboBox->setMaxCount(2147483646);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font3);

        horizontalLayout_3->addWidget(label);

        dateTimeEdit = new QDateTimeEdit(groupBox_2);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setMinimumSize(QSize(150, 30));
        dateTimeEdit->setMaximumSize(QSize(150, 30));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Microsoft JhengHei UI Light"));
        font5.setPointSize(13);
        font5.setBold(false);
        font5.setWeight(50);
        font5.setKerning(true);
        font5.setStyleStrategy(QFont::PreferAntialias);
        dateTimeEdit->setFont(font5);
        dateTimeEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        dateTimeEdit->setDate(QDate(2021, 9, 25));
        dateTimeEdit->setTime(QTime(9, 30, 0));

        horizontalLayout_3->addWidget(dateTimeEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setMaximumSize(QSize(16777215, 30));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        font6.setPointSize(12);
        font6.setBold(false);
        font6.setWeight(50);
        font6.setStrikeOut(false);
        font6.setKerning(true);
        font6.setStyleStrategy(QFont::PreferAntialias);
        label_2->setFont(font6);

        horizontalLayout_2->addWidget(label_2);

        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(150, 30));
        spinBox->setMaximumSize(QSize(100, 30));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Microsoft JhengHei UI Light"));
        font7.setPointSize(12);
        font7.setBold(false);
        font7.setWeight(50);
        font7.setKerning(true);
        font7.setStyleStrategy(QFont::PreferAntialias);
        spinBox->setFont(font7);
        spinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBox->setMinimum(1);
        spinBox->setMaximum(10500000);
        spinBox->setValue(50);

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout_7->addLayout(verticalLayout_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 360, 235, 115));
        groupBox_3->setMinimumSize(QSize(235, 0));
        groupBox_3->setMaximumSize(QSize(230, 16777215));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Arial Black"));
        font8.setPointSize(12);
        font8.setBold(true);
        font8.setWeight(75);
        groupBox_3->setFont(font8);
        groupBox_3->setAlignment(Qt::AlignCenter);
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setMinimumSize(QSize(90, 30));
        checkBox_2->setMaximumSize(QSize(90, 30));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        font9.setPointSize(12);
        font9.setBold(false);
        font9.setWeight(50);
        checkBox_2->setFont(font9);
        checkBox_2->setChecked(true);

        horizontalLayout_5->addWidget(checkBox_2);

        checkBox_1 = new QCheckBox(groupBox_3);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setMinimumSize(QSize(90, 30));
        checkBox_1->setMaximumSize(QSize(90, 30));
        checkBox_1->setFont(font9);

        horizontalLayout_5->addWidget(checkBox_1);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setMinimumSize(QSize(30, 30));
        label_21->setMaximumSize(QSize(30, 30));
        label_21->setFont(font9);

        horizontalLayout_30->addWidget(label_21);

        spinBox_5 = new QSpinBox(groupBox_3);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setMinimumSize(QSize(70, 30));
        spinBox_5->setMaximumSize(QSize(50, 30));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Microsoft JhengHei UI Light"));
        font10.setPointSize(12);
        font10.setBold(false);
        font10.setWeight(50);
        spinBox_5->setFont(font10);
        spinBox_5->setAlignment(Qt::AlignCenter);
        spinBox_5->setReadOnly(false);
        spinBox_5->setMinimum(1);
        spinBox_5->setMaximum(5000);
        spinBox_5->setValue(10);

        horizontalLayout_30->addWidget(spinBox_5);


        horizontalLayout_29->addLayout(horizontalLayout_30);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMinimumSize(QSize(30, 30));
        label_22->setMaximumSize(QSize(30, 30));
        label_22->setFont(font9);

        horizontalLayout_31->addWidget(label_22);

        spinBox_2 = new QSpinBox(groupBox_3);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMinimumSize(QSize(70, 30));
        spinBox_2->setMaximumSize(QSize(50, 30));
        spinBox_2->setFont(font10);
        spinBox_2->setAlignment(Qt::AlignCenter);
        spinBox_2->setReadOnly(false);
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(500);

        horizontalLayout_31->addWidget(spinBox_2);


        horizontalLayout_29->addLayout(horizontalLayout_31);


        verticalLayout->addLayout(horizontalLayout_29);


        gridLayout_4->addLayout(verticalLayout, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 240, 235, 113));
        groupBox_4->setMinimumSize(QSize(235, 90));
        groupBox_4->setMaximumSize(QSize(230, 16777215));
        groupBox_4->setFont(font8);
        groupBox_4->setAlignment(Qt::AlignCenter);
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font9);

        horizontalLayout_14->addWidget(label_10);

        dateTimeEdit_3 = new QDateTimeEdit(groupBox_4);
        dateTimeEdit_3->setObjectName(QString::fromUtf8("dateTimeEdit_3"));
        dateTimeEdit_3->setMinimumSize(QSize(150, 30));
        dateTimeEdit_3->setMaximumSize(QSize(150, 30));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Microsoft JhengHei UI Light"));
        font11.setPointSize(13);
        font11.setBold(false);
        font11.setWeight(50);
        dateTimeEdit_3->setFont(font11);
        dateTimeEdit_3->setAlignment(Qt::AlignCenter);
        dateTimeEdit_3->setDate(QDate(2021, 9, 25));
        dateTimeEdit_3->setTime(QTime(9, 30, 0));

        horizontalLayout_14->addWidget(dateTimeEdit_3);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 30));
        label_11->setMaximumSize(QSize(16777215, 30));
        QFont font12;
        font12.setFamily(QString::fromUtf8("Microsoft JhengHei UI"));
        font12.setPointSize(12);
        font12.setBold(false);
        font12.setWeight(50);
        font12.setStrikeOut(false);
        label_11->setFont(font12);

        horizontalLayout_15->addWidget(label_11);

        dateTimeEdit_4 = new QDateTimeEdit(groupBox_4);
        dateTimeEdit_4->setObjectName(QString::fromUtf8("dateTimeEdit_4"));
        dateTimeEdit_4->setMinimumSize(QSize(150, 30));
        dateTimeEdit_4->setMaximumSize(QSize(150, 30));
        dateTimeEdit_4->setFont(font11);
        dateTimeEdit_4->setLayoutDirection(Qt::LeftToRight);
        dateTimeEdit_4->setAlignment(Qt::AlignCenter);
        dateTimeEdit_4->setDateTime(QDateTime(QDate(2021, 9, 26), QTime(9, 0, 0)));

        horizontalLayout_15->addWidget(dateTimeEdit_4);


        verticalLayout_4->addLayout(horizontalLayout_15);


        gridLayout_6->addLayout(verticalLayout_4, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 600, 235, 115));
        groupBox_6->setMinimumSize(QSize(235, 0));
        groupBox_6->setMaximumSize(QSize(230, 16777215));
        groupBox_6->setFont(font8);
        groupBox_6->setAlignment(Qt::AlignCenter);
        groupBox_6->setFlat(false);
        groupBox_6->setCheckable(false);
        gridLayout_3 = new QGridLayout(groupBox_6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(30, 30));
        label_14->setMaximumSize(QSize(30, 30));
        label_14->setFont(font9);

        horizontalLayout_18->addWidget(label_14);

        spinBox_8 = new QSpinBox(groupBox_6);
        spinBox_8->setObjectName(QString::fromUtf8("spinBox_8"));
        spinBox_8->setMinimumSize(QSize(70, 30));
        spinBox_8->setMaximumSize(QSize(50, 30));
        spinBox_8->setFont(font10);
        spinBox_8->setAlignment(Qt::AlignCenter);
        spinBox_8->setReadOnly(true);
        spinBox_8->setMaximum(1000000);

        horizontalLayout_18->addWidget(spinBox_8);


        horizontalLayout_20->addLayout(horizontalLayout_18);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(30, 30));
        label_13->setMaximumSize(QSize(30, 30));
        label_13->setFont(font9);

        horizontalLayout_17->addWidget(label_13);

        doubleSpinBox_7 = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_7->setObjectName(QString::fromUtf8("doubleSpinBox_7"));
        doubleSpinBox_7->setMinimumSize(QSize(70, 30));
        doubleSpinBox_7->setMaximumSize(QSize(50, 30));
        doubleSpinBox_7->setFont(font10);
        doubleSpinBox_7->setAlignment(Qt::AlignCenter);
        doubleSpinBox_7->setReadOnly(true);
        doubleSpinBox_7->setMaximum(1999999.989999999990687);

        horizontalLayout_17->addWidget(doubleSpinBox_7);


        horizontalLayout_20->addLayout(horizontalLayout_17);


        gridLayout_3->addLayout(horizontalLayout_20, 0, 0, 1, 1);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_16 = new QLabel(groupBox_6);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(30, 30));
        label_16->setMaximumSize(QSize(30, 30));
        label_16->setFont(font9);

        horizontalLayout_22->addWidget(label_16);

        doubleSpinBox_10 = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_10->setObjectName(QString::fromUtf8("doubleSpinBox_10"));
        doubleSpinBox_10->setMinimumSize(QSize(70, 30));
        doubleSpinBox_10->setMaximumSize(QSize(50, 30));
        doubleSpinBox_10->setFont(font10);
        doubleSpinBox_10->setAlignment(Qt::AlignCenter);
        doubleSpinBox_10->setReadOnly(true);
        doubleSpinBox_10->setDecimals(4);
        doubleSpinBox_10->setMaximum(99999999.999899998307228);
        doubleSpinBox_10->setSingleStep(0.000001000000000);

        horizontalLayout_22->addWidget(doubleSpinBox_10);

        toolButton_5 = new QToolButton(groupBox_6);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        toolButton_5->setMinimumSize(QSize(107, 30));
        toolButton_5->setFont(font8);
        toolButton_5->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QToolButton{\n"
"background:rgb(160, 192, 240);\n"
"}\n"
"\n"
"\n"
"QToolButton:hover{  /*\351\274\240\346\240\207\346\224\276\344\270\212\345\220\216*/\n"
"background:rgb(46, 142, 253);\n"
"}\n"
"\n"
"\n"
""));

        horizontalLayout_22->addWidget(toolButton_5);


        horizontalLayout_21->addLayout(horizontalLayout_22);


        gridLayout_3->addLayout(horizontalLayout_21, 1, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 480, 235, 113));
        groupBox_7->setMinimumSize(QSize(235, 0));
        groupBox_7->setMaximumSize(QSize(230, 16777215));
        groupBox_7->setFont(font8);
        groupBox_7->setAlignment(Qt::AlignCenter);
        groupBox_7->setFlat(false);
        groupBox_7->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox_7);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        label_19 = new QLabel(groupBox_7);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMinimumSize(QSize(30, 30));
        label_19->setMaximumSize(QSize(30, 30));
        label_19->setFont(font9);

        horizontalLayout_27->addWidget(label_19);

        doubleSpinBox_12 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_12->setObjectName(QString::fromUtf8("doubleSpinBox_12"));
        doubleSpinBox_12->setMinimumSize(QSize(70, 30));
        doubleSpinBox_12->setMaximumSize(QSize(50, 30));
        doubleSpinBox_12->setFont(font10);
        doubleSpinBox_12->setAlignment(Qt::AlignCenter);
        doubleSpinBox_12->setReadOnly(false);
        doubleSpinBox_12->setMaximum(9999999.000000000000000);
        doubleSpinBox_12->setSingleStep(0.100000000000000);

        horizontalLayout_27->addWidget(doubleSpinBox_12);


        horizontalLayout_26->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMinimumSize(QSize(30, 30));
        label_20->setMaximumSize(QSize(30, 30));
        label_20->setFont(font9);

        horizontalLayout_28->addWidget(label_20);

        doubleSpinBox_13 = new QDoubleSpinBox(groupBox_7);
        doubleSpinBox_13->setObjectName(QString::fromUtf8("doubleSpinBox_13"));
        doubleSpinBox_13->setMinimumSize(QSize(70, 30));
        doubleSpinBox_13->setMaximumSize(QSize(50, 30));
        doubleSpinBox_13->setFont(font10);
        doubleSpinBox_13->setAlignment(Qt::AlignCenter);
        doubleSpinBox_13->setReadOnly(false);
        doubleSpinBox_13->setMaximum(99999999.000000000000000);
        doubleSpinBox_13->setSingleStep(0.100000000000000);

        horizontalLayout_28->addWidget(doubleSpinBox_13);


        horizontalLayout_26->addLayout(horizontalLayout_28);


        gridLayout_2->addLayout(horizontalLayout_26, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton_3 = new QToolButton(groupBox_7);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(210, 30));
        toolButton_3->setFont(font8);
        toolButton_3->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QToolButton{\n"
"background:rgb(160, 192, 240);\n"
"}\n"
"\n"
"\n"
"QToolButton:hover{  /*\351\274\240\346\240\207\346\224\276\344\270\212\345\220\216*/\n"
"background:rgb(46, 142, 253);\n"
"}\n"
"\n"
"\n"
""));

        horizontalLayout->addWidget(toolButton_3);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        groupBox_8 = new QGroupBox(groupBox);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 720, 235, 81));
        groupBox_8->setMinimumSize(QSize(235, 0));
        groupBox_8->setMaximumSize(QSize(230, 16777215));
        groupBox_8->setFont(font8);
        groupBox_8->setAlignment(Qt::AlignCenter);
        groupBox_8->setFlat(false);
        groupBox_8->setCheckable(false);
        gridLayout_8 = new QGridLayout(groupBox_8);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        toolButton_4 = new QToolButton(groupBox_8);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setMinimumSize(QSize(210, 30));
        toolButton_4->setFont(font8);
        toolButton_4->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QToolButton{\n"
"background:rgb(160, 192, 240);\n"
"}\n"
"\n"
"\n"
"QToolButton:hover{  /*\351\274\240\346\240\207\346\224\276\344\270\212\345\220\216*/\n"
"background:rgb(46, 142, 253);\n"
"}\n"
"\n"
"\n"
""));

        horizontalLayout_6->addWidget(toolButton_4);


        gridLayout_8->addLayout(horizontalLayout_6, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 1, 1, 1);


        retranslateUi(SingleMachine);

        QMetaObject::connectSlotsByName(SingleMachine);
    } // setupUi

    void retranslateUi(QWidget *SingleMachine)
    {
        SingleMachine->setWindowTitle(QApplication::translate("SingleMachine", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("SingleMachine", "\350\256\276\347\275\256", nullptr));
        groupBox_2->setTitle(QApplication::translate("SingleMachine", "\345\256\236\346\227\266\346\237\245\350\257\242", nullptr));
        checkBox_3->setText(QApplication::translate("SingleMachine", "\346\234\200\350\277\221\346\250\241\346\254\241", nullptr));
        checkBox_4->setText(QApplication::translate("SingleMachine", "\346\234\200\350\277\221\345\214\272\351\227\264", nullptr));
        label_3->setText(QApplication::translate("SingleMachine", "\346\225\260\346\215\256\347\261\273\345\236\213", nullptr));
        comboBox->setItemText(0, QApplication::translate("SingleMachine", "\346\263\250\345\260\204\346\256\265\345\216\213\345\212\233\345\271\263\345\235\207\345\200\274", nullptr));
        comboBox->setItemText(1, QApplication::translate("SingleMachine", "\350\256\241\351\207\217\346\211\255\347\237\251", nullptr));
        comboBox->setItemText(2, QApplication::translate("SingleMachine", "\350\256\241\351\207\217\346\227\266\351\227\264", nullptr));

        label->setText(QApplication::translate("SingleMachine", "\350\260\203\346\234\272\346\227\266\351\227\264", nullptr));
        label_2->setText(QApplication::translate("SingleMachine", "\346\234\200\350\277\221\346\250\241\346\225\260", nullptr));
        groupBox_3->setTitle(QApplication::translate("SingleMachine", "\346\230\276\347\244\272\347\261\273\345\236\213", nullptr));
        checkBox_2->setText(QApplication::translate("SingleMachine", "\346\212\230\347\272\277\346\250\241\345\274\217", nullptr));
        checkBox_1->setText(QApplication::translate("SingleMachine", "\347\256\261\347\272\277\346\250\241\345\274\217", nullptr));
        label_21->setText(QApplication::translate("SingleMachine", "\346\250\241\346\254\241", nullptr));
        label_22->setText(QApplication::translate("SingleMachine", "\345\260\217\346\227\266", nullptr));
        groupBox_4->setTitle(QApplication::translate("SingleMachine", "\345\216\206\345\217\262\346\237\245\350\257\242", nullptr));
        label_10->setText(QApplication::translate("SingleMachine", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_11->setText(QApplication::translate("SingleMachine", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        groupBox_6->setTitle(QApplication::translate("SingleMachine", "\347\273\237\350\256\241\344\277\241\346\201\257", nullptr));
        label_14->setText(QApplication::translate("SingleMachine", "\346\250\241\346\225\260", nullptr));
        label_13->setText(QApplication::translate("SingleMachine", "\345\235\207\345\200\274", nullptr));
        label_16->setText(QApplication::translate("SingleMachine", "\346\226\271\345\267\256", nullptr));
        toolButton_5->setText(QApplication::translate("SingleMachine", "\350\256\241\347\256\227", nullptr));
        groupBox_7->setTitle(QApplication::translate("SingleMachine", "\347\233\221\346\216\247\350\256\276\347\275\256", nullptr));
        label_19->setText(QApplication::translate("SingleMachine", "\344\270\212\351\231\220", nullptr));
        label_20->setText(QApplication::translate("SingleMachine", "\344\270\213\351\231\220", nullptr));
        toolButton_3->setText(QApplication::translate("SingleMachine", "\347\246\201\347\224\250/\345\220\257\347\224\250", nullptr));
        groupBox_8->setTitle(QApplication::translate("SingleMachine", "\346\243\200\346\265\213\346\240\207\350\256\260", nullptr));
        toolButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SingleMachine: public Ui_SingleMachine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEMACHINE_H
