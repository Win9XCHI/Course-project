#ifndef PROJECTBD_H
#define PROJECTBD_H

#include <QtSql>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDebug>
#include <QSqlError>
#include "route.h"

class ProjectBD {
private:
    QSqlDatabase db;
    QSqlQuery query;

    int size;

public:
    ProjectBD();
    virtual ~ProjectBD() {

    }

    bool createConnection();
    QString LastError();
    int GetSize();
    Route GetSelectTrain(int, int, int, int);
    itemList<QString> GetSelectStation(int,int,int,int,int,int, int);
    QString GetSelectSchedule(int);
    int GetIdStation();
    int GetIdTrain();
    bool GetPlaceCarriage();
    QString GetTypeCarriage();
    int GetIdCarriage();
    int GetNumberCarriage();
    QString GetSelectInput();
    QString GetTypeTrain();

    bool DELETE1(QString, QString);
    bool SELECT(QString, QString, QString, QString, QString);
    bool UPDATE(QString, QString, QString);

    bool InsertTrain(QString, QString, QString, QString, QString, QString, QString);
    bool InsertTC(QString, QString, QString, QString, QString);
    bool InsertCarriage(QString, QString, QString, QString);
    bool InsertST(QString, QString, QString, QString, QString);
    bool InsertStation(QString, QString, QString, QString);
    bool InsertSchedule(QString, QString, QString, QString);  

};

#endif // PROJECTBD_H
