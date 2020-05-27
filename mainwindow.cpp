#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include <QtDebug>
#include "fournisseur.h"
#include "nourriture.h"
#include <QMessageBox>
#include <QString>
#include <QDate>
#include <QDateEdit>
#include <QMediaPlayer>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include<QElapsedTimer>
#include<QDebug>
#include <QSound>
#include <QMediaPlayer>
#include <iostream>
#include <QProgressBar>
#include <QStatusBar>
#include "connexion.h"
#include<QTimer>
#include<QTime>
#include<QDateTime>
#include <QLCDNumber>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include "chartview.h"
#include "avis_fournisseur.h"
#include "tableprinter.h"
#include "tableprinter.cpp"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
//#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
//
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrintDialog>
//#include"qcustomplot.h"
#include<QPdfWriter>
QT_CHARTS_USE_NAMESPACE

// ----------------- example of inharitance from PagePrepare ---------------------

class PrintBorder : public PagePrepare {
public:
    virtual void preparePage(QPainter *painter);
    static int pageNumber;
};

int PrintBorder::pageNumber = 0;

void PrintBorder::preparePage(QPainter *painter) { // print a border on each page
    QRect rec = painter->viewport();
    painter->setPen(QPen(QColor(0, 0, 0), 1));
    painter->drawRect(rec);
    painter->translate(10, painter->viewport().height() - 10);
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
}

// --------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    mute=0;
    client_ = NULL;
    // Connect all signals and slots
    connect(ui->pushButtonSend, SIGNAL(clicked(bool)), this, SLOT(sendEmail()));
    connect(ui->pushButtonClear, SIGNAL(clicked(bool)), this, SLOT(clearFields()));
    connect(ui->pushButtonSend_2 , SIGNAL(clicked(bool)), this, SLOT(sendEmail_2()));
    connect(ui->pushButtonClear_2, SIGNAL(clicked(bool)), this, SLOT(clearFields()));
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon("C:/Users/SBS/Documents/testqt/Ressources/8.png"));
    mSystemTrayIcon->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->tabfournisseur->setModel(tmpfournisseur.afficher());
    ui->tabnourriture->setModel(tmpnourriture.affichern());
    ui->tabavisf->setModel(tmpavisf.afficher());
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);   
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track")
                                                           << tr("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(player);
    player->setPlaylist(m_playlist);
    player->setVolume(100);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);


     ui->progressBar->setVisible(false);

  timereal = new QTimer(this) ;
connect (timereal,SIGNAL(timeout()),this,SLOT(time()));
timereal->start(1000);

    QPixmap px("C:/Users/SBS/Documents/testqt/Ressources/log.jpg");
   // ui->bg->setPixmap(px);


    QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/stop.png");
    px3=px3.scaledToWidth(ui->bttn_muter->width()  );
    ui->bttn_muter->setPixmap(px3);

    if(translatorEn.load("C:/Users/SBS/Documents/testqt/English.qm"))
        qDebug()<<"successfully load translation_En file.";
/*mortadha */
    ui->tabprofil->setModel(tmpprofil.afficher());
    ui->tabouv->setModel(tmpouvrier.afficher());
connect(ui->pushButton_51 , SIGNAL(clicked(bool)), this, SLOT(sendEmail_3()));
connect(ui->pushButton_53, SIGNAL(clicked(bool)), this, SLOT(ui->stackedWidget_2->setCurrentIndex(1);));
    /*mortadha*/
ui->pushButton_nour_four->setStyleSheet("qproperty-iconSize: 90px 90px ;");
ui->pushButton_admin->setStyleSheet("qproperty-iconSize: 90px 90px ;");
ui->pushButton_plante->setStyleSheet("qproperty-iconSize: 90px 90px ;");
ui->pushButton_animal->setStyleSheet("qproperty-iconSize: 90px 90px ;");
ui->pushButton_materiel->setStyleSheet("qproperty-iconSize: 90px 90px ;");

/*yassine */
/**yassine **/
ui->label_ve->hide();
ui->label_vi->hide();
ui->label_vag->hide();
ui->label_vt->hide();
ui->label_vn->hide();
ui->label_vad->hide();
ui->label_vrn->hide();
ui->label_vnn->hide();
ui->label_vin->hide();
/*************/
//connect(ui->textEdit_chat,SIGNAL(timeout()),ui->textEdit_chat,SLOT(chat()));
timerealll = new QTimer(this) ;
connect (timerealll,SIGNAL(timeout()),this,SLOT(chat()));
timerealll->start(1000);
//chatend
ui->stackedWidget_calculatrice->hide();
//yassinev2
ui->label_yassinevm->hide();
ui->label_yassinevmar->hide();
ui->label_yassinevm_2->hide();
ui->label_yassinevmar_2->hide();
ui->label_yassineeref->hide();
ui->label_yassineeref_2->hide();
ui->label_yassineenom->hide();
ui->label_yassineenom_2->hide();
QString sDate = QDateTime::currentDateTime().toString("dddd dd/MM/yyyy");
ui->DateEquipement->setText(sDate);

ui->DateVehicule->setText(sDate);
//
ui->stackedWidget_profile->hide();
}

void MainWindow::changeEvent(QEvent* event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}
MainWindow::~MainWindow()
{   client_->deleteLater();
    delete ui;
}

void MainWindow::on_pushButton_nour_four_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(0);
    ui->stackedWidgetbaha2->setCurrentIndex(0);
    ui->stackedWidgetbaha3->setCurrentIndex(0);
    ui->tabfournisseur->setModel(tmpfournisseur.afficher());
    ui->tabnourriture->setModel(tmpnourriture.affichern());
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select REF_NOURRITURE from NOURRITURE ");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_idf_avis->setModel(modal);
    q.prepare("select ID_FOURNISSEUR from FOURNISSEUR ");
            q.exec();
            modal->setQuery(q);
            ui->colfour->setModel(modal);
      ui->pushButton_nour_four->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
      ui->pushButton_admin->setFlat(1);
      ui->pushButton_plante->setFlat(1);
      ui->pushButton_materiel->setFlat(1);
      ui->pushButton_animal->setFlat(1);
      ui->pushButton_nour_four->setFlat(0);
}

void MainWindow::on_pushButton_admin_clicked()
{ //  dfdfdvhvnfgfdg
    ui->stackedWidgetbaha1->setCurrentIndex(1);
    ui->pushButton_admin->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
    ui->pushButton_nour_four->setFlat(1);
    ui->pushButton_plante->setFlat(1);
    ui->pushButton_materiel->setFlat(1);
    ui->pushButton_animal->setFlat(1);
    ui->pushButton_admin->setFlat(0);

}

void MainWindow::on_pushButton_plante_clicked()
{
   //page 2 stat fi plante...
    ui->stackedWidgetbaha1->setCurrentIndex(2);
    ui->afficherplantes->setModel(tmpplante.afficher());
    ui->afficherproduitv->setModel(tmpproduitv.afficher());
    ui->pushButton_plante->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
    ui->pushButton_nour_four->setFlat(1);
    ui->pushButton_admin->setFlat(1);
    ui->pushButton_materiel->setFlat(1);
    ui->pushButton_animal->setFlat(1);
    ui->pushButton_plante->setFlat(0);
}

void MainWindow::on_pushButton_materiel_clicked()
{
  ui->stackedWidgetbaha1->setCurrentIndex(3);
  ui->tableViewVehilcule->setModel(tmpvehicule.afficher());//refresh
  ui->pushButton_materiel->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
  ui->pushButton_nour_four->setFlat(1);
  ui->pushButton_admin->setFlat(1);
  ui->pushButton_plante->setFlat(1);
  ui->pushButton_animal->setFlat(1);
  ui->pushButton_materiel->setFlat(0);

}

void MainWindow::on_pushButton_animal_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(11);
    ui->tableanim->setModel(tmpanimal.afficher());//refresh
    ui->tableprod->setModel(tmpprod.afficher());
    ui->pushButton_animal->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
    ui->pushButton_nour_four->setFlat(1);
    ui->pushButton_admin->setFlat(1);
    ui->pushButton_plante->setFlat(1);
    ui->pushButton_materiel->setFlat(1);
    ui->pushButton_animal->setFlat(0);
}

void MainWindow::on_pushButton_5_clicked()
{   float i=   timer.elapsed();
    i=i/60000;
    QString nom=QString::number(i); ;
           // qDebug() << "fdsfsdfdsfdsf "<< i;
          //
        mSystemTrayIcon->showMessage(tr("merci , vous avez travaillée pendant (en minutes ) :  "),tr(nom.toUtf8().constData() ) );
          //
        player->stop();
      ui->stackedWidget_2->setCurrentIndex(0);
    //  test=fermerConnexion();

}



void MainWindow::on_pushButton_ajoutern_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur ");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_idf->setModel(modal);
}

void MainWindow::on_pushButton_triendesc_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
      QString val=ui->recherche_n->text();   //text();
    QString valt= ui->type_trie_n->currentText();
    //
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100000);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setFormat("Connecting");
    for( int i = 0; i<=100000; i+=10 ) {
        ui->progressBar->setValue(i);
    }
    //
    if (valt =="select")
    {           ui->progressBar->setFormat("Erreur");
        QMessageBox msBox;
        msBox.setText("Please select type de trie ");
        msBox.exec();
        ui->progressBar->setVisible(false);
    }
    else
    {
        ui->tabnourriture->setModel(tmpnourriture.affichernqd(val,valt));
        ui->progressBar->setVisible(false);
    }
}

