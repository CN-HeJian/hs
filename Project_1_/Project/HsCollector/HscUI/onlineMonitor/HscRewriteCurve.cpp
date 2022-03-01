#include "HscRewriteCurve.h"
#include "ui_HscRewriteCurve.h"

#include <QDebug>

HscRewriteCurve::HscRewriteCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscRewriteCurve)
{
    ui->setupUi(this);

    initView();
    loadCollectSetting();
    initSignalSlots();
}

HscRewriteCurve::~HscRewriteCurve()
{
    delete ui;
}

void HscRewriteCurve::startPlot()
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

void HscRewriteCurve::setAisxValue(int x, int y)
{
    ui->plot->xAxis->setRangeUpper(x);
    ui->plot->yAxis->setRangeUpper(y);
    ui->plot->replot();
}

void HscRewriteCurve::initView()
{
    // 初始化界面
    ui->PlotControlsBox->setVisible(false);
    // 绘图界面
    setupPlot();
}

void HscRewriteCurve::plotRewriteCurve(QList<QList<HscCollectDataModel>> *list)
{
    qDebug() << "rewrite";
    qDebug() << ui->plot->plottableCount();
    m_totalData = list;
    // 重写
    if (m_rewriteCount == m_displayCount) {
        ui->plot->clearGraphs();
        qDebug () << "clear";
        m_channels = 0;
        m_rewriteCount = 0;
    }

    // 绘制最新一条
    auto &data = list->last();
    for (auto i(0); i < data.count(); ++i) {
        plotCurve(data[i]);
    }
    // 存储到数据库
    emit saveData(&(list->last()));
    ++m_rewriteCount;
}

void HscRewriteCurve::setupPlot()
{
    ui->plot->clearItems();

    // 初始化曲线参数
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->plot->xAxis->setTicker(timeTicker);
    ui->plot->xAxis->setLabel(tr(u8"时间[ms]"));
    ui->plot->axisRect()->setupFullAxesBox();

    ui->plot->xAxis->setRange(0, 3000);
    ui->plot->yAxis->setRange(0, 300);
    ui->plot->yAxis->setLabel(tr(u8"压力[MPa]"));


    /* User interactions Drag and Zoom are allowed only on X axis, Y is fixed manually by UI control */
    ui->plot->setInteraction (QCP::iRangeDrag, true);
    ui->plot->setInteraction (QCP::iRangeZoom, true);
    ui->plot->setInteraction (QCP::iSelectPlottables, true);
    ui->plot->setInteraction (QCP::iSelectLegend, true);
//    ui->plot->axisRect()->setRangeDrag (Qt::Horizontal);
//    ui->plot->axisRect()->setRangeZoom (Qt::Horizontal);
    // 选框放大
//    ui->plot->selectionRect()->setPen(QPen(Qt::black, 1, Qt::DashLine));
//    ui->plot->selectionRect()->setBrush(QBrush(QColor(0, 0, 100, 50)));
//    ui->plot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void HscRewriteCurve::loadCollectSetting()
{
    // 曲线颜色
    auto &sensorSetting  = HscCollectSettingModel::sensorsModel;
    m_lineColors.resize(sensorSetting.count());
    for (auto i(0); i < sensorSetting.count(); ++i) {
        m_lineColors[i] = QColor(sensorSetting[i].curveColor);
    }
}

void HscRewriteCurve::initSignalSlots()
{
    /* Wheel over plot when plotting */
    connect (ui->plot, SIGNAL(mouseWheel (QWheelEvent*)), this, SLOT(onMouseWheelInPlot (QWheelEvent*)));
    connect (ui->plot, SIGNAL(mouseMove (QMouseEvent*)), this, SLOT(onMouseMoveInPlot (QMouseEvent*)));

    /* Channel selection */
    QObject::connect (ui->plot, SIGNAL(selectionChangedByUser()), this, SLOT(channel_selection()));
    QObject::connect (ui->plot, SIGNAL(legendDoubleClick (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)), this, SLOT(legend_double_click (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));

    /* Connect update timer to replot slot */
    connect (&m_updateTimer, SIGNAL(timeout()), this, SLOT(replot()));
}

void HscRewriteCurve::plotCurve(HscCollectDataModel data)
{

    int data_members = 0;
    volatile bool you_shall_NOT_PASS = false;

    /* When a fast baud rate is set (921kbps was the first to starts to bug),
       this method is called multiple times (2x in the 921k tests), so a flag
       is used to throttle
       TO-DO: Separate processes, buffer data (1) and process data (2) */
    while (you_shall_NOT_PASS) { }
    you_shall_NOT_PASS = true;

    if (m_plotting) {
        data_members = HscCollectSettingModel::sensorsModel.count();
        for (auto i(0); i < data_members; i++) {
            while (ui->plot->plottableCount() <= (data_members*m_rewriteCount +i)) {
                ui->plot->addGraph();
                ui->plot->graph()->setPen (m_lineColors[i]);
                ui->plot->graph()->setName (QString("Channel %1").arg(m_channels));
                if(ui->plot->legend->item(m_channels)) {
                    ui->plot->legend->item(m_channels)->setTextColor (m_lineColors[i]);
                }
                ui->listWidget_Channels->addItem(ui->plot->graph()->name());
                ui->listWidget_Channels->item(m_channels)->setForeground(QBrush(m_lineColors[i]));
                ++m_channels;
              }

            // graph添加数据
            ui->plot->graph(i+m_rewriteCount*data_members)->addData (data.m_moment, (data.m_data)[i]);

            if (HscCollectSettingModel::sensorsModel[i].enable == 0) {
                ui->plot->graph(i+m_rewriteCount*data_members)->setVisible(false);
            } else {
                ui->plot->graph(i+m_rewriteCount*data_members)->setVisible(true);
            }
        }
      }
    you_shall_NOT_PASS = false;
}

void HscRewriteCurve::replot()
{
//    ui->plot->xAxis->setRange(m_dataPointNumber - ui->spinPoints->value(), m_dataPointNumber);
    ui->plot->replot();
}

void HscRewriteCurve::updateChannelVisible()
{
    for (auto i(0); i<m_channels; ++i) {
        int index = i % HscCollectSettingModel::sensorsModel.count();
        if (HscCollectSettingModel::sensorsModel[index].enable == 0) {
            ui->plot->graph(i)->setVisible(false);
        } else {
            ui->plot->graph(i)->setVisible(true);
        }
    }
}

void HscRewriteCurve::on_spinPoints_valueChanged (int arg1)
{
    Q_UNUSED(arg1)
//    ui->plot->xAxis->setRange(dataPointNumber - ui->spinPoints->value(), dataPointNumber);
    ui->plot->xAxis->setRange(0, ui->spinPoints->value());
    ui->plot->replot();
}

void HscRewriteCurve::on_spinYStep_valueChanged(int arg1)
{
    ui->plot->yAxis->ticker()->setTickCount(arg1);
    ui->plot->replot();
    ui->spinYStep->setValue(ui->plot->yAxis->ticker()->tickCount());
}

void HscRewriteCurve::on_spinAxesMin_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeLower (arg1);
    ui->plot->replot();
}

void HscRewriteCurve::on_spinAxesMax_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeUpper (arg1);
    ui->plot->replot();
}

