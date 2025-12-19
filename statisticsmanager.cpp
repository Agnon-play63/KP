#include "statisticsmanager.h"
#include <QSqlQuery>

StatisticsManager::StatisticsManager(QObject *parent)
    : QObject(parent)
{
}

double StatisticsManager::calculateRevenue(const QDate &fromDate, const QDate &toDate)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(st.price) FROM ClientSubscriptions cs "
                  "JOIN SubscriptionTypes st ON cs.type_id = st.id "
                  "WHERE cs.start_date BETWEEN :d1 AND :d2");
    query.bindValue(":d1", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":d2", toDate.toString("yyyy-MM-dd"));

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

int StatisticsManager::countSubscriptions(const QDate &fromDate, const QDate &toDate)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ClientSubscriptions WHERE start_date BETWEEN :d1 AND :d2");
    query.bindValue(":d1", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":d2", toDate.toString("yyyy-MM-dd"));

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QMap<QString, int> StatisticsManager::getSubscriptionDistribution(const QDate &fromDate, const QDate &toDate)
{
    QMap<QString, int> distribution;

    QSqlQuery query;
    query.prepare("SELECT st.name, COUNT(cs.id) as count FROM ClientSubscriptions cs "
                  "JOIN SubscriptionTypes st ON cs.type_id = st.id "
                  "WHERE cs.start_date BETWEEN :d1 AND :d2 "
                  "GROUP BY st.name ORDER BY count DESC");
    query.bindValue(":d1", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":d2", toDate.toString("yyyy-MM-dd"));

    if (query.exec()) {
        while (query.next()) {
            distribution.insert(query.value(0).toString(), query.value(1).toInt());
        }
    }

    return distribution;
}

StatisticsManager::Statistics StatisticsManager::calculateStatistics(const QDate &fromDate, const QDate &toDate)
{
    Statistics stats;
    stats.totalRevenue = calculateRevenue(fromDate, toDate);
    stats.subscriptionsSold = countSubscriptions(fromDate, toDate);
    stats.subscriptionDistribution = getSubscriptionDistribution(fromDate, toDate);

    return stats;
}
