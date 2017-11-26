#ifndef SEARCHTRAIN_H
#define SEARCHTRAIN_H
#include <QDebug>
#include "list.h"
#include <string>

class ProjectBD;

class SearchTrain {
private:
    Mylist<QString> Object;
    int Door;

    bool SelV(ProjectBD, QString, QString, bool);
    bool SelT(ProjectBD, QString, QString, bool);
    void WriteNumbers(QString, QString);
    int WriteNumbers(ProjectBD,int);
    QString ReadNumbers(QString);
    void RemoveFile();
    std::string EN_RU(std::string );
    bool NOSFunc(int , ProjectBD, int, int, QString );
    Mylist<QString> StationCheck(ProjectBD);

    int TypeFunc(ProjectBD);
    int TrainFunc(ProjectBD);
    int StationFunc(ProjectBD);
    int FormationFile(int, ProjectBD);
    int FTrainFile(int, ProjectBD);
    int StationFile(int, ProjectBD);
    int SearchMapWay(ProjectBD);

    int ADD(ProjectBD, int);
    int DeleteNumber(ProjectBD);
    int DeleteSC(ProjectBD);
    int DeleteSh(ProjectBD);
    QString Authentication(ProjectBD);

public:
    SearchTrain();
    virtual ~SearchTrain() {

    }
    void ReadFile();
    void Error(int, QString);
    int HallWay(ProjectBD);
};

#endif // SEARCHTRAIN_H
