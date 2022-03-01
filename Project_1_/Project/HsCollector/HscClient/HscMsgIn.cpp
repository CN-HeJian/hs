#include "HscMsgIn.h"

HscMsgIn::HscMsgIn(){

}

HscMsgIn::~HscMsgIn(){

}

bool HscMsgIn::getDI(int i){
    return d_i.get(i);
}

float HscMsgIn::getAI(int i){
    return a_i[i].get();
}
