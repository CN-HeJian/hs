 #include "SingleMachine.h"
#include "ui_SingleMachine.h"

#include <QDebug>

SingleMachine::SingleMachine(string machineName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleMachine)
{
    ui->setupUi(this);
    m_machineName = machineName;
    init();
}


SingleMachine::SingleMachine(string machineName,int dataType,int displayType,int boxChartHourNums,int lineChartLine_avgNum,QString modifyProcessParameterTime,int selectLatelyMoldCnt,int selectRange,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleMachine)
{
    ui->setupUi(this);
    m_machineName = machineName;
    m_dateType = dataType_t(dataType);
    m_displayType = display_t(displayType);
    m_lineChart_avgNum = lineChartLine_avgNum;
    m_boxChart_HourNums = boxChartHourNums;
    m_modifyProcessParameterTime = modifyProcessParameterTime.toStdString();
    m_selectLatelyMoldCnt = selectLatelyMoldCnt;
    m_selectRangeType = selectRange_t(selectRange);
    init();
    initInterface();
}

SingleMachine::~SingleMachine()
{
    delete ui;
}

/*
 * 初始化combox
*/
void SingleMachine::init(){
    //设置时间，防止每次都需要更改太多内容
    QDateTime current_date =QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(current_date.addDays(-1)); //设置一下最近查询时间
    ui->dateTimeEdit_3->setDateTime(current_date.addDays(-1)); //设置一下开始时间
    ui->dateTimeEdit_4->setDateTime(current_date);   //设置一下结束时间

     m_modifyProcessParameterTime = current_date.addDays(-1).toString("yyyy-MM-dd hh:mm:ss").toStdString();
     m_queryStartTime = current_date.addDays(-1).toString("yyyy-MM-dd hh:mm:ss").toStdString();
     m_queryEndTime = current_date.toString("yyyy-MM-dd hh:mm:ss").toStdString();

    connect(ui->plotWidget,SIGNAL(selectionChangedByUser()),this,SLOT(selectionChange()));
    connect(ui->plotWidget, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove1(QMouseEvent*)));
    //QObject::connect (ui->plotWidget, SIGNAL(legendDoubleClick (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)), this, SLOT(legend_double_click (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));



    bTracer1 = false;
       bTracer2 = false;


       QPen graphPen;
       graphPen.setColor(QColor(42,140,254));
       graphPen.setWidthF(3);


       tracer1 = new QCPItemTracer(ui->plotWidget);
          tracer1->setPen(graphPen); //实线游标
          tracer1->setStyle(QCPItemTracer::tsCrosshair);//十字星线
          tracer1->setSize(3.0);
          tracer1->setVisible(false);
          tracer1->position->setCoords(5,0);

          graphPen;
          graphPen.setColor(QColor(42,140,254));
          graphPen.setWidthF(3);
          //构建游标2
          tracer2 = new QCPItemTracer(ui->plotWidget);
          tracer2->setPen(graphPen); //实线游标
          tracer2->setStyle(QCPItemTracer::tsCrosshair);//十字星线
          tracer2->setSize(5.0);
          tracer2->setVisible(false);
          tracer2->position->setCoords(15,0);

          ui->plotWidget->replot();




    connect(ui->plotWidget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(ui->plotWidget, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClick(QMouseEvent*)));
    connect(ui->plotWidget, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));

}


/**
 * @brief 鼠标点击事件
 * @param e
 */
void SingleMachine::mousePress(QMouseEvent* e)
{
    QCustomPlot *curCustomPlot = qobject_cast<QCustomPlot *>(sender());

    if(m_isShow==false  || m_enlarge){
        return ;
    }
    if(curCustomPlot == ui->plotWidget)
    {
        //获取单击时的位置
        int x = curCustomPlot->xAxis->pixelToCoord(e->pos().x());
        int trace1Pos = tracer1->position->key();
        int trace2Pos = tracer2->position->key();
        if(abs(trace1Pos-x)<abs(trace2Pos-x)){
            //选择游标1
            bTracer1 = true;
            bTracer2 = false;
            QPen graphPen;
            graphPen.setColor(QColor(42,140,254));
            graphPen.setWidthF(3);
            tracer1->setPen(graphPen); //实线游标
            graphPen.setColor(QColor(42,140,254));
            graphPen.setWidth(2);
            tracer2->setPen(graphPen); //实线游标
        }else{
            //选择游标2
            bTracer1 = false;
            bTracer2 = true;
            QPen graphPen;
            graphPen.setColor(QColor(42,140,254));
            graphPen.setWidthF(3);
            tracer2->setPen(graphPen); //实线游标
            graphPen.setColor(QColor(42,140,254));
            graphPen.setWidth(2);
            tracer1->setPen(graphPen); //实线游标
        }
        ui->plotWidget->replot();
    }
}



