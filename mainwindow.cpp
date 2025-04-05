#include "mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    QStringList list = QSqlDatabase::drivers();
    
    qDebug() << list;
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("test");
    // db.setPassword();
    db.setPort(3306);
    
    if (!db.open()) {
        qDebug() << "The failure: " << db.lastError().text();
    } else {
        qDebug() << "Connect successfully!!!";
    }
}

MainWindow::~MainWindow() {
    delete ui;
}                                                                                                                                                    
