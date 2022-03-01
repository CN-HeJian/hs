#ifndef HSCCOLLECTIONDATA_H
#define HSCCOLLECTIONDATA_H


class HscCollectionData
{

public:
    explicit HscCollectionData();

    int getId() const;
    void setId(int Id);

    double getCh1() const;
    void setCh1(double ch);

    double getCh2() const;
    void setCh2(double ch);

    double getCh3() const;
    void setCh3(double ch);

    double getCh4() const;
    void setCh4(double ch);

    double getCh5() const;
    void setCh5(double ch);

    double getCh6() const;
    void setCh6(double ch);

    double getCh7() const;
    void setCh7(double ch);

    double getCh8() const;
    void setCh8(double ch);

    double getCh9() const;
    void setCh9(double ch);

    double getCh10() const;
    void setCh10(double ch);

private:
    int m_id;
    double ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9,ch10;

};

#endif // HSCCOLLECTIONDATA_H
