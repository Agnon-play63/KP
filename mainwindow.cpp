#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientmanager.h"
#include "trainermanager.h"
#include "subscriptionmanager.h"
#include "schedulemanager.h"
#include "statisticsmanager.h"
#include "namevalidator.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlRelation>
#include <QPair>
#include <QMouseEvent>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , clientManager(nullptr)
    , trainerManager(nullptr)
    , subscriptionManager(nullptr)
    , scheduleManager(nullptr)
    , statisticsManager(nullptr)
    , nameValidator(new NameValidator(this))
{
    ui->setupUi(this);
    setupModels();
    setWindowTitle("Фитнес-центр: Управление клиентами и тренировками");

    auto applyTableStyle = [this](QTableView* table) {
        if (!table) return;
        table->setMouseTracking(true);
        table->setStyleSheet("QTableView::item:hover { background-color: #E6F7FF; color: black; }");
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->viewport()->installEventFilter(this);
    };

    applyTableStyle(ui->tvClients);
    applyTableStyle(ui->tvTrainers);
    applyTableStyle(ui->tvSubTypes);
    applyTableStyle(ui->tvSchedule);
    applyTableStyle(ui->tvStatsDetails);

    ui->deFrom->setDate(QDate::currentDate().addDays(-30));
    ui->deTo->setDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModels()
{
    modelClients = new QSqlTableModel(this);
    modelClients->setTable("Clients");
    modelClients->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelClients->setHeaderData(1, Qt::Horizontal, "ФИО");
    modelClients->setHeaderData(2, Qt::Horizontal, "Телефон");
    modelClients->setHeaderData(3, Qt::Horizontal, "Статус Абонемента");
    ui->tvClients->setModel(modelClients);
    ui->tvClients->hideColumn(0);
    ui->tvClients->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    modelTrainers = new QSqlTableModel(this);
    modelTrainers->setTable("Trainers");
    modelTrainers->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelTrainers->select();
    modelTrainers->setHeaderData(1, Qt::Horizontal, "ФИО");
    modelTrainers->setHeaderData(2, Qt::Horizontal, "Специализация");
    ui->tvTrainers->setModel(modelTrainers);
    ui->tvTrainers->hideColumn(0);

    modelSubTypes = new QSqlTableModel(this);
    modelSubTypes->setTable("SubscriptionTypes");
    modelSubTypes->setEditStrategy(QSqlTableModel::OnFieldChange);
    modelSubTypes->select();
    modelSubTypes->setHeaderData(1, Qt::Horizontal, "Название");
    modelSubTypes->setHeaderData(2, Qt::Horizontal, "Цена");
    modelSubTypes->setHeaderData(3, Qt::Horizontal, "Занятий");
    ui->tvSubTypes->setModel(modelSubTypes);
    ui->tvSubTypes->hideColumn(0);

    modelSchedule = new QSqlRelationalTableModel(this);
    modelSchedule->setTable("Schedule");
    modelSchedule->setRelation(1, QSqlRelation("Trainers", "id", "full_name"));
    modelSchedule->setRelation(2, QSqlRelation("Clients", "id", "full_name"));
    modelSchedule->setHeaderData(1, Qt::Horizontal, "Тренер");
    modelSchedule->setHeaderData(2, Qt::Horizontal, "Клиент");
    modelSchedule->setHeaderData(3, Qt::Horizontal, "Время");
    modelSchedule->setHeaderData(4, Qt::Horizontal, "Занятие");
    ui->tvSchedule->setModel(modelSchedule);
    ui->tvSchedule->setItemDelegate(new QSqlRelationalDelegate(ui->tvSchedule));
    ui->tvSchedule->hideColumn(0);

    clientManager = new ClientManager(modelClients, nameValidator, this);
    trainerManager = new TrainerManager(modelTrainers, nameValidator, this);
    subscriptionManager = new SubscriptionManager(modelSubTypes, nameValidator, this);
    scheduleManager = new ScheduleManager(modelSchedule, this);
    statisticsManager = new StatisticsManager(this);

    clientManager->updateSubscriptionStatuses();
    modelClients->select();
    on_calendarSchedule_selectionChanged();
}

void MainWindow::updateClientSubscriptionStatuses()
{
    clientManager->updateSubscriptionStatuses();
}

// Слоты для клиентов
void MainWindow::on_btnAddClient_clicked()
{
    bool ok;
    QString name;
    bool validName = false;

    while (!validName) {
        name = QInputDialog::getText(this, "Новый клиент", "Введите ФИО:",
                                     QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QString sanitized = nameValidator->sanitizeName(name);
        if (sanitized.isEmpty()) {
            QMessageBox::warning(this, "Ошибка",
                                 "ФИО не может быть пустым и должно содержать только буквы!");
            continue;
        }

        if (sanitized != name) {
            int ret = QMessageBox::question(this, "Исправление ФИО",
                                            "Найдены недопустимые символы.\n\n"
                                            "Было: " + name + "\nСтало: " + sanitized + "\n\n"
                                                                                   "Использовать исправленный вариант?",
                                            QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                name = sanitized;
                validName = true;
            }
        } else {
            validName = true;
        }
    }

    QString formattedName = nameValidator->formatName(name.trimmed());
    if (name != formattedName) {
        int ret = QMessageBox::question(this, "Форматирование ФИО",
                                        "Привести к правильному формату?\n\n"
                                        "Было: " + name + "\nСтало: " + formattedName,
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            name = formattedName;
        }
    }

    QString phone;
    bool validPhone = false;
    while (!validPhone) {
        phone = QInputDialog::getText(this, "Новый клиент",
                                      "Введите номер телефона (+7XXXXXXXXXX):",
                                      QLineEdit::Normal, "+7", &ok);
        if (!ok) return;

        if (nameValidator->validatePhone(phone)) {
            validPhone = true;
        } else {
            QMessageBox::warning(this, "Ошибка",
                                 "Номер телефона должен быть в формате +7XXXXXXXXXX\n"
                                 "(начинается с +7, затем ровно 10 цифр");
        }
    }

    if (clientManager->addClient(name, phone)) {
        QMessageBox::information(this, "Успех", "Клиент добавлен.");
    } else {
        QMessageBox::critical(this, "Ошибка БД", "Не удалось добавить клиента");
    }
}

void MainWindow::on_btnEditClient_clicked()
{
    QModelIndexList selectedIndexes = ui->tvClients->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите клиента для редактирования!");
        return;
    }

    int row = selectedIndexes.first().row();
    if (row < 0 || row >= modelClients->rowCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверный индекс клиента!");
        return;
    }

    QSqlRecord record = modelClients->record(row);
    QString oldName = record.value("full_name").toString();
    QString oldPhone = record.value("phone").toString();
    int id = record.value("id").toInt();

    bool ok;
    QString newName;
    bool validName = false;

    while (!validName) {
        newName = QInputDialog::getText(this, "Редактирование", "ФИО:",
                                        QLineEdit::Normal, oldName, &ok);
        if (!ok) return;

        QString sanitized = nameValidator->sanitizeName(newName);
        if (sanitized.isEmpty()) {
            QMessageBox::warning(this, "Ошибка",
                                 "ФИО не может быть пустым и должно содержать только буквы!");
            continue;
        }

        if (sanitized != newName) {
            int ret = QMessageBox::question(this, "Исправление ФИО",
                                            "Найдены недопустимые символы.\n\n"
                                            "Было: " + newName + "\nСтало: " + sanitized + "\n\n"
                                                                                      "Использовать исправленный вариант?",
                                            QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                newName = sanitized;
                validName = true;
            }
        } else {
            validName = true;
        }
    }

    QString formattedName = nameValidator->formatName(newName.trimmed());
    if (newName != formattedName) {
        int ret = QMessageBox::question(this, "Форматирование ФИО",
                                        "Привести к правильному формату?\n\n"
                                        "Было: " + newName + "\nСтало: " + formattedName,
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            newName = formattedName;
        }
    }

    QString newPhone;
    bool validPhone = false;
    while (!validPhone) {
        newPhone = QInputDialog::getText(this, "Редактирование",
                                         "Введите номер телефона (+7XXXXXXXXXX):",
                                         QLineEdit::Normal, oldPhone, &ok);
        if (!ok) return;

        if (nameValidator->validatePhone(newPhone)) {
            validPhone = true;
        } else {
            QMessageBox::warning(this, "Ошибка",
                                 "Номер телефона должен быть в формате +7XXXXXXXXXX\n"
                                 "(начинается с +7, затем ровно 10 цифр");
        }
    }

    if (clientManager->editClient(id, newName, newPhone)) {
        QMessageBox::information(this, "Успех", "Данные клиента обновлены!");
    }
}

void MainWindow::on_btnDelClient_clicked()
{
    if (!ui->tvClients->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Ошибка", "Выберите клиента для удаления!");
        return;
    }

    int row = ui->tvClients->currentIndex().row();

    if (QMessageBox::question(this, "Удаление", "Удалить клиента?") == QMessageBox::Yes) {
        clientManager->deleteClient(row);
    }
}

void MainWindow::on_btnRegisterVisit_clicked()
{
    if (!ui->tvClients->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Ошибка", "Выберите клиента, чтобы отметить посещение!");
        return;
    }

    int row = ui->tvClients->currentIndex().row();
    int clientId = modelClients->record(row).value("id").toInt();

    if (clientManager->registerVisit(clientId)) {
        QMessageBox::information(this, "Успех", "Посещение отмечено!");
    } else {
        int ret = QMessageBox::question(this, "Нет абонемента",
                                        "Нет активного абонемента. Выдать пробный (1 занятие)?");
        if (ret == QMessageBox::Yes) {
            QSqlQuery query;
            query.prepare("INSERT INTO ClientSubscriptions (client_id, type_id, start_date, end_date, visits_left) "
                          "VALUES (?, 1, date('now'), date('now','+1 day'), 1)");
            query.addBindValue(clientId);
            if (query.exec()) {
                clientManager->updateSubscriptionStatuses();
                QMessageBox::information(this, "Инфо", "Выдан пробный абонемент.");
            }
        }
    }
}

// Слоты для тренеров
void MainWindow::on_btnAddTrainer_clicked()
{
    bool ok;
    QString name;
    bool validName = false;

    while (!validName) {
        name = QInputDialog::getText(this, "Новый тренер", "ФИО тренера:",
                                     QLineEdit::Normal, "", &ok);
        if (!ok) return;

        QString sanitized = nameValidator->sanitizeName(name);
        if (sanitized.isEmpty()) {
            QMessageBox::warning(this, "Ошибка",
                                 "ФИО не может быть пустым и должно содержать только буквы!");
            continue;
        }

        if (sanitized != name) {
            int ret = QMessageBox::question(this, "Исправление ФИО",
                                            "Найдены недопустимые символы.\n\n"
                                            "Было: " + name + "\nСтало: " + sanitized + "\n\n"
                                                                                   "Использовать исправленный вариант?",
                                            QMessageBox::Yes | QMessageBox::No);
            if (ret == QMessageBox::Yes) {
                name = sanitized;
                validName = true;
            }
        } else {
            validName = true;
        }
    }

    QString formattedName = nameValidator->formatName(name.trimmed());
    if (name != formattedName) {
        int ret = QMessageBox::question(this, "Форматирование ФИО",
                                        "Привести к правильному формату?\n\n"
                                        "Было: " + name + "\nСтало: " + formattedName,
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            name = formattedName;
        }
    }

    QStringList specs = trainerManager->getSpecializations();
    QString spec = QInputDialog::getItem(this, "Специализация",
                                         "Выберите или введите новую:", specs, 0, true, &ok);
    if (!ok || spec.trimmed().isEmpty()) return;

    QString formattedSpec = nameValidator->formatSpecialization(spec);
    if (spec != formattedSpec) {
        int ret = QMessageBox::question(this, "Форматирование специализации",
                                        "Привести к правильному формату?\n\n"
                                        "Было: " + spec + "\nСтало: " + formattedSpec,
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            spec = formattedSpec;
        }
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Trainers WHERE LOWER(full_name) = LOWER(?)");
    query.addBindValue(name);
    if (query.exec() && query.next() && query.value(0).toInt() > 0) {
        int ret = QMessageBox::question(this, "Предупреждение",
                                        "Тренер с таким ФИО уже существует.\n"
                                        "Добавить все равно?",
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret != QMessageBox::Yes) return;
    }

    if (trainerManager->addTrainer(name, spec)) {
        QMessageBox::information(this, "Успех", "Тренер добавлен!");
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка при добавлении тренера");
    }
}

void MainWindow::on_btnDelTrainer_clicked()
{
    if (!ui->tvTrainers->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Ошибка", "Выберите тренера для удаления!");
        return;
    }

    int row = ui->tvTrainers->currentIndex().row();
    if (QMessageBox::question(this, "Удаление", "Удалить тренера?") == QMessageBox::Yes) {
        trainerManager->deleteTrainer(row);
    }
}

// Слоты для абонементов
void MainWindow::on_btnAddSubType_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Новый тариф", "Название:",
                                         QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    QString formattedName = nameValidator->formatSubscriptionName(name.trimmed());
    if (name != formattedName) {
        int ret = QMessageBox::question(this, "Форматирование названия",
                                        "Привести к правильному формату?\n\n"
                                        "Было: " + name + "\nСтало: " + formattedName,
                                        QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            name = formattedName;
        }
    }

    int price = QInputDialog::getInt(this, "Цена", "Цена (руб):", 1000, 0, 1000000, 1, &ok);
    if (!ok) return;

    int visits = QInputDialog::getInt(this, "Посещения", "Кол-во занятий:", 12, 1, 1000, 1, &ok);
    if (!ok) return;

    if (subscriptionManager->addSubscriptionType(name, price, visits)) {
        QMessageBox::information(this, "Успех",
                                 QString("Тип абонемента добавлен!\n"
                                         "Название: %1\n"
                                         "Цена: %2 руб.\n"
                                         "Посещений: %3")
                                     .arg(name).arg(price).arg(visits));
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка при добавлении типа абонемента");
    }
}

void MainWindow::on_btnAddSubscription_clicked()
{
    QModelIndexList selectedIndexes = ui->tvClients->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите клиента!");
        return;
    }

    int row = selectedIndexes.first().row();
    if (row < 0 || row >= modelClients->rowCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверный индекс клиента!");
        return;
    }

    QSqlRecord record = modelClients->record(row);
    int clientId = record.value("id").toInt();
    QString clientName = record.value("full_name").toString();

    if (clientId <= 0) {
        QMessageBox::warning(this, "Ошибка", "Неверный ID клиента!");
        return;
    }

    QMap<QString, QPair<int, int>> subMap = subscriptionManager->getSubscriptionTypes();
    QStringList subNames = subMap.keys();

    if (subNames.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "В базе нет доступных типов абонементов.");
        return;
    }

    bool ok;
    QString subName = QInputDialog::getItem(this, "Добавить абонемент",
                                            QString("Выберите тип абонемента для клиента\n\"%1\":").arg(clientName),
                                            subNames, 0, false, &ok);
    if (!ok) return;

    QPair<int, int> selectedSub = subMap.value(subName);
    int subTypeId = selectedSub.first;

    QDate defaultStartDate = QDate::currentDate();
    QMessageBox::information(this, "Даты", "Дату начала примем за сегодняшнюю (" +
                                               defaultStartDate.toString("yyyy-MM-dd") + ").");

    if (subscriptionManager->addClientSubscription(clientId, subTypeId, clientName)) {
        QMessageBox::information(this, "Успех",
                                 QString("Абонемент **%1** добавлен клиенту **%2**.")
                                     .arg(subName).arg(clientName));
        clientManager->updateSubscriptionStatuses();
    } else {
        QMessageBox::critical(this, "Ошибка БД", "Не удалось добавить абонемент");
    }
}

