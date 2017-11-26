#include "searchtrain.h"
#include "list.h"
#include "projectbd.h"
#include <fstream>
#include <windows.h>
#include <string>


SearchTrain::SearchTrain() {
    Door = 0;
}

int SearchTrain::HallWay(ProjectBD ObjectBD) {
    int size = 0;
    RemoveFile(); //видалення файлів

    Door = Object.Search("C").toInt();
    int numList = Object.NumberListItem();
    if (Door == 0) {
        for (int i = 0; i < numList; i++) {
            if (Object.popName(i) == "Fil") {
                Door = 10;
            }
        }
    }

    switch(Door) {
        case 0: {
            size = TypeFunc(ObjectBD); //пошук маршрутів (1)

            if (size > 0) {
               size = FormationFile(size, ObjectBD); //запис маршрутів
               if (size != 0) {
                   Error(size, "Simakin flew");
                   return 0;
               }
               else {
                   ofstream fout("File.txt", ios_base::app);
                   fout << "$";
                   fout.close();
                   return 0;
               }
            }
            else {
                ofstream fout("File.txt");
                fout << "Not Train";
                fout.close();
                return 0;
               return 0;
            }
            return size;
            break;
        }
        case 10: {
        size = TrainFunc(ObjectBD); //пошук маршрутів (1)

        if (size < 0) {
            ofstream fout("File.txt");
            QString buf;

            switch (size) {
                case -98: {
                    buf = "Not Train";
                    break;
                }
                case -99: {
                    buf = "Not Train";
                    break;
                }
                case -97: {
                    buf = "Not type";
                    break;
                }
                case -1: {
                    buf = "false";
                    size = 0;
                    break;
                }
            }
            fout << buf.toStdString();
            fout.close();
            return 0;
        }
        else {
           size = FTrainFile(size, ObjectBD); //запис маршрутів
        }

        ofstream fout("File.txt", ios_base::app);
        fout << "$";
        fout.close();
        return 0;

            break;
        }
        case 1: {
        }
        case 2: {
        }
        case 3: {
        }
        case 4: {
            size = ADD(ObjectBD, Door); //
            ofstream fout("FileCheck.txt");
            QString buf;

            if (size < 0) {

                switch (size) {
                    case -12: {
                        buf = "Not num";
                        break;
                    }
                    case -13: {
                        buf = "Not St_1";
                        break;
                    }
                    case -14: {
                        buf = "Not St_2";
                        break;
                    }
                    case -21: {
                        buf = "Not cod";
                        break;
                    }
                    case -1: {
                        buf = "false";
                        size = 0;
                        break;
                    }
                }
                fout << buf.toStdString();
            }
            else {
               fout << "OK";
            }
            fout.close();
            return size;
            break;
        }
        case 5: {
            size = StationFunc(ObjectBD); //

            if (size < 0) {
                ofstream fout("File.txt");
                QString buf;

                switch (size) {
                    case -19: {
                        buf = "Not dat";
                        break;
                    }
                    case -32: {
                        buf = "Not St";
                        break;
                    }
                    case -1: {
                        buf = "false";
                        size = 0;
                        break;
                    }
                }
                fout << buf.toStdString();
                fout.close();
                return 0;
            }
            else {
               size = StationFile(size, ObjectBD);
            }

            ofstream fout("File.txt", ios_base::app);
            fout << "$";
            fout.close();
            return 0;
            break;

        }
        case 6: {
            Mylist<QString> StationInput = StationCheck(ObjectBD);
            ofstream fout("File.txt");
            int col = StationInput.NumberListItem() + 1;

            if (col != 1) {
                fout << "$";

                for (int i = 1; i < col; i++) {
                    fout << StationInput.Search(StationInput.popName(i)).toStdString() + "$";
                }
            }
            else {
                fout << "Not Station";
            }
            fout.close();
            break;
        }

    case 7: {
        size = DeleteNumber(ObjectBD);
        ofstream fout("FileCheck.txt");

        if (size == 0) {
            fout << "true";
        }
        else {
            fout << "Not Delete (Error DataBase)";
        }
        fout.close();
        break;
    }
    case 8: {
        size = DeleteSC(ObjectBD);
        ofstream fout("FileCheck.txt");

        if (size == 0) {
            fout << "true";
        }
        else {
            fout << "Not Delete (Error DataBase)";
        }
        fout.close();
        break;
    }
    case 9: {
        size = DeleteSh(ObjectBD);
        ofstream fout("FileCheck.txt");

        if (size == 0) {
            fout << "true";
        }
        else {
            fout << "Not Delete (Error DataBase)";
        }
        fout.close();
        break;
    }


    case 111: {

        QString p = Authentication(ObjectBD);
        ofstream fout("FileCheck.txt");
        ofstream fout2("access.log", ios_base::app);

            if (p == "-10") {
                fout << "Not Authentication";
            }
            else {
                if (p == "-1") {
                    fout << "Error server";
                }
                else {
                    fout << "true";
                    fout2 << "Signed in [" + p.toStdString() + "]\n";
                }
            }
        fout.close();
        fout2.close();
        break;
    }

    case 20: {
        size = SearchMapWay(ObjectBD);
        if (size != 0) {
             Error(size, "Simakin flew");
         }
         else {
              ofstream fout("File.txt", ios_base::app);
              fout << "$";
              fout.close();
         }
        break;
    }

        default: {
            return -1;
        }
    }
    return 0;
}

