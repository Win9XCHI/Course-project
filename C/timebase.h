#ifndef TIMEBASE_H
#define TIMEBASE_H
#include <QDebug>

class TimeBase {
protected:
    int H;
    double M;

    void SetHH(QString);
    void SetMM(QString);
    int GetHH();
    double GetMM();
    QString GetT();
public:
    TimeBase();
    TimeBase(int, double);
    TimeBase(QString);
    virtual ~TimeBase() {

    }

};

#endif // TIMEBASE_H
