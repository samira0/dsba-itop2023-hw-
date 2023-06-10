#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "proxy.h"
#include "booktable.h"
#include "about.h"
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void openDataFile();
    void openAddRowDialog();
    void showAboutDialog();

    void setMinFilterStars(int value);
    void setMinFilterStarsString(QString value);
    void setMaxFilterStars(int value);
    void setMaxFilterStarsString(QString value);

    void setName(QString newText);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonRemoveRow_clicked();

    void on_BasketButton_clicked();

    void on_comboBoxSwitchTheme_currentIndexChanged(int index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_lineEditSearch_textChanged(const QString &arg1);

private:
    Proxy* _proxy;
    Ui::MainWindow* ui;
    BookTable* _table;

    About* _about;

    QString _currentFolder;
    QList<QWidget*> _extraButtons;
    QTranslator* _translator;
};
#endif// MAINWINDOW_H
