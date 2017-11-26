#include "route.h"
#include "list.h"
#include <QDebug>
#include <cstdlib>
#include <fstream>

Route::Route() {
    id = 0;
    StationStart = "";
    StationFinish = "";
    Num_Station = 0;
    ColCarriage = 0;
    Type1 = -1000;
    Type2 = -1000;
    Type3 = -1000;
    Type4 = -1000;
    Type5 = -1000;
    Type6 = -1000;
}

bool Route::check() { //перевірка на кількість маршрутів
    bool FLAG = false;

    if (Route::size_route >= 10) {
        FLAG = true;
    }
    return FLAG;
}

Route& Route::operator= ( Route right ) {
    id = right.id;
    StationStart = right.StationStart;
    StationFinish = right.StationFinish;
    Num_Station = right.Num_Station;
    Time_1 = right.Time_1;
    Time_2 = right.Time_2;
    Station = right.Station;
    Type = right.Type;
    ColCarriage = right.ColCarriage;
    Type1 = right.Type1;
    Type2 = right.Type2;
    Type3 = right.Type3;
    Type4 = right.Type4;
    Type5 = right.Type5;
    Type6 = right.Type6;
    return *this ;
}

void Route::WriteFile(QString St1, QString St2, QString dat) { //запись в файл інформацію про маршрут
    ofstream fout("File.txt", ios_base::app);

    QString St3 = "";

    for (int i = 0; i < St1.length(); i++) {

        if (St1[i] == '\'') {
            i++;
        }
        St3 += St1[i];
    }
    St1 = St3;
    St3 = "";

    for (int i = 0; i < St2.length(); i++) {
        if (St2[i] == '\'') {
            i++;
        }
        St3 += St2[i];
    }
    St2 = St3;

    fout << "\n$" << id << "|" << StationStart.toStdString() << "|" << StationFinish.toStdString() << "|" << Time_roat().GetTime().toStdString() << "|" << dat.toStdString() << " " << Time_1.GetTime().toStdString() << "|";

    if (Time_roat().CheckData()) {
        QString NewDat = "";
        QString Day = "";
        QString Month = "";
        QString Year = "";
        int u = 0;
        bool flag = false;
        for(int i = 0; i < dat.length(); i++) {
            if (i < 4) {
                Year[i] = dat[i];
            }
            if (i > 4 && i < 7) {
                Month[u] = dat[i];
                u++;
            }
            if (i == 7) {
                u = 0;
            }
            if (i > 7) {
                Day[u] = dat[i];
                u++;
            }
        }

        if ((Day == "30" && Month == "11") || (Day == "30" && Month == "09") || (Day == "30" && Month == "06") || (Day == "30" && Month == "04")) {
            flag = true;
        }
        if ((Day == "31" && Month == "01") || (Day == "31" && Month == "03") || (Day == "31" && Month == "05") || (Day == "31" && Month == "07") || (Day == "31" && Month == "08") || (Day == "31" && Month == "10") || (Day == "31" && Month == "12")) {
            flag = true;
        }
        if (Day == "28" && Month == "02") {
            flag = true;
        }

        if (flag) {
            if (Day == "31" && Month == "12") {
                NewDat = Year;
                int numberI = NewDat.toInt();
                numberI++;
                NewDat = "";
                NewDat += QString::number(numberI);
                NewDat += "01-01";

            }
            else {
                NewDat = Month;
                int numberI = NewDat.toInt();
                numberI++;
                NewDat = "";
                if (numberI < 10) {
                    NewDat += Year + "-" + "0" + QString::number(numberI) + "-01";
                }
                else {
                    NewDat += Year + "-" + QString::number(numberI) + "-01";
                }
            }
        }
        else {
            NewDat = dat.at(dat.length() - 1);
            int numberI = NewDat.toInt();
            numberI++;

            for(int i = 0; i < dat.length() - 1; i++) {
                NewDat[i] = dat[i];
            }
            NewDat += QString::number(numberI);
        }

        fout << NewDat.toStdString() << " ";

    }
    else {
        fout << dat.toStdString() << " ";
    }

    int numList = Station.NumberListItem();
    fout << Time_2.GetTime().toStdString() << "|" << "\n";
    fout << numList << "|\n";

    for (int i = 1; i <= numList; i++) {

        if (St1 == Station.popName(i) || St2 == Station.popName(i)) {
            fout << "&" << Station.popName(i).toStdString() << "|" << Station.popCoordinates(i).toStdString() << "|\n";
        }
        else {
            //fout << "|" << Station.popName(i).toStdString() << "|" << Station.popCoordinates(i).toStdString() << "|\n";
        }
    }

    fout.close();
}