int SearchTrain::SearchMapWay(ProjectBD ObjectBD) {
    Route ObjectRoute;
    itemList<QString> Buff;

    if (ObjectBD.SELECT("Station.Name_S, Station.Coordinates, Station_Train.Sequence_number", "Station, Station_Train", "Station_Train.idTrain = " + Object.Search("Num") + " AND Station_Train.idStation_Train = Station.idStation", "", "")) {
          for (int j = 0; j < ObjectBD.GetSize(); j++) {
           Buff = ObjectBD.GetSelectStation(1,1,0,1,0,0,0);
           ObjectRoute.SetName_S(Buff.GetName());
           ObjectRoute.SetIdCoordinates(Buff.GetCoordinates());
           ObjectRoute.SetSequence_number(Buff.GetNum());
           ObjectRoute.SetStation();
           }
          ObjectRoute.WriteFileMap(Object);
     }
     else {
        Error(-2, "SMW SS| " + ObjectBD.LastError());
           return -2;
     }
    return 0;
}

QString SearchTrain::Authentication(ProjectBD ObjectBD) {
    QString PIB;

    if (ObjectBD.SELECT("PIB", "Input", "Login = '" + Object.Search("login") + "' AND Password = '" + Object.Search("password") + "'","", "")) {
        PIB = ObjectBD.GetSelectInput();

        if (PIB == "") {
            return "-10";
        }
    }
    else {
        Error(-1, "A SI| " + ObjectBD.LastError());
        return "-1";
    }

    return PIB;
}

int SearchTrain::DeleteNumber(ProjectBD ObjectBD) {
    QString num;
    num = Object.Search("Num");
    int numC;

    if (ObjectBD.DELETE1("Station_Train", "idTrain = " + num)) {

        if (ObjectBD.SELECT("idTrain_Carriage", "Train_Carriage", "idTrain = " + num,"", "")) {

            for (int i = 0; i < ObjectBD.GetSize(); i++) {
                 numC = ObjectBD.GetIdCarriage();

                if (ObjectBD.DELETE1("Carriage", "Carriage.idCarriage = " + QString::number(numC))) {

                    if (ObjectBD.DELETE1("Train_Carriage", "idTrain = " + num)) {

                        if (ObjectBD.DELETE1("Schedul", "idTrain_S = " + num)) {

                            if (ObjectBD.DELETE1("Train", "idTrain = " + num)) {

                            }
                            else {
                                Error(-5, "DN DT| " + ObjectBD.LastError());
                                return -5;
                            }
                        }
                        else {
                            Error(-4, "DN DSh| " + ObjectBD.LastError());
                            return -4;
                        }
                    }
                    else {
                        Error(-3, "DN DTC| " + ObjectBD.LastError());
                        return -3;
                    }
                }
                else {
                    Error(-2, "DN DC| " + ObjectBD.LastError());
                    return -2;
                }
            }
         }
         else {
            Error(-6, "DN STC| " + ObjectBD.LastError());
            return -6;
         }
    }
    else {
        Error(-1, "DN DST| " + ObjectBD.LastError());
        return -1;
    }
    return 0;
}

int SearchTrain::DeleteSC(ProjectBD ObjectBD) {
    QString num;
    num = Object.Search("Num");
    int Sn, numC;

    if (Object.Search("S") != "0") {

        if (ObjectBD.SELECT("Sequence_number", "Station_Train", "idStation_Train = " + Object.Search("S"),"", "")) {
            Sn = ObjectBD.GetSelectStation(0,0,0,1,0,0,0).GetNum();


            if (ObjectBD.DELETE1("Station_Train", "idTrain = " + num + " AND idStation_Train = " + Object.Search("S"))) {

               if (ObjectBD.UPDATE("Train", "Number_of_stations = Number_of_stations - 1","idTrain = " + num)) {

                   if (ObjectBD.SELECT("idTrain_Carriage", "Train_Carriage", "idTrain = " + num,"", "")) {

                       for (int i = 0; i < ObjectBD.GetSize(); i++) {
                            numC = ObjectBD.GetIdCarriage();

                            if (ObjectBD.DELETE1("Carriage", " Station_number = " + QString::number(Sn) + " AND idCarriage = " + QString::number(numC))) {

                                if (ObjectBD.UPDATE("Station_Train", "Sequence_number = Sequence_number - 1","Sequence_number > " + QString::number(Sn) + " AND idTrain = " + num)) {


                                }
                                else {
                                    Error(-6, "DSC UC| " + ObjectBD.LastError());
                                    return -6;
                                }
                            }
                            else {
                                Error(-3, "DSC DC| " + ObjectBD.LastError());
                                return -3;
                            }
                       }
                    }
                    else {
                       Error(-5, "DSC STC| " + ObjectBD.LastError());
                       return -5;
                    }
                }
                else {
                   Error(-2, "DSC UT| " + ObjectBD.LastError());
                   return -2;
                }
            }
            else {
                Error(-1, "DSC DST| " + ObjectBD.LastError());
                return -1;
            }
        }
        else {
            Error(-4, "DSC SST| " + ObjectBD.LastError());
            return -4;
        }
    }
    if (Object.Search("nC") != 0) {

        if (ObjectBD.DELETE1("Carriage", "idCarriage = " + Object.Search("nC"))) {
            if (ObjectBD.SELECT("Number_carriage", "Train_Carriage", "idTrain_Carriage = " + Object.Search("nC"),"", "")) {
                Sn = ObjectBD.GetNumberCarriage();

                if (ObjectBD.DELETE1("Train_Carriage", "idTrain_Carriage = " + Object.Search("nC"))) {

                    if (ObjectBD.UPDATE("Train_Carriage", "Number_carriage = Number_carriage - 1","Number_carriage > " + QString::number(Sn) + " AND idTrain = " + num)) {


                    }
                    else {
                        Error(-10, "DSC UTC| " + ObjectBD.LastError());
                        return -10;
                    }
                }
                else {
                    Error(-8, "DSC DTC| " + ObjectBD.LastError());
                    return -8;
                }
            }
            else {
                Error(-9, "DSC STC| " + ObjectBD.LastError());
                return -9;
            }
        }
        else {
            Error(-7, "DSC DC| " + ObjectBD.LastError());
            return -7;
        }
    }
    return 0;
}

