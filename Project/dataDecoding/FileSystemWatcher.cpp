#include "FileSystemWatcher.h"


FileSystemWatcher* FileSystemWatcher::m_pInstance = NULL;
unsigned int FileSystemWatcher::select = 1;

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent),
      pool(3)
{
   // pool(3);
    pool.init();
    //used.resize(3,false);
}

void FileSystemWatcher::phaseCsv(string path,vector<vector<float>> &matrix){
    ifstream fp(path); //定义声明一个ifstream对象，指定文件路径
    string line;
    getline(fp,line); //跳过列名，第一行不做处理
    matrix.resize(7);
    while (getline(fp,line)){ //循环读取每行数据
        string number;
        //vector<float> data_line;
        istringstream readstr(line); //string数据流化
        //将一行数据按'，'分割
        for(int j = 0;j < 7;j++){ //可根据数据的实际情况取循环获取
            getline(readstr,number,','); //循环读取数据
            matrix[j].push_back(atof(number.c_str())); //字符串传int
        }
        //matrix.push_back(data_line); //插入到vector中
    }
}

float FileSystemWatcher::calculatePresAvg(vector<vector<float>> &matrix){

    //cout<<"matrix[1] size : "<<matrix[1].size()<<endl;

    //索引出注射段压力数据
    vector<float> injectPres = matrix[1];
    //cout<<"injectionPres "<<injectPres.size()<<endl;
    //需要索引出开始的位置

    auto be = injectPres.begin();
    //需要计算出最大值的位置
    auto max_iter = max_element(injectPres.begin(),injectPres.end());

    double avgPres = 0;
    int length = max_iter-be+1;
    //cout<<"length: "<<length<<endl;

    for(auto i = be;i<=max_iter;i++){
        avgPres +=((*i)/length);
    }
    //std::cout<<"avgPres:  "<<avgPres<<endl;
    return avgPres;
}


// 监控文件或目录
void FileSystemWatcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);

    if (m_pInstance == NULL)
    {
        m_pInstance = new FileSystemWatcher();
        m_pInstance->m_pSystemWatcher = new QFileSystemWatcher();

        // 连接QFileSystemWatcher的directoryChanged和fileChanged信号到相应的槽
        connect(m_pInstance->m_pSystemWatcher, SIGNAL(directoryChanged(QString)), m_pInstance, SLOT(directoryUpdated(QString)));
        connect(m_pInstance->m_pSystemWatcher, SIGNAL(fileChanged(QString)), m_pInstance, SLOT(fileUpdated(QString)));
    }

    // 添加监控路径
    m_pInstance->m_pSystemWatcher->addPath(path);



    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        m_pInstance->m_currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

void FileSystemWatcher::removeWatchPath(QString path){
    m_pInstance->m_pSystemWatcher->removePath(path);
}

