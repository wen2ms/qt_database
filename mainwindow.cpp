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
    
    sql = "UPDATE user SET id = 2 WHERE id = 1";
    
    db.transaction();
    
    bool is_succuessful = query.exec(sql);
    if (is_succuessful) {
        qDebug() << "commit";
        db.commit();
    } else {
        qDebug() << "rollback";
        db.rollback();
    }
    
    sql = "UPDATE user SET name = 'Tom999' WHERE id = 1";
    
    db.transaction();
    
    is_succuessful = query.exec(sql);
    if (is_succuessful) {
        qDebug() << "commit";
        db.commit();
    } else {
        qDebug() << "rollback";
        db.rollback();
    }
    
    sql = "UPDATE user SET name = 'Tom1' WHERE id = 1";
    query.exec(sql);
    
    db.close();
}

MainWindow::~MainWindow() {
    delete ui;
}                                                                                                                                                    
