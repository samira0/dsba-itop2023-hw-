#include "booktable.h"
#include <QFile>
#include <QTextStream>

BookTable::BookTable(QObject* parent)
    : QAbstractTableModel(parent)
{
    _header.append("ID");
    _header.append("Title");
    _header.append("Category");
    _header.append("Price");
    _header.append("Price after tax");
    _header.append("Tax amount");
    _header.append("Availability");
    _header.append("Number of reviews");
    _header.append("Book description");
    _header.append("Image link");
    _header.append("Stars");
    _header.append("In Basket");
}

bool BookTable::saveDataToFile(const QString& path)
{
    QFile outputFile(path);
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }
    QTextStream outputStream(&outputFile);
    for (int i = 0; i < _header.size(); i++)
        outputStream << _header[i] << (i < _header.size() - 1 ? ';' : '\n');

    for (int i = 0; i < _data.size(); i++)
    {
        for (int j = 0; j < _data[i].size(); j++)
            outputStream << _data[i][j].toString() << (j < _data[i].size() - 1 ? ';' : '\n');
    }

    outputFile.close();
    return true;
}

QVariant BookTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == _header.size())
            return "Basket";
        else if (section >= 0 && section < _header.size())
            return _header[section];
    }
    return QVariant();
}

int BookTable::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;


    return _data.size();
}

int BookTable::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return _header.size() + 1;
}

QVariant BookTable::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int column = index.column();
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (index.column() == _header.size())
            return QVariant();
        return _data.at(row).at(column);
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else if (role == Qt::CheckStateRole && column == _header.size())
    {
        bool isChecked = _data[row].back() == "true";
        return isChecked ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool BookTable::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row();
    int column = index.column();
    if (index.isValid() && role == Qt::CheckStateRole && column == _header.size())
    {
        bool isChecked = _data[row].back() == "true";
        isChecked = !isChecked;
        _data[row].back() = isChecked ? "true" : "false";

        emit dataChanged(index, index, {role});
        emit dataChanged(index.sibling(row, _header.size()), index.sibling(row, _header.size()), {role});

        return true;
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        _data[row][column] = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags BookTable::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flags = QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

    if (index.column() == _header.size())
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}


bool BookTable::reloadDataFromFile(const QString& path)
{

    QList<QList<QVariant>> newData;

    QFile inputFile(path);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        QList<QString> items = line.split(";");
        for (int i = 0; i < items.size(); ++i)
        {
            QVariant value;
            if (i == 0 || i == 6 || i == 7)
            {
                value = items[i].toInt();
            }
            else
            {
                value = items[i];
            }

            dataRow.append(value);
        }
        newData.append(dataRow);
    }
    inputFile.close();

    beginResetModel();
    _data = newData;
    endResetModel();
    return true;
}

void BookTable::appendRow(const QList<QVariant>& newRow)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(newRow);
    endInsertRows();
}

bool BookTable::removeRow(int row, const QModelIndex &parent)
{
    if (row >= 0 && row < _data.size())
    {
        beginRemoveRows(parent, row, row);
        _data.removeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

QList<QList<QVariant>> BookTable::getData() const
{
    return _data;
}

QList<QVariant> BookTable::getCheckedBooks()
{
    QList<QVariant> checkedBooks;

    for (int i = 0; i < _data.size(); i++)
    {
        if (_data[i].back() == "true")
        {
            checkedBooks.append(_data[i][1]);
        }
    }
    return checkedBooks;
}

double BookTable::getCheckedFullPrices()
{
    double full = 0.0;

    for (int i = 0; i < _data.size(); i++)
    {
        if (_data[i].back() == "true")
        {
            full += _data[i][3].toDouble();
        }
    }
    return full;
}
