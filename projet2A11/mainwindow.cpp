#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QMessageBox>
#include <QMediaPlayer>
#include"smtpp.h"
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
QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //bool etat=true;
    QMediaPlayer * player = new QMediaPlayer;//musique
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("C:/Users/mortadha/Desktop/Post Malone - Better Now.mp3"));
    player->setVolume(0);

    /*bool  e=get_etat();
    if(on_pushButton_42_clicked()!=e)
    {*/
    player->play();
    //e=1;
    // }
    /*if(on_pushButton_42_clicked()==e)
    {
    player->stop();
    }*/

    QPixmap bkngd("C:/Users/mortadha/Documents/projet2A11/resources/6759149_preview.jpg");//background
    bkngd=bkngd.scaled(this->size()*1.23,Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkngd);
    this->setPalette(palette);
   resize(QDesktopWidget().availableGeometry(this).size());
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tabprofil->setModel(tmpprofil.afficher());
    ui->tabouv->setModel(tmpouvrier.afficher());

    notif = new QSystemTrayIcon(this);
        notif->setIcon(QIcon("C:/Users/mortadha/Documents/projet2A11/resources/ouvrier.png"));
        notif->setVisible(true);
        connect(ui->pushButton_51, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->pushButton_53, SIGNAL(clicked()),this, SLOT(ui->stackedWidget->setCurrentIndex(1);));
        // notif=new QSystemTrayIcon(this);
    //notif->setIcon(QIcon("C:/Users/mortadha/Desktop/Chat_Alert-512.png"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_ajouter_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_supprimer_profile_clicked()
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
  notif->showMessage(tr("Profil ajouté "),tr(username.toUtf8().constData()));
ui->stackedWidget->setCurrentIndex(1);
ui->tabprofil->setModel(tmpprofil.afficher());
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_11_clicked()
{
    QString username = ui->username_2->text();
    QString password = ui->password_2->text();
    QString role = ui->role_2->text();
    QString etat="connecté(e)";

           if((username !=  "")&&(password!="")&&(role !="")) {
login h(username,password,role);
bool test=h.connect();

if(h.connect())
{
QMessageBox::information(this, "Connetion", "Connecté(e)");
       ui->stackedWidget->setCurrentIndex(1);
         notif->showMessage(tr(username.toUtf8().constData()),tr(etat.toUtf8().constData()));

}
else{
QMessageBox::warning(this,"Connection", "Vérifier svp ");
}

           }
else {
    QMessageBox::warning(this,"Connection", "Vérifier svp ");

}
}
void MainWindow::on_pushButton_12_clicked()
{
    close();
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
  notif->showMessage(tr("Profil Modifié "),tr(username.toUtf8().constData()));
ui->stackedWidget->setCurrentIndex(1);
ui->tabprofil->setModel(tmpprofil.afficher());
}

void MainWindow::on_modifier_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

void MainWindow::on_pushButton_38_clicked()
{
    int id;
    QString username = ui->username_7->text();

QString password,role;
           if((username !=  ""))
           {
               QMessageBox::information(this, "Suppression", "Supprimé");
           }
           else
           {
               QMessageBox::warning(this,"Suppression", "Verifié(e) svp ");
           }

profil p(id,username,password,role);
bool test=p.supprimer(username);
  notif->showMessage(tr("Profil Supprimé "),tr(username.toUtf8().constData()));
ui->stackedWidget->setCurrentIndex(1);
ui->tabprofil->setModel(tmpprofil.afficher());
}

void MainWindow::on_pushButton_37_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_trieup_profile_clicked()//up
{
ui->tabprofil->setModel(tmpprofil.sortid_up());
}

void MainWindow::on_triedown_profile_clicked()//down
{
ui->tabprofil->setModel(tmpprofil.sortid_down());
}

int MainWindow::on_pushButton_42_clicked()
{
return 1;
}

void MainWindow::on_supprimer_ouvrier_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID_OUVRIER from OUVRIERS ");
        q.exec();
        modal->setQuery(q);
        ui->id_ouvrier_3->setModel(modal);
        ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_ajouter_ouvrier_clicked()
{
 ui->stackedWidget->setCurrentIndex(2);
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
  notif->showMessage(tr("Ouvrier ajouté "),tr(nom.toUtf8().constData()));
ui->stackedWidget->setCurrentIndex(1);
ui->tabouv->setModel(tmpouvrier.afficher());
      }

void MainWindow::on_pushButton_50_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_pushButton_51_clicked()
{
    Smtpp* smtpp = new Smtpp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtpp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtpp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::on_pushButton_52_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_supprimer_ouv_clicked()
{
    long id_ouvrier=ui->id_ouvrier->currentText().toInt();
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
      notif->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabouv->setModel(tmpouvrier.afficher());
}

void MainWindow::on_pushButton_53_clicked()
{
ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_54_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_stats_clicked()
{
    // Assign names to the set of bars used
            QBarSet *set0 = new QBarSet("salaire");

            QSqlQuery q;
                          q.prepare("select salaire from ouvriers order by id_ouvrier desc ");
                          if(q.exec())
                          {
                                         while (q.next())
                                         {
                                             float a=q.value(0).toFloat();
                                           *set0 << a ;
                                         }
}
            QBarSeries *series = new QBarSeries();

            // 2. Stacked bar chart
            // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
            series->append(set0);


            // Used to define the bar chart to display, title
            // legend,
            QChart *chart = new QChart();

            // Add the chart
            chart->addSeries(series);

            // Set title
            chart->setTitle("salaire selon le nom ouvrier ");

            // Define starting animation
            // NoAnimation, GridAxisAnimations, SeriesAnimations
            chart->setAnimationOptions(QChart::AllAnimations);

            // Holds the category titles
            QStringList categories;
            //QSqlQuery q;
                          q.prepare("select NOM from OUVRIERS order by ID_OUVRIER  ");
                          if(q.exec())
                        {
                            while (q.next())
                            {
                            QString a=q.value(0).toString() ;
                             categories << a ;
                            }
                        }
            // Adds categories to the axes
            QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();

            // 1. Bar chart
            chart->setAxisX(axis, series);

            // 2. Stacked Bar chart
            // chart->setAxisY(axis, series);

            // Define where the legend is displayed
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);

            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            // Used to change the palette
            QPalette pal = qApp->palette();

            // Change the color around the chart widget and text
            pal.setColor(QPalette::Window, QRgb(0xffffff));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));

            // Apply palette changes to the application
            qApp->setPalette(pal);

chartView->setParent(ui->horizontalFrame);
ui->stackedWidget->setCurrentIndex(7);

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

void MainWindow::on_modifier_ouvrier_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel ();
        QSqlQuery q;
        q.prepare("select ID_OUVRIER from OUVRIERS ");
        q.exec();
        modal->setQuery(q);
        ui->id_ouvrier_2->setModel(modal);
        ui->stackedWidget->setCurrentIndex(9);
  //  ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_58_clicked()
{

    long id_ouvrier=0;
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
           notif->showMessage(tr("Ouvrier Modifié "),tr(nom.toUtf8().constData()));
           ui->stackedWidget->setCurrentIndex(1);
           ui->tabouv->setModel(tmpouvrier.afficher());
}

void MainWindow::on_supprimer_ouv_2_clicked()
{
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
      notif->showMessage(tr("ouvrier Supprimé "),tr(prenom.toUtf8().constData()));
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabouv->setModel(tmpouvrier.afficher());
}

void MainWindow::on_pushButton_60_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_61_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_55_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