int SearchTrain::DeleteSh(ProjectBD ObjectBD) {

    if (!ObjectBD.DELETE1("Schedul", "idTrain_S = " + Object.Search("Num") + " AND Start = '" + Object.Search("dat") + "'")) {
        Error(-1, "DSh DSh| " + ObjectBD.LastError());
        return -1;
    }
    return 0;
}

Mylist<QString> SearchTrain::StationCheck(ProjectBD ObjectBD) {
    QString val;
    itemList<QString> St;
    Mylist<QString> StationInput;
    int u = 0;
    val = Object.Search("value");

    if (ObjectBD.SELECT("Name_S, Branch", "Station", "Name_S LIKE '%" + val + "%'","", "")) {
        for (int i = 0; i < ObjectBD.GetSize(); i++) {
            St = ObjectBD.GetSelectStation(0,1,0,0,0,0,1);
            val = St.GetName() + "|" + St.GetBranch();
            if (val != "|") {
                StationInput.push("Station" + QString::number(u), val);
                u++;
            }
        }
    }
    else {
        Error(-1, "SC SS| " + ObjectBD.LastError());
    }

    return StationInput;
}

int SearchTrain::StationFunc(ProjectBD ObjectBD) {
    int size2 = 0;
    int size;
    QString num;

    if (ObjectBD.SELECT("Schedul.idTrain_S", "Schedul", "Schedul.Start = '" + Object.Search("dat") + "'","", "")) { //запит на дату
        size = WriteNumbers(ObjectBD,0); //запис у файл номерів

        if (size == 0) {
            return -19;
        }

        string buffer;
        ifstream file("Numbers.txt");

        for (int i = 0; i < size; i++) {
            file >> buffer;
            num = QString::fromStdString(buffer); //считування номерів

            if (ObjectBD.SELECT("Train.idTrain", "Station, Station_Train, Train", "Station.Name_S = '" + Object.Search("St") + "' AND Station.idStation = Station_Train.idStation_Train AND Station_Train.idTrain = " + num + " AND Train.idTrain = " + num,"", "")) {
                int st = ObjectBD.GetIdTrain();

                if (st != 0) {
                    WriteNumbers(num, "2"); //запис номерів
                    size2++;
                }
            }
            else {
                Error(-2, "StFu SidT| " + ObjectBD.LastError());
            }
        }
        file.close();

        if (size2 == 0) {
            return -32;
        }
        else {
            size = size2;
        }

    }
    else {
        Error(-1, "StFu SSh| " + ObjectBD.LastError());
        return -1;
    }

    return size;
}

int SearchTrain::StationFile(int size, ProjectBD ObjectBD) {
    Route ObjectRoute[size];
    string buffer;
    QString num;
    itemList<QString> Buff;
    Route::size_route = size; //кількість маршрутів
    ifstream file("Numbers2.txt");
    int mas[size];

    for (int i = 0; i < size; i++ ) {
        mas[i] = i;
        file >> buffer;
        num = QString::fromStdString(buffer); //считування номера

        if (ObjectBD.SELECT("idTrain, St_1, St_2, TypeTrain", "Train", "idTrain = " + num,"", "")) {
           ObjectRoute[i] = ObjectBD.GetSelectTrain(1,1,1,1); //запис номера, станції початку та кінця

           if (ObjectBD.SELECT("Station.Name_S, Station_Train.Arrival_time, Station_Train.Time_of_departure", "Station, Station_Train", "Station_Train.idTrain = " + num + " AND Station_Train.idStation_Train = Station.idStation AND Station.Name_S = '" + Object.Search("St") + "'", "", "")) {
               Buff = ObjectBD.GetSelectStation(0,1,0,0,1,1,0); //видає час
               ObjectRoute[i].SetTime(Buff.GetTD(), Buff.GetArr());

           }
           else {
               file.close();
               Error(-3, "StF SST| " + ObjectBD.LastError());
               return -3;
           }
        }
        else {
            file.close();
            Error(-1, "StF ST| " + ObjectBD.LastError());
            return -1;
        }
    }
    file.close();

    int i = size - 1;
    int m = 0;
    int l = 1;
    int k = 1;
    int p1,p2;
    while ((k != 0) && (i > 0))  {
        k = 0; // обмінів не було

        for (int j = 0; j <= i - 1; j++) {
            p1 = ObjectRoute[m].TimeInt();
            p2 = ObjectRoute[l].TimeInt();
           if (p1 > p2) {

              int a = mas[m];
              mas[m] = mas[l];
              mas[l] = a;
              k = 1;
            }
           else {
               m = mas[j + 1];
           }
           l++;
           if (j == i - 1) {
               m = mas[0];
               l = mas[1];
           }
        }
        i--;
     }

    for (i = 0; i < size; i++) {
        ObjectRoute[mas[i]].WriteFileSt();
    }
    return 0;
}

