#include "plante.h"
#include <QDebug>
#include "connexion.h"


plante::plante()
{
nom_plante="";
nombre=0;
prix=0;
surface=0;
type=0;
zone=-1;
age=0;
}
plante::plante(QString nomm,int nb,float prixx,float surfacee,float humiditee,float fructificationn,float fprixx,int agee,QString reclotee,int typee,int zonee,int idff,QString refnn)
{
  this->nom_plante=nomm;
    this->nombre=nb;
    this->prix=prixx;
    this->surface=surfacee;
    this->humidite=humiditee;
    this->fructification=fructificationn;
    this->fprix=fprixx;
    this->age=agee;
    this->reclote=reclotee;
    this->type=typee;
    this->zone=zonee;
    this->idf=idff;
    this->refn=refnn;

}
QString plante::get_nom_plante(){return nom_plante ;}
int plante::get_nombre(){return nombre ;}
float plante::get_prix(){return prix ;}
float plante::get_surface(){return surface ;}
float plante::get_humidite(){return humidite ;}
float plante::get_fructification(){return fructification ;}
float plante::get_fprix(){return fprix ;}
int plante::get_age(){return age ;}
QString plante::get_reclote(){return reclote ;}
int plante::get_type(){return type ;}
int plante::get_zone(){return zone ;}
//hedhom ?le


bool plante::ajouter()
{
QSqlQuery query;
QString res2= QString::number(nombre);
QString res3= QString::number(age);
QString res4= QString::number(type);
QString res5= QString::number(zone);
QString res6= QString::number(prix);
QString res7= QString::number(fprix);
QString res8= QString::number(surface);
QString res9= QString::number(humidite);
QString res10= QString::number(idf);
QString res11= QString::number(fructification);



query.prepare("INSERT INTO PLANTE (NOM_PLANTE,NOMBRE,PRIX,SURFACE,HUMIDITE,FRUCTIFICATION,FPRIX,AGE,RECLOTE,TYPE,ZONE,ID_FOURNISSEUR,REF_NOURRITURE) "
                    "VALUES (:nom_plante,:nombre,:prix,:surface,:humidite,:fructification,:fprix,:age,:reclote,:type,:zone,:idf,:refn)");
query.bindValue(":nom_plante",nom_plante);
query.bindValue(":nombre",res2);
query.bindValue(":prix",res6);
query.bindValue(":surface",res8);
query.bindValue(":humidite",res9);
query.bindValue(":fructification",res11);
query.bindValue(":fprix",res7);
query.bindValue(":age",res3);
query.bindValue(":reclote",reclote);
query.bindValue(":type",res4);
query.bindValue(":zone",res5);
query.bindValue(":idf",res10);
query.bindValue(":refn",refn);


return    query.exec();
}

QSqlQueryModel * plante::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PLANTE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_plante"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("surface"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("humidite"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("fructification"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("fprix"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("reclote"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(10, Qt::Horizontal, QObject::tr("zone"));
model->setHeaderData(11, Qt::Horizontal, QObject::tr("idf"));
model->setHeaderData(12, Qt::Horizontal, QObject::tr("refn"));
    return model;
}

QSqlQueryModel * plante::afficherup()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PLANTE  ORDER BY zone ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_plante"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("surface"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("humidite"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("fructification"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("fprix"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("reclote"));
model->setHeaderData(9, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(10, Qt::Horizontal, QObject::tr("zone"));
model->setHeaderData(11, Qt::Horizontal, QObject::tr("idf"));
model->setHeaderData(12, Qt::Horizontal, QObject::tr("refn"));

    return model;
}


QSqlQueryModel * plante::afficherdown()
    {QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from PLANTE ORDER BY zone DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_plante"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("surface"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("humidite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fructification"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("fprix"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("reclote"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("zone"));
     model->setHeaderData(11, Qt::Horizontal, QObject::tr("idf"));
     model->setHeaderData(12, Qt::Horizontal, QObject::tr("refn"));

        return model;
    }




bool plante::supprimer(QString nom)
{
QSqlQuery query;

query.prepare("Delete from PLANTE where NOM_PLANTE = :nom_plante ");
query.bindValue(":nom_plante",nom);
return    query.exec();
}



QSqlQueryModel * plante::rechercher(QString nom)
    {QSqlQueryModel * model= new QSqlQueryModel();
     QSqlQuery query;

     model->setQuery("SELECT * FROM plante WHERE NOM_PLANTE like '%"+nom+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_plante"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nombre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("surface"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("humidite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fructification"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("fprix"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("reclote"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("zone"));
     model->setHeaderData(11, Qt::Horizontal, QObject::tr("idf"));
     model->setHeaderData(12, Qt::Horizontal, QObject::tr("refn"));


        return model;
    }




bool plante::modifier()
{
QSqlQuery query;
QString res2= QString::number(nombre);
QString res3= QString::number(age);


QString res6= QString::number(prix);
QString res7= QString::number(fprix);
QString res8= QString::number(surface);




query.prepare("UPDATE plante SET NOMBRE=:nombre,PRIX=:prix,SURFACE=:surface,FPRIX=:fprix,AGE=:age WHERE nom_plante=:nom_plante");
query.bindValue(":nom_plante",nom_plante);
query.bindValue(":nombre",res2);
query.bindValue(":prix",res6);
query.bindValue(":surface",res8);

query.bindValue(":fprix",res7);
query.bindValue(":age",res3);





return    query.exec();
}
