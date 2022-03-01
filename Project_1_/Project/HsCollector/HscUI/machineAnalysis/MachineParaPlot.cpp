#include "machineParaPlot.h"

MachineParaPlot::MachineParaPlot(QWidget *parent) :
    QCustomPlot(parent)
{








    //this->setMouseControl(true);
    this->xAxis->setRange(0,80);
    this->yAxis->setRange(0,40);
    this->axisRect()->setupFullAxesBox();
   // this->xAxis->setLabel(u8"模次");
   // this->xAxis2->setLabel(u8"时间");
    this->xAxis2->setTickLabels(true);
//    QSharedDataPointer<QCPAxisTickerDateTime> dateTick(new QCPAxisTickerDateTime);
//    dateTick->setDateTimeFormat("hh:mm:ss");
//    this->xAxis2->setTickLabelRotation(35);
//    dateTick->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
//    this->xAxis->setTicker(dateTick);
    QSharedPointer<QCPAxisTickerDateTime> timer(new QCPAxisTickerDateTime);

 //this->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

  //设置时间格式

  //timer->setDateTimeFormat("yyyy-MM-dd hh:mm:ss");

  timer->setDateTimeFormat("yy-M-d h:mm");

  //设置时间轴 一共几格

  timer->setTickCount(6);

  //设置label 旋转35° 横着显示可能显示不全

  //this->xAxis->setTickLabelRotation(90);
this->legend->setVisible(true);


  timer->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);

  //设置坐标轴

  this->xAxis2->setTicker(timer);


    //this->yAxis->setLabel(u8"压力/Mpa");

   this->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    this->legend->setBorderPen(Qt::NoPen);
    this->legend->setFont(legendFont);
    this->legend->setBrush(QColor(255,255,255,0));//设置图例为透明
    this->rescaleAxes();

}





MachineParaPlot::~MachineParaPlot(){

}

#include <stdlib.h>
#include <math.h>

//测试用，生成正态分布数据
double MachineParaPlot::gaussrand()
{
    static double V1, V2, S;
    static int phase = 0;
    double X;

    if ( phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            V1 = 2 * U1 - 1;
            V2 = 2 * U2 - 1;
            S = V1 * V1 + V2 * V2;
        } while(S >= 1 || S == 0);

        X = V1 * sqrt(-2 * log(S) / S);
    } else
        X = V2 * sqrt(-2 * log(S) / S);

    phase = 1 - phase;

    return X;
}

void MachineParaPlot::setlegend(string label){
    this->legend->setVisible(true);
//    QCPBars *bars2 = new QCPBars(this->xAxis, this->yAxis);

//       bars2->setPen(QPen(QColor(138,180,219)));

//       bars2->setName("敏视达");
//        this->legend->addElement(0,1,this->legend->item(1));
//       this->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);
     this->graph(0)->setName(QString::fromStdString(label));
     this->replot();
}




void MachineParaPlot::setxAxis2Range(string low,string hight){
    string d_low,d_hight;
    for(int i=0;i<low.size();i++){
        if(low[i]==' '||low[i]=='-'||low[i]==':'){
            continue;
        }else{
            d_low +=low[i];
            d_hight +=hight[i];
        }
    }
    QString s_low = QString::fromStdString(d_low);
    QString s_hight = QString::fromStdString(d_hight);



    QDateTime l_initialTime = QDateTime::fromString(s_low, "yyyyMMddHHmmss");
    QDateTime h_initialTime = QDateTime::fromString(s_hight, "yyyyMMddHHmmss");

    int _low = l_initialTime.toTime_t();
    int _hight =  h_initialTime.toTime_t();

     this->xAxis2->setTickLabels(true);
    //this->xAxis2->setVisible(true);
    this->xAxis2->setRange(_low,_hight+(_hight-_low)*0.2);
    this->replot();
}

