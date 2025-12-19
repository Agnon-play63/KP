#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

bool connectToDb() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fitness_club.db");

    if (!db.open()) {
        qDebug() << "Error: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;


    query.exec("CREATE TABLE IF NOT EXISTS Trainers ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "full_name TEXT NOT NULL, "
               "specialization TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS Clients ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "full_name TEXT NOT NULL, "
               "phone TEXT, "
               "comment TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS SubscriptionTypes ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "price REAL NOT NULL, "
               "visits_count INTEGER NOT NULL)");

    query.exec("CREATE TABLE IF NOT EXISTS ClientSubscriptions ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "client_id INTEGER, "
               "type_id INTEGER, "
               "start_date DATE, "
               "end_date DATE, "
               "visits_left INTEGER, "
               "FOREIGN KEY(client_id) REFERENCES Clients(id), "
               "FOREIGN KEY(type_id) REFERENCES SubscriptionTypes(id))");

    query.exec("CREATE TABLE IF NOT EXISTS Schedule ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "trainer_id INTEGER, "
               "client_id INTEGER, "
               "start_time DATETIME, "
               "activity_name TEXT, "
               "FOREIGN KEY(trainer_id) REFERENCES Trainers(id), "
               "FOREIGN KEY(client_id) REFERENCES Clients(id))");


    query.exec("SELECT count(*) FROM Trainers");
    if (query.next() && query.value(0).toInt() == 0) {
        query.exec("INSERT INTO Trainers (full_name, specialization) VALUES ('Иван Петров', 'Бокс')");
        query.exec("INSERT INTO Clients (full_name, phone, comment) VALUES ('Анна Смирнова', '89001112233', 'Нет абонемента')");
        query.exec("INSERT INTO SubscriptionTypes (name, price, visits_count) VALUES ('Разовое', 500, 1)");
        query.exec("INSERT INTO SubscriptionTypes (name, price, visits_count) VALUES ('10 занятий', 4000, 10)");
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!connectToDb()) {
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
