/***********************************************************************************************************************
**
** Copyright (C) 2016-2020 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXSQLTABLEVIEW_H
#define QXSQLTABLEVIEW_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSqlTableView stellt eine View für SQL-Modelle bereit.

  Die Klasse erweitert die Qt-Klasse QTableView um spezielle Methoden für die Zusammenarbeit mit SQL-Modellen. Außerdem
  verfügt die Klasse über ein internes QSortFilterProxyModel, wodurch der Verwender kein zusätzliches Model für die
  Sortierung vereinbaren muss.
*/
class QxSqlTableView : public QTableView
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(bool proxyEnabled READ isProxyEnabled WRITE setProxyEnabled)
    Q_PROPERTY(bool selectNewRecords READ selectNewRecords WRITE setSelectNewRecords)
    Q_PROPERTY(bool resizeColumnsEnabled READ isResizeColumnsEnabled WRITE setResizeColumnsEnabled)
    //! @endcond

public:
    QxSqlTableView(QWidget *parent = 0);
    void setSortingColumn(const QString &column, Qt::SortOrder order = Qt::AscendingOrder);
    void setColumnVisible(const QString &column, bool visible = true);
    bool isProxyEnabled() const;
    void setProxyEnabled(bool enabled);
    QSortFilterProxyModel* proxyModel();
    bool selectNewRecords() const;
    void setSelectNewRecords(bool select);
    bool isResizeColumnsEnabled() const;
    void setResizeColumnsEnabled(bool enabled);
    virtual void setModel(QAbstractItemModel *model);
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;

protected slots:
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);

private:
    bool m_proxy;
    bool m_selectNewRecords;
    bool m_resizeColumns;
    QSortFilterProxyModel m_proxyModel;

private:
    void updateConnections();
};

} // namespace

#endif // QXSQLTABLEVIEW_H
