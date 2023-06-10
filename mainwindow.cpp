#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrow.h"
#include "basket.h"
#include "booktable.h"
#include "information.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>

const int NAME_COLUMN = 1;

QString loadCurrentFolderFromFile()
{
    QFile inputFile("./settings_file.txt");
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return QString("");
    }
    QTextStream inputStream(&inputFile);

    return inputStream.readLine();
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _table = new BookTable(this);
    _about = new About(this);
    _proxy = new Proxy(this);
    _proxy->setSourceModel(_table);
    _translator = new QTranslator(this);

    ui->tableView->setModel(_proxy);
    ui->tableView->setSortingEnabled(true);

    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(4);
    ui->tableView->hideColumn(5);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(8);
    ui->tableView->hideColumn(9);


    QObject::connect(ui->actionOpen_File, &QAction::triggered, this, &MainWindow::openDataFile);
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    QObject::connect(ui->pushButtonAddRow, &QPushButton::clicked, this, &MainWindow::openAddRowDialog);

    QObject::connect(ui->minStarsSlider, &QSlider::valueChanged, this, &MainWindow::setMinFilterStars);
    QObject::connect(ui->minStarsLineEdit, &QLineEdit::textChanged, this, &MainWindow::setMinFilterStarsString);
    QObject::connect(ui->maxStarsSlider, &QSlider::valueChanged, this, &MainWindow::setMaxFilterStars);
    QObject::connect(ui->maxStarsLineEdit, &QLineEdit::textChanged, this, &MainWindow::setMaxFilterStarsString);

    ui->comboBoxSwitchTheme->addItem("Black Theme");
    ui->comboBoxSwitchTheme->addItem("White Theme");
    ui->comboBoxSwitchTheme->addItem("Red Theme");
    ui->comboBoxSwitchTheme->addItem("Yellow Theme");
    ui->comboBoxSwitchTheme->addItem("Blue Theme");
    ui->comboBoxSwitchTheme->addItem("Magenta Theme");

    _currentFolder = loadCurrentFolderFromFile();
}

void MainWindow::on_comboBoxSwitchTheme_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        return setPalette(QPalette(Qt::black));
    case 1:
        return setPalette(QPalette(Qt::white));
    case 2:
        return setPalette(QPalette(Qt::darkRed));
    case 3:
        return setPalette(QPalette(Qt::darkYellow));
    case 4:
        return setPalette(QPalette(Qt::darkBlue));
    case 5:
        return setPalette(QPalette(Qt::darkMagenta));
    }

}

void MainWindow::setMinFilterStars(int value)
{
    ui->minStarsLineEdit->setText(QString::number(value));
    _proxy->setMinStars(value);
}
void MainWindow::setMinFilterStarsString(QString value)
{
    ui->minStarsSlider->setValue(value.toInt());
    _proxy->setMinStars(value.toInt());
}
void MainWindow::setMaxFilterStars(int value)
{
    ui->maxStarsLineEdit->setText(QString::number(value));
    _proxy->setMaxStars(value);
}
void MainWindow::setMaxFilterStarsString(QString value)
{
    ui->maxStarsSlider->setValue(value.toInt());
    _proxy->setMaxStars(value.toInt());
}

QString extractDir(const QString& file)
{
    return file;
}

void saveCurrentFolderToFile(const QString& _currentFolder)
{
    QFile outputFile("./settings_file.txt");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream outputStream(&outputFile);
    outputStream << _currentFolder;
}

void MainWindow::showAboutDialog()
{
    _about->show();
}

void MainWindow::openDataFile()
{
    if (_currentFolder.isEmpty())
    {
        _currentFolder = ".";
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", _currentFolder, "*.csv");

    _currentFolder = fileName;
    saveCurrentFolderToFile(_currentFolder);


    if (!_table->reloadDataFromFile(fileName))
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
    }
}


void MainWindow::openAddRowDialog()
{
    AddRow dialog;
    if (dialog.exec())
    {
        QList<QVariant> dataRow = dialog.getDataRow();
        _table->appendRow(dataRow);
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::setName(QString newText)
{
    QModelIndex currentItem = ui->tableView->currentIndex();
    int row = currentItem.row();

    QModelIndex nameItemProxy = _proxy->index(row, NAME_COLUMN);

    QModelIndex nameItemOriginal = _proxy->mapToSource(nameItemProxy);

    _table->setData(nameItemOriginal, newText);
}

MainWindow::~MainWindow()
{
    BookTable newOne;
    newOne.saveDataToFile("./settings_file.txt");
    delete ui;
}

void MainWindow::on_pushButtonRemoveRow_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty())
    {
        for (int i = selectedIndexes.size() - 1; i >= 0; --i)
        {
            int row = selectedIndexes.at(i).row();
            _table->removeRow(row, QModelIndex());
        }
    }
}


void MainWindow::on_BasketButton_clicked()
{
    QList<QVariant> books = _table->getCheckedBooks();
    double full = _table->getCheckedFullPrices();
    QList<QString> list;
    for (QVariantList::iterator iter = books.begin(); iter != books.end(); iter++)
    {
        QString str = iter->toString();
        list.append(str);
    }
    Basket booklist(0, QList<QString> (list), full);
    if (booklist.exec())
    {

    }
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QList<QVariant> rowData  = _table->getData().at(_proxy->mapToSource(index).row());
    Information info(0, rowData);
    info.setBookData(rowData);
    if (info.exec())
    {

    }
}

void MainWindow::on_lineEditSearch_textChanged(const QString &arg1)
{
    Proxy* model = qobject_cast<Proxy*>(ui->tableView->model());
    if (model)
    {
        QString searchString = ui->lineEditSearch->text();
        model->setSearchText(searchString);
    }
}
