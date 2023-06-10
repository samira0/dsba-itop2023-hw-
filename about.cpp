#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QGridLayout* layout = ui->gridLayout;
    AdditionalWidget* icon = new AdditionalWidget;
    icon->setAttribute(Qt::WA_DeleteOnClose);
    layout->addWidget(icon, 0, 1);
    for (int i = 0; i<layout->columnCount(); i++)
        layout->setColumnStretch(i, 1);
}

About::~About()
{
    delete ui;
}
