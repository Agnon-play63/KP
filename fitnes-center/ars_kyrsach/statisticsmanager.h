#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QDate>

class StatisticsManager : public QObject
{
    Q_OBJECT

public:
    explicit StatisticsManager(QObject *parent = nullptr);

    struct Statistics {
        double totalRevenue;
        int subscriptionsSold;
        QMap<QString, int> subscriptionDistribution;
    };

    Statistics calculateStatistics(const QDate &fromDate, const QDate &toDate);

private:
    double calculateRevenue(const QDate &fromDate, const QDate &toDate);
    int countSubscriptions(const QDate &fromDate, const QDate &toDate);
    QMap<QString, int> getSubscriptionDistribution(const QDate &fromDate, const QDate &toDate);
};

#endif // STATISTICSMANAGER_H