//折线图
void MachineParaPlot::plotData(vector<string> dates,vector<float> datas,unordered_set<string> detected){
    if(!datas.size()) {
        deleteAll();
//        QVector<double> x{0};
//        QVector<double> y{0};
//        this->addGraph();
//        this->graph()->setData(x,y);
//        this->replot();
        return;
    }
    deleteAll();

    this->xAxis->setTickLabelRotation(0);
    this->xAxis->setRange(1,datas.size()*1.2);//设置x轴范围


    float low_val = *min_element(datas.begin(),datas.end());
    float hight_val = *max_element(datas.begin(),datas.end());
    this->yAxis->setRange(low_val-(hight_val-low_val)*0.4,hight_val+(hight_val-low_val)*0.3); //设置y轴范围

    this->addGraph();

    QSharedPointer<QCPAxisTickerFixed> initTicker(new QCPAxisTickerFixed);
    initTicker->setTickStep(0.5);
    initTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
    graph(0)->keyAxis()->setTicker(initTicker);


    QVector<double> x(datas.size());
    QVector<double> y(datas.size());
    string day;
    string hour;
    string last_day = "";

    //检测点
    QVector<double> testX;
    QVector<double> testY;

    for(int i = 0; i<datas.size();i++)
    {

        x[i] = ((double)(i));
        y[i] = (datas[i]);
        string date = dates[i];

        if(detected.find(date)!=detected.end()){
            testX.push_back(i);
            testY.push_back(datas[i]);
        }

//        day = date.substr(8,2);
//        hour = date.substr(11,2);
//        if(hour=="09" && day!=last_day){
//            qDebug()<<"date:"<<QString::fromStdString(date)<<QString::fromStdString(last_day);
//            testX.push_back(i);
//            testY.push_back(datas[i]);
//            last_day = day;
//        }
    }


    this->graph()->setData(x,y);

    this->addGraph();
    this->graph(1)->setData(testX,testY);

    //42,140,254
    QPen graphPen;
    graphPen.setColor(QColor(0,0,255));
    graphPen.setWidthF(1);
    this->graph(0)->setPen(graphPen);
    this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare,5));


    QPen graphPen1;
    graphPen1.setColor(QColor(0,255,0));
    graphPen1.setWidthF(1.5);
    this->graph(1)->setLineStyle(QCPGraph::LineStyle::lsNone);
    this->graph(1)->setPen(graphPen1);
    this->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc,10));
    this->graph(1)->setName("Checked");

    this->setMouseControl(false);//鼠标不能移动
    this->replot();
}

//箱线图
void MachineParaPlot::BoxPlot(vector<float> currentShowDatas,vector<string> dates,int hour,string label){
    if(currentShowDatas.size()==0 || hour==0 ){

        return;
    }else{
        deleteAll();
        //存放计算结果的数组
        QVector<double> keys,minimumdatas,lowerQuartiledatas,mediandatas,upperQuartiledatas,maximumdatas;

        vector<QVector<double>> originData;
        vector<QString> ticker;

        string m_lastHour=dates[0].substr(8,2)+dates[0].substr(11,2);
        int hourNum = 0;
        vector<bool> visited(10000,false);
        QVector<double> tmp;
        vector<string> newTime={m_lastHour};
        for(int i=0;i<dates.size();i++){
            string curHour = dates[i].substr(8,2)+dates[i].substr(11,2);

            if(curHour!=m_lastHour){
                hourNum++;

            }


            if(hourNum!=0 && hourNum%hour==0 && visited[int(hourNum/hour)]==false ){ //4%3==1

                visited[int(hourNum/hour)] = true;
                if(tmp.size()<5){ //数量太少了
                    tmp.clear();
                    //continue;
                }else{
                    originData.push_back(tmp);
                    newTime.push_back(curHour);
                    tmp.clear();
                    ticker.push_back(QString::fromStdString(newTime[newTime.size()-2]));
                }
            }
            tmp.push_back(double(currentShowDatas[i]));

            m_lastHour = curHour;
        }

        for(int i=1;i<=originData.size();i++){
            keys.push_back(i);

            getStaticVal(originData[i-1],minimumdatas,lowerQuartiledatas,mediandatas,upperQuartiledatas,maximumdatas);
        }

        QCPStatisticalBox *statistical = new QCPStatisticalBox(this->xAxis, this->yAxis);
        statistical->setName(QString::fromStdString(label));
        QBrush boxBrush(QColor(122, 21, 132, 100));
        boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
        statistical->setBrush(boxBrush);
        statistical->setData(keys,minimumdatas,lowerQuartiledatas,mediandatas,upperQuartiledatas,maximumdatas);

        float low_val = *min_element(currentShowDatas.begin(),currentShowDatas.end());
        float hight_val = *max_element(currentShowDatas.begin(),currentShowDatas.end());
        this->yAxis->setRange(low_val-(hight_val-low_val)*0.1,hight_val+(hight_val-low_val)*0.1); //设置y轴范围
        this->xAxis->setSubTicks(false);
        this->xAxis->setRange(0,originData.size()+2);//设置x轴范围

        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

        //设置坐标轴的下标
        for(int i=1;i<=ticker.size();i++){
            textTicker->addTick(i,ticker[i-1]);
        }
        this->xAxis->setTickLabelRotation(90);
        this->xAxis->setTicker(textTicker);
        this->xAxis2->setTickLabels(false);
        this->setMouseControl(false);//鼠标不能动
        this->replot();
    }
}

