#include "allmachineWindow.h"
#include "ui_allmachineWindow.h"



allMachineWindow::allMachineWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::allMachineWindow)
   // m_manager(6343)
{
     m_manager = new ControlCenter(6343);
    IdUsed.resize(500,false);
    ui->setupUi(this);
    uiInit();
    readConfig();//读入条件
    startAll();//启用所有读入的条件
}

allMachineWindow::~allMachineWindow()
{
    saveConfig();
    delete ui;
}

/*
 *  初始化槽函数
 */
void allMachineWindow::uiInit(){
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(slotHeaderClicked(int)));
    connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem *)),this,SLOT(getItem(QTableWidgetItem *)));
    connect(m_manager,SIGNAL(MachineDataTimeUpdate_ControlCenter(QString,int)),this,SLOT(MachineDataTimeUpdate_ControlCenter(QString,int)));
    connect(m_manager,SIGNAL(waveDataTimeUpdate_ControlCenter(QString,int)),this,SLOT(waveDataTimeUpdate_ControlCenter(QString,int)));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setFrameShape(QFrame::NoFrame);
    ui->tableWidget->horizontalHeader()->setStyleSheet("border-bottom-width: 0.5px;border-style: solid;border-color: rgb(229,229,229);");
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//表头字体居中
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);  //全局开始双击可编辑
    ui->tableWidget->setIconSize(QSize(400,400));
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

}


/*
*  启用所有读入的机台
*/
void allMachineWindow::startAll(){
     int iRow = ui->tableWidget->rowCount();
     for(int i =0;i<iRow;i++){
         int id = ui->tableWidget->item(i,0)->text().toInt();
         newMachine(id,ui->tableWidget->item(i,5)->text(),ui->tableWidget->item(i,4));
     }
}

/*
*  槽函数更新机台数据的刷新时间
*/
void allMachineWindow::MachineDataTimeUpdate_ControlCenter(QString date,int id){
    qDebug()<<"controlCneter"<<date<<id;
    int iRow = ui->tableWidget->rowCount();
    for(int i=0;i<iRow;i++){
        if(ui->tableWidget->item(i,0)->text().toInt() == id){
            ui->tableWidget->item(i,2)->setText(date);
        }
    }
}


void allMachineWindow::waveDataTimeUpdate_ControlCenter(QString date,int id){
    qDebug()<<"controlCneter"<<date<<id;
    int iRow = ui->tableWidget->rowCount();
    for(int i=0;i<iRow;i++){
        if(ui->tableWidget->item(i,0)->text().toInt() == id){
            ui->tableWidget->item(i,3)->setText(date);
        }
    }
}



/*
 * 双击表头，实现排序
*/
void allMachineWindow::slotHeaderClicked(int clounm)
{
    if(clounm!=0){
        return ;
    }
   // ui->tableWidget->sortItems(clounm,Qt::AscendingOrder);
}


/*
 * 双击的槽函数,启用/禁用
*/
void  allMachineWindow::getItem(QTableWidgetItem* tmp){
    int row = tmp->row();
    int col = tmp->column();

    qDebug()<<"row"<<"col"<<row<<col;

    if(col ==0 ||col==1||col==2||col==3){
        return ;
    }
    //启用或者禁用
    int id = ui->tableWidget->item(row,0)->text().toInt();

    if(col==4){
        int id = ui->tableWidget->item(row,0)->text().toInt();
       // qDebug()<<"id"<<id;
        //如果没有填上数字，则不能启用或者禁用，初始化一个机器需要校验
        if(id==0){
            return ;
        }
        if(!IdUsed[id]){
            newMachine(id,ui->tableWidget->item(row,5)->text(),ui->tableWidget->item(row,4));
        }else{
            deleteMachine(id,ui->tableWidget->item(row,4));
        }
    }
//    //删除选中行
//    if(col ==6 && row !=-1){
//        deleteMachine(id,ui->tableWidget->item(row,4));//先禁用再删除
//        ui->tableWidget->removeRow(row);
//    }
}

/*
 * 新增一个机台
*/
void allMachineWindow::on_pushButton_clicked()
{
    int iRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(iRow + 1);//总行数增加1
    int col = ui->tableWidget->columnCount();
    for(int i=0;i<col;i++){
        QTableWidgetItem* tmp = new QTableWidgetItem();
        if( i==2 || i==3 || i==4 ){  //设置为不可编辑
            tmp->setFlags(tmp->flags() & 33);
            if(i==0){
                tmp->setText(QString::number(iRow+1, 10));
            }
        }
        if(i==2 || i==3){
            tmp->setText("---");
        }
        tmp->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter); //item置于中心
        ui->tableWidget->setItem(iRow,i,tmp);
        tmp->setFont(QFont("Times New Roman", 15));
        if(i==4){
            QIcon icon;
            icon.addFile(":/end.PNG", QSize(400,400));
            tmp->setIcon(icon);
        }
        if(i==5){
            tmp->setText("E");
        }
//        if(i==6){
//            QIcon icon;
//            icon.addFile(":/orange.PNG", QSize(400,400));
//            tmp->setIcon(icon);
//        }
    }
}

/*
 * 启用一个机台
*/
void allMachineWindow::newMachine(int id,QString path,QTableWidgetItem* item){
    if(id==0){
        return ;
    }
    //没有使用
    if(!IdUsed[id]){
        m_manager->initMachine(id,path);
        IdUsed[id] = true;
        QIcon icon;
        icon.addFile(":/l.PNG", QSize(400,400));
        item->setIcon(icon);
    }else {

    }
}


/*
 *  禁用一个机台
 *
 */
void allMachineWindow::deleteMachine(int id,QTableWidgetItem* item){
    //已经使用
    if(IdUsed[id]){
        IdUsed[id] = false;
        m_manager->deleteMa(id);
        QIcon icon;
        icon.addFile(":/end.PNG", QSize(400,400));
        item->setIcon(icon);
    }
}

/*
 *  保存条件
 *
 */
void allMachineWindow::saveConfig(){
    QFile saveFile("save.json");
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
     }

    int iRow = ui->tableWidget->rowCount();
    QJsonObject MachineObject;
    QJsonArray Machines;

    for(int i=0;i<iRow;i++){
         QJsonObject everymachine;
         everymachine["id"] = ui->tableWidget->item(i,0)->text();
         everymachine["name"] = ui->tableWidget->item(i,1)->text();
         everymachine["path"] = ui->tableWidget->item(i,5)->text();
         Machines.append(everymachine);
    }

    MachineObject["allMachines"] = Machines;
    QJsonDocument saveDoc(MachineObject);
    saveFile.write(saveDoc.toJson());
}

/*
 *  读入条件
 *
 */
void allMachineWindow::readConfig(){
    QFile loadFile(QStringLiteral("save.json"));
    if (!loadFile.open(QIODevice::ReadOnly)) {
          qWarning("Couldn't open save file.");
     }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    QJsonArray levelArray = json["allMachines"].toArray();
    for (int levelIndex = 0; levelIndex < levelArray.size(); ++levelIndex) {
        QJsonObject levelObject = levelArray[levelIndex].toObject();
        on_pushButton_clicked();
        int iRow = ui->tableWidget->rowCount();
        ui->tableWidget->item(iRow-1,0)->setText(levelObject["id"].toString());
        ui->tableWidget->item(iRow-1,1)->setText(levelObject["name"].toString());
        ui->tableWidget->item(iRow-1,5)->setText(levelObject["path"].toString());
    }
}