int SearchTrain::TrainFunc(ProjectBD ObjectBD) { //пошук маршрутів (1)
    bool FlagV = false; //для перевірки виконання запиту
    QString fil;
    int size2 = 0;
    int size;
    QString num;
    QString Ofil;

    if (Object.Search("Fil") == "1") {
        if (ObjectBD.SELECT("idTrain", "Train", "","", "")) { //запит на філії
            size = WriteNumbers(ObjectBD,1); //запис у файл номерів
            if (size == 0) {
                return -98;
            }
        }
        else {
            qDebug() << "Error train select (T1)";
            ObjectBD.LastError();
            Error(-3, ObjectBD.LastError());
            return -1;
        }
    }
    else {
        Ofil = Object.Search("Fil");
            if (Ofil == "2") {
                fil = "Одеська";
            }
            if (Ofil == "3") {
                fil = "Південна";
            }
            if (Ofil == "4") {
                fil = "Південно-Західна";
            }
            if (Ofil == "5") {
                fil = "Придніпровська";
            }
            if (Ofil == "6") {
                fil = "Донецька";
            }
            if (Ofil == "7") {
                fil = "Львівська";
            }
        if (ObjectBD.SELECT("Train.idTrain", "Train, Station, Station_Train", "Station_Train.idTrain = Train.idTrain AND Station_Train.Sequence_number = 1 AND Station_train.idStation_Train = Station.idStation AND Station.Branch = '" + fil + "'","", "")) { //запит на філії
            size = WriteNumbers(ObjectBD,1); //запис у файл номерів
            if (size == 0) {
                return -99;
            }
        }
        else {
            qDebug() << "Error train select (T1)";
            ObjectBD.LastError();
            Error(-3, ObjectBD.LastError());
            return -1;
        }
    }
        string buffer;
        ifstream file0("Numbers.txt");

        for (int i = 0; i < size; i++) {

            file0 >> buffer;
            num = QString::fromStdString(buffer); //считування номера
            FlagV = false;

            // перевірка на тип
            int numList = Object.NumberListItem();
            for (int i = 1; i <= numList; i++) { //йдемо по вхідним данним

                if (!FlagV) {
                    Ofil = Object.popName(i);
                    if (Ofil == "v1") {
                        FlagV = SelV(ObjectBD,"v1", num, FlagV);
                    }
                    if (Ofil == "v2") {
                        FlagV = SelV(ObjectBD,"v2", num, FlagV);
                    }
                    if (Ofil == "v3") {
                        FlagV = SelV(ObjectBD,"v3", num, FlagV);
                    }
                    if (Ofil == "v4") {
                        FlagV = SelV(ObjectBD,"v4", num, FlagV);
                    }
                    if (Ofil == "v5") {
                        FlagV = SelV(ObjectBD,"v5", num, FlagV);
                    }
                }
            }

            if (FlagV) { //чи були знайдені v та t
                WriteNumbers(num, "1"); //запис нових номерів маршрутів
                size2++; //рахує кількість нових маршрутів
            }
        }
        file0.close();

        size = size2;

        if (size == 0) {
            return -97;
        }

    return size; //повертає кількість знайдених номерів маршрутів
}

int SearchTrain::FTrainFile(int size, ProjectBD ObjectBD) { //вивід інформації по маршрутам
    Route ObjectRoute[size];
    string buffer;
    QString num;
    Route::size_route = size; //кількість маршрутів
    ifstream file("Numbers1.txt");

    for (int i = 0; i < size; i++ ) {
        file >> buffer;
        num = QString::fromStdString(buffer); //считування номера

        if (ObjectBD.SELECT("idTrain, St_1, St_2", "Train", "idTrain = " + num,"", "")) {
           ObjectRoute[i] = ObjectBD.GetSelectTrain(1,1,1,0); //запис номера, станції початку та кінця
           ObjectRoute[i].WriteFile();
        }
        else {
            file.close();
            return -1;
        }
    }
    file.close();
    return 0;
}

bool SearchTrain::SelV(ProjectBD ObjectBD, QString v, QString num, bool flagV) { //повертає чи виконаний запит
    bool flag = false;

    if (ObjectBD.SELECT("idTrain", "Train", "idTrain = " + num + " AND TypeTrain = '" + Object.Search(v) + "'","", "")) {

        if (ObjectBD.GetSize() > 0) { //скільки було виведено записів запитом
            flag = true;
        }
        else {
            if (!flagV) {
                flag = false;
            }
        }
    }
    else {
       ObjectBD.LastError(); //повертає останню помилку
       flag = false;
    }

    return flag;
}

bool SearchTrain::SelT(ProjectBD ObjectBD, QString t, QString num, bool flagT) {
    bool flag = false;

    if (ObjectBD.SELECT("idTrain", "Train_Carriage", "idTrain = " + num + " AND Type_C = '" + Object.Search(t) + "'","", "")) {

        if (ObjectBD.GetSize() > 0) {
            flag = true;
        }
        else {
            if (!flagT) {
                flag = false;
            }
        }
    }
    else {
       ObjectBD.LastError();
       flag = false;
    }

    return flag;
}

