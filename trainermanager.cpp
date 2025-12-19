#include "trainermanager.h"
#include "namevalidator.h"
#include <QSqlQuery>
#include <QMessageBox>

TrainerManager::TrainerManager(QSqlTableModel *model, NameValidator *validator, QObject *parent)
    : QObject(parent), trainerModel(model), nameValidator(validator)
{
}

bool TrainerManager::trainerExists(const QString &name)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Trainers WHERE LOWER(full_name) = LOWER(?)");
    query.addBindValue(name);
    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

QString TrainerManager::formatSpecialization(const QString &spec)
{
    if (spec.trimmed().isEmpty()) return spec;

    QString formatted = spec.trimmed().toLower();
    formatted[0] = formatted[0].toUpper();

    QStringList words = formatted.split(" ", Qt::SkipEmptyParts);
    if (words.size() > 1) {
        for (int i = 0; i < words.size(); ++i) {
            if (!words[i].isEmpty()) {
                words[i][0] = words[i][0].toUpper();
            }
        }
        formatted = words.join(" ");
    }

    return formatted;
}

bool TrainerManager::addTrainer(const QString &name, const QString &specialization)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Trainers (full_name, specialization) VALUES (:name, :spec)");
    query.bindValue(":name", name);
    query.bindValue(":spec", specialization);

    if (query.exec()) {
        trainerModel->select();
        return true;
    }
    return false;
}

bool TrainerManager::deleteTrainer(int row)
{
    if (trainerModel->removeRow(row)) {
        trainerModel->submitAll();
        trainerModel->select();
        return true;
    }
    return false;
}

QStringList TrainerManager::getSpecializations()
{
    QStringList specs;
    QSqlQuery query("SELECT DISTINCT specialization FROM Trainers WHERE specialization IS NOT NULL AND specialization != ''");
    while (query.next()) {
        QString spec = query.value(0).toString();
        if (!spec.isEmpty() && !specs.contains(spec)) {
            specs << spec;
        }
    }

    if (specs.isEmpty()) {
        specs << "Йога" << "Бокс" << "Тренажерный зал" << "Кардио"
              << "Силовые тренировки" << "Пилатес" << "Стретчинг";
    }

    return specs;
}
