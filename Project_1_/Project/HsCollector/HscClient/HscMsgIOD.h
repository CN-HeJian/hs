#ifndef HSCMSGIOD_H
#define HSCMSGIOD_H

#include <cstdint>
#include <string>
#include <ostream>

template <int N> class HscMsgIOD;

template<int N>
std::ostream& operator << (std::ostream& os,
                           const HscMsgIOD<N>& bits);

template <int N=8>
class HscMsgIOD{
public:
    HscMsgIOD(int val = 0){
        for(int i=0; i<N; i++){
            set(i, (val>>i) & 0x1);
        }
    }
    ~HscMsgIOD(){}

    bool get(int i) const{
        return bits[i/8] & (1<<(i%8));
    }

    void set(int i, bool val = true){
        bits[i/8] = val ? bits[i/8] | (1<<(i%8)) :
                ~(~bits[i/8] | (1<<(i%8)));
    }

    void clear(){
        for(int i=0; i<int((N+7)/8); i++){
            bits = 0;
        }
    }

public:
    std::string toString(char zero='0', char one='1') const {
        std::string ret;
        for(int i=N-1; i>=0; i--){
            ret.append(1, get(i) ? one : zero);
        }
        return ret;
    }
public:
    HscMsgIOD<N>& operator = (int val){
        for(int i=0; i<N; i++){
            set(i, (val>>i) & 0x1);
        }
        return *this;
    }

    friend std::ostream& operator<< <>(std::ostream& os,
                                       const HscMsgIOD<N>& bits);
private:
    uint8_t bits[(N+7)/8];
};

template<int N>
std::ostream& operator << (std::ostream& os, const HscMsgIOD<N>& bits)
{
    os << bits.toString();
    return os;
}

#endif // HSCMSGIOD_H
