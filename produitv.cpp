#include "produitv.h"
#include <QDebug>
#include "connexion.h"

produitv::produitv()
{
nom_produit="";
quantite=0;
prixunitaire=0;
}



produitv::produitv(QString nomm,int nb,float prixx)
{
  this->nom_produit=nomm;
    this->quantite=nb;
    this->prixunitaire=prixx;


}


QString produitv::get_nom_produit(){return nom_produit;}
int produitv::get_quantite(){return quantite;}
float produitv::get_prixunitaire(){return prixunitaire;}


bool produitv::ajouter()
{
QSqlQuery query;
QString res2= QString::number(quantite);
QString res3= QString::number(prixunitaire);




query.prepare("INSERT INTO PRODUIT_VEGETAL (NOM_PRODUIT,QUANTITE,PRIX_UNITAIRE) "
                    "VALUES (:nom_produit,:quantite,:prixunitaire)");
query.bindValue(":nom_produit",nom_produit);
query.bindValue(":quantite",res2);
query.bindValue(":prixunitaire",res3);



return    query.exec();
}

QSqlQueryModel * produitv::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PRODUIT_VEGETAL");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_produit"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prixunitaire"));



    return model;
}

QSqlQueryModel * produitv::afficherup()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PRODUIT_VEGETAL  ORDER BY nom_produit ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_produit"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prixunitaire"));


    return model;
}


QSqlQueryModel * produitv::afficherdown()
    {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from PRODUIT_VEGETAL  ORDER BY nom_produit DESC");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_produit"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prixunitaire"));



        return model;
    }




bool produitv::supprimer(QString nom)
{
QSqlQuery query;

query.prepare("Delete from PRODUIT_VEGETAL where nom_produit = :nom_produit ");
query.bindValue(":nom_produit",nom);
return    query.exec();
}



QSqlQueryModel * produitv::rechercher(QString nom)
    {QSqlQueryModel * model= new QSqlQueryModel();
     QSqlQuery query;

     model->setQuery("SELECT * FROM PRODUIT_VEGETAL WHERE NOM_PRODUIT like '%"+nom+"%' ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom_produit"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("prixunitaire"));



        return model;
    }




bool produitv::modifier()
{
QSqlQuery query;
QString res2= QString::number(quantite);
QString res3= QString::number(prixunitaire);





query.prepare("UPDATE PRODUIT_VEGETAL SET quantite=:quantite,prix_unitaire=:prixunitaire WHERE nom_produit=:nom_produit");
query.bindValue(":nom_produit",nom_produit);
query.bindValue(":quantite",res2);
query.bindValue(":prixunitaire",res3);



return    query.exec();
}