// 只要任何监控的目录更新（添加、删除、重命名），就会调用。
void FileSystemWatcher::directoryUpdated(const QString &path)
{
    //qDebug() << QString("Directory updated: %1").arg(path);
    //qDebug()<<"---------------------";

    // 比较最新的内容和保存的内容找出区别(变化)
    QStringList currEntryList = m_currentContentsMap[path];
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    // 添加了文件
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    // 文件已被移除
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    // 更新当前设置
    m_currentContentsMap[path] = newEntryList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty())
    {
        // 文件/目录重命名
        if ((newFile.count() == 1) && (deleteFile.count() == 1))
        {
            qDebug() << QString("File Renamed from %1 to %2").arg(deleteFile.first()).arg(newFile.first());
        }
    }
    else
    {
        // 添加新文件/目录至Dir
        if (!newFile.isEmpty())
        {
           // qDebug() << "New Files/Dirs added: " << newFile;

            foreach (QString file, newFile)
            {
                // 处理操作每个新文件....

                //qDebug()<<"path "<<path<<" "<<"file "<<file;
                //会额外生一个Header.csv文件、删除！！！
                if(file=="Header.csv"){
                   // qDebug()<<"file"<<file;
                    continue;
                }

                auto future1 = pool.submit(updateWaveFeature, path, file);
               // return_data tmp = future1.get();
               // qDebug()<<tmp.avg<<" "<<tmp.count<<" "<<tmp.dateTime<<" "<<tmp.tableName;

               // updateWaveFeature(path,file);

                /*

                //暂停一段时间，等待文件全部写完，这一段比较耗时，需要用到多线程
                QTime time;
                time.start();
                while(time.elapsed()<10000);
                string fullPath;
                fullPath = path.toStdString() +"/"+ file.toStdString();
                vector<vector<float>> matrix;
                //读取csv文件
                phaseCsv(fullPath,matrix);
                //开始读取
                float avg = calculatePresAvg(matrix);

                //获取表的名字
                int Slash = 0;
                QString tableName = "";
                qDebug()<<"path:  "<<path<<endl;
                for(int i=path.size()-1;i>=0;i--){
                    if(path[i]=='/'){
                        Slash++;
                        continue;
                    }
                    if(Slash<3){
                        continue;
                    }
                    if(Slash>=4){
                        break;
                    }
                    tableName = path[i] + tableName;
                }


                //获取模次名
                QString moldCount;
                int dotNum = 0;
                int Down_loopNUm = 0;
                for(int i=file.size()-1;i>=0;i--){
                    if(file[i]=="."){
                        dotNum++;
                        continue;
                    }
                    if(file[i]=='_'){
                        Down_loopNUm++;
                    }
                    if(dotNum!=1){
                        continue;
                    }
                    if(Down_loopNUm==1){
                        break;
                    }
                    moldCount = file[i]+moldCount;
                }

                //qDebug()<<"moldCount : "<<moldCount<<endl;

                int count = moldCount.toInt();

                //开始组装一下时间
               QString year = file.mid(0,4);
               QString month = file.mid(4,2);
               QString day = file.mid(6,2);
               QString hour = file.mid(9,2);
               QString minute = file.mid(11,2);
               QString second = file.mid(13,2);

               QString DateTime = year+"-"+month+"-"+day+" "+hour+":00:00";
               //qDebug()<<"DateTime "<<DateTime<<endl;

               sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
               //void updateTableField(QString TableName,QString columnName,float value,int count_val,QString dateTime);
               //qDebug()<<"path "<<path<<" "<<"file "<<file;
               qDebug()<<"TableName:"<<tableName<<" "<<"dateTime:"<<DateTime<<"moldCnt:"<<moldCount<<"avgPress:"<<avg;
               //qDebug()<<"---------------------------------------------------------------"<<endl;

               temp_sqlServer->updateTableField(tableName,"injectionPhasePressAvg",avg,count,DateTime);
               //qDebug()<<"---------------------------------------------------------------"<<endl;

               //波形数据更新了！！！
               class GetMessage *temp_getMessage = Singleton<class GetMessage>::Instance();
               temp_getMessage->waveDataUpdate(tableName,hour+":"+minute+":"+second);

               */



            }
        }

        // 从Dir中删除文件/目录
        if (!deleteFile.isEmpty())
        {
            qDebug() << "Files/Dirs deleted: " << deleteFile;

            foreach(QString file, deleteFile)
            {
                // 处理操作每个被删除的文件....
            }
        }
    }
}

// 文件修改时调用
void FileSystemWatcher::fileUpdated(const QString &path)
{
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();

    qDebug() << QString("The file %1 at path %2 is updated").arg(strName).arg(strPath);
}