//画出监控的上下限制
void MachineParaPlot::plotGraph2(double up,double down){

    int xMax = (int)this->xAxis->range().upper+1;

    if(this->graphCount()<2){
        this->addGraph();
        this->addGraph();
    }

    this->addGraph();

    QVector<double> x(xMax,0);
    QVector<double> y(xMax,0);
    QVector<double> z(xMax,0);
    for(int i = 0; i<xMax;i++)
    {
        x[i] = ((double)(i));
        y[i] = up;
        z[i] = down;
    }
    this->graph(2)->setData(x,y);

    this->addGraph();
    this->graph(3)->setData(x,z);

    this->graph(3)->setName("up");
    this->graph(2)->setName("down");

    QPen graphPen;
    graphPen.setColor(QColor(255,0,0));
    graphPen.setWidthF(2);
    this->graph(2)->setPen(graphPen);
   // this->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare,1));
    graphPen.setColor(QColor(255,0,0));
    this->graph(3)->setPen(graphPen);
    //this->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare,2));
     this->replot();
}

void MachineParaPlot::deleteGraph2(){
    this->removeGraph(3);
    this->replot();
    this->removeGraph(2);
    this->replot();

}




//更新曲线
void MachineParaPlot::updateCurrentShowData(){

}

//添加曲线
void MachineParaPlot::addCurrentShowData(){

}

//计算箱线图的特征值
void MachineParaPlot::getStaticVal(QVector<double> data,QVector<double> &minimumdatas,QVector<double>&lowerQuartiledatas,QVector<double>&mediandatas,QVector<double>&upperQuartiledatas,QVector<double>&maximumdatas){
    if(data.size()<5){
        return ;
    }
    sort(data.begin(),data.end());
    minimumdatas.push_back(*min_element(data.begin(),data.end()));
    maximumdatas.push_back(*max_element(data.begin(),data.end()));
    double m_media,m_lowerQuartiledatas,m_upperQuartiledatas;
    if(data.size()&1 == 1){
         m_media =  data[data.size()/2];
        if(((data.size()-1)/2)&1==0){//是偶数
             m_lowerQuartiledatas = (data[((data.size()-1)/2)/2]+data[((data.size()-1)/2)/2+1])/2;
             m_upperQuartiledatas = (data[((data.size()-1)/2)/2+(data.size()-1)/2+1]+data[((data.size()-1)/2)/2+1+(data.size()-1)/2+1])/2;
        }else{//是基数
             m_lowerQuartiledatas = data[((data.size()-1)/2)/2];
             m_upperQuartiledatas = data[((data.size()-1)/2)/2+(data.size()-1)/2+1];
        }
    }else{
         m_media =  (data[data.size()/2]+data[data.size()/2-1])/2;
        if(((data.size())/2)&1==0){//是偶数
             m_lowerQuartiledatas = (data[((data.size())/2)/2]+data[((data.size())/2)/2-1])/2;
             m_upperQuartiledatas = (data[((data.size())/2)/2+data.size()/2]+data[((data.size())/2)/2-1+data.size()/2])/2;
        }else{//是基数
             m_lowerQuartiledatas = data[((data.size())/2)/2];
             m_upperQuartiledatas = data[((data.size())/2)/2+(data.size())/2];
        }
    }
    mediandatas.push_back(m_media);
    lowerQuartiledatas.push_back(m_lowerQuartiledatas);
    upperQuartiledatas.push_back(m_upperQuartiledatas);
}

