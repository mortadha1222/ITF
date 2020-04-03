#include "connexion.h"
#include <QSqlDatabase>
#include<QDebug>
#include <QSqlQuery>
#include<iostream>
#include <QSqlError>
using namespace std;
connexion::connexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("mortadha22");
    db.setPassword("esprit20");
    if(db.open())
    {
        cout<<"succes"<<endl;
    }
        else
        {
        qDebug()<< db.lastError();
        cout<<"failed"<<endl;
        }
}
