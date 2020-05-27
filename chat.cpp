#include "chat.h"

chat::chat()
{

}
chat::chat(QString m ,int i)
{
this->msg=m;
this->id_p=i;

}
bool chat::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id_p);

    query.prepare("INSERT INTO CHAT (MSG, ID_PARTICIPANT) "
                        "VALUES (:m, :id )");
    query.bindValue(":id", res);
    query.bindValue(":m", msg);


    return    query.exec();

}
QSqlQueryModel * chat::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from CHAT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MSG"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_PARTICIPANT"));
    return model;
}
//////
participant::participant()
{

}
participant::participant(int i,QString n ,int s)
{
this->nom_p=n;
this->id_p=i;
this->status=s;
}
bool participant::ajouter()
{
    QSqlQuery query;
    QString res= QString::number(id_p);
    QString res2= QString::number(status);

    query.prepare("INSERT INTO PARTICIPANT (ID, NOM_PARTICIPANT,STATUS) "
                        "VALUES (:id, :nom,:s )");
    query.bindValue(":nom", res);
    query.bindValue(":id", res);
    query.bindValue(":s", res2);


    return    query.exec();

}
QSqlQueryModel * participant::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from PARTICIPANT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_PARTICIPANT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("STATUS"));
    return model;
}
