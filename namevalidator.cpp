#include "namevalidator.h"
#include <QRegularExpression>

NameValidator::NameValidator(QObject *parent)
    : QObject(parent)
{
}

bool NameValidator::containsOnlyValidCharacters(const QString &text, bool allowNumbers)
{
    for (const QChar &ch : text) {
        bool isValid = ch.isLetter() || ch == ' ' || ch == '-' || ch == '\'' || ch == '.' ||
                       ch == QChar(0x0401) || ch == QChar(0x0451);

        if (allowNumbers) {
            isValid = isValid || ch.isDigit();
        }

        if (!isValid) {
            return false;
        }
    }
    return true;
}

QString NameValidator::sanitizeName(const QString &name)
{
    QString result;

    for (const QChar &ch : name) {
        if (ch.isLetter() || ch == ' ' || ch == '-' || ch == '\'' || ch == '.' ||
            ch == QChar(0x0401) || ch == QChar(0x0451)) {
            result.append(ch);
        }
    }

    return result;
}

QString NameValidator::formatName(const QString &name)
{
    if (name.isEmpty()) return name;

    QString formatted = name.toLower();
    QStringList words = formatted.split(" ", Qt::SkipEmptyParts);

    for (int i = 0; i < words.size(); ++i) {
        if (!words[i].isEmpty()) {
            words[i][0] = words[i][0].toUpper();

            if (words[i].contains("-")) {
                QStringList parts = words[i].split("-");
                for (int j = 0; j < parts.size(); ++j) {
                    if (!parts[j].isEmpty()) {
                        parts[j][0] = parts[j][0].toUpper();
                    }
                }
                words[i] = parts.join("-");
            }
        }
    }

    return words.join(" ");
}

bool NameValidator::isValidName(const QString &name)
{
    if (name.trimmed().isEmpty()) {
        return false;
    }

    return containsOnlyValidCharacters(name);
}

bool NameValidator::validatePhone(const QString &phone)
{
    QRegularExpression phoneRegex("^\\+7\\d{10}$");
    return phoneRegex.match(phone).hasMatch();
}

QString NameValidator::formatSpecialization(const QString &spec)
{
    if (spec.trimmed().isEmpty()) return spec;

    QString formatted = spec.trimmed().toLower();
    if (!formatted.isEmpty()) {
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
    }

    return formatted;
}

QString NameValidator::formatSubscriptionName(const QString &name)
{
    return formatName(name.trimmed());
}
