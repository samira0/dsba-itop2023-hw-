#ifndef ADDROW_H
#define ADDROW_H

#include <QDialog>

namespace Ui {
class AddRow;
}

class AddRow : public QDialog
{
    Q_OBJECT

public:
    explicit AddRow(QWidget *parent = nullptr);
    ~AddRow();

    QList<QVariant> getDataRow();

private:
    Ui::AddRow *ui;
};

#endif // ADDROW_H