int SearchTrain::TypeFunc(ProjectBD ObjectBD) { //пошук маршрутів (1)
    bool FlagV = false; //для перевірки виконання запиту
    bool FlagT = false;
    int size2 = 0;
    int size;
    QString num;
    QString Ofil;

    if (ObjectBD.SELECT("Schedul.idTrain_S", "Schedul", "Schedul.Start = '" + Object.Search("dat") + "'","", "")) { //запит на дату
        size = WriteNumbers(ObjectBD,0); //запис у файл номерів
        string buffer;
        ifstream file0("Numbers.txt");

        for (int i = 0; i < size; i++) {

            file0 >> buffer;
            num = QString::fromStdString(buffer); //считування номера
            FlagT = false;
            FlagV = false;

            // перевірка на тип
            int numList = Object.NumberListItem();
            for (int i = 1; i <= numList; i++) { //йдемо по вхідним данним

                if (!FlagV) {
                    Ofil = Object.popName(i);
                    if (Ofil == "v1") {
                        FlagV = SelV(ObjectBD,"v1", num, FlagV);
                    }
                    if (Ofil == "v2") {
                        FlagV = SelV(ObjectBD,"v2", num, FlagV);
                    }
                    if (Ofil == "v3") {
                        FlagV = SelV(ObjectBD,"v3", num, FlagV);
                    }
                    if (Ofil == "v4") {
                        FlagV = SelV(ObjectBD,"v4", num, FlagV);
                    }
                    if (Ofil == "v5") {
                        FlagV = SelV(ObjectBD,"v5", num, FlagV);
                    }
                }
                if (!FlagT) {
                    Ofil = Object.popName(i);
                    if (Ofil == "t1") {
                        FlagT = SelT(ObjectBD,"t1", num, FlagT);
                    }
                    if (Ofil == "t2") {
                        FlagT = SelT(ObjectBD,"t2", num, FlagT);
                    }
                    if (Ofil == "t3") {
                        FlagT = SelT(ObjectBD,"t3", num, FlagT);
                    }
                    if (Ofil == "t4") {
                        FlagT = SelT(ObjectBD,"t4", num, FlagT);
                    }
                    if (Ofil == "t5") {
                        FlagT = SelT(ObjectBD,"t5", num, FlagT);
                    }
                    if (Ofil == "t6") {
                        FlagT = SelT(ObjectBD,"t6", num, FlagT);
                    }
                }
            }

            if (FlagT && FlagV) { //чи були знайдені v та t
                WriteNumbers(num, "1"); //запис нових номерів маршрутів
                size2++; //рахує кількість нових маршрутів
            }
        }
        file0.close();

        size = 0;
        // перевірка на станції
        ifstream file("Numbers1.txt");
        bool flag_St = false;
        QString type;
        bool flag_Ca = false;
        bool Type1 = false;
        bool Type2 = false;
        bool Type3 = false;
        bool Type4 = false;
        bool Type5 = false;
        bool Type6 = false;
        int NOS = 0;
        int st1 = 0;
        int st2 = 0;

        for (int i = 0; i < size2; i++) {
            file >> buffer;
            num = QString::fromStdString(buffer); //считування номерів
            flag_St = false;

            if (ObjectBD.SELECT("Station_Train.Sequence_number, Station.Name_S", "Station, Station_Train", "Station.Name_S in ('" + Object.Search("St_1") + "', '" + Object.Search("St_2") + "')  AND Station.idStation = Station_Train.idStation_Train AND Station_Train.idTrain = " + num ,"", "Station_Train.Sequence_number DESC")) {
                itemList<QString> Obj1 = ObjectBD.GetSelectStation(0,1,0,1,0,0,0);
                itemList<QString> Obj2 = ObjectBD.GetSelectStation(0,1,0,1,0,0,0); //запит по станціям
                st1 = Obj1.GetNum();
                st2 = Obj2.GetNum();

                if (st1 == 0 || st2 == 0) {
                    flag_St = true;
                }
            }

            if (ObjectBD.SELECT("TypeTrain","Train","idTrain = " + num,"","")) {
                    type = ObjectBD.GetTypeTrain();
             }
            if (type == "Електричка") {
                if (st1 > st2 && !flag_St) {
                    WriteNumbers(num, "2"); //запис номерів
                    size++;
                }
            }
            else {
                //Carriage
                if (ObjectBD.SELECT("Type_C", "Train_Carriage", "idTrain = " + num ,"", "")) {
                    for (int j = 0; j < ObjectBD.GetSize(); j++) {
                        QString c = ObjectBD.GetTypeCarriage();

                        if (c == "СВ") {
                            Type1 = true;
                            continue;
                        }
                        if (c == "Люкс") {
                            Type2 = true;
                            continue;
                        }
                        if (c == "Купе") {
                            Type3 = true;
                            continue;
                        }
                        if (c == "Плацкарт") {
                            Type4 = true;
                            continue;
                        }
                        if (c == "Сидячий 1-го класу") {
                            Type5 = true;
                            continue;
                        }
                        if (c == "Сидячий 2-го класу") {
                            Type6 = true;
                        }
                    }

                    if ( Type1) {
                        NOS = 18;
                        flag_Ca = NOSFunc(NOS,ObjectBD, st1, st2, num);
                    }
                    if ( Type2 && !flag_Ca) {
                        NOS = 36;
                        flag_Ca = NOSFunc(NOS,ObjectBD, st1, st2, num);
                    }
                    if ( Type3 && !flag_Ca) {
                        NOS = 36;
                        flag_Ca = NOSFunc(NOS,ObjectBD, st1, st2, num);
                    }
                    if ( Type4 && !flag_Ca) {
                        NOS = 56;
                        flag_Ca = NOSFunc(NOS,ObjectBD, st1, st2, num);
                    }
                    if ( Type5 && !flag_Ca) {
                        NOS = 60;
                        flag_Ca = NOSFunc(NOS,ObjectBD, st1, st2, num);
                    }
                    if ( Type6 && !flag_Ca) {
                        NOS = 60;
                        flag_Ca = NOSFunc(NOS,ObjectBD, st1, st2, num);
                    }
                }

                if (st1 > st2 && !flag_St && flag_Ca) { //перевірка станцій
                    WriteNumbers(num, "2"); //запис номерів
                    size++;
                }
            }

        }
        file.close();

        if (size == 0) {
            return -3;
        }

    }
    else {
        ObjectBD.LastError();
        Error(-1, " |" + ObjectBD.LastError());
        return -1;
    }

    return size; //повертає кількість знайдених номерів маршрутів
}

