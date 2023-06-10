#ifndef BOOKTABLE_H
#define BOOKTABLE_H

#include <QAbstractTableModel>

class BookTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BookTable(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool reloadDataFromFile(const QString& path);
    bool saveDataToFile(const QString& path);

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void appendRow(const QList<QVariant>& newRow);
    bool removeRow(int row, const QModelIndex &parent);
    QList<QList<QVariant>> getData() const;
    QVariant getStatement() const;
    QList<QVariant> getCheckedBooks();
    double getCheckedFullPrices();

private:

    QList<QList<QVariant>> _data;
    QList<QString> _header;
};


#endif // BOOKTABLE_H
