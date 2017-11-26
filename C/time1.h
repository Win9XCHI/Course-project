#ifndef TIME_H
#define TIME_H
#include "timebase.h"

class Time : TimeBase {
private:
    bool data;
public:   
    Time();
    virtual ~Time() {

    }

    bool CheckData();
    Time operator - (Time& );
    Time& operator= ( Time&  );

    void SetH(QString);
    void SetM(QString);
    int GetH();
    double GetM();
    QString GetTime();
};

#endif // TIME_H