void MainWindow::on_btnDelSubType_clicked()
{
    if (!ui->tvSubTypes->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Ошибка", "Выберите тип абонемента для удаления!");
        return;
    }

    int row = ui->tvSubTypes->currentIndex().row();
    if (QMessageBox::question(this, "Удаление", "Удалить этот вид абонемента?") == QMessageBox::Yes) {
        subscriptionManager->deleteSubscriptionType(row);
    }
}

// Слоты для расписания
void MainWindow::on_calendarSchedule_selectionChanged()
{
    QDate date = ui->calendarSchedule->selectedDate();
    scheduleManager->filterByDate(date);
}

void MainWindow::on_btnAddTraining_clicked()
{
    QDate date = ui->calendarSchedule->selectedDate();

    QMap<QString, int> trainerMap = scheduleManager->getTrainers();
    QStringList trainerNames = trainerMap.keys();
    if (trainerNames.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет тренеров в базе.");
        return;
    }

    QMap<QString, int> clientMap = scheduleManager->getClients();
    QStringList clientNames = clientMap.keys();

    bool ok = true;
    QString trainerName = QInputDialog::getItem(this, "Занятие", "Тренер:",
                                                trainerNames, 0, false, &ok);
    if (!ok) return;

    QString clientName = QInputDialog::getItem(this, "Занятие", "Клиент:",
                                               clientNames, 0, false, &ok);
    if (!ok) return;

    QString activityName = QInputDialog::getText(this, "Занятие", "Название:",
                                                 QLineEdit::Normal, "Тренировка", &ok);
    if (!ok) return;

    QString timeStr = QInputDialog::getText(this, "Занятие", "Время (HH:MM):",
                                            QLineEdit::Normal, "12:00", &ok);
    if (!ok) return;

    QString dateTime = date.toString("yyyy-MM-dd") + " " + timeStr;
    int client_id = clientName == "Групповое занятие / Нет клиента" ? 0 : clientMap.value(clientName);

    if (scheduleManager->addTraining(trainerMap.value(trainerName), client_id,
                                     activityName, dateTime)) {
        QMessageBox::information(this, "Успех", "Занятие добавлено.");
    } else {
        QMessageBox::critical(this, "Ошибка БД", "Не удалось добавить занятие");
    }
}

