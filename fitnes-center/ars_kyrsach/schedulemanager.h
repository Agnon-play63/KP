#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include <QSqlRelationalTableModel>
#include <QDate>

class ScheduleManager : public QObject
{
    Q_OBJECT

public:
    explicit ScheduleManager(QSqlRelationalTableModel *model, QObject *parent = nullptr);

    bool addTraining(int trainerId, int clientId, const QString &activityName,
                     const QString &dateTimeStr);
    bool deleteTraining(int row);
    void filterByDate(const QDate &date);

    QMap<QString, int> getTrainers();
    QMap<QString, int> getClients();

private:
    QSqlRelationalTableModel *scheduleModel;
};

#endif // SCHEDULEMANAGER_H
