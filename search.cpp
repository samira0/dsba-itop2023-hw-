#include "search.h"
#include "ui_search.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStringList>
#include <QLineEdit>
#include <QCompleter>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QString>

//bool Search::pointerFromFile(const QString& path)
//{
//    QList<QList<QVariant>> newData;

//    QFile inputFile(path);
//    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
//    {
//        return false;
//    }
//    QTextStream inputStream(&inputFile);

//    QString firstline = inputStream.readLine();

//    while (!inputStream.atEnd())
//    {
//        QString line = inputStream.readLine();

//        QList<QVariant> dataRow;
//        QList<QString> items = line.split(";");
//        for (int i = 0; i < items.size(); ++i)
//        {
//            QVariant value;
//            if (i == 0 || i == 6 || i == 7)
//            {
//                value = items[i].toInt();
//            }
//            else
//            {
//                value = items[i];
//            }

//            dataRow.append(value);
//        }
//        newData.append(dataRow);
//    }
//    inputFile.close();
//    return true;
//}

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);

    QHBoxLayout *layout = new QHBoxLayout();

    QStringList wordList;

    QFile f(":/kojd/Book_Dataset_1.csv");
    if (f.open(QIODevice::ReadOnly))
    {
        QString data;
        data = f.readAll();
        wordList = data.split(';');

        f.close();
    }

    QLabel *label = new QLabel("Select");
    QLineEdit *lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    QCompleter *completer = new QCompleter(wordList);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    lineEdit->setCompleter(completer);

    layout->addWidget(label);
    layout->addWidget(lineEdit);

    this->setLayout(layout);
    this->show();
}

Search::~Search()
{
    delete ui;
}
