#include "HscRealTimeMonitor.h"
#include "ui_HscRealTimeMonitor.h"

#include "HscOnlineMonitor.h"
#include "HscCollectSettingModel.h"

HscRealTimeMonitor::HscRealTimeMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscRealTimeMonitor),
    m_monitorSetting(new HscMonitorSetting(this))
{
    ui->setupUi(this);

    initView();
    loadCollectSetting();
    initSignalSlots();
}

HscRealTimeMonitor::~HscRealTimeMonitor()
{
    delete ui;
}

void HscRealTimeMonitor::startPlot()
{
    if (!m_plotting) {
        qDebug() << "start plot";
        m_updateTimer.start(50);
        m_plotting = true;
    } else {
        qDebug() << "stop plot";
        m_updateTimer.stop();
        m_plotting = false;
    }
}

void HscRealTimeMonitor::setAisxValue(int x, int y)
{
    ui->plot->xAxis->setRangeUpper(x);
    ui->plot->yAxis->setRangeUpper(y);
    ui->plot->replot();
}

void HscRealTimeMonitor::monitorSetting()
{
    if (m_monitorSetting->isVisible()) {
        m_monitorSetting->setVisible(false);
    } else {
        m_monitorSetting->setVisible(true);
    }

}

void HscRealTimeMonitor::initView()
{
    // 初始化界面
    ui->PlotControlsBox->setVisible(false);
    // 监控设置界面
    initMonitorView();
    // 绘图界面
    setupPlot();
}

void HscRealTimeMonitor::initMonitorView()
{
    // 监控设置界面
    ui->curveLayout->addWidget(m_monitorSetting);
    m_monitorSetting->setVisible(false);
    m_monitorRects.resize(10);
    for (auto &item : m_monitorRects) {
        item.resize(4);
    }
}

void HscRealTimeMonitor::setupPlot()
{

    // 清空
    ui->plot->clearItems();

    /** See QCustomPlot examples / styled demo **/
    // X Axis
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->plot->xAxis->setTicker(timeTicker);
    ui->plot->xAxis->setLabel(tr(u8"时间[ms]"));
    ui->plot->axisRect()->setupFullAxesBox();
    // Range
    ui->plot->xAxis->setRangeLower(0);
    ui->plot->xAxis->setRange(0, 3000);

    // Y Axis
    ui->plot->yAxis->setLabel(tr(u8"压力[MPa]"));
    ui->plot->yAxis->rescale(true);
    // Range
    ui->plot->yAxis->setRangeLower(0);
    ui->plot->yAxis->setRange(0, 300);
    // User can change Y axis tick step with a spin box
    //    ui->plot->yAxis->setAutoTickStep (false);
    //    ui->plot->yAxis->(ui->spinYStep->value());

    // User interactions Drag and Zoom are allowed only on X axis, Y is fixed manually by UI control
    //    ui->plot->setInteraction (QCP::iRangeDrag, true);
    //    ui->plot->setInteraction (QCP::iRangeZoom, true);
    //    ui->plot->setInteraction (QCP::iSelectPlottables, true);
    //    ui->plot->setInteraction (QCP::iSelectLegend, true);
    //    ui->plot->axisRect()->setRangeDrag (Qt::Horizontal);
    //    ui->plot->axisRect()->setRangeZoom (Qt::Horizontal);
    // 选框放大
    //    ui->plot->selectionRect()->setPen(QPen(Qt::black, 1, Qt::DashLine));
    //    ui->plot->selectionRect()->setBrush(QBrush(QColor(0, 0, 100, 50)));
    //    ui->plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    // Legend 图例说明
    //    QFont legendFont;
    //    legendFont.setPointSize (9);
    //    ui->plot->legend->setVisible (true);
    //    ui->plot->legend->setFont (legendFont);
    //    ui->plot->legend->setBrush (gui_colors[3]);
    //    ui->plot->legend->setBorderPen (gui_colors[2]);
    // By default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement
    //    ui->plot->axisRect()->insetLayout()->setInsetAlignment (0, Qt::AlignTop|Qt::AlignRight);
}