/**
 * @brief 鼠标移动事件
 * @param e
 */
void SingleMachine::mouseMove(QMouseEvent *e)
{
    if(m_enlarge){
        return ;
    }
    QCustomPlot *curCustomPlot = qobject_cast<QCustomPlot *>(sender());

    if(curCustomPlot == ui->plotWidget)
    {
        if(bTracer1)
        {
            int x = curCustomPlot->xAxis->pixelToCoord(e->pos().x());
            int pos = x;
            if(pos < 0)
            {
                return ;
            }
            qDebug() << "POS:" << pos;

            tracer1->position->setCoords(pos, 0);
            tracer1->setVisible(true);
            curCustomPlot->replot();
           // ui->lineEditStart->setText(QString("%1").arg(x));
        }

        if(bTracer2)
        {
            int x = curCustomPlot->xAxis->pixelToCoord(e->pos().x());
            int pos = x;
            if(pos < 0)
            {
                return ;
            }

            tracer2->position->setCoords(pos, 0);
            tracer2->setVisible(true);
            curCustomPlot->replot();
          //  ui->lineEditEnd->setText(QString("%1").arg(x));
        }
    }
}


/**
 * @brief 鼠标双击事件
 * @param e
 */
void SingleMachine::mouseDoubleClick(QMouseEvent* e)
{
    QCustomPlot *curCustomPlot = qobject_cast<QCustomPlot *>(sender());
    if(curCustomPlot == ui->plotWidget)
    {
        if(bTracer1){
            bTracer1 = false;
        }
        if(bTracer2){
            bTracer2 = false;
        }
    }
}


void SingleMachine::staticLabel(){
    m_isShow = !m_isShow;
    if(m_isShow){

        tracer1->setVisible(true);
        tracer2->setVisible(true);
    }else{
        int xMax = (int)ui->plotWidget->xAxis->range().upper+1;


        tracer1->position->setCoords(xMax/2, 0);
        tracer2->position->setCoords(xMax/2, 0);
        tracer1->setVisible(false);
        tracer2->setVisible(false);
    }
    ui->plotWidget->replot();
}

/*
 * 设置界面
*/
void SingleMachine::initInterface(){
    setSelectRangeType();
    setDataType();
    setModifyProcessParameterTime();
    setSelectLatelyMoldCnt();
    setDisplay_t();
    setLineChart_avgNum();
    setBoxChart_HourNums();
}

//********************************************************************SET***********************************************************************//

//********************************************************************SET***********************************************************************//

//依据最近模次还是最近区间选择
void SingleMachine::setSelectRangeType(){
    if(m_selectRangeType == latelyMold ){
        ui->checkBox_4->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Checked);
    }else{
        ui->checkBox_4->setCheckState(Qt::Checked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
    }
}


void SingleMachine::setDataType(){
    ui->comboBox->setCurrentIndex(m_dateType);
}


void SingleMachine::setModifyProcessParameterTime(){
    ui->dateTimeEdit->setDateTime( QDateTime::fromString(QString::fromStdString(m_modifyProcessParameterTime), "yyyy-MM-dd hh:mm:ss"));
}

void SingleMachine::setSelectLatelyMoldCnt(){
    ui->spinBox->setValue(m_selectLatelyMoldCnt);
}


void SingleMachine::setDisplay_t(){
    if(m_displayType == LineChart ){
        ui->checkBox_2->setCheckState(Qt::Checked);
        ui->checkBox_1->setCheckState(Qt::Unchecked);
    }else{
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox_1->setCheckState(Qt::Checked);
    }
}


void SingleMachine::setLineChart_avgNum(){
    ui->spinBox_5->setValue(m_lineChart_avgNum);
}


void SingleMachine::setBoxChart_HourNums(){
    ui->spinBox_2->setValue(m_boxChart_HourNums);
}


void SingleMachine::zoomLarge(bool flag){
    if(flag){
        m_enlarge = true;
        ui->plotWidget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    }else{
        m_enlarge = false;
        ui->plotWidget->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
    }
}

//********************************************************************SLOT***********************************************************************//

//********************************************************************SLOT***********************************************************************//

//最近模次
void SingleMachine::on_checkBox_3_clicked(bool checked)
{
    qDebug()<<"lately  mold  checked "<<checked;
    if(checked){
        ui->checkBox_4->setCheckState(Qt::Unchecked);
        m_selectRangeType = latelyMold; //更改为最近模次模式
    }else{
        ui->checkBox_4->setCheckState(Qt::Checked);
        m_selectRangeType = regionMold; //更改为最近区间模式
    }
}

