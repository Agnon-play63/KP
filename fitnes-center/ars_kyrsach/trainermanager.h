#ifndef TRAINERMANAGER_H
#define TRAINERMANAGER_H

#include <QObject>
#include <QSqlTableModel>
#include <QStringList>
#include <QMap>

class NameValidator;

class TrainerManager : public QObject
{
    Q_OBJECT

public:
    explicit TrainerManager(QSqlTableModel *model, NameValidator *validator, QObject *parent = nullptr);

    bool addTrainer(const QString &name, const QString &specialization);
    bool deleteTrainer(int row);
    QStringList getSpecializations();

private:
    QSqlTableModel *trainerModel;
    NameValidator *nameValidator;

    QString formatSpecialization(const QString &spec);
    bool trainerExists(const QString &name);
};

#endif // TRAINERMANAGER_H
