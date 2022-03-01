#ifndef HSCMACHINEANALYSISACTION_H
#define HSCMACHINEANALYSISACTION_H

#include <QWidget>
#include <machineAnalysis/HscMachineAnalysis.h>

namespace Ui {
class HscMachineAnalysisAction;
}

//request 需要设置一个请求类型的结构体

class HscMachineAnalysisAction : public QWidget
{
    Q_OBJECT

public:
    explicit HscMachineAnalysisAction(QWidget *parent = nullptr);
    ~HscMachineAnalysisAction();
public:
    void bindWidget(QWidget *widget);
private slots:
    void on_toolButton_2_clicked();

    //void on_toolButton_clicked();
    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();


    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();
    void on_toolButton_9_clicked();

    void on_toolButton_11_clicked();


    void on_toolButton_12_clicked();

    void on_toolButton_13_clicked();

private:
    Ui::HscMachineAnalysisAction *ui;
    HscMachineAnalysis *m_widget=nullptr;
    bool m_cycleplot = false;
     bool m_zoomLarge = false;
};

#endif // HSCMACHINEANALYSISACTION_H