//最近区间
void SingleMachine::on_checkBox_4_clicked(bool checked)
{
    qDebug()<<"lately region checked "<<checked;
    if(checked){
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        m_selectRangeType = regionMold; //更改为最近区间模式
    }else{
        ui->checkBox_3->setCheckState(Qt::Checked);
        m_selectRangeType = latelyMold; //更改为最近模次模式
    }
}

/*
 * 拉取数据类型更改
*/
void SingleMachine::on_comboBox_currentTextChanged(const QString &arg1)
{
    qDebug()<<"select data type change to "<<arg1;
    int curIndex = ui->comboBox->currentIndex();
    m_dateType = (dataType_t)curIndex; //强制转换更改数据类型
}

/*
 * 最近调机时间更改
*/
void SingleMachine::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    QString timeStr = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<"timeStr"<<timeStr;
    m_modifyProcessParameterTime = timeStr.toStdString();
}

//开始时间调整
void SingleMachine::on_dateTimeEdit_3_dateTimeChanged(const QDateTime &dateTime)
{
    QString timeStr = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<"timeStr"<<timeStr;
    m_queryStartTime = timeStr.toStdString();
}

//结束时间调整
void SingleMachine::on_dateTimeEdit_4_dateTimeChanged(const QDateTime &dateTime)
{
    QString timeStr = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<"timeStr"<<timeStr;
    m_queryEndTime = timeStr.toStdString();
}

/*
 * 模次数更改
*/
void SingleMachine::on_spinBox_valueChanged(int arg1)
{
    qDebug()<<"select mold cnt change to "<<arg1;
     m_selectLatelyMoldCnt  = arg1;
}

/*
 * 显示类型变成折线图
*/
void SingleMachine::on_checkBox_2_clicked(bool checked)
{
    if(checked){
        ui->checkBox_1->setCheckState(Qt::Unchecked);
        m_displayType = LineChart;
    }else{
        ui->checkBox_1->setCheckState(Qt::Checked);
        m_displayType = BoxChart;
    }
}

/*
 * 显示类型变为箱线图
*/
void SingleMachine::on_checkBox_1_clicked(bool checked)
{
    if(checked){
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        m_displayType = BoxChart;
    }else{
        ui->checkBox_2->setCheckState(Qt::Checked);
        m_displayType = LineChart;
    }
}

/*
 * 折线图显示模次变化
*/
void SingleMachine::on_spinBox_5_valueChanged(int arg1)
{
    m_lineChart_avgNum = arg1;
}

/*
 * 箱线图显示小时变化
*/
void SingleMachine::on_spinBox_2_valueChanged(int arg1)
{
    m_boxChart_HourNums = arg1;
}


//up
void SingleMachine::on_doubleSpinBox_12_valueChanged(double arg1)
{
    UpLimit = arg1;
}

//down
void SingleMachine::on_doubleSpinBox_13_valueChanged(double arg1)
{
    DownLimit = arg1;
}


//********************************************************************GET***********************************************************************//

//********************************************************************GET***********************************************************************//


/*
 * 获取当前的机器名
*/
string SingleMachine::getMachineName(){
    return m_machineName;
}

/*
 * 获取当前机器状态
*/
state_t SingleMachine::getMachineState(){
    return m_machineState;
}

/*
 * 获取当前请求的时间区间
*/
selectRange_t  SingleMachine::getCurMachineSelectRangeType(){
    return m_selectRangeType;
}

/*
 * 获取当前显示的数据类型
*/
dataType_t SingleMachine::getDataType(){
    return m_dateType;
}

/*
 * 获取上一次调整工艺的时间
*/
string SingleMachine::getModifyProcessParameterTime(){
    return m_modifyProcessParameterTime;
}

/*
 * 获取开始时间
*/
string SingleMachine::getStartTime(){
    return m_queryStartTime;
}

/*
 * 获取结束时间
*/
string SingleMachine::getEndTime(){
    return m_queryEndTime;
}

/*
 * 如果是最近模式、获取最近模次的数量
*/
int SingleMachine::getSelectLatelyMoldCnt(){
    return m_selectLatelyMoldCnt;
}

/*
 *  获取当前的显示模式
*/
display_t SingleMachine::getDisplayType(){
    return  m_displayType;
}

/*
 *  模次平均次数
*/
int SingleMachine::getLineChartAvgNum(){
    return  m_lineChart_avgNum;
}

