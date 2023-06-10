#include "additionalwidget.h"
#include <QPainter>
#include <QPainterPath>

AdditionalWidget::AdditionalWidget(QWidget *parent)
    : QWidget{parent}
{

}

void AdditionalWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter myline(this);

    myline.setRenderHint(QPainter::Antialiasing, true);

    myline.fillRect(rect(), Qt::darkMagenta);

    QPen linePen(Qt::black);
    linePen.setWidth(3);

    myline.drawLine(50, 50, 50, 350);
    myline.drawLine(350, 50, 350, 350);
    myline.drawLine(200, 100, 200, 400);

    myline.drawLine(50, 50, 200, 100);
    myline.drawLine(350, 50, 200, 100);

    myline.drawLine(50, 350, 200, 400);
    myline.drawLine(350, 350, 200, 400);

    linePen.setWidth(2);

    myline.drawLine(210, 120, 340, 80);
    myline.drawLine(210, 140, 340, 100);
    myline.drawLine(210, 160, 340, 120);
    myline.drawLine(210, 180, 340, 140);
    myline.drawLine(210, 200, 340, 160);
    myline.drawLine(210, 220, 340, 180);
    myline.drawLine(210, 240, 340, 200);
    myline.drawLine(210, 260, 340, 220);
    myline.drawLine(210, 280, 340, 240);
    myline.drawLine(210, 300, 340, 260);
    myline.drawLine(210, 320, 340, 280);
    myline.drawLine(210, 340, 340, 300);
    myline.drawLine(210, 360, 340, 320);

    myline.drawLine(190, 120, 60, 80);
    myline.drawLine(190, 140, 60, 100);
    myline.drawLine(190, 160, 60, 120);
    myline.drawLine(190, 180, 60, 140);
    myline.drawLine(190, 200, 60, 160);
    myline.drawLine(190, 220, 60, 180);
    myline.drawLine(190, 240, 60, 200);
    myline.drawLine(190, 260, 60, 220);
    myline.drawLine(190, 280, 60, 240);
    myline.drawLine(190, 300, 60, 260);
    myline.drawLine(190, 320, 60, 280);
    myline.drawLine(190, 340, 60, 300);
    myline.drawLine(190, 360, 60, 320);
}
