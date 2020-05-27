#include "chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include "connexion.h"
#include<QSqlQuery>
ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{

    connexion c;
     bool test=c.ouvrirConnexion();

    //![1]
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("prix");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);
    //![1]

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
          series0->append(a,b);
          //*seriessss <<   QPointF(a, b) ;
      }}}
    //![2]

/*    //![3]
    QPainterPath starPath;
    starPath.moveTo(28, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(14 + 14 * qCos(0.8 * i * M_PI),
                        15 + 14 * qSin(0.8 * i * M_PI));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    series2->setBrush(star);
    series2->setPen(QColor(Qt::transparent));
    //![3]
*/
    //![4]
    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);


    chart()->setTitle(" scatterchart ref en fonction de prix");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
    //![4]

    //![5]
    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    //![5]
}
ChartView2::ChartView2(QWidget *parent) :
    QChartView(new QChart(), parent)
{

    connexion c;
     bool test=c.ouvrirConnexion();

    //![1]
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("age");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);
    //![1]

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
          series0->append(a,b);
          //*seriessss <<   QPointF(a, b) ;
      }}}
    //![2]

/*    //![3]
    QPainterPath starPath;
    starPath.moveTo(28, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(14 + 14 * qCos(0.8 * i * M_PI),
                        15 + 14 * qSin(0.8 * i * M_PI));
    }
    starPath.closeSubpath();

    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);

    series2->setBrush(star);
    series2->setPen(QColor(Qt::transparent));
    //![3]
*/
    //![4]
    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);


    chart()->setTitle(" scatterchart id en fonction de age");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
    //![4]

    //![5]
    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    //![5]
}

