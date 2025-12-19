/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget_2;
    QWidget *tab_6;
    QTableView *tvClients;
    QPushButton *btnAddClient;
    QPushButton *btnEditClient;
    QPushButton *btnDelClient;
    QPushButton *btnRegisterVisit;
    QPushButton *btnAddSubscription;
    QWidget *tab_7;
    QTableView *tvTrainers;
    QPushButton *btnAddTrainer;
    QPushButton *btnDelTrainer;
    QWidget *tab_8;
    QTableView *tvSubTypes;
    QPushButton *btnAddSubType;
    QPushButton *btnDelSubType;
    QWidget *tab_9;
    QCalendarWidget *calendarSchedule;
    QPushButton *btnAddTraining;
    QPushButton *btnDelTraining;
    QPushButton *btnRefresh;
    QTableView *tvSchedule;
    QWidget *tab_10;
    QDateEdit *deFrom;
    QDateEdit *deTo;
    QPushButton *btnCalcStats;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QTableView *tvStatsDetails;
    QGroupBox *groupBox;
    QLabel *lblTotalRevenue;
    QLabel *lblSoldCount;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(624, 547);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(0, 0, 611, 501));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        tvClients = new QTableView(tab_6);
        tvClients->setObjectName("tvClients");
        tvClients->setGeometry(QRect(0, 0, 321, 471));
        btnAddClient = new QPushButton(tab_6);
        btnAddClient->setObjectName("btnAddClient");
        btnAddClient->setGeometry(QRect(320, 0, 281, 41));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setUnderline(true);
        btnAddClient->setFont(font);
        btnEditClient = new QPushButton(tab_6);
        btnEditClient->setObjectName("btnEditClient");
        btnEditClient->setGeometry(QRect(320, 40, 281, 41));
        btnEditClient->setFont(font);
        btnDelClient = new QPushButton(tab_6);
        btnDelClient->setObjectName("btnDelClient");
        btnDelClient->setGeometry(QRect(320, 80, 281, 41));
        btnDelClient->setFont(font);
        btnRegisterVisit = new QPushButton(tab_6);
        btnRegisterVisit->setObjectName("btnRegisterVisit");
        btnRegisterVisit->setGeometry(QRect(320, 120, 281, 41));
        btnRegisterVisit->setFont(font);
        btnAddSubscription = new QPushButton(tab_6);
        btnAddSubscription->setObjectName("btnAddSubscription");
        btnAddSubscription->setGeometry(QRect(320, 160, 281, 41));
        btnAddSubscription->setFont(font);
        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        tvTrainers = new QTableView(tab_7);
        tvTrainers->setObjectName("tvTrainers");
        tvTrainers->setGeometry(QRect(0, 0, 301, 471));
        btnAddTrainer = new QPushButton(tab_7);
        btnAddTrainer->setObjectName("btnAddTrainer");
        btnAddTrainer->setGeometry(QRect(310, 0, 141, 41));
        btnAddTrainer->setFont(font);
        btnDelTrainer = new QPushButton(tab_7);
        btnDelTrainer->setObjectName("btnDelTrainer");
        btnDelTrainer->setGeometry(QRect(460, 0, 141, 41));
        btnDelTrainer->setFont(font);
        tabWidget_2->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        tvSubTypes = new QTableView(tab_8);
        tvSubTypes->setObjectName("tvSubTypes");
        tvSubTypes->setGeometry(QRect(0, 0, 301, 471));
        btnAddSubType = new QPushButton(tab_8);
        btnAddSubType->setObjectName("btnAddSubType");
        btnAddSubType->setGeometry(QRect(310, 0, 141, 41));
        btnAddSubType->setFont(font);
        btnDelSubType = new QPushButton(tab_8);
        btnDelSubType->setObjectName("btnDelSubType");
        btnDelSubType->setGeometry(QRect(460, 0, 141, 41));
        btnDelSubType->setFont(font);
        tabWidget_2->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName("tab_9");
        calendarSchedule = new QCalendarWidget(tab_9);
        calendarSchedule->setObjectName("calendarSchedule");
        calendarSchedule->setGeometry(QRect(0, 0, 312, 190));
        btnAddTraining = new QPushButton(tab_9);
        btnAddTraining->setObjectName("btnAddTraining");
        btnAddTraining->setGeometry(QRect(0, 190, 311, 31));
        btnAddTraining->setFont(font);
        btnDelTraining = new QPushButton(tab_9);
        btnDelTraining->setObjectName("btnDelTraining");
        btnDelTraining->setGeometry(QRect(0, 220, 311, 31));
        btnDelTraining->setFont(font);
        btnRefresh = new QPushButton(tab_9);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setGeometry(QRect(0, 250, 311, 31));
        btnRefresh->setFont(font);
        tvSchedule = new QTableView(tab_9);
        tvSchedule->setObjectName("tvSchedule");
        tvSchedule->setGeometry(QRect(320, 0, 281, 471));
        tvSchedule->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tvSchedule->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tabWidget_2->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        deFrom = new QDateEdit(tab_10);
        deFrom->setObjectName("deFrom");
        deFrom->setGeometry(QRect(0, 0, 111, 41));
        deTo = new QDateEdit(tab_10);
        deTo->setObjectName("deTo");
        deTo->setGeometry(QRect(270, 0, 111, 41));
        btnCalcStats = new QPushButton(tab_10);
        btnCalcStats->setObjectName("btnCalcStats");
        btnCalcStats->setGeometry(QRect(490, 0, 111, 41));
        btnCalcStats->setFont(font);
        lineEdit = new QLineEdit(tab_10);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(110, 0, 111, 41));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        lineEdit->setFont(font1);
        lineEdit->setReadOnly(true);
        lineEdit_2 = new QLineEdit(tab_10);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(380, 0, 111, 41));
        lineEdit_2->setFont(font1);
        lineEdit_2->setReadOnly(true);
        tvStatsDetails = new QTableView(tab_10);
        tvStatsDetails->setObjectName("tvStatsDetails");
        tvStatsDetails->setGeometry(QRect(380, 40, 221, 411));
        groupBox = new QGroupBox(tab_10);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(110, 50, 201, 201));
        groupBox->setFont(font1);
        lblTotalRevenue = new QLabel(groupBox);
        lblTotalRevenue->setObjectName("lblTotalRevenue");
        lblTotalRevenue->setGeometry(QRect(10, 70, 111, 16));
        lblSoldCount = new QLabel(groupBox);
        lblSoldCount->setObjectName("lblSoldCount");
        lblSoldCount->setGeometry(QRect(10, 140, 111, 16));
        tabWidget_2->addTab(tab_10, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 624, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnAddClient->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnEditClient->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btnDelClient->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnRegisterVisit->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\321\202\320\270\321\202\321\214 \320\277\320\276\321\201\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        btnAddSubscription->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\260\320\261\320\276\320\275\320\265\320\274\320\265\320\275\321\202", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("MainWindow", "\320\232\320\273\320\270\320\265\320\275\321\202\321\213", nullptr));
        btnAddTrainer->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelTrainer->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QCoreApplication::translate("MainWindow", "\320\242\321\200\320\265\320\275\320\265\321\200\321\213", nullptr));
        btnAddSubType->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelSubType->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QCoreApplication::translate("MainWindow", "\320\220\320\261\320\276\320\275\320\265\320\274\320\265\320\275\321\202\321\213", nullptr));
        btnAddTraining->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\321\200\320\265\320\275\320\270\321\200\320\276\320\262\320\272\321\203", nullptr));
        btnDelTraining->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\267\320\260\320\275\321\217\321\202\320\270\320\265", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_9), QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        btnCalcStats->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\320\241 \320\272\320\260\320\272\320\276\320\263\320\276 \321\207\320\270\321\201\320\273\320\260", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276 \320\272\320\260\320\272\320\276\320\265 \321\207\320\270\321\201\320\273\320\276", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\275\320\260\320\275\321\201\320\276\320\262\321\213\320\265 \320\270\321\202\320\276\320\263\320\270", nullptr));
        lblTotalRevenue->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\200\321\203\321\207\320\272\320\260: [0 \321\200\321\203\320\261]", nullptr));
        lblSoldCount->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\260\320\275\320\276: [0 \321\210\321\202]", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_10), QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260/\320\244\320\270\320\275\320\260\320\275\321\201\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
