#include "DataProcess.h"
#include <string>
#include <QDebug>
#include <iostream>
#include <algorithm>
#include "math.h"



DataProcess::DataProcess()
{
}

//异常检测
vector<float> DataProcess::OutLineDect(vector<float> &data){

    int n = data.size();
    int nzero = n;
    if(n==0){
        return data;
    }
    //计算均值
    for(int i=0;i<data.size();i++){
        if(data[i]==0&&nzero>1){
            nzero--;
        }
    }
    //cout<<"nzero"<<nzero<<endl;

    double avg=0;
    for(int i=0;i<n;i++){
       // cout<<"data[i]"<<data[i]<<endl;
       // cout<<"avg"<<avg;
        avg += data[i]/nzero;
    }
  //  cout<<"avg"<<avg<<endl;


    //零值使用均值替代
    for(int i=0;i<n;i++){
        if(data[i]==0){
            data[i] = avg;
        }
    }

    //计算标准差
    double stdSqare=0,std_cal=0;
    for(int i=0;i<n;i++){
        stdSqare += (data[i]-avg)*(data[i]-avg)/n;
    }
    std_cal = std::sqrt((double)stdSqare);
    float up  = avg + 3*std_cal;
    float down = avg - 3*std_cal;

    //3sigma原则剔除异常
    int cnt=0;
    for(int i=0;i<n;i++){
        if(data[i]<down || data[i]>up){
            data[i] = avg;
            cnt++;
        }
    }
    //数据输出
    qDebug()<<"avg: "<<avg<<"std: "<<std_cal<<"up: "<<up<<"down: "<<down<<"cnt: "<<cnt;

    return data;
}

//平滑处理
vector<float> DataProcess::SlidingWindow(const vector<float> &data,int avgNum){
    //特殊情况
    int length = data.size();
    if(avgNum==1 || length==0)
        return data;
    //计算前缀和
    vector<float> sum(length,0);
    float tempsum = 0;
    for(int i=0;i<length;i++){
        tempsum +=data[i];
        sum[i] = tempsum;
    }
    //平滑滤波
    vector<float> res(length,0);
    for(int i=0;i<length;i++){
        if(i<avgNum){
            res[i] = (sum[i]/(i+1));
        }else{
            res[i] = ((sum[i]-sum[i-avgNum])/avgNum);  //快速计算区间[i,i+k]之间的和
        }
    }
    return res;
}
