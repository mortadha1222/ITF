#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<QPrinter>
#include<QPrintDialog>
//#include "mailing/SmtpMime"

#include <QPainter>
#include<QtPrintSupport>
#include<smtpp.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterplante.h"
#include "ui_ajouterplante.h"
#include "ajouterf.h"
#include "ajoutern.h"
#include "ajouterequipement.h"
#include "ajoutervehicule.h"
#include "plante.h"
#include <QMessageBox>
#include<QDebug>
#include<QPixmap>
QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    ui->afficherplantes->setModel(tmpplante.afficher());
    ui->afficherproduitv->setModel(tmpproduitv.afficher());
  connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(sendMail()));
   // ui->stackedWidget_2->setCurrentIndex(0);
    //QPixmap px("C:/Users/ahmed/Documents/testqt/Ressources/log.jpg");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ajouterplante_clicked()
{
ui->stackedWidget_2->setCurrentIndex(3);




}

void MainWindow::on_pushButton_11_clicked()
{
   ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_12_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}






void MainWindow::on_ajoutplante_clicked()
{

        QString nom_plante=ui->inom->text();
        int nombre=ui->inombre->text().toInt();
        float prix=ui->iprix->text().toFloat();
         float surface=ui->isurface->text().toFloat();
         float humidite=ui->ihumidite->text().toFloat();
         QString fructification=ui->ifructification->text();
        float  fprix=ui->iprix->text().toFloat();
         int age=ui->iage->text().toInt();
         QString reclote=ui->ireclote->text();
         int type=ui->itype->text().toInt();
         int zone=ui->izone->text().toInt();
        plante p(nom_plante,nombre,prix,surface,humidite,fructification,fprix,age,reclote,type,zone);
        bool test=p.ajouter();
        if(test)
      {

           ui->afficherplantes->setModel(tmpplante.afficher());//refresh
      QMessageBox::information(nullptr, QObject::tr("Ajouter un étudiant"),
                        QObject::tr("plante ajouté.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
            QMessageBox::critical(nullptr, QObject::tr("Ajouter une plante"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_pushButton_2_clicked()
{
    Smtpp* smtpp = new Smtpp("samibhh1998@gmail.com", "txngnk98","smtp.gmail.com", 465);
     connect(smtpp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));



     smtpp->sendMail("sami.belhajhassine@esprit.tn", "sami.belhajhassine@esprit.tn" , "ui->subject->text()","ui->msg->toPlainText()");
}



void MainWindow::on_supprimerplante_clicked()
{

ui->stackedWidget_2->setCurrentIndex(2);

}

void MainWindow::on_pushButton_9_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString nom= ui->nomasupprimer->text();
     bool test=tmpplante.supprimer(nom);
   if(test)
    {ui->afficherplantes->setModel(tmpplante.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une plante"),
                    QObject::tr("supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une plante"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_19_clicked()
{
ui->afficherplantes->setModel(tmpplante.afficherdown());
}



void MainWindow::on_pushButton_20_clicked()
{
ui->afficherplantes->setModel(tmpplante.afficherup());
}





void MainWindow::on_pushButton_21_clicked()
{
    QString nom=ui->nomrecherche->text();
    ui->afficherplantes->setModel(tmpplante.rechercher(nom));
}

void MainWindow::on_nomrecherche_textChanged(const QString &arg1)
{

    ui->afficherplantes->setModel(tmpplante.rechercher(arg1));
}



void MainWindow::on_afficherplantes_activated(const QModelIndex &index)
{
    QString val=ui->afficherplantes->model()->data(index).toString();
    QSqlQuery q;
    q.prepare("select * from PLANTE where nom_plante='"+val+"'");
  if(q.exec())
      while (q.next()) {
          ui->modnom->setText(q.value(0).toString());
                  ui->modnombre->setText(q.value(1).toString());
                  ui->modprix->setText(q.value(2).toString());
      ui->modsurface->setText(q.value(3).toString());
                  ui->modprix->setText(q.value(4).toString());
                  ui->modage->setText(q.value(5).toString());
      }

}



void MainWindow::on_mod_clicked()
{
    QString nom_plante=ui->modnom->text();
    int nombre=ui->modnombre->text().toInt();
    float prix=ui->modprix->text().toFloat();
     float surface=ui->modsurface->text().toFloat();
    float  fprix=ui->modprix->text().toFloat();
     int age=ui->modage->text().toInt();
    plante p(nom_plante,nombre,prix,surface,0,"",fprix,age,"",0,0);
    bool test=p.modifier();
    if(test)
  {

       ui->afficherplantes->setModel(tmpplante.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("modifier"),
                    QObject::tr("modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_produitvdown_clicked()
{
 ui->afficherproduitv->setModel(tmpproduitv.afficherdown());
}

void MainWindow::on_produitvup_clicked()
{
     ui->afficherproduitv->setModel(tmpproduitv.afficherup());
}

void MainWindow::on_ajouterproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);

}

void MainWindow::on_pushButton_22_clicked()
{
    QString nom_produitv=ui->inomproduitv->text();
    int quantite=ui->iquantite->text().toInt();
    float prixunitaire=ui->iprixunitaire->text().toFloat();

    produitv p(nom_produitv,quantite,prixunitaire);
    bool test=p.ajouter();
    if(test)
  {

       ui->afficherproduitv->setModel(tmpproduitv.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("Ajouter un étudiant"),
                    QObject::tr("Etudiant ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un étudiant"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_pushButton_24_clicked()
{
    QString nom= ui->nomproduitasupprimer->text();
     bool test=tmpproduitv.supprimer(nom);
   if(test)
    {ui->afficherproduitv->setModel(tmpproduitv.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une plante"),
                    QObject::tr("supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une plante"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_supprimerproduitv_clicked()
{
        ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_pushButton_25_clicked()
{
   ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_mod_2_clicked()
{
    QString nom_produit=ui->modnomproduitv->text();
    int quantite=ui->modquantite->text().toInt();
    float prixunitaire=ui->modprixunitaire->text().toFloat();

  produitv p(nom_produit,quantite,prixunitaire);
    bool test=p.modifier();
    if(test)
  {

       ui->afficherproduitv->setModel(tmpproduitv.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("modifier"),
                    QObject::tr("modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_afficherproduitv_activated(const QModelIndex &index)
{
    QString val=ui->afficherproduitv->model()->data(index).toString();
    QSqlQuery q;
    q.prepare("select * from produit_vegetal where nom_produit='"+val+"'");
  if(q.exec())
      while (q.next()) {
          ui->modnomproduitv->setText(q.value(0).toString());
                  ui->modquantite->setText(q.value(1).toString());
                  ui->modprixunitaire->setText(q.value(2).toString());
    /*  ui->modnomplante->setText(q.value(3).toString());
                  ui->modidfour->setText(q.value(4).toString());*/

      }
}

void MainWindow::on_rechercherproduitv_clicked()
{
    QString nom=ui->nomproduitrecherche->text();
    ui->afficherproduitv->setModel(tmpproduitv.rechercher(nom));
}

void MainWindow::on_opplus_clicked()
{
    double num1=ui->numero1->text().toDouble();
    double num2=ui->numero2->text().toDouble();
    double result=num1+num2;
               ui->resultatcalc->setText(QString :: number(result));
               result=0;

}

void MainWindow::on_opmoins_clicked()
{
    double num1=ui->numero1->text().toDouble();
    double num2=ui->numero2->text().toDouble();
    double result=num1-num2;
               ui->resultatcalc->setText(QString :: number(result));
               result=0;
}

void MainWindow::on_opetoile_clicked()
{
    double num1=ui->numero1->text().toDouble();
    double num2=ui->numero2->text().toDouble();
    double result=num1*num2;
               ui->resultatcalc->setText(QString :: number(result));
               result=0;
}

void MainWindow::on_opsur_clicked()
{
   double num1=ui->numero1->text().toDouble();
    double num2=ui->numero2->text().toDouble();
    if(num2==0)
        ui->resultatcalc->setText("ERROR !");
else
   { double result=num1/num2;
               ui->resultatcalc->setText(QString :: number(result));
               result=0;
    }
}

void MainWindow::on_exitcalc_clicked()
{
      ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_calculator_clicked()
{
 ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_statplante_clicked()
{
bool test=true;
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select NOM_PLANTE,NOMBRE  from PLANTE  order by NOMBRE  DESC");
        if(q.exec())
      { //  int c=0;
           qDebug()<<"azazazazazaz";
          while (q.next())
          {
              qDebug()<<"azazazazazaz";
          QString a=q.value(0).toString() ;
          int b= q.value(1).toInt()  ;
         // if(c==0)
         // {
             // QPieSlice *slice =  series->append(a, b );
             // slice->setExploded();
             // slice->setLabelVisible();
          //}
         // else
         // {
              series->append(a, b );
          //}
      }}}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("donut chart repartition des plante par nombre :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->horizontalFrame);
    ui->stackedWidget_2->setCurrentIndex(7);

}

void MainWindow::on_anulerstato_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_printplante_clicked()
{/*
QPrinter printer;
QPrintDialog dialog(&printer, this);
dialog.setWindowTitle("Print Document");

if(ui->afficherplantes)
{
  dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
if(dialog.exec() != QDialog::Accepted){
    return;
}*/

    QPixmap pix(ui->afficherplantes->size());
      QPainter painter(&pix);
     ui->afficherplantes->render(&painter);
      painter.end();
      QPrinter printer(QPrinter::HighResolution);
      printer.setOrientation(QPrinter::Landscape);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName("C:/Users/asus/Desktop/test/plantes.pdf"); // will be in build folder

      painter.begin(&printer);
      double xscale = printer.pageRect().width() / double(pix.width());
      double yscale = printer.pageRect().height() / double(pix.height());
      double scale = qMin(xscale, yscale);
      painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                        printer.paperRect().y() + printer.pageRect().height() / 2);
      painter.scale(scale, scale);
      painter.translate(-ui->afficherplantes->width() / 2, -ui->afficherplantes->height() / 2);
      painter.drawPixmap(0, 0, pix);

    QTextDocument doc;

    doc.setHtml("Table plante");
    doc.drawContents(&painter);

      painter.end();
    }


void MainWindow::on_supprimerplante_2_clicked()
{
    QString nom= ui->nomasupprimer->text();
     bool test=tmpplante.supprimer(nom);
   if(test)
    {ui->afficherplantes->setModel(tmpplante.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une plante"),
                    QObject::tr("supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une plante"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_anulersupprimerplante_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_printprodv_clicked()
{
    QPixmap pix(ui->afficherproduitv->size());
      QPainter painter(&pix);
     ui->afficherproduitv->render(&painter);
      painter.end();
      QPrinter printer(QPrinter::HighResolution);
      printer.setOrientation(QPrinter::Landscape);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName("C:/Users/asus/Desktop/test/produitv.pdf"); // will be in build folder

      painter.begin(&printer);
      double xscale = printer.pageRect().width() / double(pix.width());
      double yscale = printer.pageRect().height() / double(pix.height());
      double scale = qMin(xscale, yscale);
      painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                        printer.paperRect().y() + printer.pageRect().height() / 2);
      painter.scale(scale, scale);
      painter.translate(-ui->afficherproduitv->width() / 2, -ui->afficherproduitv->height() / 2);
      painter.drawPixmap(0, 0, pix);

    QTextDocument doc;

    doc.setHtml("Produit table");
    doc.drawContents(&painter);

      painter.end();


}





void MainWindow::on_statsproduitv_clicked()
{
    bool test=true;
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select NOM_PRODUIT,PRIX_UNITAIRE  from PRODUIT_VEGETAL  order by PRIX_UNITAIRE  DESC");
        if(q.exec())
      { //  int c=0;
         //  qDebug()<<"azazazazazaz";
          while (q.next())
          {
              //qDebug()<<"azazazazazaz";
          QString a=q.value(0).toString() ;
          float b= q.value(1).toFloat()  ;
         // if(c==0)
         // {
             // QPieSlice *slice =  series->append(a, b );
             // slice->setExploded();
             // slice->setLabelVisible();
          //}
         // else
         // {
              series->append(a, b );
          //}
      }}}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("donut chart repartition des produits par nombre :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->horizontalFrame );
    ui->stackedWidget_2->setCurrentIndex(7);
}

void MainWindow::on_anulerajouterplante_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_annulerajouterproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_annulersupprimerproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_supprimerproduitv_2_clicked()
{
    QString nom= ui->nomproduitasupprimer->text();
     bool test=tmpproduitv.supprimer(nom);
   if(test)
    {ui->afficherproduitv->setModel(tmpproduitv.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un produit"),
                    QObject::tr("supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un produit"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
       ui->stackedWidget_2->setCurrentIndex(1);
}

