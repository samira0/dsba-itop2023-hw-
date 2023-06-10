#include "addrow.h"
#include "ui_addrow.h"

AddRow::AddRow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRow)
{
    ui->setupUi(this);
}

AddRow::~AddRow()
{
    delete ui;
}

QList<QVariant> AddRow::getDataRow()
{
    QList<QVariant> dataRow;
    dataRow.append(1);
    dataRow.append(ui->lineEditTitle->text());
    dataRow.append(ui->lineEditCategory->text());
    dataRow.append(ui->lineEditPrice->text());
    dataRow.append(ui->lineEditPrice->text());
    dataRow.append(0);
    dataRow.append(ui->spinBoxAvailability->value());
    dataRow.append(0);
    dataRow.append(ui->lineEditDescription->text());
    dataRow.append(ui->lineEditLink->text());
    dataRow.append(ui->comboBox->currentText().toInt());
    dataRow.append("false");

    return dataRow;
}