void MainWindow::on_pushButton_ajf_clicked()
{
ui->label_vi->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >id  doit etre seulement chiffres ");
ui->label_vad->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' > adresse : 21 rue kharoubba , tunis ");
ui->label_vn->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >nom seulement lettre ");
ui->label_ve->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >emil format : mail@gmail.com");
ui->label_vt->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >numéro de tel de formart exemple : +216 74 145 654 ");
ui->label_vag->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >age supérieur a 18 ");
//
int id = ui->lineEdit_idf->text().toInt();
int idd = ui->lineEdit_idf->text().length();
QString adresse= ui->lineEdit_adressef->text();
int add= ui->lineEdit_adressef->text().length();
QString nom= ui->lineEdit_nomf->text();
QString email= ui->lineEdit_emailf->text();
QString tel = ui->lineEdit_telf->text();
int tell =ui->lineEdit_telf->text().length();
QString sexe= ui->comboBox_sexef->currentText();
int age = ui->spinBox_agef->value();
QString type=ui->comboBox_typef->currentText();
//
int a=0,b=0,c=0,d=0,e=0,g=0;
//
bool test;
//
 if(id < 0 || idd==0)
 { ui->label_vi->show(); a=0;}
 else { ui->label_vi->hide(); a=1;}
 if(ui->lineEdit_adressef->hasAcceptableInput() && add!=0)
 { ui->label_vad->hide(); b=1;}
 else { ui->label_vad->show();b=0;  }
 if(nom=="")
 { ui->label_vn->show(); c=0;}
else { ui->label_vn->hide(); c=1;}

 if(ui->lineEdit_emailf->hasAcceptableInput() && email!="" )
 { ui->label_ve->hide(); d=1;}
 else { ui->label_ve->show(); d=0; }
 if( ui->lineEdit_telf->hasAcceptableInput() && tell!=0 && tell>=12 )
 { ui->label_vt->hide(); e=1;}
 else { ui->label_vt->show();e=0; }
 if(age<18)
 { ui->label_vag->show(); g=0; }
 else {  ui->label_vag->hide(); g=1;}
 fournisseur f(id,adresse,nom,email,tel,sexe,age,type);
int vv=0;
if( a==1 && b==1 && c==1 && d==1 && e==1  && g==1 )
{ 
     QSqlQuery q;
     q.prepare("select ID_FOURNISSEUR from FOURNISSEUR where ID_FOURNISSEUR=:ref ");
     q.bindValue(":ref",ui->lineEdit_idf->text());
     q.exec();
     while(q.next())
     {
      vv=1;
     }
     if(vv==0){
test=f.ajouter();     }
     else
     {
     ui->label_vi->show();
     mSystemTrayIcon->showMessage(tr("id_FOURNISSEUR  "),tr("existe déja") );
     test=false;
     }

}
else { test=false; }
if(test)
{
    //
    QMediaPlayer * player = new QMediaPlayer;//musique
       connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
       player->setMedia(QUrl::fromLocalFile("C:/Users/SBS/Documents/testqt/Ressources/Click.wav"));
       player->setVolume(100);
       player->play();
  //
mSystemTrayIcon->showMessage(tr("founisseur ajouté "),tr(nom.toUtf8().constData()) );
  //
QMessageBox::information(nullptr, QObject::tr("Ajouter un fournisseur"),
              QObject::tr("fournisseur ajouté.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);
    ui->stackedWidget_2->setCurrentIndex(1);
ui->tabfournisseur->setModel(tmpfournisseur.afficher());
}
else
{  QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
              QObject::tr("Erreur !.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);}

//ui->stackedWidget_2->setCurrentIndex(1);
//ui->tabfournisseur->setModel(tmpfournisseur.afficher());
}


void MainWindow::on_pushButton_ajouterf_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
    ui->lineEdit_idf->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >type only numbers");

}

void MainWindow::on_tabfournisseur_activated(const QModelIndex &index)
{
QString val=ui->tabfournisseur->model()->data(index).toString();
QSqlQuery q;
q.prepare("select * from fournisseur where ID_FOURNISSEUR='"+val+"'");
if(q.exec())
{
    while (q.next())
    {
    ui->idfaff->setText(q.value(0).toString());
    ui->adraff->setText(q.value(1).toString());
    ui->nfaff->setText(q.value(2).toString());
    ui->efaff->setText(q.value(3).toString());
    ui->tfaff->setText(q.value(4).toString()) ;
    ui->sfaff->setText(q.value(5).toString());
    ui->afaff->setText(q.value(6).toString()) ;
if("animal"==q.value(7).toString()) { ui->comboBox_typef_2->setCurrentIndex(0); }
else  if("plante"==q.value(7).toString()) { ui->comboBox_typef_2->setCurrentIndex(1); }
else{ ui->comboBox_typef_2->setCurrentIndex(2); }
    }
}
}

void MainWindow::on_fs_clicked()
{QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "fournisseur", "supprimer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      qDebug() << "Yes was clicked";
      int id = ui->idfaff->text().toInt();
      bool test=tmpfournisseur.supprimer(id);
      ui->idfaff->setText("");
      ui->adraff->setText("");
      ui->nfaff->setText("");
      ui->efaff->setText("");
      ui->tfaff->setText("");
      ui->sfaff->setText("");
      ui->afaff->setText("");
      ui->tabfournisseur->setModel(tmpfournisseur.afficher());
    } else {
      qDebug() << "Yes was *not* clicked";
    }


}

void MainWindow::on_fm_clicked()
{
    int id = ui->idfaff->text().toInt();
    QString adresse= ui->adraff->text();
    QString nom= ui->nfaff->text();
    QString email= ui->efaff->text();
    QString tel = ui->tfaff->text();
    QString sexe= ui->sfaff->text();
    int age = ui->afaff->text().toInt();
    QString type=ui->comboBox_typef_2->currentText();
   if(ui->idfaff->text()=="")
   {    QMessageBox::information(this,"Pour Modifier il Faut","Double clique sur id de fournisseur dans le tableau");    }
else{
    fournisseur f(id,adresse,nom,email,tel,sexe,age,type);
    bool test=f.modifier();
   // bool test=tmpfournisseur.supprimer(id);
    ui->idfaff->setText("");
    ui->adraff->setText("");
    ui->nfaff->setText("");
    ui->efaff->setText("");
    ui->tfaff->setText("");
    ui->sfaff->setText("");
    ui->afaff->setText("");
    if(test)
    {
        ui->tabfournisseur->setModel(tmpfournisseur.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("modifier un fournisseur"),
                    QObject::tr("fournisseur modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
}
void MainWindow::on_pushButton_ajn_clicked()
{
ui->label_vrn->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >ce champ est nécessaire ");
ui->label_vnn->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >ce champ est nécessaire ");
ui->label_vin->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >vous devez deposer une image ");
//
    QString r = ui->lineEdit_refn->text();
    int i= ui->comboBox_idf->currentText().toInt(); // bb->text().toInt();
    QString n= ui->lineEdit_nomn->text();
    QDate d= ui->QDateEdit_date_expn->date() ;
    float p = ui->QDoubleSpinBox_prixn->value();
    float q = ui->QDoubleSpinBox_quantiten->value();
    QString img= ui->lineEdit_imagen->text();
    int a=0,b=0,c=0;
    bool test;
   if(ui->lineEdit_imagen->text().length()!=0)
   {a=1; ui->label_vin->hide();}
   else { a=0;ui->label_vin->show(); }
   if(ui->lineEdit_nomn->text().length()!=0)
   {b=1; ui->label_vnn->hide();}
   else { b=0;ui->label_vnn->show(); }
   if(ui->lineEdit_refn->text().length()!=0)
   {c=1;ui->label_vrn->hide(); }
   else { c=0; ui->label_vrn->show();}
   int vv=0;
   nourriture f(r,i,n,d,p,q,img);
   if(a==1 && b==1 && c==1)
   {
       QSqlQuery q;
       q.prepare("select REF_NOURRITURE from NOURRITURE where REF_NOURRITURE=:ref ");
       q.bindValue(":ref",r);
       q.exec();
       while(q.next())
       {
        vv=1;
       }
       if(vv==0){
         test=f.ajoutern();
       }
       else
       {
       ui->label_vrn->show();
       mSystemTrayIcon->showMessage(tr("reference nourriture  "),tr("existe déja") );
       test=false;
       }

   }
   else { test=false; }


   if(test)
    {
        //
        QMediaPlayer * player = new QMediaPlayer;//musique
           connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
           player->setMedia(QUrl::fromLocalFile("C:/Users/SBS/Documents/testqt/Ressources/Click.wav"));
           player->setVolume(100);
           player->play();
      //
           //
         mSystemTrayIcon->showMessage(tr("nourriture ajoutée "),tr(n.toUtf8().constData()) );
           //
    QMessageBox::information(nullptr, QObject::tr("Ajouter une nourriture"),
                  QObject::tr("nourriture ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->tabnourriture->setModel(tmpnourriture.affichern());

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une nourriture"),
                  QObject::tr("Erreur dfdf !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

   // ui->stackedWidget_2->setCurrentIndex(1) ;
  //  ui->tabnourriture->setModel(tmpnourriture.affichern());

}



void MainWindow::on_tabnourriture_activated(const QModelIndex &index)
{

if( index.column() ==0 )
{
    //
    QString val=ui->tabnourriture->model()->data(index).toString();
    QSqlQuery q;
    q.prepare("select * from nourriture where REF_NOURRITURE='"+val+"'");
    if(q.exec())
    {
        while (q.next())
        {
        ui->lineEdit_refn_2->setText(q.value(0).toString());
        ui->lineEdit_idfa->setText(q.value(1).toString());
        ui->lineEdit_nomn_2->setText(q.value(2).toString());
        ui->lineEdit_dateexpa->setText(q.value(3).toString());
        ui->lineEdit_prixn->setText(q.value(4).toString());
        ui->lineEdit_quantiten->setText(q.value(5).toString());

        QPixmap px1(q.value(6).toString());
        px1=px1.scaledToWidth(ui->label_imagen->width()  );
        ui->label_imagen->setPixmap(px1);
        //
        QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID_FOURNISSEUR from fournisseur ");
        q.exec();
        modal->setQuery(q);
        ui->comboBox_idf_2->setModel(modal);
       // ui->tabnourriture->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        }
    }
}
 else   if( index.column() ==1 )
   {
           QString nom,email;
           int numero;
           int idf=ui->tabnourriture->model()->data(index).toInt();
           QSqlQuery qu;
           qu.prepare("select * from FOURNISSEUR where ID_FOURNISSEUR= '"+QString::number(idf)+"' ");
           if(qu.exec())
             while (qu.next()) {
                 nom =qu.value(2).toString();
                 email =qu.value(3).toString();
                 numero =qu.value(4).toInt();
                               }
           QMessageBox::information(this,"Information Sur Fournisseur","ID:"+QString::number(idf)+" Nom: "+nom+" Email: "+email+" Numero: "+QString::number(numero)+"  ");
   }
else   if( index.column() ==6 )
  {
          QString idf=ui->tabnourriture->model()->data(index).toString();
QMessageBox about;
about.setWindowTitle("image nourriture");
QPixmap px=idf;
px=px.scaled(350,250);
about.setIconPixmap(px);
about.show() ;
about.exec();
}
}
void MainWindow::on_nm_clicked()
{
    QString r = ui->lineEdit_refn_2->text();
    int i= ui->comboBox_idf_2->currentText().toInt(); // b->text().toInt();
    QString n= ui->lineEdit_nomn_2->text();
    QDate d  = QDate::fromString(ui->QDateEdit_dateexpn->text(),"dd/MM/yyyy");
    float p = ui->lineEdit_prixn->text().toFloat();
    float q = ui->lineEdit_quantiten->text().toFloat();

if(r=="")
{    QMessageBox::information(this,"Pour Modifier il Faut","Double clique sur la reference de nourriture dans le tableau");
}
else{
    nourriture f(r,i,n,d,p,q,"");
    bool test=f.modifiern();
    //bool test=tmpfournisseur.supprimern(r);
    ui->lineEdit_refn->setText("");
    ui->lineEdit_idfa->setText("");
    ui->lineEdit_nomn->setText("");
    ui->lineEdit_dateexpa->setText("");
    ui->lineEdit_prixn->setText("");
    ui->lineEdit_quantiten->setText("");
    if(test)
    {
        ui->tabnourriture->setModel(tmpnourriture.affichern());//refresh
        QMessageBox::information(nullptr, QObject::tr("modifier un nourriture"),
                    QObject::tr("nourriture modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier un nourriture"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tabnourriture->setModel(tmpnourriture.affichern());//refresh

}
}

void MainWindow::on_ns_clicked()
{  
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "nourriture", "supprimer?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
          qDebug() << "Yes was clicked";
          QString id = ui->lineEdit_refn_2->text();
          bool test=tmpnourriture.supprimern(id);
          ui->lineEdit_refn->setText("");
          ui->lineEdit_idfa->setText("");
          ui->lineEdit_nomn_2->setText("");
          ui->lineEdit_dateexpa->setText("");
          ui->lineEdit_prixn->setText("");
          ui->lineEdit_quantiten->setText("");
          ui->tabnourriture->setModel(tmpnourriture.affichern());//refresh
        } else {
          qDebug() << "Yes was *not* clicked";
        }
}

void MainWindow::on_tabWidget_baha_currentChanged()
{
    ui->tabnourriture->setModel(tmpnourriture.affichern());
}


void MainWindow::on_pushButton_ajn_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->tabnourriture->setModel(tmpnourriture.affichern());

}

void MainWindow::on_pushButton_trienasc_clicked()
{
        ui->stackedWidget_2->setCurrentIndex(1);
          QString val=ui->recherche_n->text();// text();
        QString valt= ui->type_trie_n->currentText();
        //
        ui->progressBar->setVisible(true);
        ui->progressBar->setRange(0, 100000);
        ui->progressBar->setValue(0);
        ui->progressBar->setTextVisible(true);
        ui->progressBar->setFormat("Connecting");
        for( int i = 0; i<=100000; i+=10 ) {
            ui->progressBar->setValue(i);
        }
        //
        if (valt =="select")
        {           ui->progressBar->setFormat("Erreur");
            QMessageBox Box;
            Box.setText("Please select type de trie par ( quantité ou prix ) ");
            Box.exec();
            ui->progressBar->setVisible(false);
        }
        else
        {
            ui->tabnourriture->setModel(tmpnourriture.affichernqa(val,valt));
            ui->progressBar->setVisible(false);
        }
}



void MainWindow::on_rech_n_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
      QString valr=ui->recherche_n->text();  //text();
    QString valt= ui->comboBox_type_rech_n->currentText();
    //
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100000);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setFormat("Connecting");
    for( int i = 0; i<=100000; i+=10 ) {
        ui->progressBar->setValue(i);
    }
    //
    if(valr=="")
    {
    ui->progressBar->setFormat("Erreur");
    QMessageBox Box;
    Box.setText("Please write something in recherche tab (vide) ");
    Box.exec();
    ui->progressBar->setVisible(false);
   ui->tabnourriture->setModel(tmpnourriture.affichern());
    }
    else if (valt =="select")
    {   //
        ui->progressBar->setFormat("Erreur");
        //
        QMessageBox Box;
        Box.setText("Please select type de trie de recherche ");
        Box.exec();
        ui->progressBar->setVisible(false);
    }
    else
    {
        ui->tabnourriture->setModel(tmpnourriture.affichernr(valr,valt));
        ui->progressBar->setVisible(false);

    }

}

void MainWindow::on_lineEdit_emailf_cursorPositionChanged()
{
    QRegExp rx ("^\\w+[\\w-\\.]*\\@\\w+((-\\w+)|(\\w*))\\.[a-z]{2,3}$");
    QRegExpValidator *validemail = new QRegExpValidator(rx,this);
    ui->lineEdit_emailf->setValidator(validemail);
    //^([a-zA-Z0-9_\-\\.]+)@([a-zA-Z0-9_\-\\.]+)\\.([a-zA-Z]{2,5})$
    /*QRegExp rx ("^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
    QRegExpValidator *validemail = new QRegExpValidator(rx,this);
    ui->lineEdit_21->setValidator(validemail);*/
    //
}

void MainWindow::on_lineEdit_telf_cursorPositionChanged()
{
    QRegExp rx ("^\\+[1-9]{1}[0-9]{3,14}$");
    QRegExpValidator *validtel = new QRegExpValidator(rx,this);
    ui->lineEdit_telf->setValidator(validtel);
}

void MainWindow::on_lineEdit_nomf_cursorPositionChanged()
{
    QRegExp rx ("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");
    QRegExpValidator *validnom = new QRegExpValidator(rx,this);
    ui->lineEdit_nomf->setValidator(validnom);
}

void MainWindow::on_lineEdit_adressef_cursorPositionChanged()
{
    QRegExp rx ("^[A-Za-z0-9 _]*[A-Za-z0-9][A-Za-z0-9 _]*$");
    QRegExpValidator *validadresse = new QRegExpValidator(rx,this);
    ui->lineEdit_adressef->setValidator(validadresse);
}

void MainWindow::on_lineEdit_idf_cursorPositionChanged()
{
    QRegExp rx ("^[0-9]*$");
    QRegExpValidator *validid = new QRegExpValidator(rx,this);
    ui->lineEdit_idf->setValidator(validid);
}

void MainWindow::on_lineEdit_nomn_cursorPositionChanged()
{
    QRegExp rx ("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");
    QRegExpValidator *validnom_nour = new QRegExpValidator(rx,this);
    ui->lineEdit_nomn->setValidator(validnom_nour);
}

void MainWindow::on_pushButton_mailn_clicked()
{
ui->stackedWidgetbaha2->setCurrentIndex(1);
}



void MainWindow::on_sliderp_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::on_position_Changed(int position)
{
    ui->sliderp->setValue(position);

}

void MainWindow::on_duration_Changed(int position)
{
    ui->sliderp->setMaximum(position);

}

void MainWindow::on_sliderv_sliderMoved(int position)
{
    player->setVolume(position);
    qDebug() << player->volume();
}
void MainWindow::on_actionCheck_database_triggered()
{
    connexion c;
     bool test=c.ouvrirConnexion();
     if(test){ mSystemTrayIcon->showMessage(tr("database is  open "),tr("connection avec succés") ); }
     else {  mSystemTrayIcon->showMessage(tr("database is not  open "),tr("connection failed ") );     }
}

void MainWindow::time()
{
QTime time = QTime::currentTime();
QString time_text = time.toString("hh : mm : ss");
if((time.second() % 2) == 0 )
{
    time_text[3] = ' ';
    time_text[8] = ' ';
}
ui->time->setText(time_text);
ui->time_2->setText(time_text);
}


void MainWindow::on_pushButton_statn_clicked()
{    // ui->stackedWidget->setCurrentIndex(5) ;
    //
    //connexion c;
    //bool test=c.ouvrirConnexion();
    //page loula stat wow timchy allah allah
    //
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select NOM_NOURRITURE,QUANTITÉ  from nourriture  order by QUANTITÉ  DESC ");
        if(q.exec())
      {   int c=0;
          while (q.next())
          {
          QString a=q.value(0).toString() ;
          float b= q.value(1).toFloat()  ;
          if(c==0)
          {
              QPieSlice *slice =  series->append(a, b );
              slice->setExploded();
              slice->setLabelVisible(); }
          else
          { series->append(a, b ); }
      }}}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("donut chart repartition des nourriture par QUANTITÉ :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->horizontalFrame   );
    //
    if(test)
      {
        QSqlQuery q;
        q.prepare("select f.NOM_FOURNISSEUR  from nourriture n  join FOURNISSEUR f on n.ID_FOURNISSEUR=f.ID_FOURNISSEUR   where n.QUANTITÉ=(select MAX(QUANTITÉ) from nourriture )  ");
        if(q.exec())
      {
          while (q.next())
          {
          QString a=q.value(0).toString() ;
    ui->maxqq->setText(a);
      }}}
    if(test)
      {
        QSqlQuery q;
        q.prepare("select f.NOM_FOURNISSEUR  from nourriture n  join FOURNISSEUR f on n.ID_FOURNISSEUR=f.ID_FOURNISSEUR   where n.PRIX=(select MAX(PRIX) from nourriture )  ");
        if(q.exec())
      {
          while (q.next())
          {
          QString a=q.value(0).toString() ;
    ui->maxpp->setText(a);
      }}}
    //
    //page 2 stat fi plante...
   // ui->stackedWidget->setCurrentIndex(4);
    //
    //![1]
        QBarSet *set0 = new QBarSet("prix"); // prix
        QBarSet *set1 = new QBarSet("quantité"); // quantité
        //
        if(test)
          {
            QSqlQuery q;
            q.prepare("select PRIX from nourriture order by REF_NOURRITURE desc ");
            if(q.exec())
          {
              while (q.next())
              {
              int a=q.value(0).toFloat();
                *set0 << a ;
              }
          }
        }
        //
        //
        if(test)
          {
            QSqlQuery q;
            q.prepare("select QUANTITÉ from nourriture order by REF_NOURRITURE desc ");
            if(q.exec())
          {
              while (q.next())
              {
              float a=q.value(0).toFloat();
                *set1 << a ;
              }
          }
        }
        //

    //![1]

    //![2]
        QHorizontalBarSeries *seriess = new QHorizontalBarSeries();
        seriess->append(set0);
        seriess->append(set1);
    //![2]

    //![3]
        QChart *chartt = new QChart();
        chartt->addSeries(seriess);
        chartt->setTitle("Simple horizontal barchart quantité(green)/prix(blue) selon  nom nourriture");
        chartt->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
        QStringList categories;
        //
        if(test)
          {
            QSqlQuery q;
            q.prepare("select NOM_NOURRITURE from nourriture order by REF_NOURRITURE desc ");
            if(q.exec())
          {
              while (q.next())
              {
              QString a=q.value(0).toString() ;
               categories << a ;
              }
          }
        }
        //
        QBarCategoryAxis *axisY = new QBarCategoryAxis();
        axisY->append(categories);
        chartt->addAxis(axisY, Qt::AlignLeft);
        seriess->attachAxis(axisY);
        QValueAxis *axisX = new QValueAxis();
        chartt->addAxis(axisX, Qt::AlignBottom);
        seriess->attachAxis(axisX);
        axisX->applyNiceNumbers();
    //![4]

    //![5]
        chartt->legend()->setVisible(true);
        chartt->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
        QChartView *chartView = new QChartView(chartt);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setParent(ui->frame12  );
    //![6]
    //page3
        //![1]
            QLineSeries *seriessss = new QLineSeries();
        //![1]
            // Customize series
            QPen pen(QRgb(0xfdb157));
            pen.setWidth(5);
            seriessss->setPen(pen);
        //![2]
            if(test)
              {
                QSqlQuery q;
                q.prepare("select REF_NOURRITURE,PRIX  from nourriture order by REF_NOURRITURE desc ");
                if(q.exec())
              {
                  while (q.next())
                  {
                  float a=q.value(0).toFloat() ;
                  float b= q.value(1).toFloat()  ;
                  seriessss->append(a,b);
                  //*seriessss <<   QPointF(a, b) ;
              }}}
        //
            //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
        //![2]

        //![3]
            QChart *charttttt = new QChart();
            charttttt->legend()->hide();
            charttttt->addSeries(seriessss);
            charttttt->createDefaultAxes();
            // charttttt->setTitle("ref en fonction de  prix ");

        //![3]

            //![2]
                // Customize series
                QPen penn(QRgb(0xfdb157));
                penn.setWidth(5);
                seriessss->setPen(penn);

                // Customize chart title
                QFont font;
                font.setPixelSize(18);
                charttttt->setTitleFont(font);
                charttttt->setTitleBrush(QBrush(Qt::white));
                charttttt->setTitle("chart reference en fonction de prix");

                // Customize chart background
                QLinearGradient backgroundGradient;
                backgroundGradient.setStart(QPointF(0, 0));
                backgroundGradient.setFinalStop(QPointF(0, 1));
                backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
                backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
                backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                charttttt->setBackgroundBrush(backgroundGradient);

                // Customize plot area background
                QLinearGradient plotAreaGradient;
                plotAreaGradient.setStart(QPointF(0, 1));
                plotAreaGradient.setFinalStop(QPointF(1, 0));
                plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
                plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
                plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                charttttt->setPlotAreaBackgroundBrush(plotAreaGradient);
                charttttt->setPlotAreaBackgroundVisible(true);
            //![2]

            //![3]
                QCategoryAxis *axisXx = new QCategoryAxis();
                QCategoryAxis *axisYy= new QCategoryAxis();

                // Customize axis label font
                QFont labelsFont;
                labelsFont.setPixelSize(12);
                axisXx->setLabelsFont(labelsFont);
                axisYy->setLabelsFont(labelsFont);

                // Customize axis colors
                QPen axisPen(QRgb(0xd18952));
                axisPen.setWidth(2);
                axisXx->setLinePen(axisPen);
                axisYy->setLinePen(axisPen);

                // Customize axis label colors
                QBrush axisBrush(Qt::white);
                axisXx->setLabelsBrush(axisBrush);
                axisYy->setLabelsBrush(axisBrush);

                // Customize grid lines and shades
                axisXx->setGridLineVisible(false);
                axisYy->setGridLineVisible(false);
                axisYy->setShadesPen(Qt::NoPen);
                axisYy->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
                axisYy->setShadesVisible(true);
            //![3]

            //![4]
                //axisXx->append("Ref", 10);
                //axisXx->append("Ref", 20);

                axisXx->append("Ref", 100);
                axisXx->setRange(0, 100);

                axisYy->append("low Price", 25);
                axisYy->append("med Price", 50);
                axisYy->append("high Price", 100);
                axisYy->setRange(0, 100);

                charttttt->addAxis(axisXx, Qt::AlignBottom);
                charttttt->addAxis(axisYy, Qt::AlignLeft);
                seriessss->attachAxis(axisXx);
                seriessss->attachAxis(axisYy);
            //![4]

        //![4]
            QChartView *charttttView = new QChartView(charttttt);
            charttttView->setRenderHint(QPainter::Antialiasing);
            charttttView->setParent(ui->frame13   );

        //![4]

    //page4 stat
   //         ChartView *chartvView = new ChartView();
     //       chartvView->setParent(ui->frame14);
    //


ui->stackedWidgetbaha1->setCurrentIndex(5) ;
}

void MainWindow::on_pushButton_6_clicked()
{    ui->stackedWidgetbaha1->setCurrentIndex(0);
     ui->tabfournisseur->setModel(tmpfournisseur.afficher());
     ui->tabnourriture->setModel(tmpnourriture.affichern());
    //ui->stackedWidget->setCurrentIndex(1);
    //->tabWidget_baha->setCurrentIndex(0);
}
void MainWindow::on_action_settings_triggered()
{
ui->stackedWidgetbaha1->setCurrentIndex(6);

connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_position_Changed);
connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_duration_Changed);

connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
connect(ui->btn_play, &QToolButton::clicked, player, &QMediaPlayer::play);
connect(ui->btn_pause, &QToolButton::clicked, player, &QMediaPlayer::pause);
connect(ui->btn_stop, &QToolButton::clicked, player, &QMediaPlayer::stop);

connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
    m_playlist->setCurrentIndex(index.row());
});

connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
    ui->label_currentmusic->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
});

}

void MainWindow::on_btn_add_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.wav)"));
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
}


void MainWindow::on_comboBox_bgapp_currentIndexChanged(const QString &arg1)
{
    QPixmap px1("C:/Users/SBS/Documents/testqt/Ressources/log.jpg");
    QPixmap px2("C:/Users/SBS/Documents/testqt/Ressources/log2.jpg");
    QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/log3.jpg");
    px1=px1.scaledToWidth(ui->label_bgapp->width()  );
    px2=px2.scaledToWidth(ui->label_bgapp->width()  );
    px3=px3.scaledToWidth(ui->label_bgapp->width()  );
    px1=px1.scaledToHeight(ui->label_bgapp->height()  );
    px2=px2.scaledToHeight(ui->label_bgapp->height()  );
    px3=px3.scaledToHeight(ui->label_bgapp->height()  );
    //
    qDebug() << arg1 << px1 << px2 << px3 ;
    //
    int w = ui->label_bgapp->width();
    int h=ui->label_bgapp->height();
    if(arg1 == "log1" )
    { ui->label_bgapp->setPixmap(px1.scaled(w,h,Qt::KeepAspectRatio));   }
    else if (arg1 == "log2")
    { ui->label_bgapp->setPixmap(px2.scaled(w,h,Qt::KeepAspectRatio));   }
    else if (arg1 == "log3")
    {   ui->label_bgapp->setPixmap(px3.scaled(w,h,Qt::KeepAspectRatio)); }
}

void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    QPixmap px1("C:/Users/SBS/Documents/testqt/Ressources/log.jpg");
    QPixmap px2("C:/Users/SBS/Documents/testqt/Ressources/log2.jpg");
    QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/log3.jpg");
    //
    qDebug() << arg1 << px1 << px2 << px3 ;
    //
    if(arg1 == "log1" )
    { ui->bg->setPixmap(px1);   }
    else if (arg1 == "log2")
    { ui->bg->setPixmap(px2);   }
    else if (arg1 == "log3")
    {   ui->bg->setPixmap(px3); }
}

void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    ui->tabnourriture->setModel(tmpnourriture.affichernr(arg1,"avancée"));
    ui->progressBar->setVisible(false);
}
void MainWindow::on_returnmn_clicked()
{
    ui->stackedWidgetbaha2->setCurrentIndex(0);
}
/**
 * @brief Slot used to send the message.
 */
