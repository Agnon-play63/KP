#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ClientManager;
class TrainerManager;
class SubscriptionManager;
class ScheduleManager;
class StatisticsManager;
class NameValidator;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    // Клиенты
    void on_btnAddClient_clicked();
    void on_btnEditClient_clicked();
    void on_btnDelClient_clicked();
    void on_btnRegisterVisit_clicked();

    // Тренеры
    void on_btnAddTrainer_clicked();
    void on_btnDelTrainer_clicked();

    // Абонементы
    void on_btnAddSubType_clicked();
    void on_btnAddSubscription_clicked();
    void on_btnDelSubType_clicked();

    // Расписание
    void on_calendarSchedule_selectionChanged();
    void on_btnAddTraining_clicked();
    void on_btnDelTraining_clicked();

    // Статистика
    void on_btnCalcStats_clicked();

    // Специализации
    void on_btnAddSpecialization_clicked();

private:
    void setupModels();
    void updateClientSubscriptionStatuses();
    void applyTableStyle(QTableView* table);

    Ui::MainWindow *ui;

    QSqlTableModel *modelClients;
    QSqlTableModel *modelTrainers;
    QSqlTableModel *modelSubTypes;
    QSqlRelationalTableModel *modelSchedule;

    ClientManager *clientManager;
    TrainerManager *trainerManager;
    SubscriptionManager *subscriptionManager;
    ScheduleManager *scheduleManager;
    StatisticsManager *statisticsManager;
    NameValidator *nameValidator;
};

#endif // MAINWINDOW_H
