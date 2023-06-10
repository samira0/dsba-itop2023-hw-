#include "information.h"
#include "ui_information.h"
#include "booktable.h"
#include <QPixmap>

Information::Information(QWidget *parent, QList<QVariant> data) :
    QDialog(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
}

Information::~Information()
{
    delete ui;
}

void Information::setBookData(const QList<QVariant>& rowData)
{
    QString title = rowData[1].toString();
    QString category = rowData[2].toString();
    QString price = rowData[3].toString();
    QString available = rowData[6].toString();
    QString description = rowData[8].toString();
    QString link = rowData[9].toString();
    QString stars = rowData[10].toString();
    QString hyperLink("<a href=\"");
    QString hyper("\"> Image </a>");
    hyperLink += link;
    hyperLink += hyper;

    ui->labelTitle->setText("Name: " + title);
    ui->labelCategory->setText("Category: " + category);
    ui->labelPrice->setText("Price: " + price);
    ui->labelAvailable->setText("Available: " + available);
    ui->plainTextEdit->setPlainText(description);
    ui->labelStars->setText("Stars: " + stars);
    ui->labelLink->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->labelLink->setOpenExternalLinks(true);
    ui->labelLink->setTextFormat(Qt::RichText);
    ui->labelLink->setText(hyperLink);
}
