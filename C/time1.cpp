#include "time1.h"
#include <math.h>

Time::Time() {
    data = false;
}

Time Time :: operator - ( Time& right ) {
    Time Ob;

    if (right.GetM() > GetM()) {
        Ob.H = abs(right.GetH() - GetH()) - 1;
        Ob.M = right.GetM() - GetM();
    }
    else {
        Ob.H = abs(right.GetH() - GetH());
        Ob.M = GetM() - right.GetM();
    }

    if (right.GetH() > 12 && GetH() < 12 ) {
        Ob.H = GetH() - right.GetH() + 24;
        Ob.data = true;
    }

    return Ob;
}

bool Time::CheckData() {
    return data;
}

Time& Time::operator= ( Time& right ) {
    H = right.GetH();
    M = right.GetM();
    data = right.CheckData();
    return *this ;
}

void Time::SetH(QString time) {
    SetHH(time);
}

void Time::SetM(QString time) {
    SetMM(time);
}

int Time::GetH() {
    return GetHH();
}

double Time::GetM() {
    return GetMM();
}

QString Time::GetTime() {
    return GetT();
}
