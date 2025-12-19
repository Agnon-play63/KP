#include "clientmanager.h"
#include "namevalidator.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>

ClientManager::ClientManager(QSqlTableModel *model, NameValidator *validator, QObject *parent)
    : QObject(parent), clientModel(model), nameValidator(validator)
{
}

bool ClientManager::addClient(const QString &name, const QString &phone)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Clients (full_name, phone, comment) VALUES (:name, :phone, 'Нет активного абонемента')");
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);

    if(query.exec()) {
        clientModel->select();
        return true;
    }
    return false;
}

bool ClientManager::editClient(int clientId, const QString &newName, const QString &newPhone)
{
    QSqlQuery query;
    query.prepare("UPDATE Clients SET full_name = :n, phone = :p WHERE id = :id");
    query.bindValue(":n", newName);
    query.bindValue(":p", newPhone);
    query.bindValue(":id", clientId);

    if (query.exec()) {
        clientModel->select();
        return true;
    }
    return false;
}

bool ClientManager::deleteClient(int row)
{
    if (clientModel->removeRow(row)) {
        clientModel->submitAll();
        clientModel->select();
        return true;
    }
    return false;
}

bool ClientManager::checkActiveSubscription(int clientId, int &subId, int &visitsLeft)
{
    QSqlQuery query;
    query.prepare("SELECT id, visits_left FROM ClientSubscriptions "
                  "WHERE client_id = ? AND visits_left > 0 AND end_date >= date('now') "
                  "ORDER BY end_date DESC LIMIT 1");
    query.addBindValue(clientId);

    if (query.exec() && query.next()) {
        subId = query.value(0).toInt();
        visitsLeft = query.value(1).toInt();
        return true;
    }
    return false;
}

bool ClientManager::addTrialSubscription(int clientId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ClientSubscriptions (client_id, type_id, start_date, end_date, visits_left) "
                  "VALUES (?, 1, date('now'), date('now','+1 day'), 1)");
    query.addBindValue(clientId);
    return query.exec();
}

bool ClientManager::registerVisit(int clientId)
{
    int subId, visitsLeft;

    if (checkActiveSubscription(clientId, subId, visitsLeft)) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE ClientSubscriptions SET visits_left = ? WHERE id = ?");
        updateQuery.addBindValue(visitsLeft - 1);
        updateQuery.addBindValue(subId);

        if (updateQuery.exec()) {
            updateSubscriptionStatuses();
            return true;
        }
        return false;
    }
    return false;
}

void ClientManager::updateSubscriptionStatuses()
{
    QSqlQuery clientQuery("SELECT id, full_name FROM Clients");

    while (clientQuery.next()) {
        int clientId = clientQuery.value(0).toInt();

        QSqlQuery subQuery;
        subQuery.prepare("SELECT visits_left FROM ClientSubscriptions "
                         "WHERE client_id = ? AND visits_left > 0 AND end_date >= date('now') "
                         "ORDER BY end_date DESC LIMIT 1");
        subQuery.addBindValue(clientId);

        QString statusText;

        if (subQuery.exec() && subQuery.next()) {
            int visitsLeft = subQuery.value(0).toInt();
            statusText = "Активен (ост: " + QString::number(visitsLeft) + ")";
        } else {
            statusText = "Нет активного абонемента";
        }

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE Clients SET comment = ? WHERE id = ?");
        updateQuery.addBindValue(statusText);
        updateQuery.addBindValue(clientId);
        updateQuery.exec();
    }

    clientModel->select();
}
