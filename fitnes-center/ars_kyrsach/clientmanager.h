#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QSqlTableModel>

class NameValidator;

class ClientManager : public QObject
{
    Q_OBJECT

public:
    explicit ClientManager(QSqlTableModel *model, NameValidator *validator, QObject *parent = nullptr);

    bool addClient(const QString &name, const QString &phone);
    bool editClient(int clientId, const QString &newName, const QString &newPhone);
    bool deleteClient(int row);
    bool registerVisit(int clientId);
    void updateSubscriptionStatuses();

private:
    QSqlTableModel *clientModel;
    NameValidator *nameValidator;

    bool checkActiveSubscription(int clientId, int &subId, int &visitsLeft);
    bool addTrialSubscription(int clientId);
};

#endif // CLIENTMANAGER_H
