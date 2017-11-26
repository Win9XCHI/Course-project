#include "timebase.h"


TimeBase::TimeBase() {
    H = 0;
    M = 0;
}

TimeBase::TimeBase(int i, double n) {
    H = i;
    M = n;
}

TimeBase::TimeBase(QString n) {
    bool flag = false;
    QString m;
    int j = 0;

    for (int i = 0; i < n.length(); i++) {
        if (n[i] == ":") {
            flag = true;
            H = m.toInt();
            m.clear();
        }

        if (!flag) {
            m[i] = n[i];
        }
        else {
            m[j] = n[i];
            j++;
        }
    }
    M = m.toInt();
}

void TimeBase::SetHH(QString time) {
    QString m;

    for (int i = 0; i < time.length(); i++) {
        if (time[i] == ":") {
            break;
        }
        else {
            m[i] = time[i];
        }
    }
    H = m.toInt();
}

void TimeBase::SetMM(QString time) {
    bool flag = false;
    QString m;
    int j = 0;

    for (int i = 0; i < time.length(); i++) {
        if (time[i] == ":") {
            flag = true;
            i++;
        }

        if (flag) {
            m[j] = time[i];
            j++;
            if (i == 3) {
                m[j] = '.';
                j++;
            }
        }
    }
    M = m.toDouble();
}

int TimeBase::GetHH() {
    return H;
}

double TimeBase::GetMM() {
    return M;
}

QString TimeBase::GetT() {
    int j(0);
    QString f = "";
    bool flag = false;
    QString s = "";

    s = QString::number(H);
    s += ":";
    s += QString::number(M);

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') {
            flag = true;
        }
    }

    for (int i = 0; i < s.length(); i++) {
        s[i] = s[j];
        j++;
        if (s[i] == '.') {
            i--;
        }
    }

    if (flag) {
        for (int i = 0; i < s.length() - 1; i++) {
            f[i] = s[i];
        }
    }
    else {
        for (int i = 0; i < s.length(); i++) {
            f[i] = s[i];
        }
        f += "0";
    }

    return f;
}
