#include "HscPeakPressureTendency.h"
#include "ui_HscPeakPressureTendency.h"

#include <QDebug>

HscPeakPressureTendency::HscPeakPressureTendency(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HscPeakPressureTendency)
{
    ui->setupUi(this);

    initView();
    loadCollectSetting();
    initSignalSlots();
}

HscPeakPressureTendency::~HscPeakPressureTendency()
{
    delete ui;
}

void HscPeakPressureTendency::startPlot()
{
    if (!m_plotting) {
//        qDebug() << "start plot";
        m_updateTimer.start(50);
        m_plotting = true;
    } else {
//        qDebug() << "stop plot";
        m_updateTimer.stop();
        m_plotting = false;
    }
}

void HscPeakPressureTendency::setAisxValue(int y)
{
    ui->plot->yAxis->setRangeUpper(y);
    ui->plot->replot();
}

void HscPeakPressureTendency::initView()
{
    // 初始化界面
    ui->PlotControlsBox->setVisible(false);
    // 绘图界面
    setupPlot();
}

void HscPeakPressureTendency::setupPlot()
{
    /* Remove everything from the plot */
    ui->plot->clearItems();

    // 初始化曲线参数
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");
    ui->plot->xAxis->setTicker(timeTicker);
    ui->plot->xAxis->setLabel(tr(u8"模次"));
    ui->plot->axisRect()->setupFullAxesBox();

    ui->plot->xAxis->setRange(0, 100);
    ui->plot->yAxis->setRange(0, 300);
    ui->plot->yAxis->setLabel(tr(u8"压力[MPa]"));

    /* Range */
    //ui->plot->yAxis->setRange (ui->spinAxesMin->value(), ui->spinAxesMax->value());
    /* User can change Y axis tick step with a spin box */
    //ui->plot->yAxis->setAutoTickStep (false);
    //ui->plot->yAxis->(ui->spinYStep->value());

    /* User interactions Drag and Zoom are allowed only on X axis, Y is fixed manually by UI control */
    ui->plot->setInteraction (QCP::iRangeDrag, true);
    ui->plot->setInteraction (QCP::iRangeZoom, true);
    ui->plot->setInteraction (QCP::iSelectPlottables, true);
    ui->plot->setInteraction (QCP::iSelectLegend, true);
    //    ui->plot->axisRect()->setRangeDrag (Qt::Horizontal);
    //    ui->plot->axisRect()->setRangeZoom (Qt::Horizontal);

    /* Legend */
    //    QFont legendFont;
    //    legendFont.setPointSize (9);
    //    ui->plot->legend->setVisible (true);
    //    ui->plot->legend->setFont (legendFont);
    //    ui->plot->legend->setBrush (gui_colors[3]);
    //    ui->plot->legend->setBorderPen (gui_colors[2]);
    /* By default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement */
    //    ui->plot->axisRect()->insetLayout()->setInsetAlignment (0, Qt::AlignTop|Qt::AlignRight);
}

void HscPeakPressureTendency::loadCollectSetting()
{
    // 曲线颜色
    auto &sensorSetting  = HscCollectSettingModel::sensorsModel;
    m_lineColors.resize(sensorSetting.count());
    for (auto i(0); i < sensorSetting.count(); ++i) {
        m_lineColors[i] = QColor(sensorSetting[i].curveColor);
    }
}

void HscPeakPressureTendency::initSignalSlots()
{
    /* Wheel over plot when plotting */
    connect (ui->plot, SIGNAL(mouseWheel (QWheelEvent*)), this, SLOT(onMouseWheelInPlot (QWheelEvent*)));

    /* Slot for printing coordinates */
    connect (ui->plot, SIGNAL(mouseMove (QMouseEvent*)), this, SLOT(onMouseMoveInPlot (QMouseEvent*)));

    /* Channel selection */
    QObject::connect (ui->plot, SIGNAL(selectionChangedByUser()), this, SLOT(channel_selection()));
    QObject::connect (ui->plot, SIGNAL(legendDoubleClick (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)), this, SLOT(legend_double_click (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));

    /* Connect update timer to replot slot */
    connect (&m_updateTimer, SIGNAL (timeout()), this, SLOT (replot()));
}

void HscPeakPressureTendency::plotCurve(QVector<double> data)
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
        /* Get size of received list */
        data_members = HscCollectSettingModel::sensorsModel.count();

        /* Parse data */
        for (auto i(0); i < data_members; i++) {
            /* Update number of axes if needed */
            while (ui->plot->plottableCount() <= channel) {
                /* Add new channel data */
                ui->plot->addGraph();
                ui->plot->graph()->setPen (m_lineColors[i]);
                ui->plot->graph()->setName (QString("Channel %1").arg(channel));
                if(ui->plot->legend->item(channel)) {
                    ui->plot->legend->item(channel)->setTextColor(m_lineColors[i]);
                }
                ui->listWidget_Channels->addItem(ui->plot->graph()->name());
                ui->listWidget_Channels->item(channel)->setForeground(QBrush(m_lineColors[i]));

                ++m_channels;
            }

            ui->plot->graph(i)->addData(m_count, data[i]);
            /* Increment data number and channel */
            channel++;

            if (HscCollectSettingModel::sensorsModel[i].enable == 0) {
                ui->plot->graph(i)->setVisible(false);
            } else {
                ui->plot->graph(i)->setVisible(true);
            }
        }
        m_dataPointNumber++;
    }
    you_shall_NOT_PASS = false;
}