bool SearchTrain::NOSFunc(int NOS, ProjectBD ObjectBD, int st2, int st1, QString num) {
    bool flag_Ca1 = true;
    bool flag_Ca2 = false;

    for (int u = 1; u <= NOS; u++) {
        if (ObjectBD.SELECT("Carriage.Employment", "Carriage, Train_Carriage", "Train_Carriage.idTrain = " + num + " AND Carriage.idCarriage = Train_Carriage.idTrain_Carriage AND Carriage.Station_number >= " + QString::number(st1) + " AND Carriage.Station_number < " + QString::number(st2) + " AND Carriage.Place = " + QString::number(u),"", "")) {

            if (ObjectBD.GetSize() != 0) {
                for (int j = 0; j < ObjectBD.GetSize(); j++) {

                    if (!ObjectBD.GetPlaceCarriage()) {
                        flag_Ca1 = false;
                        break;
                    }
                }
                if (flag_Ca1) {
                    flag_Ca2 = true;
                }
            }
        }
    }

    return flag_Ca2;
}

void SearchTrain::WriteNumbers(QString num, QString i) { //запис номера маршруту
     i = "Numbers" + i + ".txt";
     ofstream fout(i.toStdString(), ios_base::app);
     fout << num.toStdString() << " ";

     fout.close();
}

int SearchTrain::WriteNumbers(ProjectBD ObjectBD, int c) { //запис номерів
    ofstream fout("Numbers.txt");
    int size;
    size = ObjectBD.GetSize(); //кількість записів після запиту

    for (int i = 0; i < size; i++) {
        if (c == 0) {
            fout << ObjectBD.GetSelectSchedule(1).toStdString() << " ";
        }
        if (c == 1) {
            Route Object = ObjectBD.GetSelectTrain(1,0,0,0);
            fout << Object.GetIdTrain() << " ";

        }
    }

   fout.close();
   return size; //повертає кількість номерів
}

void SearchTrain::ReadFile() { //вхідні дані
    string buffer;
    QString name;
    int ad = 0;;

    ifstream file("dataIndex.txt",  std::ifstream::binary);
    int j = 0;

    while (file >> buffer) {
        if (j % 2 == 0) {
            name = QString::fromStdString(buffer);
        }
        else {
            if (buffer == "111") {
                ad = 111;
            }
            if (ad == 0) {
                buffer = EN_RU(buffer);
            }

            if (name == "Type") {
                switch (QString::fromStdString(buffer).toInt()) {

                    case 1: {
                        buffer = "Швидкісний";
                        break;
                    }
                    case 2: {
                        buffer = "Фірмовий";
                        break;
                    }
                    case 3: {
                        buffer = "Швидкий";
                        break;
                    }
                    case 4: {
                        buffer = "Пасажирський";
                        break;
                    }
                    case 5: {
                        buffer = "Електричка";
                        break;
                    }
                }
            }

            if (name == "Type_V") {
                switch (QString::fromStdString(buffer).toInt()) {

                    case 1: {
                        buffer = "СВ";
                        break;
                    }
                    case 2: {
                        buffer = "Люкс";
                        break;
                    }
                    case 3: {
                        buffer = "Купе";
                        break;
                    }
                    case 4: {
                        buffer = "Плацкарт";
                        break;
                    }
                    case 5: {
                        buffer = "Сидячий 1-го класу";
                        break;
                    }
                    case 6: {
                        buffer = "Сидячий 2-го класу";
                        break;
                    }
                }
            }

            if(name == "v1") {
                buffer = "Швидкісний";
            }
            if(name == "v2") {
                buffer = "Фірмовий";
            }
            if(name == "v3") {
                buffer = "Швидкий";
            }
            if(name == "v4") {
                buffer = "Пасажирський";
            }
            if(name == "v5") {
                buffer = "Електричка";
            }
            if(name == "t1") {
                buffer = "СВ";
            }
            if(name == "t2") {
                buffer = "Люкс";
            }
            if(name == "t3") {
                buffer = "Купе";
            }
            if(name == "t4") {
                buffer = "Плацкарт";
            }
            if(name == "t5") {
                buffer = "Сидячий 1-го класу";
            }
            if(name == "t6") {
                buffer = "Сидячий 2-го класу";
            }

            Object.push(name, QString::fromStdString(buffer));
        }
        j++;
    }
    file.close();
}

void SearchTrain::Error(int size, QString i) { //запис у файл помилок
    ofstream fout("Error.txt", ios_base::app);
    fout << "!Not_Train " << size << " " << i.toStdString();
    fout.close();
}

void SearchTrain::RemoveFile() {
    remove("Error.txt");
    remove("File.txt");
    remove("Numbers.txt");
    remove("Numbers1.txt");
    remove("Numbers2.txt");
    remove("FileCheck.txt");
}