void HscRewriteCurve::on_pushButton_AutoScale_clicked()
{
    ui->plot->yAxis->rescale(true);
    ui->spinAxesMax->setValue(int(ui->plot->yAxis->range().upper) + int(ui->plot->yAxis->range().upper*0.1));
    ui->spinAxesMin->setValue(int(ui->plot->yAxis->range().lower) + int(ui->plot->yAxis->range().lower*0.1));
}

void HscRewriteCurve::on_listWidget_Channels_itemDoubleClicked(QListWidgetItem *item)
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

void HscRewriteCurve::on_pushButton_ResetVisible_clicked()
{
    for(int i=0; i<ui->plot->graphCount(); i++)
    {
        ui->plot->graph(i)->setVisible(true);
        ui->listWidget_Channels->item(i)->setBackground(Qt::NoBrush);
    }
}

void HscRewriteCurve::on_savePNGButton_clicked()
{
//    ui->plot->savePng(QString::number(m_dataPointNumber) + ".png", 1920, 1080, 2, 50);
}

void HscRewriteCurve::onMouseWheelInPlot(QWheelEvent *event)
{
//    QWheelEvent inverted_event = QWheelEvent(event->posF(), event->globalPosF(),
//                                             -event->pixelDelta(), -event->angleDelta(),
//                                             0, Qt::Vertical, event->buttons(), event->modifiers());
//    QApplication::sendEvent (ui->spinPoints, &inverted_event);
}

void HscRewriteCurve::onMouseMoveInPlot(QMouseEvent *event)
{
    int xx = int(ui->plot->xAxis->pixelToCoord(event->x()));
    int yy = int(ui->plot->yAxis->pixelToCoord(event->y()));
    QString coordinates("X: %1 Y: %2");
    coordinates = coordinates.arg(xx).arg(yy);
    //    ui->statusBar->showMessage(coordinates);
}

void HscRewriteCurve::channel_selection (void)
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

void HscRewriteCurve::legend_double_click(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event)
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

void HscRewriteCurve::on_spinBox_valueChanged(int arg1)
{
    m_displayCount = arg1;
    m_rewriteCount = 0;
    m_channels = 0;
    ui->plot->clearGraphs();
}
