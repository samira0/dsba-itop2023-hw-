#include "proxy.h"

Proxy::Proxy(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    _minStars = 0;
    _maxStars = 5;
    _starsFilterEnabled = true;
}

void Proxy::setSearchText(const QString& searchText)
{
    _searchText = searchText;
    invalidateFilter();
}

void Proxy::setMinStars(int minStars)
{
    this->_minStars = minStars;
    invalidateFilter();
}

void Proxy::setMaxStars(int maxStars)
{
    this->_maxStars = maxStars;
    invalidateFilter();
}

bool Proxy::starsFitsFilter(QVariant dataStars) const
{
    if (_starsFilterEnabled)
    {
        return _minStars <= dataStars.toInt() && dataStars.toInt() <= _maxStars;
    }
    return true;
}

bool Proxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariant data0 = sourceModel()->data(index0);
    bool accepts0 = data0.toString().contains(filterRegularExpression());

    QModelIndex indexStars = sourceModel()->index(sourceRow, 10, sourceParent);
    QVariant dataStars = sourceModel()->data(indexStars);
    bool acceptsStars = starsFitsFilter(dataStars);
    if (_searchText.isEmpty())
        return accepts0 && acceptsStars;

    for (int i = 0; i < sourceModel()->columnCount(sourceParent); ++i)
    {
        QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
        QString data = sourceModel()->data(index).toString();
        if (data.contains(_searchText, Qt::CaseInsensitive))
            return accepts0 && acceptsStars;
    }

    return false;
}
