#include "subscriptionmanager.h"
#include "namevalidator.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>

SubscriptionManager::SubscriptionManager(QSqlTableModel *model, NameValidator *validator, QObject *parent)
    : QObject(parent), subscriptionModel(model), nameValidator(validator)
{
}

QDate SubscriptionManager::calculateEndDate(int visitsCount, const QDate &startDate)
{
    if (visitsCount == 1) {
        return startDate.addDays(1);
    }
    return startDate.addMonths(1);
}

bool SubscriptionManager::addSubscriptionType(const QString &name, int price, int visits)
{
    QSqlQuery query;
    query.prepare("INSERT INTO SubscriptionTypes (name, price, visits_count) VALUES (:n, :p, :v)");
    query.bindValue(":n", name);
    query.bindValue(":p", price);
    query.bindValue(":v", visits);

    if (query.exec()) {
        subscriptionModel->select();
        return true;
    }
    return false;
}

bool SubscriptionManager::deleteSubscriptionType(int row)
{
    if (subscriptionModel->removeRow(row)) {
        subscriptionModel->submitAll();
        subscriptionModel->select();
        return true;
    }
    return false;
}

QMap<QString, QPair<int, int>> SubscriptionManager::getSubscriptionTypes()
{
    QMap<QString, QPair<int, int>> subMap;

    QSqlQuery query("SELECT id, name, visits_count FROM SubscriptionTypes ORDER BY name");
    while(query.next()) {
        QString name = query.value(1).toString();
        int id = query.value(0).toInt();
        int visits = query.value(2).toInt();
        subMap.insert(name, qMakePair(id, visits));
    }

    return subMap;
}

bool SubscriptionManager::addClientSubscription(int clientId, int subscriptionTypeId, const QString &clientName)
{
    QSqlQuery query;
    query.prepare("SELECT visits_count FROM SubscriptionTypes WHERE id = ?");
    query.addBindValue(subscriptionTypeId);

    if (!query.exec() || !query.next()) {
        return false;
    }

    int visitsCount = query.value(0).toInt();
    QDate startDate = QDate::currentDate();
    QDate endDate = calculateEndDate(visitsCount, startDate);

    QString startStr = startDate.toString("yyyy-MM-dd");
    QString endStr = endDate.toString("yyyy-MM-dd");

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO ClientSubscriptions (client_id, type_id, start_date, end_date, visits_left) "
                        "VALUES (?, ?, ?, ?, ?)");
    insertQuery.addBindValue(clientId);
    insertQuery.addBindValue(subscriptionTypeId);
    insertQuery.addBindValue(startStr);
    insertQuery.addBindValue(endStr);
    insertQuery.addBindValue(visitsCount);

    return insertQuery.exec();
}
