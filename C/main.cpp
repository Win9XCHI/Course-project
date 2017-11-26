#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>
#include "list.h"
#include "projectbd.h"
#include "searchtrain.h"
#include "route.h"
#include "time1.h"

using namespace std;
int Route::size_route = 0; //для кол записів після запросу

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);
    ProjectBD ObjectBD; //БД
    SearchTrain Obj; //пошук
    int size;

    if (ObjectBD.createConnection()) { //перевірка звязку
        Obj.ReadFile(); //зчитування вхідних данних

        size = Obj.HallWay(ObjectBD);

        if (size == -1 ) {
            Obj.Error(size, "Door not found! "); //помилка
        }

     }
   else {
        qDebug() << "No Connection db!";
    }

    return 0;
}



