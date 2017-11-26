#ifndef ITEMLIST_H
#define ITEMLIST_H
#include "time1.h"
#include <QDebug>

template <class Type>
class itemList {
private:
    QString name;
    Type info;
    int num;

    int idStation;
    Type Branch;
    Type Coordinates;
    Time Arrival_time;
    Time Time_of_departure;

public:
    itemList *next;
    itemList *prev;

    itemList() {
        next = nullptr;
        prev = nullptr;
        num = 0;
        idStation = 0;
    }

    itemList(Type p) {
        name = p;
        info = p;
    }

    virtual ~itemList() {
    }

    void SetArr(QString n) {
        Arrival_time.SetH(n);
        Arrival_time.SetM(n);
    }

    void SetTD(QString n) {
        Time_of_departure.SetH(n);
        Time_of_departure.SetM(n);
    }

    Time GetArr() {
        return Arrival_time;
    }

    Time GetTD() {
        return Time_of_departure;
    }

    void SetNum(int num_l) {
        num = num_l;
    }

    void SetBranch(Type b) {
        Branch = b;
    }

    void SetName(Type name_l) {
        name = name_l;
    }

    void SetIdStation(int C) {
        idStation = C;
    }

    void SetCoordinates(Type C) {
        Coordinates = C;
    }

    void SetInfo(Type info_l) {
        info = info_l;
    }

    Type GetBranch() {
        return Branch;
    }

    Type GetName() {
        return name;
    }

    int GetNum() {
        return num;
    }

    Type GetInfo() {
        return info;
    }

    int GetIdStation() {
        return idStation;
    }

    Type GetCoordinates() {
        return Coordinates;
    }

    itemList& operator= ( itemList right ) {
        name = right.name;
        info = right.info;
        num = right.num;
        idStation = right.idStation;
        Coordinates = right.Coordinates;
        Arrival_time = right.Arrival_time;
        Time_of_departure = right.Time_of_departure;
        Branch = right.Branch;

        next = right.next;
        prev = right.prev;
        return *this ;
    }

};

#endif // ITEMLIST_H
