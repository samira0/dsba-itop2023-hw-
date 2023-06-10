#ifndef BASKET_H
#define BASKET_H

#include <QDialog>

namespace Ui {
class Basket;
}

class Basket : public QDialog
{
    Q_OBJECT

public:
    explicit Basket(QWidget *parent = nullptr, QList<QString> books = {}, double fullPrice = 0.0);
    ~Basket();

private:
    Ui::Basket *ui;
    QStringList *model;
};

#endif// BASKET_H
