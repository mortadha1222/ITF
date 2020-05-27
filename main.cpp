#include "mainwindow.h"
#include <QApplication>
#include<qlabel.h>
#include <QMessageBox>
#include "connexion.h"
#include <QtDebug>
#include<QTranslator>
#include <QtPlugin>

//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
   // w.setAttribute(Qt::WA_TranslucentBackground,true  );
   // w.setWindowFlags(Qt::FramelessWindowHint );
    connexion c;




    // bool
    bool test=c.ouvrirConnexion();
    w.test=test;
    //
    QFile file("C:/Users/SBS/Documents/testqt/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    w.setStyleSheet(styleSheet);
    //
    if(w.test)
     {
         w.show();
//QMessageBox::critical(nullptr, QObject::tr("database is not open"),
//QObject::tr("connection avec succés.\n"
//"Click Cancel to exit."), QMessageBox::Cancel);

    }
     else{
//QMessageBox::critical(nullptr, QObject::tr("database is not open"),
//QObject::tr("connection failed.\n"
// "Click Cancel to exit."), QMessageBox::Cancel);
     }
       return a.exec();
}