void HscRealTimeMonitor::loadCollectSetting()
{
    // 曲线颜色
    auto &sensorSetting  = HscCollectSettingModel::sensorsModel;
    m_lineColors.resize(sensorSetting.count());
    for (auto i(0); i < sensorSetting.count(); ++i) {
        m_lineColors[i] = QColor(sensorSetting[i].curveColor);
    }
}

void HscRealTimeMonitor::initSignalSlots()
{
    // Wheel over plot when plotting
    connect (ui->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(onMouseWheelInPlot (QWheelEvent*)));

    // Channel selection
    QObject::connect (ui->plot, SIGNAL(selectionChangedByUser()), this, SLOT(channel_selection()));
    QObject::connect (ui->plot, SIGNAL(legendDoubleClick (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)), this, SLOT(legend_double_click (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));

    // Connect update timer to replot slot
    connect(&m_updateTimer, SIGNAL(timeout()), this, SLOT(replot()));

    // 选框
    QObject::connect(ui->plot, &QCustomPlot::mousePress, this, &HscRealTimeMonitor::onMousePressInPlot);
    QObject::connect(ui->plot, &QCustomPlot::mouseMove, this, &HscRealTimeMonitor::onMouseMoveInPlot);
    QObject::connect(ui->plot, &QCustomPlot::mouseRelease, this, &HscRealTimeMonitor::onMouseReleaseInPlot);

    // 设置
    connect(m_monitorSetting, &HscMonitorSetting::currentChannel, this, [&](int channel){
        m_selectedChannel = channel;
        qDebug() << m_selectedChannel;
    });

}

void HscRealTimeMonitor::updateStatus(QString status)
{
    if (status == "start") {
        ui->tbtn_clampSignal->setStyleSheet("background:red");
        ui->tbtn_injeFinishTB->setStyleSheet("background:green");
    } else if (status == "stop") {
        ui->plot->clearGraphs();
        ui->tbtn_clampSignal->setStyleSheet("background:green");
        ui->tbtn_injeFinishTB->setStyleSheet("background:red");
    }
}

void HscRealTimeMonitor::plotCurve(HscCollectDataModel data)
{

    int data_members = 0;
    int channel = 0;
    volatile bool you_shall_NOT_PASS = false;

    /* When a fast baud rate is set (921kbps was the first to starts to bug),
       this method is called multiple times (2x in the 921k tests), so a flag
       is used to throttle
       TO-DO: Separate processes, buffer data (1) and process data (2) */
    while (you_shall_NOT_PASS) { }
    you_shall_NOT_PASS = true;

    if (m_plotting) {
        // 绘制通道
        m_channels = 0;
        // 传感器数量
        data_members = HscCollectSettingModel::sensorsModel.count();
        // 解析数据
        for (auto i(0); i < data_members; i++) {
            // 对比绘制数目与
            while(ui->plot->plottableCount() <= channel) {
                // 新增channel
                ui->plot->addGraph();
                ui->plot->graph()->setPen (m_lineColors[m_channels]);
                ui->plot->graph()->setName (QString("ch %1").arg(i));
                if(ui->plot->legend->item(m_channels)) {
                    ui->plot->legend->item (m_channels)->setTextColor(m_lineColors[m_channels]);
                }
                ui->listWidget_Channels->addItem(ui->plot->graph()->name());
                ui->listWidget_Channels->item(channel)->setForeground(QBrush(m_lineColors[m_channels]));
                m_channels++;
            }


            // graph添加数据
            ui->plot->graph(channel)->addData(data.m_moment, (data.m_data)[channel]);

            // 输入数据对应channel数量
            channel++;
            // 曲线显隐
            if (HscCollectSettingModel::sensorsModel[i].enable == 0) {
                ui->plot->graph(i)->setVisible(false);
            } else {
                ui->plot->graph(i)->setVisible(true);
            }

        }

        // 数据点数
        m_dataPointNumber++;
      }
    you_shall_NOT_PASS = false;
}

void HscRealTimeMonitor::replot()
{
//    ui->plot->xAxis->setRange(m_dataPointNumber - ui->spinPoints->value(), m_dataPointNumber);
    ui->plot->replot();
}

void HscRealTimeMonitor::plotItemRect()
{
    // 根据监控设置模型绘制选框
    for (auto i(0); i<10; ++i) {
        auto &monitorItem = HscMonitorSettingModel::monitorSettingModel[i];
        for (auto j(0); j<4; ++j) {
            auto &eigenvalueItem = monitorItem.listOfEigenvalueMonitor[j];
            if (eigenvalueItem.enable == 0) {
                if (m_monitorRects[i][j]) {
                    m_monitorRects[i][j]->setVisible(false);
                }
                continue;
            } else {
                if (m_monitorRects[i][j] == nullptr) {
                    m_monitorRects[i][j] = new QCPItemRect(ui->plot);
                    m_monitorRects[i][j]->setSelectable(true);
                }
                QPen pen;
                pen.setColor(QColor(HscCollectSettingModel::sensorsModel[i].curveColor));
                m_monitorRects[i][j]->setPen(pen);
                // 设置选中的rect
                if (i == m_selectedChannel) {
                    m_currentRect = m_monitorRects[i][j];
                    m_selectedMonitor = j;
                }

//                qDebug() << "plot";
                m_monitorRects[i][j]->setVisible(true);
                m_monitorRects[i][j]->topLeft->setCoords(eigenvalueItem.lowerTime, eigenvalueItem.upperPres);
                m_monitorRects[i][j]->bottomRight->setCoords(eigenvalueItem.upperTime, eigenvalueItem.lowerPres);
                ui->plot->replot();
            }
        }
    }
}

void HscRealTimeMonitor::statisticData(QList<HscDataAnalysisModel> *list)
{
//    qDebug() << "statistic data";
    ++m_totalCount;
    if (list->last().good == true) {
        ++m_goodCount;
    } else {
        ++m_badCount;
    }

    ui->lEdt_total->setText(QString::number(m_totalCount));
    ui->lEdt_good->setText(QString::number(m_goodCount));
    ui->lEdt_bad->setText(QString::number(m_badCount));

}

void HscRealTimeMonitor::on_spinPoints_valueChanged (int arg1)
{
    Q_UNUSED(arg1)
//    ui->plot->xAxis->setRange(dataPointNumber - ui->spinPoints->value(), dataPointNumber);
//    ui->plot->xAxis->setRange(0, ui->spinPoints->value());
    ui->plot->replot();
}

void HscRealTimeMonitor::on_spinYStep_valueChanged(int arg1)
{
    ui->plot->yAxis->ticker()->setTickCount(arg1);
    ui->plot->replot();
    ui->spinYStep->setValue(ui->plot->yAxis->ticker()->tickCount());
}

void HscRealTimeMonitor::on_spinAxesMin_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeLower (arg1);
    ui->plot->replot();
}

