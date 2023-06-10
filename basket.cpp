#include "basket.h"
#include "ui_basket.h"
#include <QStringListModel>

Basket::Basket(QWidget *parent, QList<QString> books, double fullPrice) :
    QDialog(parent),
    ui(new Ui::Basket)
{
    ui->setupUi(this);
    QStringListModel *model = new QStringListModel(this);
    model->setStringList(books);
    ui->listView->setModel(model);
    QString value = QString::number(fullPrice);
    ui->labelFullPrice->setText("Sum: " + value);
}

Basket::~Basket()
{
    delete ui;
}