int SearchTrain::FormationFile(int size, ProjectBD ObjectBD) { //вивід інформації по маршрутам
    Route ObjectRoute[size];
    itemList<QString> Buff;
    itemList<QString> Buff2;
    string buffer;
    QString num;
    Route::size_route = size; //кількість маршрутів
    ifstream file("Numbers2.txt");
    QString St_1 = Object.Search("St_1");
    QString St_2 = Object.Search("St_2");
    QString dat = Object.Search("dat");
    int mas[size];

    for (int i = 0; i < size; i++ ) {
        mas[i] = i;
        file >> buffer;
        num = QString::fromStdString(buffer); //считування номера

        if (ObjectBD.SELECT("idTrain, St_1, St_2", "Train", "idTrain = " + num,"", "")) {
           ObjectRoute[i] = ObjectBD.GetSelectTrain(1,1,1,0); //запис номера, станції початку та кінця

           if (ObjectBD.SELECT("Station.Name_S, Station.Coordinates, Station_Train.Sequence_number", "Station, Station_Train", "Station_Train.idTrain = " + num + " AND Station_Train.idStation_Train = Station.idStation", "", "")) {

               for (int j = 0; j < ObjectBD.GetSize(); j++) {
                   Buff = ObjectBD.GetSelectStation(1,1,0,1,0,0,0);
                   ObjectRoute[i].SetName_S(Buff.GetName());
                   ObjectRoute[i].SetIdCoordinates(Buff.GetCoordinates());
                   ObjectRoute[i].SetSequence_number(Buff.GetNum()); // запис координатів станцій
                   ObjectRoute[i].SetStation();
               }

               if (ObjectBD.SELECT("Station.Name_S, Station_Train.Arrival_time, Station_Train.Time_of_departure", "Station, Station_Train", "Station_Train.idTrain = " + num + " AND Station_Train.idStation_Train = Station.idStation AND Station.Name_S in ('" + St_1 + "', '" + St_2 + "')", "", "Station_Train.Sequence_number DESC")) {
                   Buff = ObjectBD.GetSelectStation(0,1,0,0,1,1,0); //видає час
                   Buff2 = ObjectBD.GetSelectStation(0,1,0,0,1,1,0);
                   ObjectRoute[i].SetTime(Buff2.GetTD(), Buff.GetArr());

               }
               else {
                   file.close();
                   Error(-3, "ForFi SS [n,t]| " + ObjectBD.LastError());
                   return -3;
               }
           }
           else {
               file.close();
               Error(-2, "ForFi SS [n,c,s]| " + ObjectBD.LastError());
               return -2;
           }
        }
        else {
            file.close();
            Error(-1, "ForFi ST| " + ObjectBD.LastError());
            return -1;
        }
    }
    file.close();

    int i = size - 1;
    int m = 0;
    int l = 1;
    int k = 1;
    int p1,p2;
    while ((k != 0) && (i > 0))  {
        k = 0; // обмінів не було

        for (int j = 0; j <= i - 1; j++) {
            p1 = ObjectRoute[m].Time_roatInt();
            p2 = ObjectRoute[l].Time_roatInt();
           if (p1 > p2) {

              int a = mas[m];
              mas[m] = mas[l];
              mas[l] = a;
              k = 1;
            }
           else {
               m = mas[j + 1];
           }
           l++;
           if (j == i - 1) {
               m = mas[0];
               l = mas[1];
           }
        }
        i--;
     }

    for (i = 0; i < size; i++) {
        ObjectRoute[mas[i]].WriteFile(St_1,St_2,dat);
    }

    return 0;
}

int SearchTrain::ADD(ProjectBD ObjectBD, int i) {
    RemoveFile();
    Route ObjectR;
    QString r1, r2;

    switch(i) {
    case 1: {

         if (ObjectBD.SELECT("idTrain", "Train", "idTrain = " + Object.Search("numTrain"), "", "")) {
             ObjectR = ObjectBD.GetSelectTrain(1,0,0,0);

             if (ObjectR.GetIdTrain() == 0) {

                 if (ObjectBD.SELECT("Name_S", "Station", "Station.Name_S in ('" + Object.Search("St_1") + "', '" + Object.Search("St_2") + "')","", "")) {
                     r1 = ObjectBD.GetSelectStation(0,1,0,0,0,0,0).GetName();
                     r2 = ObjectBD.GetSelectStation(0,1,0,0,0,0,0).GetName();

                     if (r1 == "") {
                         return -13;
                     }
                     if (r2 == "") {
                         return -14;
                     }

                     if (ObjectBD.InsertTrain(Object.Search("numTrain"), Object.Search("St_1"), Object.Search("St_2"), Object.Search("Col"), Object.Search("Time"), Object.Search("Type"), Object.Search("Col_V"))) {
                         return 0;
                     }
                     else {
                        Error(-15, "ADD IT| " + ObjectBD.LastError());
                     }
                 }
                 else {
                     Error(-11, "ADD SST| " + ObjectBD.LastError());
                     return -1;
                 }
             }
             else {
                 return -12;
             }
         }
         else {
             Error(-1, "ADD SN| " + ObjectBD.LastError());
             return -1;
         }

        break;
    }
    case 2: {

        if (ObjectBD.SELECT("idStation", "Station", "idStation = " + Object.Search("cod"), "", "")) {

            if (ObjectBD.GetIdStation() != 0) {
                if (ObjectBD.InsertST(Object.Search("cod"), Object.Search("num"), Object.Search("num_S"), Object.Search("Time_1"), Object.Search("Time_2"))) {
                    return 0;
                }
                else {
                   Error(-25, "ADD IST| " + ObjectBD.LastError());
                }
            }
            else {
                return -21;
            }
        }
        else {
            Error(-2, "ADD Sid| " + ObjectBD.LastError());
            return -2;
        }
        break;
    }
    case 3: {

        if (ObjectBD.InsertSchedule(Object.Search("num"), Object.Search("dat"), Object.Search("T1"), Object.Search("T2"))) {
            return 0;
        }
        else {
           Error(-35, "ADD ISch| " + ObjectBD.LastError());
        }
        break;
    }
    case 4: {
        bool fl = true;
        QString type;
        int NOS(0), COL(0);

        COL = Object.Search("Col").toInt();
        QString n = Object.Search("Type_V");
        if ( n == "СВ") {
            NOS = 18;
        }
        if ( n == "Люкс") {
            NOS = 36;
        }
        if ( n == "Купе") {
            NOS = 36;
        }
        if ( n == "Плацкарт") {
            NOS = 56;
        }
        if ( n == "Сидячий 1-го класу") {
            NOS = 60;
        }
        if ( n == "Сидячий 2-го класу") {
            NOS = 60;
        }

        if (ObjectBD.InsertTC(Object.Search("cod_V"), Object.Search("num"), Object.Search("num_V"), Object.Search("Type_V"), QString::number(NOS))) {
            if (ObjectBD.SELECT("TypeTrain","Train","idTrain = " + Object.Search("num"),"","")) {
                type = ObjectBD.GetTypeTrain();
                if (type == "Електричка") {
                    fl = false;
                }
            }

            if (fl) {

                for (int i = 1; i <= COL; i++) {

                    for (int j = 1; j <= NOS; j++) {

                        if (!ObjectBD.InsertCarriage(Object.Search("cod_V"), QString::number(i), QString::number(j), "-")) {
                            Error(-36, "ADD IC| " + ObjectBD.LastError());
                        }
                    }
                }
            }
            return 0;
        }
        else {
           Error(-35, "ADD ITC| " + ObjectBD.LastError());
        }
        break;
    }

    }
    return 0;
}

