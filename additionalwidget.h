#ifndef ADDITIONALWIDGET_H
#define ADDITIONALWIDGET_H

#include <QWidget>
#include <QPainterPath>

class AdditionalWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdditionalWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
signals:

private:
    QPainterPath createBookPath(int width, int height);

};

#endif // ADDITIONALWIDGET_H
