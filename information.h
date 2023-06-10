#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDialog>

namespace Ui {
class Information;
}

class Information : public QDialog
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = nullptr, QList<QVariant> data ={} );
    ~Information();

    void setBookData(const QList<QVariant>& rowData);

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
