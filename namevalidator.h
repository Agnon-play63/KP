#ifndef NAMEVALIDATOR_H
#define NAMEVALIDATOR_H

#include <QObject>
#include <QString>

class NameValidator : public QObject
{
    Q_OBJECT

public:
    explicit NameValidator(QObject *parent = nullptr);

    QString sanitizeName(const QString &name);
    QString formatName(const QString &name);
    bool isValidName(const QString &name);
    bool validatePhone(const QString &phone);

    QString formatSpecialization(const QString &spec);
    QString formatSubscriptionName(const QString &name);

private:
    bool containsOnlyValidCharacters(const QString &text, bool allowNumbers = false);
};

#endif // NAMEVALIDATOR_H