void HscPeakPressureTendency::replot()
{
//    if (m_dataPointNumber - ui->spinPoints->value() < 0) {
//        ui->plot->xAxis->setRange(0, ui->spinPoints->value());
//    } else {
//        ui->plot->xAxis->setRange(m_dataPointNumber - ui->spinPoints->value(), m_dataPointNumber);
//    }
    ui->plot->replot();
}

void HscPeakPressureTendency::updateChannelVisible()
{
    for (auto i(0); i<m_channels; ++i) {
        if (HscCollectSettingModel::sensorsModel[i].enable == 0) {
            ui->plot->graph(i)->setVisible(false);
        } else {
            ui->plot->graph(i)->setVisible(true);
        }
    }
}

void HscPeakPressureTendency::plotTendencyCurve(QList<HscDataAnalysisModel> *list)
{
//    qDebug() << "plot peak pressure";
    m_totalData = list;
    m_count = list->count();
    auto &data = list->last();
    // 峰值压力
    plotCurve(data.peakPressures);

    if (m_count == 100) {
        ui->plot->clearGraphs();
        m_channels = 0;
    }
}

void HscPeakPressureTendency::on_spinPoints_valueChanged (int arg1)
{
    Q_UNUSED(arg1)
    //    ui->plot->xAxis->setRange(dataPointNumber - ui->spinPoints->value(), dataPointNumber);
    ui->plot->xAxis->setRange(0, ui->spinPoints->value());
    ui->plot->replot();
}

void HscPeakPressureTendency::on_spinYStep_valueChanged(int arg1)
{
    ui->plot->yAxis->ticker()->setTickCount(arg1);
    ui->plot->replot();
    ui->spinYStep->setValue(ui->plot->yAxis->ticker()->tickCount());
}

void HscPeakPressureTendency::on_spinAxesMin_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeLower (arg1);
    ui->plot->replot();
}

void HscPeakPressureTendency::on_spinAxesMax_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeUpper (arg1);
    ui->plot->replot();
}

void HscPeakPressureTendency::on_pushButton_AutoScale_clicked()
{
    ui->plot->yAxis->rescale(true);
    ui->spinAxesMax->setValue(int(ui->plot->yAxis->range().upper) + int(ui->plot->yAxis->range().upper*0.1));
    ui->spinAxesMin->setValue(int(ui->plot->yAxis->range().lower) + int(ui->plot->yAxis->range().lower*0.1));
}

void HscPeakPressureTendency::on_listWidget_Channels_itemDoubleClicked(QListWidgetItem *item)
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

void HscPeakPressureTendency::on_pushButton_ResetVisible_clicked()
{
    for(int i=0; i<ui->plot->graphCount(); i++)
    {
        ui->plot->graph(i)->setVisible(true);
        ui->listWidget_Channels->item(i)->setBackground(Qt::NoBrush);
    }
}

void HscPeakPressureTendency::on_savePNGButton_clicked()
{
    //    ui->plot->savePng(QString::number(m_dataPointNumber) + ".png", 1920, 1080, 2, 50);
}

void HscPeakPressureTendency::onMouseWheelInPlot(QWheelEvent *event)
{
    QWheelEvent inverted_event = QWheelEvent(event->posF(), event->globalPosF(),
                                             -event->pixelDelta(), -event->angleDelta(),
                                             0, Qt::Vertical, event->buttons(), event->modifiers());
    QApplication::sendEvent (ui->spinPoints, &inverted_event);
}

void HscPeakPressureTendency::onMouseMoveInPlot(QMouseEvent *event)
{
    int xx = int(ui->plot->xAxis->pixelToCoord(event->x()));
    int yy = int(ui->plot->yAxis->pixelToCoord(event->y()));
    QString coordinates("X: %1 Y: %2");
    coordinates = coordinates.arg(xx).arg(yy);
    //    ui->statusBar->showMessage(coordinates);
}

void HscPeakPressureTendency::channel_selection (void)
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

void HscPeakPressureTendency::legend_double_click(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event)
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
