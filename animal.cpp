#include "animal.h"
#include <QDebug>
//#include "connection.h"

Animal::Animal()
{
   id=0;
   nb=0;
   prix=0;
   nom="";
}
 Animal::Animal(int id,QString nom,int nb,float prix,int idf)
{
    this->id=id;
     this->nom=nom;
     this->nb=nb;
     this->prix=prix;
     this->idf=idf;

}
 QString Animal::get_nom(){return nom;}
 int Animal::get_id(){return id;}
 int Animal::get_nb(){return nb;}
 float Animal::get_prix(){return prix;}

 bool Animal::ajouter()
 {
     QString mj1= QString::number(id);
     QString mj2= QString::number(nb);
     QString mj3= QString::number(prix);
     QString mj4= QString::number(idf);

 QSqlQuery query;
 query.prepare("INSERT INTO Animal (ID, NOMBRE, PRIX, NOM,ID_FOURNISSEUR) "
                     "VALUES (:id, :nb, :prix, :nom,:i)");

 query.bindValue(":id", mj1);
 query.bindValue(":nom", nom);
 query.bindValue(":nb", mj2);
 query.bindValue(":prix", mj3);
 query.bindValue(":i", mj4);

 return    query.exec();
 }

 QSqlQueryModel * Animal::afficher()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Animal");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
 return model;
 }

 QSqlQueryModel * Animal::afficherup_ID()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from animal ORDER BY ID ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

     return model;
 }
 QSqlQueryModel * Animal::afficherdown_ID()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from animal ORDER BY ID DESC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

     return model;
 }
 QSqlQueryModel * Animal::afficherup_prix()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from animal ORDER BY PRIX ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

     return model;
 }
 QSqlQueryModel * Animal::afficherdown_prix()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from animal ORDER BY PRIX DESC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

     return model;
 }
 QSqlQueryModel * Animal::afficherup_nb()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from animal ORDER BY NOMBRE ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

     return model;
 }
 QSqlQueryModel * Animal::afficherdown_nb()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from animal ORDER BY NOMBRE DESC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

     return model;
 }


 QSqlQueryModel * Animal::rechercher(QString nom)
     {
     QSqlQueryModel * model= new QSqlQueryModel();
      QSqlQuery query;

      model->setQuery("SELECT * FROM animal WHERE nom like '%"+nom+"%' ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));


         return model;
     }

 bool Animal::modifier()
 {
     QString mj= QString::number(nb);
     QString mj1= QString::number(prix);
     QString mj2= QString::number(id);
     QString mj4= QString::number(idf);
 QSqlQuery query;
 query.prepare("UPDATE Animal SET NOMBRE=:nb,PRIX=:prix,NOM=:nom,ID_FOURNISSEUR=:i  WHERE ID=:id");
 query.bindValue(":nom",nom);
 query.bindValue(":id",mj2);
 query.bindValue(":nb", mj);
 query.bindValue(":prix", mj1);
 query.bindValue(":i", mj4);

 return    query.exec();
 }




 bool Animal::supprimer(int NId)
 {
     QSqlQuery query;

     query.prepare("Delete from Animal where id = :id");
     query.bindValue(":id",NId);
     return    query.exec();
 }

