#include "mainwindow.h"
#include <QApplication>
#include "connexion.h"
#include <QtCharts/QChartView>


int main(int argc, char *argv[])
{
    connexion c;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