/*
 *  箱线图小时数
*/
int SingleMachine::getBoxChart_HourNums(){
    return m_boxChart_HourNums;
}

/*
 * 人工手动标记点
*/
QString SingleMachine::getDetectMoldDate(){
    return detectMoldDate;
}

//********************************************************************SET***********************************************************************//

//********************************************************************SET***********************************************************************//

/*
 *  设置图中显示数据的类型、例如注射段压力平均值、注射段二阶导数
 *
*/
void SingleMachine::setPlotDataType(dataType_t type){
    plotDataType = type;
}
/*
 *  设置图中显示的数据
 *
*/
void SingleMachine::setPlotdData(vector<string> dates,vector<float> vals){
    //plotData = *Data;
    m_dates  = dates;
    m_vals = vals;
}

void SingleMachine::setDetectedData(vector<string> detected){
   //m_detected = detected;
    //m_detected.clear();
    //unordered_set<string> mp;
    for(int i=0;i<detected.size();i++){
       // qDebug()<<"setDect"<<QString::fromStdString(c)<<endl;
       mp.insert(detected[i]);
       //  m_detected.emplace(c);       //m_detected[c.first] = c.second;
    }
}

//********************************************************************PLOT***********************************************************************//

//********************************************************************PLOT***********************************************************************//

/*
 *  槽函数，图标与图例同步显示
*/
void SingleMachine::selectionChange(){
    ui->plotWidget->comformity();
}

/*
 *  控制模块绘图
 *
 */
void SingleMachine::controlPlot(){
    if(m_dates.size()==0){
        cout<<"no data"<<endl;
        m_dates = {};
        m_vals = {};
        ui->plotWidget->plotData(m_dates,m_vals,mp);
        ui->plotWidget->replot();
        //ui->
        return;
    }
    //如果为画出直线
    if(m_displayType == LineChart){

       m_slideWindow = m_dataProcess.SlidingWindow(m_vals,m_lineChart_avgNum);
       // ui->plotWidget->plotData(slideWindow);
       // ui->plotWidget->setxAxis2Range(m_dates[0],m_dates[m_dates.size()-1]);
        //ui->plotWidget->setlegend("");
        ui->plotWidget->plotData(m_dates,m_slideWindow,mp);
        ui->plotWidget->setlegend(label[plotDataType]);
        ui->plotWidget->setxAxis2Range(m_dates[0],m_dates[m_dates.size()-1]);
        if(isStart){
            ui->plotWidget->plotGraph2(UpLimit,DownLimit);
        }
    }
    //如果为画箱线图
    else if(m_displayType == BoxChart){
        int avgHour = m_boxChart_HourNums;
        //ui->plotWidget->setlegend(label[plotDataType]);
        if(m_isShow){
            staticLabel();
        }
        ui->plotWidget->BoxPlot(m_vals,m_dates,m_boxChart_HourNums,label[plotDataType]);
    }
}

void SingleMachine::mouseMove1(QMouseEvent *e)
{
    double x = ui->plotWidget->xAxis->pixelToCoord(e->pos().x());
    if(is_CreateCursor){
        //下面的代码很关键
        tracer->setPen(QPen(Qt::DashLine));//游标线型：虚线
        tracer->setStyle(QCPItemTracer::tsPlus);//游标样式：十字星、圆圈、方框等
        tracer->setGraph(ui->plotWidget->graph(0)); //将游标和该曲线图层想连接
        tracer->setGraphKey(x); //将游标横坐标（key）设置成刚获得的横坐标数据x
        tracer->setInterpolating(true); //游标的纵坐标可以通过曲线数据线性插值自动获得（这就不用手动去计算了）
        tracer->updatePosition(); //使得刚设置游标的横纵坐标位置生效
        //以下代码用于更新游标说明的内容
        double xValue = tracer->position->key();
        double yValue = tracer->position->value();
        string date = "   "+m_dates[xValue];
        tracerLabel->setText(QString::fromStdString(date));
        ui->plotWidget->replot(); //不要忘了重绘
      }else{

      }
}

/*
 *  添加游标
 *
 */
void SingleMachine::addCursor(){
    if(!m_dates.size()){
        return ;
    }
    if( is_CreateCursor){//基数
           is_CreateCursor = false;
           delete tracer;
           delete  tracerLabel;
           ui->plotWidget->replot();
       }else{//偶数
           is_CreateCursor = true;
           tracer = new QCPItemTracer(ui->plotWidget); //生成游标
           tracer->setPen(QPen(Qt::red));
           tracer->setBrush(QBrush(Qt::red));
           tracer->setSize(2000.0);
           tracerLabel = new QCPItemText(ui->plotWidget); //生成游标说明
           tracerLabel->setLayer("overlay");
           tracerLabel->setPen(QPen(Qt::red));
           tracerLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignBottom);
           tracerLabel->position->setParentAnchor(tracer->position);
    }
}

