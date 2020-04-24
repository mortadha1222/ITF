#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include<QFile>
#include "connexion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   Connexion c;

   bool test= c.ouvrirConnexion();

   MainWindow w;
   QFile file("C:/Users/asus/Desktop/testqt/style.qss");
       file.open(QFile::ReadOnly);
       QString styleSheet = QLatin1String(file.readAll());
       w.setStyleSheet(styleSheet);
              if(test)
{
        w.show();


    }
          else
               QMessageBox::information(nullptr, QObject::tr("database is not open"),
                           QObject::tr("Echec de la connexion.\n""Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
}