void MainWindow::sendEmail()
{
    // Create the email object
    Email email = createEmail();

    // Create the SMTPClient
    client_ = new SMTPClient("smtp.gmail.com",465);


    // Connection used to receive the results
    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Try to send the email
    client_->sendEmail(email);
}

/**
 * @brief Create and return an Email object based on the fields from the form.
 */
Email MainWindow::createEmail()
{
    // Create the credentials EmailAddress
    EmailAddress credentials(mail,mdp);

    // Create the from EmailAddress
    EmailAddress from(mail);

    // Create the to EmailAddress
    EmailAddress to(ui->lineEditEmailTo->text());

    // Create the email
    Email email(credentials,
                from,
                to,
                ui->lineEditSubject->text(),
                ui->textEditContent->toPlainText());

    return email;
}
void MainWindow::sendEmail_2()
{
    // Create the email object
    Email email = createEmail_2();

    // Create the SMTPClient
    client_ = new SMTPClient("smtp.gmail.com",465);

    // Connection used to receive the results
    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Try to send the email
    client_->sendEmail(email);
}
Email MainWindow::createEmail_2()
{
    // Create the credentials EmailAddress
    EmailAddress credentials(mail,mdp);

    // Create the from EmailAddress
    EmailAddress from(mail);

    // Create the to EmailAddress
    EmailAddress to(ui->lineEditEmailTo_2->text());

    // Create the email
    Email email(credentials,
                from,
                to,
                ui->lineEditSubject_2->text(),
                ui->textEditContent_2->toPlainText());

    return email;
}
void MainWindow::sendEmail_3()
{
    // Create the email object
    Email email = createEmail_3();

    // Create the SMTPClient
    client_ = new SMTPClient("smtp.gmail.com",465);

    // Connection used to receive the results
    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Try to send the email
    client_->sendEmail(email);
}
Email MainWindow::createEmail_3()
{
    // Create the credentials EmailAddress
    EmailAddress credentials(mail,mdp);

    // Create the from EmailAddress
    EmailAddress from(mail);

    // Create the to EmailAddress
    EmailAddress to( ui->rcpt->text());

    // Create the email
    Email email(credentials,
                from,
                to,
                ui->subject->text(),
                ui->msg->toPlainText());

    return email;
}
/**
 * @brief Function responsible for clear all fields.
 * Note: it will not change the Host and Port fields.
 */
void MainWindow::clearFields()
{
   // ui->lineEditEmailCredentials->clear();
   // ui->lineEditPasswordCredentials->clear();
   // ui->lineEditEmailFrom->clear();
    ui->lineEditEmailTo->clear();
    ui->lineEditSubject->clear();
    ui->textEditContent->clear();
    ui->lineEditEmailTo_2->clear();
    ui->lineEditSubject_2->clear();
    ui->textEditContent_2->clear();
}

/**
 * @brief Slot the receives a result from the SMTPClient object.
 * @param status - The status (Success or Failed)
 * @param errorMessage - The error message if the status is Failed
 */
void MainWindow::onStatus(Status::e status, QString errorMessage)
{
    // Show a message based on the Status
    switch (status)
    {
    case Status::Success:
        QMessageBox::information(NULL, tr("SMTPClient"), tr("Message successfully sent!"));
        break;
    case Status::Failed:
    {
        QMessageBox::warning(NULL, tr("SMTPClient"), tr("Could not send the message!"));
        qCritical() << errorMessage;
    }
        break;
    default:
        break;
    }

    // Delete the client pointer
    client_->deleteLater();
}


void MainWindow::on_btn_add_2_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Photo Files (*.jpg)"));
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
      //  m_playListModel->appendRow(items);
      //  m_playlist->addMedia(QUrl(filePath));
        QPixmap px1(filePath);
        px1=px1.scaledToWidth(ui->label_bgapp->width()  );
        ui->label_bgapp->setPixmap(px1);
        ui->comboBox_bgapp->addItem(QIcon(filePath),QDir(filePath).dirName());
        /*
    QPixmap px1("C:/Users/SBS/Documents/testqt/Ressources/log.jpg");
    QPixmap px2("C:/Users/SBS/Documents/testqt/Ressources/log2.jpg");
    QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/log3.jpg");
    //
    qDebug() << arg1 << px1 << px2 << px3 ;
    //
    if(arg1 == "log1" )
    { ui->label_7->setPixmap(px1);   }
    else if (arg1 == "log2")
    { ui->label_7->setPixmap(px2);   }
    else if (arg1 == "log3")
    {   ui->label_7->setPixmap(px3); }
 * */

    }
}

void MainWindow::on_pushButton_mailf_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(1);
}

void MainWindow::on_pushButton_statf_clicked()
{
    // ui->stackedWidget->setCurrentIndex(5) ;
      //
      //connexion c;
      //bool test=c.ouvrirConnexion();
      //page loula stat wow timchy allah allah
      //
    QPieSeries *aseries = new QPieSeries();
      aseries->setHoleSize(0.35);
      if(test)
        {
          QSqlQuery q;
          q.prepare("SELECT COUNT(*) FROM FOURNISSEUR WHERE SEXE_FOURNISSEUR='homme'");
          if(q.exec())
        {
            while (q.next())
            {
            //QString a=q.value(0).toString() ;
            int b= q.value(0).toInt()  ;
                QPieSlice *aslice =  aseries->append("homme", b );
                qDebug() << "h= " << b ;
                aslice->setExploded();
                aslice->setLabelVisible();

        }}}
            if(test)
              {
                QSqlQuery q;
                q.prepare("SELECT COUNT(*) FROM FOURNISSEUR WHERE SEXE_FOURNISSEUR='femme'");
                if(q.exec())
              {
                  while (q.next())
                  {
                  //QString a=q.value(0).toString() ;
                  int b= q.value(0).toInt()  ;
                      QPieSlice *aslice =  aseries->append("femme", b );
                      qDebug() << "f= " << b ;
                      aslice->setExploded();
                      aslice->setLabelVisible();

              }}}
      QChart *achart = new QChart();
      achart->addSeries(aseries);
      achart->setAnimationOptions(QChart::SeriesAnimations);
      achart->setTitle("donut chart repartition des fournisseur par sexe :");
      achart->setTheme(QChart::ChartThemeDark );
      QChartView *achartview = new QChartView(achart);
      achartview->setRenderHint(QPainter::Antialiasing);
      achart->legend()->setAlignment(Qt::AlignRight);
      achartview->setParent(ui->horizontalFrame_2   );
      //
      //page 2 stat fi plante...
     // ui->stackedWidget->setCurrentIndex(4);
      //
      //![1]
          QBarSet *aset0 = new QBarSet("age"); // prix
          //
          if(test)
            {
              QSqlQuery q;
              q.prepare("select AGE_FOURNISSEUR from FOURNISSEUR order by ID_FOURNISSEUR desc ");
              if(q.exec())
            {
                while (q.next())
                {
                int a=q.value(0).toInt();
                  *aset0 << a ;
                }
            }
          }
          //
          //

          //

      //![1]

      //![2]
          QHorizontalBarSeries *aseriess = new QHorizontalBarSeries();
          aseriess->append(aset0);
      //![2]

      //![3]
          QChart *achartt = new QChart();
          achartt->addSeries(aseriess);
          achartt->setTitle("Simple horizontal barchart age selon  nom fournisseur");
          achartt->setAnimationOptions(QChart::SeriesAnimations);
      //![3]

      //![4]
          QStringList acategories;
          //
          if(test)
            {
              QSqlQuery q;
              q.prepare("select NOM_FOURNISSEUR from FOURNISSEUR order by ID_FOURNISSEUR desc ");
              if(q.exec())
            {
                while (q.next())
                {
                QString a=q.value(0).toString() ;
                 acategories << a ;
                }
            }
          }
          //
          QBarCategoryAxis *aaxisY = new QBarCategoryAxis();
          aaxisY->append(acategories);
          achartt->addAxis(aaxisY, Qt::AlignLeft);
          aseriess->attachAxis(aaxisY);
          QValueAxis *aaxisX = new QValueAxis();
          achartt->addAxis(aaxisX, Qt::AlignBottom);
          aseriess->attachAxis(aaxisX);
          aaxisX->applyNiceNumbers();
      //![4]

      //![5]
          achartt->legend()->setVisible(true);
          achartt->legend()->setAlignment(Qt::AlignBottom);
      //![5]

      //![6]
          QChartView *achartView = new QChartView(achartt);
          achartView->setRenderHint(QPainter::Antialiasing);
          achartView->setParent(ui->frame12_4  );
      //![6]
      //
      //
          //page3
              //![1]
                  QLineSeries *aseriessss = new QLineSeries();
              //![1]
                  // Customize series
                  QPen pen(QRgb(0xfdb157));
                  pen.setWidth(5);
                  aseriessss->setPen(pen);
              //![2]
                  if(test)
                    {
                      QSqlQuery q;
                      q.prepare("select ID_FOURNISSEUR,AGE_FOURNISSEUR  from FOURNISSEUR order by ID_FOURNISSEUR asc ");
                      if(q.exec())
                    {
                        while (q.next())
                        {
                        int a=q.value(0).toInt() ;
                        int b= q.value(1).toInt()  ;
                        aseriessss->append(a,b);
                        //*seriessss <<   QPointF(a, b) ;
                    }}}
              //
                  //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
              //![2]

              //![3]
                  QChart *acharttttt = new QChart();
                  acharttttt->legend()->hide();
                  acharttttt->addSeries(aseriessss);
                  acharttttt->createDefaultAxes();
                  // charttttt->setTitle("id  en fonction de  age ");

              //![3]

                  //![2]
                      // Customize series
                      QPen penn(QRgb(0xfdb157));
                      penn.setWidth(5);
                      aseriessss->setPen(penn);

                      // Customize chart title
                      QFont font;
                      font.setPixelSize(18);
                      acharttttt->setTitleFont(font);
                      acharttttt->setTitleBrush(QBrush(Qt::white));
                      acharttttt->setTitle("chart id en fonction de age");

                      // Customize chart background
                      QLinearGradient backgroundGradient;
                      backgroundGradient.setStart(QPointF(0, 0));
                      backgroundGradient.setFinalStop(QPointF(0, 1));
                      backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
                      backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
                      backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                      acharttttt->setBackgroundBrush(backgroundGradient);

                      // Customize plot area background
                      QLinearGradient plotAreaGradient;
                      plotAreaGradient.setStart(QPointF(0, 1));
                      plotAreaGradient.setFinalStop(QPointF(1, 0));
                      plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
                      plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
                      plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                      acharttttt->setPlotAreaBackgroundBrush(plotAreaGradient);
                      acharttttt->setPlotAreaBackgroundVisible(true);
                  //![2]

                  //![3]
                      QCategoryAxis *axisXx = new QCategoryAxis();
                      QCategoryAxis *axisYy= new QCategoryAxis();

                      // Customize axis label font
                      QFont labelsFont;
                      labelsFont.setPixelSize(12);
                      axisXx->setLabelsFont(labelsFont);
                      axisYy->setLabelsFont(labelsFont);

                      // Customize axis colors
                      QPen axisPen(QRgb(0xd18952));
                      axisPen.setWidth(2);
                      axisXx->setLinePen(axisPen);
                      axisYy->setLinePen(axisPen);

                      // Customize axis label colors
                      QBrush axisBrush(Qt::white);
                      axisXx->setLabelsBrush(axisBrush);
                      axisYy->setLabelsBrush(axisBrush);

                      // Customize grid lines and shades
                      axisXx->setGridLineVisible(false);
                      axisYy->setGridLineVisible(false);
                      axisYy->setShadesPen(Qt::NoPen);
                      axisYy->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
                      axisYy->setShadesVisible(true);
                  //![3]

                  //![4]
                      //axisXx->append("Ref", 10);
                      //axisXx->append("Ref", 20);

                      axisXx->append("ID", 200);
                      axisXx->setRange(0, 200);

                      axisYy->append("low age", 25);
                      axisYy->append("med age", 50);
                      axisYy->append("high age", 100);
                      axisYy->setRange(0, 100);

                      acharttttt->addAxis(axisXx, Qt::AlignBottom);
                      acharttttt->addAxis(axisYy, Qt::AlignLeft);
                      aseriessss->attachAxis(axisXx);
                      aseriessss->attachAxis(axisYy);
                  //![4]

              //![4]
                  QChartView *acharttttView = new QChartView(acharttttt);
                  acharttttView->setRenderHint(QPainter::Antialiasing);
                  acharttttView->setParent(ui->frame13_2   );

              //![4]

      //
    //page4 stat
//     ChartView2 *achartvView = new ChartView2();
  //  achartvView->setParent(ui->frame14_2);
      //
      //
ui->stackedWidgetbaha1->setCurrentIndex(4);
      //
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(0);
}

