#ifndef CHAT_H
#define CHAT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class chat
{

private:
    QString msg;
    int id_p;

public:
    chat();
    chat(QString ,int);
    bool ajouter();
    QSqlQueryModel * afficher();
};
class participant
{

private:
    QString nom_p;
    int id_p,status;

public:
    participant();
    participant( int  ,QString,int);
    bool ajouter();
    QSqlQueryModel * afficher();
};

#endif // CHAT_H
