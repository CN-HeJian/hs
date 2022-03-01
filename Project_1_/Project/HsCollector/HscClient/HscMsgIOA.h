#ifndef HSCMSGIOA_H
#define HSCMSGIOA_H

#include <cstdint>

class HscMsgIOA{
public:
    HscMsgIOA(uint16_t value = 0):
        aio(value){
    }
    ~HscMsgIOA(){

    }
    float get(){
        return 10.0f * ((aio&0x8000) ? (aio-0xffff): aio) / 0x7fff;
    }
private:
    uint16_t aio;
};

#endif // HSCMSGIOA_H
