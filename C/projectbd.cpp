#include "projectbd.h"

ProjectBD::ProjectBD() {
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    db.setDatabaseName("Project.sqlite");
    size = 0;
}


bool ProjectBD::createConnection() { //налагодження звязку
    bool connected = db.open();

    if (!connected) {
        qDebug() << db.lastError().text();          // Остання помилка
    }
    else {
        query = QSqlQuery( db );
    }
    return connected;
}

QString ProjectBD::LastError() { //остання помилка
    qDebug() <<  query.lastError().text();
    return query.lastError().text();
}

int ProjectBD::GetSize() { //кількість записів після запиту
    return size;
}

bool ProjectBD::DELETE1(QString table_name, QString definition) { //видалення записів
    bool flag = true;

    if (table_name != "" && definition != "" ) {
        if (definition != "") {
            query.prepare("DELETE FROM " + table_name + " WHERE " + definition + ";");
        }
        else {
            query.prepare("DELETE FROM " + table_name + ";");
        }
        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::SELECT(QString column, QString table, QString definition, QString limit, QString Order_by) {
    bool flag = true;

    if (table != "" ) {

            if (limit == "") {

                if (Order_by == "") {
                    if (definition == "") {
                        query.prepare("SELECT " + column + " FROM " + table + " ;");
                    }
                    else {
                        query.prepare("SELECT " + column + " FROM " + table + " WHERE " + definition + " ;");
                    }
                }
                else {
                    if (definition == "") {
                        query.prepare("SELECT " + column + " FROM " + table + " ORDER BY " + Order_by + ";");
                    }
                    else {
                        query.prepare("SELECT " + column + " FROM " + table + " WHERE " + definition + " ORDER BY " + Order_by + ";");
                    }
                }
            }
            else {
                if (Order_by == "") {
                    if (definition == "") {
                        query.prepare("SELECT " + column + " FROM " + table + " LIMIT " + limit + " ;");
                    }
                    else {
                        query.prepare("SELECT " + column + " FROM " + table + " WHERE " + definition + " LIMIT " + limit + ";");
                    }
                }
                else {
                    if (definition == "") {
                        query.prepare("SELECT " + column + " FROM " + table + " LIMIT " + limit + " ORDER BY " + Order_by + ";");
                    }
                    else {
                        query.prepare("SELECT " + column + " FROM " + table + " WHERE " + definition + " LIMIT " + limit + " ORDER BY " + Order_by + ";");
                    }
                }
            }
            flag = query.exec();
            size = 0;
            while (query.next()) size++;
            while (query.previous()) {

            }
        }
        else {
            flag = false;
        }

        return flag;
}

bool ProjectBD::UPDATE(QString table, QString value, QString definition) {
    bool flag = true;

    if (table != "" && value != "") {

        if (definition != "") {
            query.prepare("UPDATE " + table + " SET " + value + " WHERE " + definition + ";");
        }
        else {
            query.prepare("UPDATE " + table + " SET " + value + ";");
        }
        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::InsertTrain(QString number, QString St1, QString St2, QString Number_of_stations, QString Time_on_road, QString TypeTrain, QString Col_Carriage) {
    bool flag = true;

    if (number != "" && St1 != "" && St2 != "" && Number_of_stations != "" && Time_on_road != "") {
        query.prepare("INSERT INTO Train (idTrain, St_1, St_2, Number_of_stations, Time_on_the_road, TypeTrain, Col_Carriage) "
                          "VALUES (:idTrain, :St1, :St2, :Number_of_stations, :Time_on_the_road, :TypeTrain, :Col_Carriage);");
            query.bindValue(":idTrain", number);
            query.bindValue(":St1", St1);
            query.bindValue(":St2", St2);
            query.bindValue(":Number_of_stations", Number_of_stations);
            query.bindValue(":Time_on_the_road", Time_on_road);
            query.bindValue(":TypeTrain", TypeTrain);
            query.bindValue(":Col_Carriage", Col_Carriage);

        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::InsertTC(QString idTrain_Carriage, QString idTrain, QString Number_carriage, QString Type_C, QString Number_of_seats) {
    bool flag = true;

    if (idTrain_Carriage != "" && idTrain != "" && Number_carriage != "" && Type_C != "" && Number_of_seats != "") {
        query.prepare("INSERT INTO  Train_Carriage (idTrain_Carriage, idTrain, Number_carriage, Type_C, Number_of_seats) "
                          "VALUES (:idTrain_Carriage, :idTrain, :Number_carriage, :Type_C, :Number_of_seats);");
            query.bindValue(":idTrain_Carriage", idTrain_Carriage);
            query.bindValue(":idTrain", idTrain);
            query.bindValue(":Number_carriage", Number_carriage);
            query.bindValue(":Type_C", Type_C);
            query.bindValue(":Number_of_seats", Number_of_seats);

        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::InsertCarriage(QString idCarriage, QString Station_number, QString Place, QString Employment) {
    bool flag = true;

    if (idCarriage != "" && Station_number != "" && Place != "" && Employment != "" ) {
        query.prepare("INSERT INTO  Carriage (idCarriage, Station_number, Place, Employment) "
                          "VALUES (:idCarriage, :Station_number, :Place, :Employment);");
            query.bindValue(":idCarriage", idCarriage);
            query.bindValue(":Station_number", Station_number);
            query.bindValue(":Place", Place);
            query.bindValue(":Employment", Employment);

        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::InsertST(QString idStation_Train, QString idTrain, QString Sequence_number, QString Arrival_time, QString Time_of_departure) {
    bool flag = true;

    if (idStation_Train != "" && idTrain != "" && Sequence_number != "" && Arrival_time != "" && Time_of_departure != "" ) {
        query.prepare("INSERT INTO  Station_Train (idStation_Train, idTrain, Sequence_number, Arrival_time, Time_of_departure) "
                          "VALUES (:idStation_Train, :idTrain, :Sequence_number, :Arrival_time, :Time_of_departure);");
            query.bindValue(":idStation_Train", idStation_Train);
            query.bindValue(":idTrain", idTrain);
            query.bindValue(":Sequence_number", Sequence_number);
            query.bindValue(":Arrival_time", Arrival_time);
            query.bindValue(":Time_of_departure", Time_of_departure);

        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::InsertStation(QString idStation, QString Coordinates, QString Name_S, QString Branch) {
    bool flag = true;

    if (idStation != "" && Coordinates != "" && Name_S != "" && Branch != "") {
        query.prepare("INSERT INTO  Station (idStation, Coordinates, Name_S, Branch) "
                          "VALUES (:idStation, :Coordinates, :Name_S, :Branch);");
            query.bindValue(":idStation", idStation);
            query.bindValue(":Coordinates", Coordinates);
            query.bindValue(":Name_S", Name_S);
            query.bindValue(":Branch", Branch);

        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

bool ProjectBD::InsertSchedule(QString idTrain_S, QString Start, QString Departure_time, QString Arrival_time) {
    bool flag = true;

    if (idTrain_S != "" && Departure_time != "" && Start != "" && Arrival_time != "") {
        query.prepare("INSERT INTO  Schedul (idTrain_S, Start, Departure_time, Arrival_time) "
                          "VALUES (:idTrain_S, :Start, :Departure_time, :Arrival_time);");
            query.bindValue(":idTrain_S", idTrain_S);
            query.bindValue(":Start", Start);
            query.bindValue(":Departure_time", Departure_time);
            query.bindValue(":Arrival_time", Arrival_time);

        flag = query.exec();
    }
    else {
        flag = false;
    }

    return flag;
}

itemList<QString> ProjectBD::GetSelectStation(int Coo, int Nam, int idS, int Sec, int Arr, int TD, int SB) {
    itemList<QString> Object;

        QSqlRecord rec = query.record();
        query.next();

            if (Coo == 1) {
                Object.SetCoordinates(query.value(rec.indexOf("Coordinates")).toString());
            }
            if (Nam == 1) {
                Object.SetName(query.value(rec.indexOf("Name_S")).toString());
            }
            if (idS == 1) {
                Object.SetIdStation(query.value(rec.indexOf("idStation_Train")).toInt());
            }
            if (Sec == 1) {
                Object.SetNum(query.value(rec.indexOf("Sequence_number")).toInt());
            }
            if (Arr == 1) {
                Object.SetArr(query.value(rec.indexOf("Arrival_time")).toString());
            }
            if (TD == 1) {
                Object.SetTD(query.value(rec.indexOf("Time_of_departure")).toString());
            }
            if (SB == 1) {
                Object.SetBranch(query.value(rec.indexOf("Branch")).toString());
            }
    return Object;
}

int ProjectBD::GetIdStation() {
    QSqlRecord rec = query.record();
    query.next();
    return query.value(rec.indexOf("idStation")).toInt();
}

int ProjectBD::GetIdTrain() {
    QSqlRecord rec = query.record();
    query.next();
    return query.value(rec.indexOf("idTrain")).toInt();
}

Route ProjectBD::GetSelectTrain(int iT, int St1, int St2, int TT) {
    Route Object;
    QSqlRecord rec = query.record();
    query.next();
    if (iT == 1) {
        Object.SetIdTrain(query.value(rec.indexOf("idTrain")).toInt());
    }
    if (St1 == 1) {
        Object.SetSt1(query.value(rec.indexOf("St_1")).toString());
    }
    if (St2 == 1) {
        Object.SetSt2(query.value(rec.indexOf("St_2")).toString());
    }
    if (TT == 1) {
        Object.SetType(query.value(rec.indexOf("TypeTrain")).toString());
    }
    return Object;
}

QString ProjectBD::GetSelectSchedule(int number) {
    QString back;

        QSqlRecord rec = query.record();
        query.next();
            switch(number) {
                case 1: {
                    back = query.value(rec.indexOf("idTrain_S")).toString();
                    break;
                }
                case 2: {
                    back = query.value(rec.indexOf("Start")).toString();
                    break;
                }
                case 3: {
                    back = query.value(rec.indexOf("Departure_time")).toString();
                    break;
                }
                case 4: {
                    back = query.value(rec.indexOf("Arrival_time")).toString();
                    break;
                }
                default: {
                    qDebug() << "Invalid parameter";
                }
            }
    return back;
}

bool ProjectBD::GetPlaceCarriage() {
    bool l = false;
    QSqlRecord rec = query.record();
    query.next();
    QString c = query.value(rec.indexOf("Employment")).toString();
    if (c == "-") {
        l = true;
    }
    return l;
}

QString ProjectBD::GetTypeCarriage() {
    QSqlRecord rec = query.record();
    query.next();

    return query.value(rec.indexOf("Type_C")).toString();
}

int ProjectBD::GetIdCarriage() {
    QSqlRecord rec = query.record();
    query.next();
    return query.value(rec.indexOf("idTrain_Carriage")).toInt();
}

int ProjectBD::GetNumberCarriage() {
    QSqlRecord rec = query.record();
    query.next();
    return query.value(rec.indexOf("Number_carriage")).toInt();
}

QString ProjectBD::GetSelectInput() {
    QSqlRecord rec = query.record();
    query.next();
    return query.value(rec.indexOf("PIB")).toString();
}

QString ProjectBD::GetTypeTrain() {
    QSqlRecord rec = query.record();
    query.next();
    return query.value(rec.indexOf("TypeTrain")).toString();
}