return_data FileSystemWatcher::updateWaveFeature(QString path,QString file){

    //暂停一段时间，等待文件全部写完，这一段比较耗时，需要用到多线程
    QTime time;
    time.start();
    while(time.elapsed()<10000);
    string fullPath;
    fullPath = path.toStdString() +"/"+ file.toStdString();
    vector<vector<float>> matrix;
    //读取csv文件
    phaseCsv(fullPath,matrix);
    //开始读取
    float avg = calculatePresAvg(matrix);

    //获取表的名字
    int Slash = 0;
    QString tableName = "";
    qDebug()<<"path:  "<<path<<endl;
    for(int i=path.size()-1;i>=0;i--){
        if(path[i]=='/'){
            Slash++;
            continue;
        }
        if(Slash<3){
            continue;
        }
        if(Slash>=4){
            break;
        }
        tableName = path[i] + tableName;
    }


    //获取模次名
    QString moldCount;
    int dotNum = 0;
    int Down_loopNUm = 0;
    for(int i=file.size()-1;i>=0;i--){
        if(file[i]=="."){
            dotNum++;
            continue;
        }
        if(file[i]=='_'){
            Down_loopNUm++;
        }
        if(dotNum!=1){
            continue;
        }
        if(Down_loopNUm==1){
            break;
        }
        moldCount = file[i]+moldCount;
    }

    //qDebug()<<"moldCount : "<<moldCount<<endl;

    int count = moldCount.toInt();

    //开始组装一下时间
   QString year = file.mid(0,4);
   QString month = file.mid(4,2);
   QString day = file.mid(6,2);
   QString hour = file.mid(9,2);
   QString minute = file.mid(11,2);
   QString second = file.mid(13,2);

   QString DateTime = year+"-"+month+"-"+day+" "+hour+":00:00";
   //qDebug()<<"DateTime "<<DateTime<<endl;

  // sqlServer *temp_sqlServer = Singleton<sqlServer>::Instance();
   sqlServer *temp_sqlServer = new sqlServer();

//   int select = 0;
//   for(int i=0;i<3;i++){
//       if(used[i]==false){
//            select = i;
//       }
//   }
   select++;

   temp_sqlServer->connect(QString::fromStdString(to_string(select)),"QSQLITE");
   temp_sqlServer->updateTableField(tableName,"injectionPhasePressAvg",avg,count,DateTime);


   temp_sqlServer->unlink();
   //QSqlDatabase::removeDatabase("jyy");

   //void updateTableField(QString TableName,QString columnName,float value,int count_val,QString dateTime);
   //qDebug()<<"path "<<path<<" "<<"file "<<file;

  // sqlServer* tmp =  new sqlServer();


   //QSqlDatabase m_sqlDatabase = QSqlDatabase::database("inject.db");
  // m_sqlDatabase.open();
  // QSqlQuery m_sqlQuery(m_sqlDatabase);

  // QString sql_cmd = "UPDATE "+ tableName +" SET "+ "injectionPhasePressAvg" + " = " + QString("%1").arg(avg,0,'G',6) + " WHERE DATE > " + "'"+DateTime +"'"+ " AND ActCntCyc == " + QString("%2").arg(count);

   //qDebug()<<"sql update: "<<TableName<<sql_cmd<<endl;


  // if(!m_sqlQuery.exec(sql_cmd))
  // {
       //qDebug()<<"Failed to update avgPress:"<<m_sqlQuery.lastError();
//
  // }
  // else
  // {
//       qDebug()<<"success to update: "<<tableName<<"avgPress";
  // }




   qDebug()<<"TableName:"<<tableName<<" "<<"dateTime:"<<DateTime<<"moldCnt:"<<moldCount<<"avgPress:"<<avg;
   //qDebug()<<"---------------------------------------------------------------"<<endl;

//   temp_sqlServer->updateTableField(tableName,"injectionPhasePressAvg",avg,count,DateTime);
   //qDebug()<<"---------------------------------------------------------------"<<endl;

   //波形数据更新了！！！
   class GetMessage *temp_getMessage = Singleton<class GetMessage>::Instance();
   temp_getMessage->waveDataUpdate(tableName,hour+":"+minute+":"+second);

   return_data tmp;
   tmp.avg = avg;
   tmp.count = count;
   tmp.dateTime = DateTime;
   tmp.tableName = tableName;

   return tmp;
}
