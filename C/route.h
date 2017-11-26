#ifndef ROUTE_H
#define ROUTE_H
#include "list.h"
#include <QDebug>
#include <sstream>

using namespace std;

class Route {
private:
    int id;
    QString StationStart;
    QString StationFinish;
    int Num_Station;
    Time Time_1;
    Time Time_2;
    QString Type;
    int ColCarriage;
    int Type1, Type2, Type3, Type4, Type5, Type6;
    Mylist<QString> Station;

    int idST;
    QString Coordinates;
    QString Name;
    int num;

    template <typename T>
    string toString(T val) {
        std::ostringstream oss;
        oss<< val;
        return oss.str();
    }
public:
    static int size_route; //кількість маршрутів
    static bool check();
    Route();

    virtual ~Route() {

    }

    void SetIdTrain(int);
    void SetSt1(QString);
    void SetSt2(QString);
    void SetType(QString);
    void SetNumber_of_stations(int);
    void SetTime(Time,Time);
    Time Time_roat();
    int Time_roatInt();
    int TimeInt();
    void SetIdStation_Train(int);
    void SetSequence_number(int);
    void SetIdCoordinates(QString);
    void SetName_S(QString);

    void SetStation();
    void WriteFile(QString, QString, QString);
    void WriteFile();
    void WriteFileSt();
    void WriteFileMap(Mylist<QString>);

    int GetIdTrain();
    QString GetSt1();
    QString GetSt2();

    Route& operator = ( Route );
};

#endif // ROUTE_H