void HscRealTimeMonitor::on_spinAxesMax_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeUpper (arg1);
    ui->plot->replot();
}

void HscRealTimeMonitor::on_pushButton_AutoScale_clicked()
{
    ui->plot->yAxis->rescale(true);
    ui->spinAxesMax->setValue(int(ui->plot->yAxis->range().upper) + int(ui->plot->yAxis->range().upper*0.1));
    ui->spinAxesMin->setValue(int(ui->plot->yAxis->range().lower) + int(ui->plot->yAxis->range().lower*0.1));
}

void HscRealTimeMonitor::on_listWidget_Channels_itemDoubleClicked(QListWidgetItem *item)
{
    int graphIdx = ui->listWidget_Channels->currentRow();

    if(ui->plot->graph(graphIdx)->visible())
    {
        ui->plot->graph(graphIdx)->setVisible(false);
        item->setBackgroundColor(Qt::black);
    }
    else
    {
        ui->plot->graph(graphIdx)->setVisible(true);
        item->setBackground(Qt::NoBrush);
    }
    ui->plot->replot();
}

void HscRealTimeMonitor::on_pushButton_ResetVisible_clicked()
{
    for(int i=0; i<ui->plot->graphCount(); i++)
    {
        ui->plot->graph(i)->setVisible(true);
        ui->listWidget_Channels->item(i)->setBackground(Qt::NoBrush);
    }
}

