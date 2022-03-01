#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <vector>
#include <string>
using namespace  std;

class DataProcess
{
public:
    DataProcess();

    vector<float> OutLineDect( vector<float> &data);
    vector<float> SlidingWindow(const vector<float> &data,int avgNum);
};

#endif // DATAPROCESS_H