void MainWindow::on_btnDelTraining_clicked()
{
    if (!ui->tvSchedule->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Ошибка", "Выберите занятие для удаления!");
        return;
    }

    int row = ui->tvSchedule->currentIndex().row();
    if (QMessageBox::question(this, "Удаление", "Удалить занятие из расписания?") == QMessageBox::Yes) {
        scheduleManager->deleteTraining(row);
    }
}

// Статистика
void MainWindow::on_btnCalcStats_clicked()
{
    QDate fromDate = ui->deFrom->date();
    QDate toDate = ui->deTo->date();

    StatisticsManager::Statistics stats = statisticsManager->calculateStatistics(fromDate, toDate);

    ui->lblTotalRevenue->setText("Выручка: " + QString::number(stats.totalRevenue) + " руб.");
    ui->lblSoldCount->setText("Продано: " + QString::number(stats.subscriptionsSold) + " шт.");

    QSqlQueryModel *statsModel = new QSqlQueryModel(this);
    QString d1 = fromDate.toString("yyyy-MM-dd");
    QString d2 = toDate.toString("yyyy-MM-dd");

    statsModel->setQuery("SELECT st.name, COUNT(cs.id) as count FROM ClientSubscriptions cs "
                         "JOIN SubscriptionTypes st ON cs.type_id = st.id "
                         "WHERE cs.start_date BETWEEN '" + d1 + "' AND '" + d2 + "' "
                                                 "GROUP BY st.name ORDER BY count DESC");

    statsModel->setHeaderData(0, Qt::Horizontal, "Абонемент");
    statsModel->setHeaderData(1, Qt::Horizontal, "Кол-во");
    ui->tvStatsDetails->setModel(statsModel);
}

// Специализации
void MainWindow::on_btnAddSpecialization_clicked()
{
    bool ok;
    QString newSpec = QInputDialog::getText(this, "Новая специализация",
                                            "Введите название:", QLineEdit::Normal, "", &ok);
    if (!ok || newSpec.trimmed().isEmpty()) return;

    QSqlQuery query;
    query.prepare("INSERT INTO Specializations (name) VALUES (:name)");
    query.bindValue(":name", newSpec.trimmed());

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Специализация добавлена в список!");
    } else {
        QMessageBox::critical(this, "Ошибка", "Ошибка БД: " + query.lastError().text());
    }
}

// Event Filter
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QWidget *viewport = qobject_cast<QWidget*>(watched);
        if (viewport) {
            QTableView *table = qobject_cast<QTableView*>(viewport->parent());
            if (table) {
                QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
                QModelIndex index = table->indexAt(mouseEvent->pos());
                if (!index.isValid()) {
                    table->clearSelection();
                }
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}
