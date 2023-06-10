#ifndef PROXY_H
#define PROXY_H

#include <QSortFilterProxyModel>

class Proxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit Proxy(QObject *parent = nullptr);

    void setMinStars(int minStars);
    void setMaxStars(int maxStars);
    bool starsFitsFilter(QVariant dataStars) const;
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    void setSearchText(const QString& searchText);

private:
    int _minStars;
    int _maxStars;
    bool _starsFilterEnabled;
    QString _searchText;

};

#endif // MYPROXY_H