void MainWindow::on_returnmn_2_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(0);
}


void MainWindow::on_pushButton_rechf_clicked()
{
    //ui->stackedWidget_2->setCurrentIndex(1);
      QString valr=ui->recherche_f->text();  //text();
    QString valt= ui->type_rech_f->currentText();
    //
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100000);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setFormat("Connecting");
    for( int i = 0; i<=100000; i+=10 ) {
        ui->progressBar->setValue(i);
    }
    //
    if(valr=="")
    {
    ui->progressBar->setFormat("Erreur");
    QMessageBox Box;
    Box.setText("Please write something in recherche tab (vide) ");
    Box.exec();
    ui->progressBar->setVisible(false);
    }
    else if (valt =="select")
    {   //
        ui->progressBar->setFormat("Erreur");
        //
        QMessageBox Box;
        Box.setText("Please select type de trie de recherche ");
        Box.exec();
        ui->progressBar->setVisible(false);
    }
    else
    {
        ui->tabfournisseur->setModel(tmpfournisseur.afficherfr(valr,valt));
        ui->progressBar->setVisible(false);

    }

}

void MainWindow::on_pushButton_triefdesc_clicked()
{
   // ui->stackedWidget_2->setCurrentIndex(1);
      QString val=ui->recherche_f->text();   //text();
    QString valt= ui->type_trie_f->currentText();
    //
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100000);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setFormat("Connecting");
    for( int i = 0; i<=100000; i+=10 ) {
        ui->progressBar->setValue(i);
    }
    //
    if (valt =="select")
    {           ui->progressBar->setFormat("Erreur");
        QMessageBox msBox;
        msBox.setText("Please select type de trie ");
        msBox.exec();
        ui->progressBar->setVisible(false);
    }
    else
    {
        ui->tabfournisseur->setModel(tmpfournisseur.affichernfd(val,valt));
        ui->progressBar->setVisible(false);
    }
}

void MainWindow::on_pushButton_triefasc_clicked()
{
   // ui->stackedWidget_2->setCurrentIndex(1);
      QString val=ui->recherche_f->text();// text();
    QString valt= ui->type_trie_f->currentText();
    //
    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 100000);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setFormat("Connecting");
    for( int i = 0; i<=100000; i+=10 ) {
        ui->progressBar->setValue(i);
    }
    //
    if (valt =="select")
    {           ui->progressBar->setFormat("Erreur");
        QMessageBox Box;
        Box.setText("Please select type de trie par ( quantité ou prix ) ");
        Box.exec();
        ui->progressBar->setVisible(false);
    }
    else
    {
        ui->tabfournisseur->setModel(tmpfournisseur.affichernfa(val,valt));
        ui->progressBar->setVisible(false);
    }
}

void MainWindow::on_pushButton_ajf_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_recherche_f_textChanged(const QString &arg1)
{
    ui->tabfournisseur->setModel(tmpfournisseur.afficherfr(arg1,"avancée"));
    ui->progressBar->setVisible(false);
}

void MainWindow::on_boutton_avis_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(2);
    ui->tabavisf->setModel(tmpavisf.afficher());

}

void MainWindow::on_returnmn_3_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_ajn_4_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(2);
}


void MainWindow::on_pushButton_ajout_avis_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(3);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur ");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_idf_avis->setModel(modal);
}


void MainWindow::on_pushButton_rfa_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(2);
}

void MainWindow::on_pushButton_ajaf_clicked()
{
    int ida = ui->ida->text().toInt() ;
    int idf= ui->comboBox_idf_avis->currentText().toInt(); // bb->text().toInt();
    int note=ui->na->value();

    avis_fournisseur a(ida,idf,note);
    bool test=a.ajouter();
    if(test)
    {
        //
        QMediaPlayer * player = new QMediaPlayer;//musique
           connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
           player->setMedia(QUrl::fromLocalFile("C:/Users/SBS/Documents/testqt/Ressources/Click.wav"));
           player->setVolume(100);
           player->play();
      //
           //
         //mSystemTrayIcon->showMessage(tr("nourriture ajoutée "),tr(n.toUtf8().constData()) );
           //
    QMessageBox::information(nullptr, QObject::tr("Ajouter un avis"),
                  QObject::tr("avis ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
        ui->stackedWidgetbaha3->setCurrentIndex(2);
        ui->tabavisf->setModel(tmpavisf.afficher());

    }
    else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un avis"),
                  QObject::tr("Erreur dfdf !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

    ui->stackedWidgetbaha3->setCurrentIndex(2) ;
    ui->tabavisf->setModel(tmpavisf.afficher());
}

void MainWindow::on_tabavisf_activated(const QModelIndex &index)
{
    QString val=ui->tabavisf->model()->data(index).toString();
    QSqlQuery q;
    q.prepare("select * from AVIS where ID_AVIS='"+val+"'");
    if(q.exec())
    {
        while (q.next())
        {
        ui->idaaff->setText(q.value(0).toString());
        ui->idfaaff->setText(q.value(1).toString());
        ui->naaff->setText(q.value(2).toString());;
        }
    }
}

void MainWindow::on_am_clicked()
{
    int ida = ui->idaaff->text().toInt();
    int idf = ui->idfaaff->text().toInt();
    int note = ui->noteam->value() ;

    avis_fournisseur a(ida,idf,note);
    bool test=a.modifier();
   // bool test=tmpfournisseur.supprimer(id);
    ui->idaaff->setText("");
    ui->idfaaff->setText("");
    ui->naaff->setText("");
    if(test)
    {
        ui->tabavisf->setModel(tmpavisf.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("modifier un avis"),
                    QObject::tr("avis modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier un avis"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_as_clicked()
{
    int id = ui->idaaff->text().toInt();
    bool test=tmpavisf.supprimer(id);
    ui->idaaff->setText("");
    ui->idfaaff->setText("");
    ui->naaff->setText("");

    if(test)
    {
        ui->tabavisf->setModel(tmpavisf.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un avis"),
                    QObject::tr("avis supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un avis"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_btn_add_3_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Photo Files (*.jpg)"));
    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
      //  m_playListModel->appendRow(items);
      //  m_playlist->addMedia(QUrl(filePath));
        QPixmap px1(filePath);
       px1=px1.scaledToWidth(ui->image_nour->width()  );
        ui->image_nour->setPixmap(px1);
        ui->lineEdit_imagen->setText(filePath);
    }
}


void MainWindow::print(QPrinter *printer) {

    // ------------------ simplest example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 5 << 5 << 10 << 15 << 20 << 25 << 30 ;
    ui->tabnourriture->setModel(tmpnourriture.affichern());
    qDebug() << "tab nourr" <<ui->tabnourriture->model() ;
    if(!tablePrinter.printTable(ui->tabnourriture->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}
void MainWindow::print2(QPrinter *printer) {

    // ------------------ simplest example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 5 << 5 << 10 << 15 << 20 << 25 << 30 ;
    ui->tabnourriture->setModel(tmpnourriture.affichern());
    qDebug() << "tab four" <<ui->tabfournisseur->model() ;
    if(!tablePrinter.printTable(ui->tabfournisseur->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}

void MainWindow::on_print_nour_clicked()
{
    QPrintPreviewDialog dialog;
    qDebug() << "mchet print nour ";
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_print_four_clicked()
{
    QPrintPreviewDialog dialog;
    qDebug() << "mchet print four";
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print2(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_cutf_clicked()
{
    ui->textEdit->cut();
}

void MainWindow::on_pastf_clicked()
{
    ui->textEdit->paste();
}

void MainWindow::on_copyf_clicked()
{
    ui->textEdit->copy();
}

void MainWindow::on_gobf_clicked()
{
    ui->textEdit->undo();
}

void MainWindow::on_goff_clicked()
{
    ui->textEdit->redo();
}

void MainWindow::on_newf_clicked()
{
    file_path_ = "";
    ui->textEdit->setText("");
}

void MainWindow::on_openf_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_savef_clicked()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_saveasf_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_printt_clicked()
{
    QPrinter printer;
     printer.setPrinterName("desired printer name");
     QPrintDialog dialog(&printer,this);
     if(dialog.exec() == QDialog::Rejected) return;
     ui->textEdit->print(&printer);
}

void MainWindow::on_returnmn_4_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(0);
}

void MainWindow::on_boutton_note_clicked()
{
    ui->stackedWidgetbaha3->setCurrentIndex(4);
}

void MainWindow::on_fontt_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit->setFont(font);
      } else return;
}

void MainWindow::on_colort_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()) {
        ui->textEdit->setTextColor(color);
      }
}

void MainWindow::on_bgcolort_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()) {
        ui->textEdit->setTextBackgroundColor(color);
      }
}

void MainWindow::on_bgct_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()) {
        ui->textEdit->setPalette(QPalette(color));
      }
}

void MainWindow::on_boutton_note_2_clicked()
{
    ui->stackedWidgetbaha2->setCurrentIndex(2);
}

void MainWindow::on_returnmn_5_clicked()
{
    ui->stackedWidgetbaha2->setCurrentIndex(0);
}

void MainWindow::on_newf_2_clicked()
{
    file_path_ = "";
    ui->textEdit_2->setText("");
}

void MainWindow::on_openf_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit_2->setText(text);
    file.close();
}

void MainWindow::on_savef_2_clicked()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream out(&file);
    QString text = ui->textEdit_2->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_saveasf_2_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream out(&file);
    QString text = ui->textEdit_2->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_cutf_2_clicked()
{
    ui->textEdit_2->cut();
}

void MainWindow::on_copyf_2_clicked()
{
ui->textEdit_2->copy();
}

void MainWindow::on_pastf_2_clicked()
{
    ui->textEdit_2->paste();

}

void MainWindow::on_gobf_2_clicked()
{
    ui->textEdit_2->undo();
}

void MainWindow::on_goff_2_clicked()
{
    ui->textEdit_2->redo();
}

void MainWindow::on_printt_2_clicked()
{
    QPrinter printer;
     printer.setPrinterName("desired printer name");
     QPrintDialog dialog(&printer,this);
     if(dialog.exec() == QDialog::Rejected) return;
     ui->textEdit_2->print(&printer);
}

void MainWindow::on_fontt_2_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_2->setFont(font);
      } else return;
}

void MainWindow::on_colort_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()) {
        ui->textEdit_2->setTextColor(color);
      }
}

void MainWindow::on_bgcolort_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()) {
        ui->textEdit_2->setTextBackgroundColor(color);
      }
}

void MainWindow::on_bgct_2_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Choose Color");
    if(color.isValid()) {
        ui->textEdit_2->setPalette(QPalette(color));
      }
}

void MainWindow::on_export_coln_clicked()
{
    QString n =ui->colnour->currentText();

    QPdfWriter pdf(exporter+"nourriture de id "+n+".pdf");
                  QPainter painter;
                  if (! painter.begin(&pdf))
                  {
                      // failed to open file
                                      qWarning("failed to open file, is it writable?");

                  }
                  QString id =ui->colnour->currentText();
               //   const time_t ctt = time();
                  QSqlQuery query;
query.exec("SELECT REF_NOURRITURE,ID_FOURNISSEUR,NOM_NOURRITURE,DATE_EXPIRATION,PRIX,QUANTITÉ,IMAGE FROM NOURRITURE WHERE REF_NOURRITURE='"+id+"'");

                          while (query.next())
                                {

                              QString REF_NOURRITURE = query.value(0).toString();
                              QString ID_FOURNISSEUR = query.value(1).toString();
                              QString NOM_NOURRITURE = query.value(2).toString();
                              QString DATE_EXPIRATION = query.value(3).toString();
                              QString PRIX = query.value(4).toString();
                              QString QUANTITE = query.value(5).toString();
                              QString IMAGE = query.value(6).toString();


                      painter.drawText(2200,3500,REF_NOURRITURE);
                      painter.drawText(2200,4000,ID_FOURNISSEUR);
                      painter.drawText(2200,4500,NOM_NOURRITURE);
                      painter.drawText(2200,5000,DATE_EXPIRATION);
                      painter.drawText(2200,5500,PRIX);
                      painter.drawText(2200,6000,QUANTITE);
                     // painter.drawText(2200,6500,IMAGE);
                      painter.drawPixmap(QRect(300,300,2600,2600),QPixmap(IMAGE)  );


                      painter.setPen(Qt::blue);
                      painter.setPen(Qt::black);
                  //    painter.drawText(500,2000,asctime(localtime(&ctt)));
                      painter.drawText(500,3500,"REF_NOURRITURE:");
                      painter.drawText(500,4000,"ID_FOURNISSEUR :");
                      painter.drawText(500,4500,"NOM_NOURRITURE:");
                      painter.drawText(500,5000,"DATE_EXPIRATION :");
                      painter.drawText(500,5500,"PRIX :");
                      painter.drawText(500,6000,"QUANTITÉ:");
                      //painter.drawText(500,6500,"IMAGE :");

                  }
                   painter.end();
                           QMessageBox::information (this,"PDF","Export fait avec succès!");

}

void MainWindow::on_tabWidget_baha_currentChanged(int index)
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    qDebug()<<index ;
    if(index==1)
    {q.prepare("select REF_NOURRITURE from NOURRITURE ");
        q.exec();
        modal->setQuery(q);
        ui->colnour->setModel(modal);
    }
    else if (index == 0)
    {q.prepare("select ID_FOURNISSEUR from FOURNISSEUR ");
        q.exec();
        modal->setQuery(q);
        ui->colfour->setModel(modal);
    }
}

void MainWindow::on_export_colf_clicked()
{
    QString n =ui->colfour->currentText();
  //  QString exporter="C:/Users/SBS/Documents/";
    QPdfWriter pdf(exporter+"fournisseur de id "+n+".pdf");
                  QPainter painter;
                  if (! painter.begin(&pdf))
                  {
                      // failed to open file
                                      qWarning("failed to open file, is it writable?");

                  }
                  QString id =ui->colfour->currentText();
               //   const time_t ctt = time();
                  QSqlQuery query;
query.exec("SELECT ID_FOURNISSEUR,ADRESSE_FOURNISSEUR,NOM_FOURNISSEUR,EMAIL_FOURNISSEUR,TEL_FOURNISSEUR,SEXE_FOURNISSEUR,AGE_FOURNISSEUR FROM FOURNISSEUR WHERE ID_FOURNISSEUR='"+id+"'");

                          while (query.next())
                                {

                              QString ID_FOURNISSEUR = query.value(0).toString();
                              QString ADRESSE_FOURNISSEUR = query.value(1).toString();
                              QString NOM_FOURNISSEUR = query.value(2).toString();
                              QString EMAIL_FOURNISSEUR = query.value(3).toString();
                              QString TEL_FOURNISSEUR = query.value(4).toString();
                              QString SEXE_FOURNISSEUR = query.value(5).toString();
                              QString AGE_FOURNISSEUR = query.value(6).toString();


                      painter.drawText(2200,3500,ID_FOURNISSEUR);
                      painter.drawText(2200,4000,ADRESSE_FOURNISSEUR);
                      painter.drawText(2200,4500,NOM_FOURNISSEUR);
                      painter.drawText(2200,5000,EMAIL_FOURNISSEUR);
                      painter.drawText(2200,5500,TEL_FOURNISSEUR);
                      painter.drawText(2200,6000,SEXE_FOURNISSEUR);
                      painter.drawText(2200,6500,AGE_FOURNISSEUR);
                      //painter.drawPixmap(QRect(300,300,2600,2600),QPixmap(IMAGE)  );


                      painter.setPen(Qt::blue);
                      painter.setPen(Qt::black);
                  //    painter.drawText(500,2000,asctime(localtime(&ctt)));
                      painter.drawText(500,3500,"ID_FOURNISSEUR:");
                      painter.drawText(500,4000,"ADRESSE_FOURNISSEUR :");
                      painter.drawText(500,4500,"NOM_FOURNISSEUR:");
                      painter.drawText(500,5000,"EMAIL_FOURNISSEUR :");
                      painter.drawText(500,5500,"TEL_FOURNISSEUR :");
                      painter.drawText(500,6000,"SEXE_FOURNISSEUR:");
                      painter.drawText(500,6500,"AGE_FOURNISSEUR :");

                  }
                   painter.end();
                           QMessageBox::information (this,"PDF","Export fait avec succès!");

}


