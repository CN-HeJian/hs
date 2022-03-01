#ifndef HSCMSGIN_H
#define HSCMSGIN_H

#include "HscDevice.h"
#include "HscMsgIOD.h"
#include "HscMsgIOA.h"

class HscMsgIn
{
public:
    HscMsgIn();
    ~HscMsgIn();

    bool getDI(int i);
    float getAI(int i);

private:
    HscMsgIOA a_i[HSC_NUM_AI];
    HscMsgIOD<HSC_NUM_DI> d_i;
};

#endif // HSCMSGIN_H
