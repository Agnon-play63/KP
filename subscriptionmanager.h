#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#include <QObject>
#include <QSqlTableModel>
#include <QDate>
#include <QMap>

class NameValidator;

class SubscriptionManager : public QObject
{
    Q_OBJECT

public:
    explicit SubscriptionManager(QSqlTableModel *model, NameValidator *validator, QObject *parent = nullptr);

    bool addSubscriptionType(const QString &name, int price, int visits);
    bool deleteSubscriptionType(int row);
    bool addClientSubscription(int clientId, int subscriptionTypeId, const QString &clientName);

    QMap<QString, QPair<int, int>> getSubscriptionTypes();

private:
    QSqlTableModel *subscriptionModel;
    NameValidator *nameValidator;

    QDate calculateEndDate(int visitsCount, const QDate &startDate);
};

#endif // SUBSCRIPTIONMANAGER_H
