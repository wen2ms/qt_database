#include "mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
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
    
    QSqlQuery query;
    QString sql = "SELECT * FROM user";
    
    query.exec(sql);
    while (query.next()) {
        qDebug() << query.value(0).toInt() << query.value(1).toString() << query.value("age").toInt()
                 << query.value("status").toString() << query.value(4).toString();
    }
    
    db.close();
}

MainWindow::~MainWindow() {
    delete ui;
}                                                                                                                                                    
