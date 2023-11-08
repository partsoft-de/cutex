/***********************************************************************************************************************
**
** Copyright (C) 2016-2023 Partsoft UG (haftungsbeschränkt)
** Contact: https://www.partsoft.de/index.php/kontakt
**
** This file is part of cutex
**
** cutex is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
** version.
**
** cutex is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License along with cutex. If not, see
** http://www.gnu.org/licenses.
**
***********************************************************************************************************************/

#include "proxymodel.h"

ProxyModel::ProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

void ProxyModel::setFilter(int column, const QString &text)
{
    m_filters.insert(column, text);
    invalidateFilter();
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent);
    QAbstractItemModel *model = sourceModel();

    for (int n = 0; n < model->columnCount(); ++n) {
        if (m_filters.contains(n)) {
            QModelIndex index = model->index(sourceRow, n);
            QString value = index.data().toString();

            if (!value.contains(m_filters.value(n), Qt::CaseInsensitive))
                return false;
        }
    }

    return true;
}