/*
 *  将信息存为json文件
 *
 */
void SingleMachine::saveToJson(QJsonObject &json) const{
    json["machineName"] = QString::fromStdString(m_machineName);
    json["selectRange_t"] = m_selectRangeType;
    json["dataType_t"] = m_dateType;
    json["modifyProcessParameterTime"] = QString::fromStdString(m_modifyProcessParameterTime);
    json["selectLatelyMoldCnt"] = m_selectLatelyMoldCnt;
    json["display_t"] = m_displayType;
    json["lineChart_avgNum"] = m_lineChart_avgNum;
    json["boxChart_HourNums"] = m_boxChart_HourNums;
}

//将数据导出来
void SingleMachine::exportData(){
    QString filename = QFileDialog::getSaveFileName(this,
            tr("Save Data"),
            m_lastSavePath,
            tr( "*.csv")); //选择路径
        if(filename.isEmpty())
        {
            return;
        }
        else
        {
            int count = 0;
            for(int i=filename.size()-1;i>=0;i--){
                if(filename[i]=="/"){
                            break;
                }
                count++;
            }
            m_lastSavePath = filename.mid(0,filename.size()-count-1);//设置上一次保存文件的路径

            qDebug()<<filename;
            QFile file(filename);
            if (!file.exists())  //文件不存在的时新建
             {
              file.open(QIODevice::WriteOnly);
              QTextStream txtOutPut(&file);
              txtOutPut << "Time,PresAvg\n"; //注意，每行数据结束后要加换行符
              file.close();
             }
            //打开文件
             file.open(QIODevice::WriteOnly | QIODevice::Append);
             QTextStream txtOutPut(&file);

             //遍历要保存的数据
             for (int i=0;i<m_dates.size();i++)
             {
              //保存数据
              QString msg = QString::fromStdString(m_dates[i]) + ","\
               + QString::number(m_vals[i])+ "\n";
                 txtOutPut << msg;
                 file.flush();//向文件中写入数据
             }
             file.close();//保存完成后关闭文件

        }
}


//开启/禁用监控
void SingleMachine::on_toolButton_3_clicked()
{
    isStart = !isStart;
    //开始监控
    if(isStart){
        ui->toolButton_3->setStyleSheet("background:green");
        ui->plotWidget->plotGraph2(UpLimit,DownLimit);

    }else{
        ui->toolButton_3->setStyleSheet("background:rgb(46, 142, 253);");
        ui->plotWidget->deleteGraph2();
    }
}





//计算统计信息，没有数据就不计算，没有加上左右边界的话就计算全部，有的话就计算区域内的数据
void SingleMachine::on_toolButton_5_clicked()
{
    int trace1Pos = tracer1->position->key();
    int trace2Pos = tracer2->position->key();

    int max_ = max(trace1Pos,trace2Pos);
    int min_ = min(trace1Pos,trace2Pos);

    int cnt = m_vals.size();

    int end_ = min(cnt,max_);



    float avg = 0.0,std = 0.0;

    int sum_cnt = end_-min_;


    for(int i=min_;i<end_;i++){
        avg +=  (float) m_slideWindow[i]/sum_cnt;
    }

    double stdSqare=0,std_cal=0;
    for(int i=min_;i<end_;i++){
        stdSqare += (m_slideWindow[i]-avg)*(m_slideWindow[i]-avg)/sum_cnt;
    }
    std_cal = std::sqrt((double)stdSqare);

    ui->spinBox_8->setValue(sum_cnt);
    ui->doubleSpinBox_7->setValue(avg);
    ui->doubleSpinBox_10->setValue(std_cal);

}


//检测标记的点
void SingleMachine::on_toolButton_4_clicked()
{
    //获取图中最后一个点的数据
    //弹出小框
    //确认之后返回,上传到服务器

    if(m_dates.size()>1){
        string lastMold = m_dates[m_dates.size()-1];


        detectMoldDate = QString::fromStdString(lastMold);

        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(lastMold));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
           case QMessageBox::Save:
               // Save was clicked
                emit detectMold(this);

               break;

           case QMessageBox::Cancel:
               // Cancel was clicked
               break;
           default:
               // should never be reached
               break;
         }

    }else{
        //弹出小框，没有数据
        QMessageBox msgBox;
        msgBox.setText("没有数据");
        msgBox.exec();
    }

}