void MainWindow::on_boutton_French_clicked()
{
    qApp->removeTranslator(&translatorEn);
}

void MainWindow::on_boutton_English_clicked()
{
    qApp->installTranslator(&translatorEn);

}

void MainWindow::on_bttn_muter_linkActivated(const QString &link)
{
    if(mute==0)
    {
        player->setMuted(1);
        mute=1;
        QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/unmute.png");
        px3=px3.scaledToWidth(ui->bttn_muter->width()  );
        ui->bttn_muter->setPixmap(px3);
        qDebug()<< "1 walet" ;
    }
    else if (mute==1)
    {
    player->setMuted(0);
    mute=0;
    QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/stop.png");
    px3=px3.scaledToWidth(ui->bttn_muter->width()  );
    ui->bttn_muter->setPixmap(px3);
    qDebug()<< "0 walet" ;
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    if(mute==0)
    {
        player->setMuted(1);
        mute=1;
        QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/unmute.png");
        px3=px3.scaledToWidth(ui->bttn_muter->width()  );
        ui->bttn_muter->setPixmap(px3);
        qDebug()<< "1 walet" ;
    }
    else if (mute==1)
    {
    player->setMuted(0);
    mute=0;
    QPixmap px3("C:/Users/SBS/Documents/testqt/Ressources/stop.png");
    px3=px3.scaledToWidth(ui->bttn_muter->width()  );
    ui->bttn_muter->setPixmap(px3);
    qDebug()<< "0 walet" ;
    }
}

void MainWindow::on_login_btn_clicked()
{
    QString username = ui->username_2->text();
    QString password = ui->password_2->text();
    QString role = ui->role_2->text();
    QString etat="connecté(e)";
           if((username !=  "")&&(password!="")&&(role !="")) {
login h(username,password,role);
bool test=h.connect();

if(test)
{
//
if( role=="admin" )
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
    ui->pushButton_admin->setEnabled(true);
    ui->pushButton_plante->setEnabled(true);
    ui->pushButton_materiel->setEnabled(true);
    ui->pushButton_animal->setEnabled(true);
    ui->pushButton_nour_four->setEnabled(true);
    ui->tabprofil->setModel(tmpprofil.afficher());
    ui->tabouv->setModel(tmpouvrier.afficher());
    ui->pushButton_nour_four->setFlat(1);
    ui->pushButton_plante->setFlat(1);
    ui->pushButton_materiel->setFlat(1);
    ui->pushButton_animal->setFlat(1);
    ui->pushButton_admin->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
  //  nom=username;
}
else if( role=="g_n_f"  )
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(0);
    ui->tabfournisseur->setModel(tmpfournisseur.afficher());
    ui->pushButton_nour_four->setEnabled(true);
    ui->pushButton_admin->setEnabled(false);
    ui->pushButton_plante->setEnabled(false);
    ui->pushButton_materiel->setEnabled(false);
    ui->pushButton_animal->setEnabled(false);
    QSqlQuery q;
    QSqlQueryModel * modal = new QSqlQueryModel ();
    q.prepare("select ID_FOURNISSEUR from FOURNISSEUR ");
            q.exec();
            modal->setQuery(q);
            ui->colfour->setModel(modal);
   ui->pushButton_nour_four->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
   ui->pushButton_admin->setFlat(1);
   ui->pushButton_plante->setFlat(1);
   ui->pushButton_materiel->setFlat(1);
   ui->pushButton_animal->setFlat(1);
}
else if( role=="g_p"  )
{   ui->pushButton_plante->setEnabled(true);
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(2);
    ui->afficherplantes->setModel(tmpplante.afficher());
    ui->afficherproduitv->setModel(tmpproduitv.afficher());
    ui->pushButton_admin->setEnabled(false);
    ui->pushButton_nour_four->setEnabled(false);
    ui->pushButton_materiel->setEnabled(false);
    ui->pushButton_animal->setEnabled(false);
    //
    ui->pushButton_plante->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
    ui->pushButton_nour_four->setFlat(1);
    ui->pushButton_admin->setFlat(1);
    ui->pushButton_materiel->setFlat(1);
    ui->pushButton_animal->setFlat(1);
}
else if( role=="g_m"  )
{
   ui->pushButton_materiel->setEnabled(true);
   ui->pushButton_plante->setEnabled(false);
   ui->pushButton_admin->setEnabled(false);
   ui->pushButton_nour_four->setEnabled(false);
   ui->pushButton_animal->setEnabled(false);
   ui->stackedWidget_2->setCurrentIndex(1);
   ui->stackedWidgetbaha1->setCurrentIndex(3);
   ui->tableViewVehilcule->setModel(tmpvehicule.afficher());//refresh
   ui->pushButton_nour_four->setFlat(1);
   ui->pushButton_admin->setFlat(1);
   ui->pushButton_plante->setFlat(1);
   ui->pushButton_animal->setFlat(1);
   ui->pushButton_materiel->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
}
else if( role=="g_a"  )
{
   ui->pushButton_materiel->setEnabled(false);
   ui->pushButton_plante->setEnabled(false);
   ui->pushButton_admin->setEnabled(false);
   ui->pushButton_nour_four->setEnabled(false);
   ui->pushButton_animal->setEnabled(true);
   ui->stackedWidget_2->setCurrentIndex(1);
   ui->stackedWidgetbaha1->setCurrentIndex(11);
   ui->tableanim->setModel(tmpanimal.afficher());//refresh
   ui->pushButton_nour_four->setFlat(1);
   ui->pushButton_admin->setFlat(1);
   ui->pushButton_plante->setFlat(1);
   ui->pushButton_materiel->setFlat(1);
   ui->pushButton_animal->setStyleSheet("qproperty-iconSize: 90px 90px ;background-color:rgba(61, 120, 72, 50%);");
}

QSqlQuery q;
q.prepare("SELECT ID,username from LOGIN WHERE username = :username and password = :password and role=:role");
q.bindValue(":username",username);
q.bindValue(":password",password);
q.bindValue(":role",role);
QString m;
if(q.exec()) {if(q.next() ){ m=q.value(0).toString(); idp=m;nom=q.value(1).toString() ;   }   }
q.prepare("select IMAGE from OUVRIERS where ID_OUVRIER=:m");
q.bindValue(":m",m);
QString ch;
if(q.exec()) {if(q.next() ){  ch=q.value(0).toString();  }    }

QPixmap pixmap(ch);
//pixmap=pixmap.scaledToWidth(ui->pushButton_imgprofile->width()  );
pixmap=pixmap.scaledToHeight(ui->pushButton_imgprofile->height()  );
QIcon ButtonIcon(pixmap);
ui->pushButton_imgprofile->setIcon(ButtonIcon);
ui->pushButton_imgprofile->setIconSize(pixmap.rect().size());
QMessageBox::information(this, "Connetion", "Connecté(e)");
mSystemTrayIcon->showMessage(tr(username.toUtf8().constData()),tr(etat.toUtf8().constData()));
timer.start();
}
else{
QMessageBox::warning(this,"Connection", "Vérifier svp ");
}
    }
else {
    QMessageBox::warning(this,"Connection", "Vérifier svp ");
}
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
   if(index==1){ ui->tabouv->setModel(tmpouvrier.afficher());}
else if(index==0) {ui->tabprofil->setModel(tmpprofil.afficher()); }
}

void MainWindow::on_trieup_profile_clicked()
{
    ui->tabprofil->setModel(tmpprofil.sortid_up());
}

void MainWindow::on_triedown_profile_clicked()
{
    ui->tabprofil->setModel(tmpprofil.sortid_down());
}

void MainWindow::on_recherche_profile_clicked()
{
    QString chercher = ui->lineEdit_cher->text();

QString username;
           if((chercher !=  ""))
           {
               QSqlQuery q;
               QSqlQueryModel *modal=new QSqlQueryModel();
               if(chercher != "")
               {
               q.prepare("select * from LOGIN where username like '%"+chercher+"%' ");
               q.bindValue(":username",chercher);
               q.exec();
               modal->setQuery(q);
               ui->tabprofil->setModel(modal);
               ui->tabprofil->setModel(modal);
              // ui->stackedWidget->setCurrentIndex(1);
           }
           else
           {
               QMessageBox::warning(this,"Probléme", "recherche invalide ");
           }


}
}

void MainWindow::on_trieup_ouvrier_clicked()
{
    ui->tabouv->setModel(tmpouvrier.sortid_up());

}

void MainWindow::on_triedown_ouvrier_clicked()
{
    ui->tabouv->setModel(tmpouvrier.sortid_down());

}

void MainWindow::on_recherche_ouvrier_clicked()
{
    QString chercher = ui->lineEdit_cher_2->text();

//int id_ouvrier;
           if((chercher !=  ""))
           {
               QSqlQuery q;
               QSqlQueryModel *modal=new QSqlQueryModel();
               if(chercher != "")
               {
               q.prepare("select * from ouvriers where id_ouvrier like '%"+chercher+"%' ");
               q.bindValue(":id_ouvrier",chercher);
               q.exec();
               modal->setQuery(q);
               ui->tabouv->setModel(modal);
               ui->tabouv->setModel(modal);
              // ui->stackedWidget->setCurrentIndex(1);
           }
           else
           {
               QMessageBox::warning(this,"Probléme", "recherche invalide ");
           }
}
}


void MainWindow::on_ajouter_profile_clicked()
{
 ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
}

void MainWindow::on_pushButton_10_clicked()
{
    int id=0;
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString role = ui->role->text();

           if((username !=  "")&&(password!="")&&(role !="")) {
               QMessageBox::information(this, "Ajout", "Ajout reussi");
}
           else {
               QMessageBox::warning(this,"Ajout", "Ajouter svp ");
           }

profil p(id,username,password,role);
bool test=p.ajouter();
  mSystemTrayIcon->showMessage(tr("Profil ajouté "),tr(username.toUtf8().constData()));
ui->stackedWidget_2->setCurrentIndex(1);
ui->stackedWidgetbaha1->setCurrentIndex(1);
ui->tabprofil->setModel(tmpprofil.afficher());
}

void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
}

void MainWindow::on_pushButton_38_clicked()
{
QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "profil ", "supprimer?",
                                   QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
       qDebug() << "Yes was clicked";
       int id;
       QString username = ui->c_username_7->currentText();

   QString password,role;

   profil p(id,username,password,role);
   bool test=p.supprimer(username);
     mSystemTrayIcon->showMessage(tr("Profil Supprimé "),tr(username.toUtf8().constData()));
     ui->stackedWidget_2->setCurrentIndex(1);
     ui->stackedWidgetbaha1->setCurrentIndex(1);
   ui->tabprofil->setModel(tmpprofil.afficher());
     } else {
       qDebug() << "Yes was *not* clicked";
     }
}


void MainWindow::on_pushButton_55_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
}

void MainWindow::on_pushButton_56_clicked()
{
    int id;
    QString username = ui->username_8->text();
    QString password = ui->password_7->text();
    QString role = ui->role_8->text();

           if((username !=  "")&&(password!="")&&(role !=""))
           {
               QMessageBox::information(this, "Modification", "Modifié");
           }
           else
           {
               QMessageBox::warning(this,"Modification", "Verifié(e) svp ");
           }

profil p(id,username,password,role);
bool test=p.Modifier();
  mSystemTrayIcon->showMessage(tr("Profil Modifié "),tr(username.toUtf8().constData()));
  ui->stackedWidget_2->setCurrentIndex(1);
  ui->stackedWidgetbaha1->setCurrentIndex(1);
  ui->tabprofil->setModel(tmpprofil.afficher());
}

void MainWindow::on_supprimer_profile_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID from LOGIN ");
        q.exec();
        modal->setQuery(q);
        ui->c_username_7->setModel(modal);
}

void MainWindow::on_modifier_profile_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}

void MainWindow::on_pushButton_50_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
}

void MainWindow::on_pushButton_60_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(1);
}

void MainWindow::on_ajouter_ouvrier_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(7);

}

void MainWindow::on_supprimer_ouvrier_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(8);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID_OUVRIER from OUVRIERS ");
        q.exec();
        modal->setQuery(q);
        ui->id_ouvrier_3->setModel(modal);

}

void MainWindow::on_modifier_ouvrier_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(9);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID_OUVRIER from OUVRIERS ");
        q.exec();
        modal->setQuery(q);
        ui->id_ouvrier_2->setModel(modal);

}

void MainWindow::on_pushButton_49_clicked()
{
    long id_ouvrier=0;
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString role = ui->role_7->text();
    float salaire = ui->salaire->text().toFloat();
    long cin = ui->cin->text().toInt();
    QDate date_debut = ui->dbt->date();
    QDate date_fin = ui->dbf->date();
    long num_tel = ui->num->text().toInt();
    QString filePath1;
    QStringList files = QFileDialog::getOpenFileNames(this,tr("Open files"),
                                                          QString(),
                                                          tr("Photo Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
        foreach (QString filePath, files) {

            QPixmap px1(filePath);
            filePath1=filePath;
            px1 = px1.scaledToWidth(ui->image->width(),Qt::SmoothTransformation);
            ui->image->setPixmap(px1);
}
         if((nom !=  "")&&(prenom!="")&&(role !="")) {
               QMessageBox::information(this, "Ajout", "Ajout reussi");
}
           else {
               QMessageBox::warning(this,"Ajout", "Ajouter svp ");
           }
qDebug()<<filePath1;
ouvrier o(id_ouvrier,nom,prenom,role,salaire,cin,date_debut,date_fin,num_tel,filePath1);
bool test=o.ajouter();
  mSystemTrayIcon->showMessage(tr("Ouvrier ajouté "),tr(nom.toUtf8().constData()));
ui->stackedWidget_2->setCurrentIndex(1);
ui->stackedWidgetbaha1->setCurrentIndex(1);
ui->tabouv->setModel(tmpouvrier.afficher());
}

void MainWindow::on_supprimer_ouv_2_clicked()
{

      QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this, "ouvrier ", "supprimer?",
                                         QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {
             qDebug() << "Yes was clicked";
             long id_ouvrier=ui->id_ouvrier_3->currentText().toInt();
             qDebug()<<id_ouvrier;
             QString nom;
             QString prenom;
             QString role;
             float salaire;
             long cin;
             QDate date_debut;
             QDate date_fin;
             long num_tel ;
             QString filePath1;
           ouvrier o(id_ouvrier,nom,prenom,role,salaire,cin,date_debut,date_fin,num_tel,filePath1);
             bool test=o.supprimer(id_ouvrier);
               mSystemTrayIcon->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
               ui->stackedWidget_2->setCurrentIndex(1);
               ui->stackedWidgetbaha1->setCurrentIndex(1);    ui->tabouv->setModel(tmpouvrier.afficher());
           } else {
             qDebug() << "Yes was *not* clicked";
           }
}

void MainWindow::on_pushButton_58_clicked()
{
    long id_ouvrier=ui->id_ouvrier_2->currentText().toULong();
    QString nom = ui->nom_2->text();
    QString prenom = ui->prenom_2->text();
    QString role = ui->role_9->text();
    float salaire = ui->salaire_2->text().toFloat();
    long cin = ui->cin_2->text().toInt();
    QDate date_debut = ui->dbt_2->date();
    QDate date_fin = ui->dbf_2->date();
    long num_tel = ui->num_2->text().toInt();
    QString filePath1;

           if((nom !=  "")&&(prenom!="")&&(role !=""))
           {
               QMessageBox::information(this, "Modification", "Modifié");
           }
           else
           {
               QMessageBox::warning(this,"Modification", "Verifié(e) svp ");
           }

           ouvrier o(id_ouvrier,nom,prenom,role,salaire,cin,date_debut,date_fin,num_tel,filePath1);
           bool test=o.Modifier();
           mSystemTrayIcon->showMessage(tr("Ouvrier Modifié "),tr(nom.toUtf8().constData()));
           ui->stackedWidget_2->setCurrentIndex(1);
           ui->stackedWidgetbaha1->setCurrentIndex(1);
           ui->tabouv->setModel(tmpouvrier.afficher());
}

void MainWindow::on_pushButton_53_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_54_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);
}