void HscRealTimeMonitor::on_savePNGButton_clicked()
{
//    ui->plot->savePng(QString::number(m_dataPointNumber) + ".png", 1920, 1080, 2, 50);
}

void HscRealTimeMonitor::onMouseWheelInPlot(QWheelEvent *event)
{
//    QWheelEvent inverted_event = QWheelEvent(event->posF(), event->globalPosF(),
//                                             -event->pixelDelta(), -event->angleDelta(),
//                                             0, Qt::Vertical, event->buttons(), event->modifiers());
//    QApplication::sendEvent (ui->spinPoints, &inverted_event);
}

void HscRealTimeMonitor::onMousePressInPlot(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {

        if (!m_currentRect) {
            return;
        }
        QPointF point = event->pos();
        double key = ui->plot->xAxis->pixelToCoord(point.x());
        double value = ui->plot->yAxis->pixelToCoord(point.y());
        emit updateTopleft(m_selectedChannel, m_selectedMonitor, value, key);
        emit updateBottomright(m_selectedChannel, m_selectedMonitor, value, key);
    }
}

void HscRealTimeMonitor::onMouseMoveInPlot(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (!m_currentRect) {
            return;
        }
        QPointF point = event->pos();
        double key = ui->plot->xAxis->pixelToCoord(point.x());
        double value = ui->plot->yAxis->pixelToCoord(point.y());
        emit updateBottomright(m_selectedChannel, m_selectedMonitor, value, key);
        ui->plot->replot();
    }
}

void HscRealTimeMonitor::onMouseReleaseInPlot(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
//        qDebug () << "release exec";
//        qDebug() << ui->plot->xAxis->pixelToCoord(m_rect.left());
//        qDebug() << ui->plot->xAxis->pixelToCoord(m_rect.top());
//        qDebug() << ui->plot->xAxis->pixelToCoord(m_rect.right());
//        qDebug() << ui->plot->xAxis->pixelToCoord(m_rect.bottom());
    }
}

void HscRealTimeMonitor::channel_selection (void)
{
    /* synchronize selection of graphs with selection of corresponding legend items */
     for (int i = 0; i < ui->plot->graphCount(); i++)
       {
         QCPGraph *graph = ui->plot->graph(i);
         QCPPlottableLegendItem *item = ui->plot->legend->itemWithPlottable (graph);
         if (item->selected())
           {
             item->setSelected (true);
//             graph->set (true);
           }
         else
           {
             item->setSelected (false);
//             graph->setSelected (false);
           }
       }
}

void HscRealTimeMonitor::legend_double_click(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event)
{
    Q_UNUSED (legend)
    Q_UNUSED(event)
    /* Only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0) */
    if (item)
      {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText (this, "修改名称", "名称:", QLineEdit::Normal, plItem->plottable()->name(), &ok, Qt::Popup);
        if (ok)
          {
            plItem->plottable()->setName(newName);
            for(int i=0; i<ui->plot->graphCount(); i++)
            {
                ui->listWidget_Channels->item(i)->setText(ui->plot->graph(i)->name());
            }
            ui->plot->replot();
          }
    }
}
