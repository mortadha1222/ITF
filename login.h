#ifndef LOGIN_H
#define LOGIN_H
#include <QApplication>
#include <QSqlQuery>

#include "mainwindow.h"
class login
{


    QSqlQuery query;
public:
    QString password,username,role;
    login();
    login(QString,QString,QString);
    bool connect();

   bool  adminConnect();
};

#endif // LOGIN_H
