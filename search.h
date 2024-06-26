#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    bool pointerFromFile(const QString& path);
    ~Search();

private:
    Ui::Search *ui;
};

#endif // SEARCH_H