//图例和曲线共同显示高亮
void MachineParaPlot::comformity(){
    //this->QCPStatisticalBox
    for (int i=0; i<this->graphCount(); ++i)
    {
        QCPGraph *graph = this->graph(i);
            QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);

            if (item->selected() || graph->selected())
            {
                item->setSelected(true);
                QPen graphPen;
                graphPen.setWidth(2);
                graphPen.setColor(QColor(122,21,132));
                graph->selectionDecorator()->setPen(graphPen);
                graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
            }
    }
    for(int i=0;i<this->plottableCount();++i){
        QCPPlottableLegendItem *item = this->legend->itemWithPlottable(this->plottable(i));
        if(this->plottable(i)->selected()||item->selected()){
            item->setSelected(true);
        }
    }
}

//删除选中曲线
void MachineParaPlot::deleteSelectedGraph(){
    for (int i=0; i<this->graphCount(); ++i)
    {
        QCPGraph *graph = this->graph(i);
        if (graph->selected())
        {
            this->graph(i)->data().data()->clear();
            this->removeGraph(i);
        }
    }
    for(int i=0;i<this->plottableCount();++i){
        if(this->plottable(i)->selected()){
            this->removePlottable(i);
        }
    }
    this->replot();
}

//删除图层中的全部曲线,包括箱线图
void MachineParaPlot::deleteAll(){
    this->clearGraphs();
    this->clearPlottables();
    this->replot();
}


//********************************************************************INIT***********************************************************************//

//********************************************************************INIT***********************************************************************//

void MachineParaPlot::setMouseControl(bool enable)
{
    if(enable)
    {
        // make left and bottom axes always transfer their ranges to right and top axes:
        connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), this->xAxis2, SLOT(setRange(QCPRange)));
        connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));

        this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                              QCP::iSelectLegend | QCP::iSelectPlottables);
    }
    else
    {
        disconnect(this->xAxis,SIGNAL(rangeChanged(QCPRange)),0,0);
        disconnect(this->yAxis,SIGNAL(rangeChanged(QCPRange)),0,0);
        this->setInteractions(QCP::Interaction(!QCP::iRangeDrag | !QCP::iRangeZoom | !QCP::iSelectAxes |
                                               !QCP::iSelectLegend | !QCP::iSelectPlottables));
    }
}

void MachineParaPlot::selectionChanged()
{
    /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            this->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        this->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            this->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        this->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<this->graphCount(); ++i)
    {
        QCPGraph *graph = this->graph(i);
        QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }

}

void MachineParaPlot::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeDrag(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeDrag(this->yAxis->orientation());
    else
        this->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}


void MachineParaPlot::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->yAxis->orientation());
    else
        this->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MachineParaPlot::titleDoubleClick(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
    {
        // Set the plot title by double clicking on it
        bool ok;
        QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
        if (ok)
        {
            title->setText(newTitle);
            this->replot();
        }
    }
}

void MachineParaPlot::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // Set an axis label by double clicking on it
    if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok)
        {
            axis->setLabel(newLabel);
            this->replot();
        }
    }
}

void MachineParaPlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)
    if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok)
        {
            plItem->plottable()->setName(newName);
            this->replot();
        }
    }
}

void MachineParaPlot::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            this->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            this->replot();
        }
    }
}

void MachineParaPlot::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
    // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    //  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    //  ui->statusBar->showMessage(message, 2500);
}

void MachineParaPlot::rescaleAllAxis()
{
    this->rescaleAxes(true);
    this->replot();
}