void MainWindow::on_pushButton_61_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_stats_clicked()
{
    // Assign names to the set of bars used
            QBarSet *set010 = new QBarSet("salaire");

            QSqlQuery q;
                          q.prepare("select salaire from ouvriers order by id_ouvrier desc ");
                          if(q.exec())
                          {
                                         while (q.next())
                                         {
                                             float a=q.value(0).toFloat();
                                           *set010 << a ;
                                         }
}
            QBarSeries *series10 = new QBarSeries();

            // 2. Stacked bar chart
            // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
            series10->append(set010);


            // Used to define the bar chart to display, title
            // legend,
            QChart *chart10 = new QChart();

            // Add the chart
            chart10->addSeries(series10);

            // Set title
            chart10->setTitle("salaire selon le nom ouvrier ");

            // Define starting animation
            // NoAnimation, GridAxisAnimations, SeriesAnimations
            chart10->setAnimationOptions(QChart::AllAnimations);

            // Holds the category titles
            QStringList categories10;
            //QSqlQuery q;
                          q.prepare("select NOM from OUVRIERS order by ID_OUVRIER  ");
                          if(q.exec())
                        {
                            while (q.next())
                            {
                            QString a=q.value(0).toString() ;
                             categories10 << a ;
                            }
                        }
            // Adds categories to the axes
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories10);
            chart10->createDefaultAxes();

            // 1. Bar chart
            chart10->setAxisX(axis, series10);

            // 2. Stacked Bar chart
            // chart->setAxisY(axis, series);

            // Define where the legend is displayed
            chart10->legend()->setVisible(true);
            chart10->legend()->setAlignment(Qt::AlignBottom);

            // Used to display the chart
            QChartView *chartView10= new QChartView(chart10);
            chartView10->setRenderHint(QPainter::Antialiasing);

            // Used to change the palette
            QPalette pal = qApp->palette();

            // Change the color around the chart widget and text
            pal.setColor(QPalette::Window, QRgb(0xffffff));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));

            // Apply palette changes to the application
            qApp->setPalette(pal);

chartView10->setParent(ui->horizontalFrame_3);
ui->stackedWidget_2->setCurrentIndex(11);

}

void MainWindow::on_ajouterplante_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur where type=:t ");
    q.bindValue(":t","plante");
    q.exec();
    modal->setQuery(q);
    ui->comboBox_idf_p->setModel(modal);
    QSqlQueryModel * modal1 = new QSqlQueryModel ();
    QSqlQuery q1;
    q1.prepare("select REF_NOURRITURE from NOURRITURE ");
    q1.exec();
    modal1->setQuery(q1);
    ui->comboBox_refn_p->setModel(modal1);
    ui->stackedWidget_2->setCurrentIndex(12);
}

void MainWindow::on_anulerajouterplante_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_ajoutplante_clicked()
{
    QString nom_plante=ui->inom->text();
    int nombre= ui->inombre->value();
    float prix=ui->iprix->value();
     float surface=ui->isurface->value();
     float humidite=ui->ihumidite->value();
     float fructification=ui->ifructification->value() ;//
    float  fprix=ui->iprix->value();
     int age=ui->iage->value();
     QString reclote=ui->ireclote->date().toString();
     int type=ui->itype->value();
     int zone=ui->izone->value();
      int idf= ui->comboBox_idf_p->currentText().toInt();
      QString refn = ui->comboBox_refn_p->currentText();
    plante p(nom_plante,nombre,prix,surface,humidite,fructification,fprix,age,reclote,type,zone,idf,refn);
    bool test=p.ajouter();
    if(test)
  {

       ui->afficherplantes->setModel(tmpplante.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("Ajouter une plante"),
                    QObject::tr("plante ajoutée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une plante"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


ui->stackedWidget_2->setCurrentIndex(1);
ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_afficherplantes_activated(const QModelIndex &index)
{
if( index.column() ==0 )
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
 else  if( index.column() ==11 )
  {
          QString nom,email;
          int numero;
          int idf=ui->afficherplantes->model()->data(index).toInt();
          QSqlQuery qu;
          qu.prepare("select * from FOURNISSEUR where ID_FOURNISSEUR= '"+QString::number(idf)+"' ");
          if(qu.exec())
            while (qu.next()) {
                nom =qu.value(2).toString();
                email =qu.value(3).toString();
                numero =qu.value(4).toInt();
                              }
          QMessageBox::information(this,"Information Sur Fournisseur","ID:"+QString::number(idf)+" Nom: "+nom+" Email: "+email+" Numero: "+QString::number(numero)+"  ");
  }

}

void MainWindow::on_mod_clicked()
{
    QString nom_plante=ui->modnom->text();
    int nombre=ui->modnombre->text().toInt();
    float prix=ui->modprix->text().toFloat();
     float surface=ui->modsurface->text().toFloat();
    float  fprix=ui->modfprix->text().toFloat();
     int age=ui->modage->text().toInt();
    plante p(nom_plante,nombre,prix,surface,0,0,fprix,age,"",0,0,0,"");
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
ui->stackedWidgetbaha1->setCurrentIndex(2);

}

void MainWindow::on_anulersupprimerplante_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(2);
    ui->afficherplantes->setModel(tmpplante.afficher());
}

void MainWindow::on_supprimerplante_2_clicked()
{
      QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this, "plante ", "supprimer?",
                                         QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {
             qDebug() << "Yes was clicked";
             QString nom= ui->c_nomasupprimer->currentText();
              bool test=tmpplante.supprimer(nom);
ui->afficherplantes->setModel(tmpplante.afficher());//refresh
ui->stackedWidget_2->setCurrentIndex(1);
              ui->stackedWidgetbaha1->setCurrentIndex(2);
           } else {
             qDebug() << "Yes was *not* clicked";
           }
}

void MainWindow::on_supprimerplante_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(13);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select NOM_PLANTE from PLANTE ");
        q.exec();
        modal->setQuery(q);
        ui->c_nomasupprimer->setModel(modal);
}

void MainWindow::on_validrechercheplante_clicked()
{
    QString nom=ui->nomrecherche->text();
    ui->afficherplantes->setModel(tmpplante.rechercher(nom));

}

void MainWindow::on_nomrecherche_textChanged(const QString &arg1)
{
    ui->afficherplantes->setModel(tmpplante.rechercher(arg1));
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->afficherplantes->setModel(tmpplante.afficherup());

}

void MainWindow::on_pushButton_19_clicked()
{
    ui->afficherplantes->setModel(tmpplante.afficherdown());

}

void MainWindow::on_annulersupprimerproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_annulerajouterproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_ajouterproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(14);
}

void MainWindow::on_supprimerproduitv_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(15);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select NOM_PRODUIT from PRODUIT_VEGETAL ");
        q.exec();
        modal->setQuery(q);
        ui->c_nomproduitasupprimer->setModel(modal);
}

void MainWindow::on_tabWidget_3_currentChanged(int index)
{
    if(index ==0  )
{       ui->afficherplantes->setModel(tmpplante.afficher());
      }
    else if (index == 1)
    {          ui->afficherproduitv->setModel(tmpproduitv.afficher());  }
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


ui->stackedWidget_2->setCurrentIndex(1);
ui->stackedWidgetbaha1->setCurrentIndex(2);

}

void MainWindow::on_ajouterproduitv_2_clicked()
{
    QString nom_produitv=ui->inomproduitv->text();
    int quantite=ui->iquantite->value();
    float prixunitaire=ui->iprixunitaire->value();

    produitv p(nom_produitv,quantite,prixunitaire);
    bool test=p.ajouter();
    if(test)
  {

       ui->afficherproduitv->setModel(tmpproduitv.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("Ajouter un produit  v"),
                    QObject::tr("Etudiant ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un  produit  v"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    ui->stackedWidget_2->setCurrentIndex(1);
    ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_supprimerproduitv_2_clicked()
{   
   QMessageBox::StandardButton reply;
       reply = QMessageBox::question(this, "produit vegetaole", "supprimer?",
                                     QMessageBox::Yes|QMessageBox::No);
       if (reply == QMessageBox::Yes) {
         qDebug() << "Yes was clicked";
         QString nom= ui->c_nomproduitasupprimer->currentText();
          bool test=tmpproduitv.supprimer(nom);
          ui->afficherproduitv->setModel(tmpproduitv.afficher());//refresh
          ui->stackedWidget_2->setCurrentIndex(1);
          ui->stackedWidgetbaha1->setCurrentIndex(2);
       } else {
         qDebug() << "Yes was *not* clicked";
       }
}

void MainWindow::on_produitvdown_clicked()
{
    ui->afficherproduitv->setModel(tmpproduitv.afficherdown());

}

void MainWindow::on_produitvup_clicked()
{
    ui->afficherproduitv->setModel(tmpproduitv.afficherup());

}

void MainWindow::on_rechercherproduitv_clicked()
{
    QString nom=ui->nomproduitrecherche->text();
    ui->afficherproduitv->setModel(tmpproduitv.rechercher(nom));

}

void MainWindow::on_pushButton_57_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);
}

void MainWindow::on_pushButton_62_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);
}


void MainWindow::on_ajouter_vehicule_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(16);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur where type=:t ");
    q.bindValue(":t","equipement");
    q.exec();
    modal->setQuery(q);
    ui->idf_equip_4->setModel(modal);
}

void MainWindow::on_modifier_vehicule_clicked()
{
    /*ui->stackedWidget_2->setCurrentIndex(17);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur ");
    q.exec();
    modal->setQuery(q);
    ui->idf_equip_3->setModel(modal);
    QMessageBox::information(this,"Pour Modifier il Faut","Double clique sur la Matricule dans le tableau");
*/
    QMessageBox::information(this,"Pour Modifier il Faut","Double clique sur la Matricule dans le tableau");

}

void MainWindow::on_supprimer_vehicule_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(18);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select MATRICULE from VEHICULE ");
        q.exec();
        modal->setQuery(q);
        ui->input_supp_equipement->setModel(modal);
}

