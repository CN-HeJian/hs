/********************************************************************************
** Form generated from reading UI file 'HscSettingAction.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSCSETTINGACTION_H
#define UI_HSCSETTINGACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HscSettingAction
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QToolButton *toolButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *HscSettingAction)
    {
        if (HscSettingAction->objectName().isEmpty())
            HscSettingAction->setObjectName(QString::fromUtf8("HscSettingAction"));
        HscSettingAction->resize(512, 78);
        horizontalLayout = new QHBoxLayout(HscSettingAction);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 3, -1, 3);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolButton = new QToolButton(HscSettingAction);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(40, 40));
        toolButton->setMaximumSize(QSize(40, 40));
        toolButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(toolButton, 0, Qt::AlignHCenter);

        label = new QLabel(HscSettingAction);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(331, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(HscSettingAction);

        QMetaObject::connectSlotsByName(HscSettingAction);
    } // setupUi

    void retranslateUi(QWidget *HscSettingAction)
    {
        HscSettingAction->setWindowTitle(QApplication::translate("HscSettingAction", "Form", nullptr));
        toolButton->setText(QApplication::translate("HscSettingAction", "...", nullptr));
        label->setText(QApplication::translate("HscSettingAction", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HscSettingAction: public Ui_HscSettingAction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSCSETTINGACTION_H