void Route::WriteFile() { //запись в файл інформацію про маршрут
    ofstream fout("File.txt", ios_base::app);

    fout << "$" << id << "|" << StationStart.toStdString() << "|" << StationFinish.toStdString() << "";

    fout.close();
}

void Route::WriteFileSt() { //запись в файл інформацію про маршрут
    ofstream fout("File.txt", ios_base::app);

    fout << "$" << id << "|" << StationStart.toStdString() << "|" << StationFinish.toStdString() << "|" << Type.toStdString() << "|" << Time_2.GetTime().toStdString() << "|" << Time_1.GetTime().toStdString() ;

    fout.close();
}

void Route::WriteFileMap(Mylist<QString> Object) {
    ofstream fout("File.txt", ios_base::app);

    QString St1 = Object.Search("St_1");
    QString St2 = Object.Search("St_2");
    QString St3 = "";

    for (int i = 0; i < Object.Search("St_1").length(); i++) {

        if (St1[i] == '\'') {
           i++;
        }
     St3 += St1[i];
     }
     St1 = St3;
     St3 = "";

     for (int i = 0; i < Object.Search("St_2").length(); i++) {
         if (St2[i] == '\'') {
             i++;
         }
         St3 += St2[i];
     }
     St2 = St3;

    fout << "\n$";
    int numList = Station.NumberListItem();
    fout << numList << "|";

    for (int i = 1; i <= numList; i++) {

        if (St1 == Station.popName(i) || St2 == Station.popName(i)) {
            fout << "&" << Station.popName(i).toStdString() << "*" << Station.popCoordinates(i).toStdString();
        }
        else {
            fout << "!" << Station.popName(i).toStdString() << "|" << Station.popCoordinates(i).toStdString();
        }
    }

    fout.close();
}

void Route::SetIdTrain(int Train) {
    id = Train;
}

void Route::SetType(QString T) {
    Type = T;
}

int Route::GetIdTrain() {
    return id;
}

void Route::SetSt1(QString St1) {
    StationStart = St1;
}

void Route::SetSt2(QString St2) {
    StationFinish = St2;
}

QString Route::GetSt1() {
    return StationStart;
}

QString Route::GetSt2() {
    return StationFinish;
}

void Route::SetNumber_of_stations(int num_s) {
    Num_Station = num_s;
}

void Route::SetTime(Time time, Time time2) {
    Time_1 = time;
    Time_2 = time2;
}

Time Route::Time_roat() { //час в дорозі
    return Time_2 - Time_1;
}

int Route::TimeInt() { //час в дорозі
    Time T = Time_1;

    QString tt = QString::number(T.GetH());
    tt += QString::number(T.GetM());
    QString ttt = "";

    for (int i = 0; i < tt.length(); i++) {
        if (tt[i] != '.') {
            ttt += tt[i];
        }
    }
    int tttt = ttt.toInt();

    return tttt;
}

int Route::Time_roatInt() { //час в дорозі
    Time T = Time_2 - Time_1;

    QString tt = QString::number(T.GetH());
    tt += QString::number(T.GetM());
    QString ttt = "";

    for (int i = 0; i < tt.length(); i++) {
        if (tt[i] != '.') {
            ttt += tt[i];
        }
    }
    int tttt = ttt.toInt();

    return tttt;
}

void Route::SetIdStation_Train(int st) {
    idST = st;
}

void Route::SetIdCoordinates(QString coo) {
    Coordinates = coo;
}

void Route::SetSequence_number(int numS) {
    num = numS;
}

void Route::SetName_S(QString name) {
    Name = name;
}

void Route::SetStation() {
    Station.push(num, idST, Coordinates, Name);
}

