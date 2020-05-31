#include "avis_fournisseur.h"

avis_fournisseur::avis_fournisseur()
{

}
avis_fournisseur::avis_fournisseur(int ida ,int idf , int note )
{
this->ida=ida;
this->idf=idf;
this->note=note;
}
bool avis_fournisseur::ajouter()
{
QSqlQuery query;
QString res= QString::number(ida);
QString res2= QString::number(idf);
QString res3= QString::number(note);
query.prepare("INSERT INTO AVIS (ID_AVIS, ID_FOURNISSEUR,NOTE) "
                    "VALUES (:ida, :idf, :note )");
query.bindValue(":ida", res);
query.bindValue(":idf", res2);
query.bindValue(":note", res3);

return    query.exec();
}
bool avis_fournisseur::modifier()
{
QSqlQuery query;
QString res= QString::number(ida);
//QString res2= QString::number(idf);
QString res3= QString::number(note);
query.prepare("update  AVIS set  NOTE=:note "
                    "where ID_AVIS = :ida");
query.bindValue(":ida", res);
//query.bindValue(":idf", res2);
query.bindValue(":note", res3);
return    query.exec();
}
QSqlQueryModel * avis_fournisseur::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from AVIS");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_AVIS"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_FOUR"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOTE"));

return model;
}
bool avis_fournisseur::supprimer(int ida)
{
QSqlQuery query;
QString res= QString::number(ida);
query.prepare("Delete from AVIS where ID_AVIS = :ida ");
query.bindValue(":ida", res);
return    query.exec();
}