void MainWindow::on_retour_vehicule_a_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_retour_vehicule_m_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_retour_vehicule_s_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_button_ajouter_vehicule_clicked()
{
    ui->label_yassinevm->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >ce champ est nécessaire  ");
    ui->label_yassinevmar->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >ce champ est nécessaire  ");
 //
    QString matricule = ui->input_matricule->text();
    QString marque= ui->input_marque_vehicule->text();
    int age= ui->input_age_vehicule->value();
    QString datedachat= ui->input_date_vehicule->date().toString();
    int idf= ui->idf_equip_4->currentText().toInt();

  vehicule ve(matricule,marque,age,datedachat,idf);
 if((matricule!="")&&(marque!="")){
  bool test=ve.ajouter();
  if(test)
{
ui->label_yassinevm->hide();
ui->label_yassinevmar->hide();
      ui->tableViewVehilcule->setModel(tmpvehicule.afficher());//refresh
      ui->stackedWidget_2->setCurrentIndex(1);
    //  ui->tableViewVehilcule->setModel(tmpvehicule.triasc());
   //  ui->tableViewVehilcule->setModel(tmpvehicule.tridesc());
QMessageBox::information(nullptr, QObject::tr("Ajouter un vehicule"),
                  QObject::tr("vehicule ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
   {   QMessageBox::critical(nullptr, QObject::tr("Ajouter un vehicule"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);}
}
else
{
if(matricule==""){ui->label_yassinevm->show();}
if(marque==""){ui->label_yassinevmar->show();}
}

}

void MainWindow::on_Modifier_vehicule_clicked()
{
    ui->label_yassinevm_2->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >ce champ est nécessaire  ");
    ui->label_yassinevmar_2->setToolTip("<img src='C:/Users/SBS/Documents/testqt/Ressources/warn.png' width='35' height='35' >ce champ est nécessaire  ");

        QString id = ui->input_matricule_m->text();
        QString marque= ui->input_marque_vehicule_m->text();
        int age= ui->input_age_vehicule_m->text().toInt();
        QString datedachat= ui->input_date_vehicule_m->text();
        int idf= ui->idf_equip_3->currentText().toInt();

        vehicule ve(id,marque,age,datedachat,idf);
if((id!="")&&(marque!="")) {
    ui->label_yassinevm_2->hide();
    ui->label_yassinevmar_2->hide();
    bool test=ve.modifier(id);
        if(test)
      {
            ui->tableViewVehilcule->setModel(tmpvehicule.afficher());//refresh
            ui->stackedWidget_2->setCurrentIndex(1);

           // ui->tableViewVehilcule->setModel(tmpvehicule.triasc());
         //  ui->tableViewVehilcule->setModel(tmpvehicule.tridesc());
      QMessageBox::information(nullptr, QObject::tr("Modifier un Vehicule"),
                        QObject::tr("Vehicule modifié.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

      }
        else
        {    QMessageBox::critical(nullptr, QObject::tr("Modifier un Vehicule"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
}
else
{
if(id==""){ui->label_yassinevm_2->show();}
if(marque==""){ui->label_yassinevmar_2->show();}

}
}

void MainWindow::on_supp_vehicule_clicked()
{  
  QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "vehicule", "supprimer?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QString reference = ui->input_supp_equipement->currentText();
        qDebug()<< reference ;

      bool test=tmpvehicule.supprimer(reference);
      ui->tableViewVehilcule->setModel(tmpvehicule.afficher());//refresh
      ui->stackedWidget_2->setCurrentIndex(1);
      } else {
        qDebug() << "Yes was *not* clicked";
      }

}

void MainWindow::on_tabWidget_5_currentChanged(int index)
{
    if (index == 0 ) { ui->tableViewVehilcule->setModel(tmpvehicule.afficher()); }
else if (index == 1 )  {  ui->tableViewEquipement->setModel(tmpequipement.afficher());  }
}

void MainWindow::on_chercher_vehicule_clicked()
{
    qDebug()<< "chercher !!" ;
    QString id=ui->input_recherche_vehicule->text();

 if(id!="")  { ui->tableViewVehilcule->setModel(tmpvehicule.recherche(id)); }
 else{ QMessageBox::information(this,"Pour chercher dans vehicule  il Faut","tapez la matricule");
     ui->tableViewVehilcule->setModel(tmpvehicule.afficher());

 }
}

void MainWindow::on_tri_asc_vehilcule_clicked()
{
 ui->tableViewVehilcule->setModel(tmpvehicule.triasc());
}

void MainWindow::on_tri_desc_vehilcule_clicked()
{
 ui->tableViewVehilcule->setModel(tmpvehicule.tridesc());
}

void MainWindow::on_retour_equipement_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_retour_equi_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_page_ajouter_equipement_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(19);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur where type=:t  ");
    q.bindValue(":t","equipement");
    q.exec();
    modal->setQuery(q);
    ui->idf_equip_2->setModel(modal);
}

void MainWindow::on_modifier_equipement_clicked()
{
    /*ui->stackedWidget_2->setCurrentIndex(20);
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur ");
    q.exec();
    modal->setQuery(q);
    ui->idf_equip->setModel(modal);*/
    QMessageBox::information(this,"Pour Modifier il Faut","Double clique sur la reference dans le tableau");

}

void MainWindow::on_supprimer_equipement_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(21);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select REFERENCE from EQUIPEMENT ");
        q.exec();
        modal->setQuery(q);
        ui->input_supp_eq->setModel(modal);
}

void MainWindow::on_supp_equipement_clicked()
{
  QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "vehicule", "supprimer?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QString reference = ui->input_supp_eq->currentText();
        qDebug()<< reference ;

      bool test=tmpequipement.supprimer(reference);
      ui->tableViewEquipement->setModel(tmpequipement.afficher());//refresh
      ui->stackedWidget_2->setCurrentIndex(1);

      } else {
        qDebug() << "Yes was *not* clicked";
      }

}

void MainWindow::on_update_equipement_clicked()
{
    QString id = ui->inputReferenceEq_2->text();
    int quantite= ui->inputQuantiteEq_2->value();
     QString nom= ui->inputNomEq_2->text();
      QString datedachat= ui->inputDateDachatEq_2->date().toString();
      int idf = ui->idf_equip->currentText().toInt();

      ui->label_yassineenom_2->hide();
      ui->label_yassineeref_2->hide();

if((nom!="")&&(id!=""))
{
  ui->label_yassineenom_2->hide();
  ui->label_yassineeref_2->hide();
     equipement eq(quantite,id,nom,datedachat,idf);
   bool test=eq.modifier(id);
   if(test)
 {
       ui->tableViewEquipement->setModel(tmpequipement.afficher());
       ui->stackedWidget_2->setCurrentIndex(1);

      // ui->tableViewEquipement->setModel(tmpequipement.triasc());
      // ui->tableViewEquipement->setModel(tmpequipement.tridesc());
 QMessageBox::information(nullptr, QObject::tr("Modifier un Equipement"),
                   QObject::tr("Equipement modifié.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

 }
   else
      { QMessageBox::critical(nullptr, QObject::tr("Modifier un Equipement"),
                   QObject::tr("Erreur !.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);}
}
   else {
       if(nom==""   ) {ui->label_yassineenom_2->show();}
       if(id=="") {ui->label_yassineeref_2->show();  }
   }

}

void MainWindow::on_ajouter_equipement_clicked()
{

    int quantite = ui->inputQuantiteEq->value();
    QString reference= ui->inputReferenceEq->text();
    QString nom= ui->inputNomEq->text();
    QString date= ui->inputDateDachatEq->date().toString();
    int idf = ui->idf_equip_2->currentText().toInt();

    ui->label_yassineenom->hide();
    ui->label_yassineeref->hide();
if((nom!="")&&(reference!=""))
{
ui->label_yassineenom->hide();
ui->label_yassineeref->hide();
equipement eq(quantite,reference,nom,date,idf);
bool test=eq.ajouter();
  if(test)
{

      ui->tableViewEquipement->setModel(tmpequipement.afficher());//refresh
     // ui->tableViewEquipement->setModel(tmpequipement.triasc());
    // ui->tableViewEquipement->setModel(tmpequipement.tridesc());
     ui->stackedWidget_2->setCurrentIndex(1);
QMessageBox::information(nullptr, QObject::tr("Ajouter un Equipement"),
                  QObject::tr("Equipement ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
   { QMessageBox::critical(nullptr, QObject::tr("Ajouter un Equipement"),
                  QObject::tr("Erreur !.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);}
}
else
{
if(nom==""   ) {ui->label_yassineenom->show();}
if(reference=="") {ui->label_yassineeref->show();  }
}

}

void MainWindow::on_chercher_equipement_clicked()
{
    QString id=ui->input_recherche_eq->text();
 if(id!="")  { ui->tableViewEquipement->setModel(tmpequipement.recherche(id)); }
 else{ QMessageBox::information(this,"Pour chercher dans equipement  il Faut","tapez la reference");
 ui->tableViewEquipement->setModel(tmpequipement.afficher());
 }

}

void MainWindow::on_tri_asc_equipement_clicked()
{
    ui->tableViewEquipement->setModel(tmpequipement.triasc());
}

void MainWindow::on_tri_desc_equipement_clicked()
{
    ui->tableViewEquipement->setModel(tmpequipement.tridesc());
}

void MainWindow::on_pushButton_63_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);
}

void MainWindow::on_pushButton_64_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);
}



void MainWindow::on_lineEdit_refn_textChanged(const QString &arg1)
{
    QRegExp rx ("^[0-9]*$");
    QRegExpValidator *validid = new QRegExpValidator(rx,this);
    ui->lineEdit_refn->setValidator(validid);
}

void MainWindow::on_pushButton_stat_plante_clicked()
{

    //
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
    chartview->setParent(ui->frame_plante_stat   );
    //
ui->stackedWidgetbaha1->setCurrentIndex(7);

}

void MainWindow::on_pushButton_retourstatp_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_pushButton_retourstatp_2_clicked()
{
     ui->stackedWidgetbaha1->setCurrentIndex(2);
}

void MainWindow::on_pushButton_stat_plante_2_clicked()
{
    //
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
    chart->setTitle("donut chart repartition des plante par nombre :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->frame_plante_stat_2   );
    //
ui->stackedWidgetbaha1->setCurrentIndex(8);
}

void MainWindow::on_boutton_settings_mail_clicked()
{
    mail=ui->lineEdit_mail->text();
    mdp=ui->lineEdit_mdpm->text() ;
}

void MainWindow::on_boutton_settings_exporter_clicked()
{
    exporter=ui->lineEdit_exporter->text();
}


void MainWindow::on_btn_add_4_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    QString somme;
    foreach (QString filePath, dir) {
        somme+=filePath;
    }
    somme+="/";
    ui->lineEdit_exporter->setText(somme);
}

void MainWindow::on_pushButton_clicked()
{
aze=1;
        QSqlQuery q;
        q.prepare("update  PARTICIPANT set STATUS=1  where ID =:nom");
        q.bindValue(":nom",idp);

        if(q.exec())
      {
      }
        QString m=nom+":has joined the chat";
        q.prepare("INSERT INTO CHAT (MSG )VALUES (:m )  ");
        q.bindValue(":m",m);
        if(q.exec()) {   }
    ui->stackedWidget_2->setCurrentIndex(22);
}

void MainWindow::on_lineEdit_chat_returnPressed()
{
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<dateTime<<dateTimeString;
//
     QString msg=nom+":"+ui->lineEdit_chat->text();
     ui->lineEdit_chat->setText("");
     QSqlQuery q;
     q.prepare("INSERT INTO CHAT (MSG,MSG_DATE )VALUES (:m,:d )  ");
     q.bindValue(":m",msg);
     q.bindValue(":d",dateTimeString);
     if(q.exec()) {   }

}

void MainWindow::on_returnfromchat_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    QSqlQuery q;
    q.prepare("update  PARTICIPANT set STATUS=0  where ID =:nom");
    q.bindValue(":nom",idp);
    if(q.exec())
  {
        ui->listWidget->clear();
        ui->textEdit_chat->setText("");
  }
    aze=0;
    QString m=nom+":has left the chat";
    q.prepare("INSERT INTO CHAT (MSG )VALUES (:m )  ");
    q.bindValue(":m",m);
    if(q.exec()) {   }

}
void MainWindow::chat()
{

    ui->listWidget->clear();
     if(aze==1){
      QSqlQuery q;
      q.prepare("select NOM_PARTICIPANT from PARTICIPANT   where STATUS=1 ");
     // q.bindValue(":n",nom);
      if(q.exec()){ while (q.next()){ ui->listWidget->addItem(q.value(0).toString());  }

      }
     }

     ui->textEdit_chat->clear();
      //
      QSqlQuery qq;
      qq.prepare("select MSG ,MSG_DATE from CHAT ");
      if(qq.exec()&&(aze==1)){
       while (qq.next())
      {
      QString s=qq.value(0).toString()+"     ,"+qq.value(1).toString();
      ui->textEdit_chat->setTextColor(Qt::black); ui->textEdit_chat->append(tr(s.toUtf8()));
      }
      }
}


void MainWindow::on_pushButton_2_clicked()
{
if(ui->stackedWidget_calculatrice->currentIndex()==1 )
{ ui->stackedWidget_calculatrice->setCurrentIndex(0);
ui->stackedWidget_calculatrice->show();
}
else if(ui->stackedWidget_calculatrice->currentIndex()==0 )
{ ui->stackedWidget_calculatrice->setCurrentIndex(1);
ui->stackedWidget_calculatrice->hide();
}
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
void MainWindow::printplante(QPrinter *printer) {

    // ------------------ simplest example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 15 << 15 << 10 << 15 << 20 << 25 << 30<<20<<25<<25<<25<<25<<25 ;
    ui->afficherplantes->setModel(tmpplante.afficher());
    qDebug() << "tab plante" <<ui->afficherplantes->model() ;
    if(!tablePrinter.printTable(ui->afficherplantes->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}
void MainWindow::printproduitv(QPrinter *printer) {

    // ------------------ simplest example --------------------------

    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 25 << 25 << 25 << 25  ;
    ui->afficherproduitv->setModel(tmpproduitv.afficher());
    qDebug() << "tab produit végétale" <<ui->afficherproduitv->model() ;
    if(!tablePrinter.printTable(ui->afficherproduitv->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    painter.end();
}

void MainWindow::on_print_plante_clicked()
{
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printplante(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_print_pr_vg_clicked()
{
    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printproduitv(QPrinter*)));
    dialog.exec();
}

void MainWindow::on_tableViewVehilcule_activated(const QModelIndex &index)
{
    if(index.column() ==0 )
 {
        QSqlQueryModel * modal = new QSqlQueryModel ();
                QSqlQuery q;
                q.prepare("select ID_FOURNISSEUR from fournisseur ");
                q.exec();
                modal->setQuery(q);
                ui->idf_equip_3->setModel(modal);
                QString valeur=ui->tableViewVehilcule->model()->data(index).toString();
                QSqlQuery q1;
                q1.prepare("select * from vehicule where matricule='"+valeur+"'");
                if(q1.exec())
                  while (q1.next()) {
                              ui->input_matricule_m->setText(q1.value(0).toString());
                              ui->input_marque_vehicule_m->setText(q1.value(1).toString());
                              ui->input_age_vehicule_m->setValue( q1.value(2).toInt());
                              QDate d = QDate::fromString(q1.value(3).toString() ) ;
                              ui->input_date_vehicule_m->setDate(d);
                              ui->idf_equip_3->setCurrentText(q1.value(4).toString());
                             // ui->comboBox_vehiculeM->addItem(q.value(4).toString());
                              //ui->stackedWidget_2->setCurrentIndex(7);
                                    }
ui->stackedWidget_2->setCurrentIndex(17);
    }
 else  if( index.column() ==4 )
{
        QString nom,email;
        int numero;
        int idf=ui->tableViewVehilcule->model()->data(index).toInt();
        QSqlQuery qu;
        qu.prepare("select * from FOURNISSEUR where ID_FOURNISSEUR= '"+QString::number(idf)+"' ");
        if(qu.exec())
          while (qu.next()) {
              nom =qu.value(2).toString();
              email =qu.value(3).toString();
              numero =qu.value(4).toInt();
                            }
        QMessageBox::information(this,"Information Sur Fournisseur","ID:"+QString::number(idf)+" Nom: "+nom+" Email: "+email+" Numero: "+QString::number(numero)+"  ");
}
else
{
        QMessageBox::information(nullptr, QObject::tr("Information Sur la Modification"),
                    QObject::tr("double clique sur la Matricule.\n"
                                "POur Le Modifier."), QMessageBox::Cancel);
}
}

void MainWindow::on_tableViewEquipement_activated(const QModelIndex &index)
{
    if(index.column() ==0 )
 {
        QSqlQueryModel * modal = new QSqlQueryModel ();
                QSqlQuery q;
                q.prepare("select ID_FOURNISSEUR from fournisseur ");
                q.exec();
                modal->setQuery(q);
                ui->idf_equip->setModel(modal);
                QString valeur=ui->tableViewEquipement->model()->data(index).toString();
                QSqlQuery q1;
                q1.prepare("select * from Equipement where reference='"+valeur+"'");
                if(q1.exec())
                  while (q1.next()) {
                              ui->inputReferenceEq_2->setText(q1.value(0).toString());
                              ui->inputNomEq_2->setText(q1.value(1).toString());
                              ui->inputQuantiteEq_2->setValue( q1.value(2).toInt());
                              QDate d = QDate::fromString(q1.value(3).toString() ) ;
                              ui->inputDateDachatEq_2->setDate(d) ;
                              ui->idf_equip->setCurrentText(q1.value(4).toString());
                             // ui->comboBox_vehiculeM->addItem(q.value(4).toString());
                              //ui->stackedWidget_2->setCurrentIndex(7);
                                    }
                ui->stackedWidget_2->setCurrentIndex(20);
    }
 else  if( index.column() ==4 )
{
        QString nom,email;
        int numero;
        int idf=ui->tableViewEquipement->model()->data(index).toInt();
        QSqlQuery qu;
        qu.prepare("select * from FOURNISSEUR where ID_FOURNISSEUR= '"+QString::number(idf)+"' ");
        if(qu.exec())
          while (qu.next()) {
              nom =qu.value(2).toString();
              email =qu.value(3).toString();
              numero =qu.value(4).toInt();
                            }
        QMessageBox::information(this,"Information Sur Fournisseur","ID:"+QString::number(idf)+" Nom: "+nom+" Email: "+email+" Numero: "+QString::number(numero)+"  ");
}
else
{
        QMessageBox::information(nullptr, QObject::tr("Information Sur la Modification"),
                    QObject::tr("double clique sur la reference.\n"
                                "POur Le Modifier."), QMessageBox::Cancel);
}

}

void MainWindow::on_input_recherche_vehicule_textChanged(const QString &arg1)
{
if(arg1==""){    ui->tableViewVehilcule->setModel(tmpvehicule.afficher());    }
}

void MainWindow::on_input_recherche_eq_textChanged(const QString &arg1)
{
    if(arg1==""){    ui->tableViewEquipement->setModel(tmpvehicule.afficher());    }

}


void MainWindow::on_recherche_n_textChanged(const QString &arg1)
{
    if(arg1==""){    ui->tabnourriture->setModel(tmpnourriture.affichern());    }
}

void MainWindow::on_pushButton_retourstatv_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(3);
}

void MainWindow::on_pushButton_retourstate_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(3);
}

void MainWindow::on_statistique_vehilcule_clicked()
{
    //
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select MATRICULE,AGE  from VEHICULE  order by AGE  DESC");
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
    chart->setTitle("donut chart repartition des vehicule par age :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->frame_vehicule   );
    //
    ui->stackedWidgetbaha1->setCurrentIndex(9);
}

void MainWindow::on_statistique_equipement_clicked()
{

    //
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select REFERENCE,QUANTITE  from EQUIPEMENT  order by QUANTITE  DESC");
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
    chart->setTitle("donut chart repartition des equipement par quantité :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->frame_equipement   );
    //
    ui->stackedWidgetbaha1->setCurrentIndex(10);
}

void MainWindow::on_pushButton_execel_clicked()
{
    QTableView *table;
    table = ui->tableViewVehilcule;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_2_clicked()
{
    QTableView *table;
    table = ui->tableViewEquipement;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //   QPixmap screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    QPixmap screenshot = QPixmap::grabWindow(ui->tableViewVehilcule->winId());

       screenshot.save(exporter+"capture-equipement.png", "png");

       QMessageBox::information(this,"capture Enregistrer","Ce capture a ete Enregistere Dans Desktop Sous le Nom capture.png");

}

void MainWindow::on_pushButton_4_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(exporter+"equipement.pdf");
    QPainter painter;
    painter.begin(&printer);

    QFont font;
    QSqlQuery query;
    QString reference,nom,quantite,datedachat,idf;


        int i=0,ligne1=250,ligne2=300,ligne3=350,ligne4=400,ligne5=450,ligne6=470;
        query.prepare("select * from EQUIPEMENT");
        if (query.exec())
        {
            while (query.next())
            {
                reference=query.value(0).toString();
                nom=query.value(1).toString();
                quantite=query.value(2).toString();
                datedachat=query.value(3).toString();
                idf=query.value(4).toString();
                i++;
                if(i>=2)
                {
                ligne1+=250;
                ligne2+=250;
                ligne3+=250;
                ligne4+=250;
                ligne5+=250;
                ligne6+=250;
                }
                qDebug()<< i ;

            font.setPixelSize(50);
            painter.setFont(font);
            painter.setPen(Qt::red);
            painter.drawText(350,150,"Equipement");

            font.setPixelSize(35);
            painter.setFont(font);
            painter.setPen(Qt::blue);
            painter.drawText(20,ligne1,"Reference: ");
            painter.drawText(20,ligne2,"Nom: ");
            painter.drawText(20,ligne3,"Quantite:");
            painter.drawText(20,ligne4,"DateDachat:");
            painter.drawText(20,ligne5,"ID_FOURNISSEUR:");


            font.setPixelSize(22);
            painter.setFont(font);
            painter.setPen(Qt::black);
            painter.drawText(250,ligne1,reference);
            painter.drawText(250,ligne2,nom);
            painter.drawText(250,ligne3,quantite);
            painter.drawText(250,ligne4,datedachat);
            painter.drawText(350,ligne5,idf);
            painter.drawText(0,ligne6,"--------------------------------------------------------------------------------------------------");

            }



    }



    painter.end();
    qDebug()<<"le pdf a ete cree";
    QMessageBox::information(this,"PDF cree","Ce PDF a ete cree Dans Desktop Sous le Nom equipement.pdf");

}

void MainWindow::on_pushButton_7_clicked()
{
    //   QPixmap screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
    QPixmap screenshot = QPixmap::grabWindow(ui->tableViewVehilcule->winId());

       screenshot.save(exporter+"capture-vehicule.png", "png");

       QMessageBox::information(this,"capture Enregistrer","Ce capture a ete Enregistere Dans Desktop Sous le Nom capture.png");

}

void MainWindow::on_pushButton_8_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(exporter+"vehicule.pdf");
    QPainter painter;
    painter.begin(&printer);

    QFont font;
    QSqlQuery query;
    QString MATRICULE,MARQUE,AGE,DATEDACHAT,ID_FOURNISSEUR;


        int i=0,ligne1=250,ligne2=300,ligne3=350,ligne4=400,ligne5=450,ligne6=470;
        query.prepare("select * from VEHICULE");
        if (query.exec())
        {
            while (query.next())
            {
                MATRICULE=query.value(0).toString();
                MARQUE=query.value(1).toString();
                AGE=query.value(2).toString();
                DATEDACHAT=query.value(3).toString();
                ID_FOURNISSEUR=query.value(4).toString();
                i++;
                if(i>=2)
                {
                ligne1+=250;
                ligne2+=250;
                ligne3+=250;
                ligne4+=250;
                ligne5+=250;
                ligne6+=250;
               }
                qDebug()<< i ;

            font.setPixelSize(50);
            painter.setFont(font);
            painter.setPen(Qt::red);
            painter.drawText(350,150,"vehicule");

            font.setPixelSize(35);
            painter.setFont(font);
            painter.setPen(Qt::blue);
            painter.drawText(20,ligne1,"MATRICULE: ");
            painter.drawText(20,ligne2,"MARQUE: ");
            painter.drawText(20,ligne3,"AGE:");
            painter.drawText(20,ligne4,"DATEDACHAT:");
            painter.drawText(20,ligne5,"ID_FOURNISSEUR:");


            font.setPixelSize(22);
            painter.setFont(font);
            painter.setPen(Qt::black);
            painter.drawText(250,ligne1,MATRICULE);
            painter.drawText(250,ligne2,MARQUE);
            painter.drawText(250,ligne3,AGE);
            painter.drawText(250,ligne4,DATEDACHAT);
            painter.drawText(350,ligne5,ID_FOURNISSEUR);
            painter.drawText(0,ligne6,"--------------------------------------------------------------------------------------------------");

            }



    }



    painter.end();
    qDebug()<<"le pdf a ete cree";
    QMessageBox::information(this,"PDF cree","Ce PDF a ete cree Dans Desktop Sous le Nom equipement.pdf");

}

void MainWindow::on_pushButton_execel_f_clicked()
{
    QTableView *table;
    table = ui->tabfournisseur;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_n_clicked()
{
    QTableView *table;
    table = ui->tabnourriture;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}




void MainWindow::on_pushButton_12_clicked()
{
    QString id= ui->username_recup->text();
    QString maill=ui->mail_recup->text();


    // Create the credentials EmailAddress
    EmailAddress credentials(mail,mdp);

    // Create the from EmailAddress
    EmailAddress from(mail);

    // Create the to EmailAddress
    EmailAddress to( maill);
    QSqlQuery q;
    q.prepare("select ROLE ,PASSWORD from LOGIN where ID='"+id+"' ");
    if(q.exec())
       {if (q.next()) {
            // Create the email
            Email email(credentials,
                        from,
                        to,
                        "récupérer mot de passe",
                        "votre role est    :"+q.value(0).toString()+"   votre mot de passe est :"+q.value(1).toString()  );






    // Create the SMTPClient
    client_ = new SMTPClient("smtp.gmail.com",465);

    // Connection used to receive the results
    connect(client_, SIGNAL(status(Status::e, QString)),
            this, SLOT(onStatus(Status::e, QString)), Qt::UniqueConnection);

    // Try to send the email
    client_->sendEmail(email);       }
     else {  QMessageBox::information(this,"recuperer mot de passe ","verifier id , id n'existe pas");  }
    }

}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget_auth->setCurrentIndex(0);
}

void MainWindow::on_login_btn_2_clicked()
{
    ui->stackedWidget_auth->setCurrentIndex(1);

}

void MainWindow::on_pushButton_imgprofile_clicked()
{
if(ui->stackedWidget_profile->currentIndex()==0 ){ ui->stackedWidget_profile->setCurrentIndex(1);ui->stackedWidget_profile->show(); }
else if(ui->stackedWidget_profile->currentIndex()==1 ){ ui->stackedWidget_profile->setCurrentIndex(0);ui->stackedWidget_profile->hide(); }

}

void MainWindow::on_pushButton_ajouterf_3_clicked()
{

    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur where type=:t ");
    q.bindValue(":t","animal");
    q.exec();
    modal->setQuery(q);
    ui->idf_animal->setModel(modal);
    ui->stackedWidget_2->setCurrentIndex(23);

}

void MainWindow::on_ajouteranim_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_ajouteranim_clicked()
{
    int id = ui->lineEdit_id_anim->text().toInt();
    int nb = ui->lineEdit_nb_anim->text().toInt();
     float prix = ui->lineEdit_prix_anim->text().toInt();
       QString nom= ui->lineEdit_nom_anim->text();
       int idf=ui->idf_animal->currentText().toInt();
     Animal e(id,nom,nb,prix,idf);
     bool test=e.ajouter();
     if(test)
   {
    ui->tableanim->setModel(tmpanimal.afficher());
    ui->stackedWidget_2->setCurrentIndex(1);
         QMessageBox::information(nullptr, QObject::tr("Ajouter un Animal"),
                     QObject::tr("Animal ajouté.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Ajouter un Animal"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_fs_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(25);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID from ANIMAL ");
        q.exec();
        modal->setQuery(q);
        ui->Idanim->setModel(modal);

}

void MainWindow::on_supprimeranim_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_supprimeranim_clicked()
{
    QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Test", "voulez vous supprimer?",
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes)
   {
     qDebug() << "Yes was clicked";

     int Idanim= ui->Idanim->currentText().toInt()  ;
          bool test1=tmpanimal.supprimer(Idanim);
        if(test1)
         {
             ui->tableanim->setModel(tmpanimal.afficher());
             ui->stackedWidget_2->setCurrentIndex(1);

             QMessageBox::information(nullptr, QObject::tr("Supprimer un animal"),
                         QObject::tr("Animal supprimé.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }
         else
             QMessageBox::critical(nullptr, QObject::tr("Supprimer un animal"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

 }

   else
   {
     qDebug() << "Yes was *not* clicked";
   }
}

void MainWindow::on_tableanim_activated(const QModelIndex &index)
{
    if(index.column() ==0 )
 {
    QSqlQueryModel * modal = new QSqlQueryModel ();
          QSqlQuery q0;
          q0.prepare("select ID_FOURNISSEUR from fournisseur where type=:t ");
          q0.bindValue(":t","animal");
          q0.exec();
          modal->setQuery(q0);
          ui->idf_animal_2->setModel(modal);
    //
    QString val=ui->tableanim->model()->data(index).toString();
    QSqlQuery q;
    q.prepare("select * from ANIMAL where ID='"+val+"'");
    if(q.exec())
    {
        while (q.next())
        {
        ui->modid_anim->setText(q.value(0).toString());
        ui->modnom_anim->setText(q.value(1).toString());
        ui->modprix_anim->setText(q.value(2).toString());
        ui->modnb_anim->setText(q.value(3).toString());
        ui->idf_animal_2->setCurrentText(q.value(4).toString());
        }
    }
}
    else  if( index.column() ==4 )
   {
           QString nom,email;
           int numero;
           int idf=ui->tableanim->model()->data(index).toInt();
           QSqlQuery qu;
           qu.prepare("select * from FOURNISSEUR where ID_FOURNISSEUR= '"+QString::number(idf)+"' ");
           if(qu.exec())
             while (qu.next()) {
                 nom =qu.value(2).toString();
                 email =qu.value(3).toString();
                 numero =qu.value(4).toInt();
                               }
           QMessageBox::information(this,"Information Sur Fournisseur","ID:"+QString::number(idf)+" Nom: "+nom+" Email: "+email+" Numero: "+QString::number(numero)+"  ");
   }
   else
   {
           QMessageBox::information(nullptr, QObject::tr("Information Sur la Modification"),
                       QObject::tr("double clique sur l' identifiant .\n"
                                   "POur Le Modifier."), QMessageBox::Cancel);
   }
}

void MainWindow::on_fm_3_clicked()
{
    int id=ui->modid_anim->text().toInt();
    QString nom=ui->modnom_anim->text();
    int nb=ui->modnb_anim->text().toInt();
    float prix=ui->modprix_anim->text().toFloat();
    int idf=ui->idf_animal_2->currentText().toInt();
  Animal p(id,nom,nb,prix,idf);
    bool test=p.modifier();
    if(test)
  {
        ui->modid_anim->setText("");
        ui->modnom_anim->setText("");
        ui->modprix_anim->setText("");
        ui->modnb_anim->setText("");
       ui->tableanim->setModel(tmpanimal.afficher());//refresh
  QMessageBox::information(nullptr, QObject::tr("modifier"),
                    QObject::tr("modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("modifier"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_rechanim_clicked()
{
    QString nom=ui->nomrecherche_an->text();
    ui->tableanim->setModel(tmpanimal.rechercher(nom));
}

void MainWindow::on_upanim_clicked()
{
    if(ui->comboBox_an->currentIndex()==0)
    ui->tableanim->setModel(tmpanimal.afficherup_ID());
    else if(ui->comboBox_an->currentIndex()==1)
    ui->tableanim->setModel(tmpanimal.afficherup_prix());
    else if(ui->comboBox_an->currentIndex()==2)
    ui->tableanim->setModel(tmpanimal.afficherup_nb());

}

void MainWindow::on_downanim_clicked()
{
    if(ui->comboBox_an->currentIndex()==0)
    ui->tableanim->setModel(tmpanimal.afficherdown_ID());
    else if(ui->comboBox_an->currentIndex()==1)
    ui->tableanim->setModel(tmpanimal.afficherdown_prix());
    else if(ui->comboBox_an->currentIndex()==2)
    ui->tableanim->setModel(tmpanimal.afficherdown_nb());

}

void MainWindow::on_nomrecherche_an_textChanged(const QString &arg1)
{
    if(arg1=="")
{  ui->tableanim->setModel(tmpanimal.afficher());  }
}

void MainWindow::on_pushButton_ajouterf_4_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
    QSqlQuery q;
    q.prepare("select ID_FOURNISSEUR from fournisseur where type=:t ");
    q.bindValue(":t","animal");
    q.exec();
    modal->setQuery(q);
    ui->idf_produit_animalier->setModel(modal);
    ui->stackedWidget_2->setCurrentIndex(24);
}

void MainWindow::on_fs_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(26);
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID from PRODUIT ");
        q.exec();
        modal->setQuery(q);
        ui->Idprod->setModel(modal);
}

void MainWindow::on_supprimerprod_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_ajouterprod_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_ajouterprod_clicked()
{
    int id = ui->lineEdit_id_prod->text().toInt();
    int nb = ui->lineEdit_nb_prod->text().toInt();
    float prix = ui->lineEdit_prix_prod->text().toInt();
    QString nom= ui->lineEdit_nom_prod->text();
    int idf=ui->idf_produit_animalier->currentText().toInt();

       Produit p(id,nom,nb,prix,idf);

     bool test=p.ajouter();
     if(test)
   {
         ui->tableprod->setModel(tmpprod.afficher());
         ui->stackedWidget_2->setCurrentIndex(1);
   QMessageBox::information(nullptr, QObject::tr("Ajouter un Produit"),
                     QObject::tr("Produit ajouté.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("Ajouter un Produit"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_supprimerprod_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "voulez vous supprimer?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      qDebug() << "Yes was clicked";

      int Idprod= ui->Idprod->currentText().toInt();
           bool test1=tmpprod.supprimer(Idprod);
         if(test1)
          {
              ui->tableprod->setModel(tmpprod.afficher());
              ui->stackedWidget_2->setCurrentIndex(1);
              QMessageBox::information(nullptr, QObject::tr("Supprimer un produit"),
                          QObject::tr("Produit supprimé.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

          }
          else
              QMessageBox::critical(nullptr, QObject::tr("Supprimer un produit"),
                          QObject::tr("Erreur !.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

  }


    else
    {
      qDebug() << "Yes was *not* clicked";
    }
}

void MainWindow::on_tableprod_activated(const QModelIndex &index)
{       QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q0;
        q0.prepare("select ID_FOURNISSEUR from fournisseur where type=:t ");
        q0.bindValue(":t","animal");
        q0.exec();
        modal->setQuery(q0);
        ui->idf_produit_animalier_2->setModel(modal);
    //
    QString val=ui->tableprod->model()->data(index).toString();
    QSqlQuery q;
    q.prepare("select * from PRODUIT where ID='"+val+"'");
    if(q.exec())
    {
        while (q.next())
        {
        ui->modid_prod->setText(q.value(0).toString());
        ui->modnom_prod->setText(q.value(1).toString());
        ui->modprix_prod->setText(q.value(2).toString());
        ui->modnb_prod->setText(q.value(3).toString());
        ui->idf_produit_animalier_2->setCurrentText(q.value(4).toString());
        }
    }
}

void MainWindow::on_rechprod_clicked()
{
    QString nom=ui->nomrecherche_proda->text();
    ui->tableprod->setModel(tmpprod.rechercher(nom));
}

void MainWindow::on_downprod_clicked()
{
    if(ui->comboBox_proda->currentIndex()==0)
    ui->tableprod->setModel(tmpprod.afficherdown_ID());
    else if(ui->comboBox_proda->currentIndex()==1)
    ui->tableprod->setModel(tmpprod.afficherdown_prix());
    else if(ui->comboBox_proda->currentIndex()==2)
    ui->tableprod->setModel(tmpprod.afficherdown_nb());
}

void MainWindow::on_upprod_clicked()
{
    if(ui->comboBox_proda->currentIndex()==0)
    ui->tableprod->setModel(tmpprod.afficherup_ID());
    else if(ui->comboBox_proda->currentIndex()==1)
    ui->tableprod->setModel(tmpprod.afficherup_prix());
    else if(ui->comboBox_proda->currentIndex()==2)
    ui->tableprod->setModel(tmpprod.afficherup_nb());
}

void MainWindow::on_nomrecherche_proda_textChanged(const QString &arg1)
{
    if(arg1=="")
{  ui->tableprod->setModel(tmpprod.afficher());  }
}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    if(index==1){ui->tableprod->setModel(tmpprod.afficher()); }
    else if (index==0){ ui->tableanim->setModel(tmpanimal.afficher());    }
}

void MainWindow::on_fm_4_clicked()
{
    int id=ui->modid_prod->text().toInt();
       QString nom=ui->modnom_prod->text();
       int quantite=ui->modnb_prod->text().toInt();
       float prix=ui->modprix_prod->text().toFloat();
       int idf=ui->idf_produit_animalier_2->currentText().toInt();

     Produit p(id,nom,quantite,prix,idf);
       bool test=p.modifier();
       if(test)
     {
           ui->modid_prod->setText("");
           ui->modnom_prod->setText("");
           ui->modprix_prod->setText("");
           ui->modnb_prod->setText("");
          ui->tableprod->setModel(tmpprod.afficher());//refresh
     QMessageBox::information(nullptr, QObject::tr("modifier"),
                       QObject::tr("modifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

     }
       else
           QMessageBox::critical(nullptr, QObject::tr("modifier"),
                       QObject::tr("non modifié !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_66_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);

}

void MainWindow::on_pushButton_65_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);

}

void MainWindow::on_pushButton_retourstate_3_clicked()
{
   ui->stackedWidgetbaha1->setCurrentIndex(11);
}

void MainWindow::on_pushButton_retourstate_2_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(11);
}

void MainWindow::on_statistique_vehilcule_3_clicked()
{
    //
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select NOM,NOMBRE  from ANIMAL  order by NOMBRE  DESC");
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
              //slice->setLabelVisible();
          //}
         // else
         // {
              series->append(a, b );
          //}
      }}}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("donut chart repartition des animal par nombre :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->frame_an  );
    //
    ui->stackedWidgetbaha1->setCurrentIndex(12);
}

void MainWindow::on_statistique_vehilcule_2_clicked()
{
    //
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select NOM,PRIX  from PRODUIT  order by PRIX  DESC");
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
              //slice->setLabelVisible();
          //}
         // else
         // {
              series->append(a, b );
          //}
      }}}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("donut chart repartition des produit animalier par prix :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->frame_pran  );
    //
    ui->stackedWidgetbaha1->setCurrentIndex(13);
}

void MainWindow::on_pushButton_execel_f_3_clicked()
{
    QTableView *table;
    table = ui->tableanim;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_f_2_clicked()
{
    QTableView *table;
    table = ui->tableprod;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_f_5_clicked()
{
    QTableView *table;
    table = ui->afficherproduitv;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_f_4_clicked()
{
    QTableView *table;
    table = ui->afficherplantes;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_f_6_clicked()
{
    QTableView *table;
    table = ui->tabprofil;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_execel_f_7_clicked()
{
    QTableView *table;
    table = ui->tabouv;

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                       filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
        QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
    }
}

void MainWindow::on_pushButton_67_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(10);

}

void MainWindow::on_stats_2_clicked()
{
    //
    qDebug() << test ;
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    if(test)
      {
        QSqlQuery q;
        q.prepare("select ROLE,COUNT(ID)  from LOGIN  GROUP by ROLE");
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
              //slice->setLabelVisible();
          //}
         // else
         // {
              series->append(a, b );
          //}
      }}}
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("donut chart repartition des profil  par role :");
    chart->setTheme(QChart::ChartThemeDark );
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartview->setParent(ui->frame_profil  );
    //
    ui->stackedWidgetbaha1->setCurrentIndex(14);
}

void MainWindow::on_pushButton_retourstate_4_clicked()
{
    ui->stackedWidgetbaha1->setCurrentIndex(1);

}

void MainWindow::on_pushButton_15_clicked()
{
    QSqlQuery rr;
    rr.prepare("INSERT INTO PARTICIPANT (ID,NOM_PARTICIPANT,STATUS) SELECT id,username,password FROM LOGIN WHERE NOT EXISTS (SELECT id FROM PARTICIPANT WHERE PARTICIPANT.id=login.id  )");

    if(rr.exec()){ while(rr.next() )  {    }     }
    rr.prepare("update  PARTICIPANT set STATUS=0   ");

    if(rr.exec()){ while(rr.next() )  {    }     }

}