string SearchTrain::EN_RU(string str) {
    string res;
    string a;

    for (int i = 0; i < str.length(); i++) {
        a = str[i];
        if (a == "a") {
            a = "а";
        }
        if (a == "b") {
            a = "б";
        }
        if (a == "c") {
            a = "в";
        }
        if (a == "d") {
            a = "г";
        }
        if (a == "e") {
            a = "д";
        }
        if (a == "f") {
            a = "е";
        }
        if (a == "g") {
            a = "є";
        }
        if (a == "h") {
            a = "ж";
        }
        if (a == "i") {
            a = "з";
        }
        if (a == "j") {
            a = "и";
        }
        if (a == "k") {
            a = "і";
        }
        if (a == "l") {
            a = "ї";
        }
        if (a == "m") {
            a = "й";
        }
        if (a == "n") {
            a = "к";
        }
        if (a == "o") {
            a = "л";
        }
        if (a == "p") {
            a = "м";
        }
        if (a == "q") {
            a = "н";
        }
        if (a == "r") {
            a = "о";
        }
        if (a == "s") {
            a = "п";
        }
        if (a == "t") {
            a = "р";
        }
        if (a == "u") {
            a = "с";
        }
        if (a == "v") {
            a = "т";
        }
        if (a == "w") {
            a = "у";
        }
        if (a == "x") {
            a = "ф";
        }
        if (a == "y") {
            a = "х";
        }
        if (a == "z") {
            a = "ш";
        }
        if (a == "+") {
            a = "ц";
        }
        if (a == "=") {
            a = "ч";
        }
        if (a == "&") {
            a = "щ";
        }
        if (a == "~") {
            a = "ь";
        }
        if (a == "[") {
            a = "ю";
        }
        if (a == "]") {
            a = "я";
        }
        if (a == "A") {
            a = "А";
        }
        if (a == "B") {
            a = "Б";
        }
        if (a == "C") {
            a = "В";
        }
        if (a == "D") {
            a = "Г";
        }
        if (a == "E") {
            a = "Д";
        }
        if (a == "F") {
            a = "Е";
        }
        if (a == "G") {
            a = "Є";
        }
        if (a == "H") {
            a = "Ж";
        }
        if (a == "I") {
            a = "З";
        }
        if (a == "J") {
            a = "И";
        }
        if (a == "K") {
            a = "І";
        }
        if (a == "L") {
            a = "Ї";
        }
        if (a == "M") {
            a = "Й";
        }
        if (a == "N") {
            a = "К";
        }
        if (a == "O") {
            a = "Л";
        }
        if (a == "P") {
            a = "М";
        }
        if (a == "Q") {
            a = "Н";
        }
        if (a == "R") {
            a = "О";
        }
        if (a == "S") {
            a = "П";
        }
        if (a == "T") {
            a = "Р";
        }
        if (a == "U") {
            a = "С";
        }
        if (a == "V") {
            a = "Т";
        }
        if (a == "W") {
            a = "У";
        }
        if (a == "X") {
            a = "Ф";
        }
        if (a == "Y") {
            a = "Х";
        }
        if (a == "Z") {
            a = "Ш";
        }
        if (a == "!") {
            a = "Ц";
        }
        if (a == "@") {
            a = "Ч";
        }
        if (a == "#") {
            a = "Щ";
        }
        if (a == "$") {
            a = "Ю";
        }
        if (a == "%") {
            a = "Я";
        }
        if (a == "_") {
            a = " ";
        }
        if (a == "-") {
            a = "-";
        }
        if (a == "'") {
            a = "'";
        }
        res += a;
    }
    return res;
}


