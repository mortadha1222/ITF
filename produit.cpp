#include "produit.h"
#include <QDebug>
//#include "connection.h"
Produit::Produit()
{
   id=0;
   quantite=0;
   prix=0;
   nom="";
}
 Produit::Produit(int id,QString nom,int quantite,float prix,int idf)
{
    this->id=id;
     this->nom=nom;
     this->quantite=quantite;
     this->prix=prix;
     this->idf=idf;


}
 bool Produit::ajouter()
 {
     QString mj1= QString::number(id);
     QString mj2= QString::number(quantite);
     QString mj3= QString::number(prix);
     QString mj4= QString::number(idf);

 QSqlQuery query;
 query.prepare("INSERT INTO produit (ID, QUANTITE, PRIX, NOM,ID_FOURNISSEUR) "
                     "VALUES (:id, :nb, :prix, :nom,:i)");
 query.bindValue(":id", mj1);
 query.bindValue(":nom", nom);
 query.bindValue(":nb", mj2);
 query.bindValue(":prix", mj3);
 query.bindValue(":i", mj4);


 return    query.exec();
 }
 QString Produit::get_nom(){return nom;}
 int Produit::get_id(){return id;}
 int Produit::get_quantite(){return quantite;}
 float Produit::get_prix(){return prix;}

 bool Produit::supprimer(int NId)
 {
     QSqlQuery query;

     query.prepare("Delete from Produit where id = :id");
     query.bindValue(":id",NId);
     return    query.exec();
 }

 QSqlQueryModel * Produit::afficher()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }

 QSqlQueryModel * Produit::afficherup_ID()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit ORDER BY ID ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }
 QSqlQueryModel * Produit::afficherdown_ID()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit ORDER BY ID DESC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }
 QSqlQueryModel * Produit::afficherup_prix()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit ORDER BY PRIX ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }
 QSqlQueryModel * Produit::afficherdown_prix()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit ORDER BY PRIX DESC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }
 QSqlQueryModel * Produit::afficherup_nb()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit ORDER BY QUANTITE ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }
 QSqlQueryModel * Produit::afficherdown_nb()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from Produit ORDER BY QUANTITE DESC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("quantite"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

 return model;
 }


 QSqlQueryModel * Produit::rechercher(QString nom)
     {
     QSqlQueryModel * model= new QSqlQueryModel();
      QSqlQuery query;

      model->setQuery("SELECT * FROM Produit WHERE nom like '%"+nom+"%' ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));

         return model;
     }

 bool Produit::modifier()
 {
     QString mj= QString::number(quantite);
     QString mj1= QString::number(prix);
     QString mj2= QString::number(id);
     QString mj4= QString::number(idf);

 QSqlQuery query;
 query.prepare("UPDATE Produit SET quantite=:nb,PRIX=:prix,NOM=:nom,ID_FOURNISSEUR=:i WHERE ID=:id");
 query.bindValue(":nom",nom);
 query.bindValue(":nb", mj);
 query.bindValue(":id", mj2);
 query.bindValue(":prix", mj1);
 query.bindValue(":i", mj4);

 return    query.exec();
 }
