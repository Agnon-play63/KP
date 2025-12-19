#include "schedulemanager.h"
#include <QSqlQuery>

ScheduleManager::ScheduleManager(QSqlRelationalTableModel *model, QObject *parent)
    : QObject(parent), scheduleModel(model)
{
}

void ScheduleManager::filterByDate(const QDate &date)
{
    QString filter = QString("date(start_time) = '%1'").arg(date.toString("yyyy-MM-dd"));
    scheduleModel->setFilter(filter);
    scheduleModel->select();
}

QMap<QString, int> ScheduleManager::getTrainers()
{
    QMap<QString, int> trainerMap;
    QSqlQuery query("SELECT id, full_name FROM Trainers");

    while(query.next()) {
        trainerMap.insert(query.value(1).toString(), query.value(0).toInt());
    }

    return trainerMap;
}

QMap<QString, int> ScheduleManager::getClients()
{
    QMap<QString, int> clientMap;
    QSqlQuery query("SELECT id, full_name FROM Clients");

    while(query.next()) {
        clientMap.insert(query.value(1).toString(), query.value(0).toInt());
    }

    return clientMap;
}

bool ScheduleManager::addTraining(int trainerId, int clientId, const QString &activityName,
                                  const QString &dateTimeStr)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Schedule (trainer_id, client_id, start_time, activity_name) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(trainerId);
    query.addBindValue(clientId);
    query.addBindValue(dateTimeStr);
    query.addBindValue(activityName);

    if(query.exec()) {
        scheduleModel->select();
        return true;
    }
    return false;
}

bool ScheduleManager::deleteTraining(int row)
{
    if (scheduleModel->removeRow(row)) {
        scheduleModel->submitAll();
        scheduleModel->select();
        return true;
    }
    return false;
}
