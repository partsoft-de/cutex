/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#include "qxsqltableview.h"
#include "qxsqlquerymodel.h"

using namespace cutex;

/*!
  Erzeugt eine neue Instanz mit dem Elternobjekt <i>parent</i>.
*/
QxSqlTableView::QxSqlTableView(QWidget *parent) : QTableView(parent)
{
    m_proxy = false;
    m_selectNewRecords = false;
    m_resizeColumns = false;

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    verticalHeader()->hide();
}

/*!
  Sortiert die Daten nach der Spalte <i>column</i> und der Sortierfolge <i>order</i>.
*/
void QxSqlTableView::setSortingColumn(const QString &column, Qt::SortOrder order)
{
    QAbstractItemModel *abstractModel = model();

    if (!abstractModel)
        return;

    if (CLASSNAME(abstractModel) == "QSortFilterProxyModel")
        abstractModel = qobject_cast<QSortFilterProxyModel*>(abstractModel)->sourceModel();

    if (QSqlQueryModel *queryModel = qobject_cast<QSqlQueryModel*>(abstractModel))
        horizontalHeader()->setSortIndicator(queryModel->record().indexOf(column), order);

    if (QxSqlQueryModel *queryModel = qobject_cast<QxSqlQueryModel*>(abstractModel))
        horizontalHeader()->setSortIndicator(queryModel->record().indexOf(column), order);
}

/*!
  Ändert die Sichtbarkeit der Spalte <i>column</i> auf den Wert <i>visible</i>.
*/
void QxSqlTableView::setColumnVisible(const QString &column, bool visible)
{
    QAbstractItemModel *abstractModel = model();

    if (!abstractModel)
        return;

    if (CLASSNAME(abstractModel) == "QSortFilterProxyModel")
        abstractModel = qobject_cast<QSortFilterProxyModel*>(abstractModel)->sourceModel();

    if (QSqlQueryModel *queryModel = qobject_cast<QSqlQueryModel*>(abstractModel))
        setColumnHidden(queryModel->record().indexOf(column), !visible);

    if (QxSqlQueryModel *queryModel = qobject_cast<QxSqlQueryModel*>(abstractModel))
        setColumnHidden(queryModel->record().indexOf(column), !visible);
}

/*!
  Gibt true zurück, wenn das interne QSortFilterProxyModel aktiviert ist.

  \sa setProxyEnabled(bool enabled)
*/
bool QxSqlTableView::isProxyEnabled() const
{
    return m_proxy;
}

/*!
  Aktiviert, bzw. deaktiviert das interne QSortFilterProxyModel.

  \sa isProxyEnabled()
*/
void QxSqlTableView::setProxyEnabled(bool enabled)
{
    m_proxy = enabled;

    if (model()) {
        if (m_proxy) {
            QTableView::setModel(&m_proxyModel);
        } else {
            QTableView::setModel(model());
        }
    }
}

/*!
  Gibt einen Zeiger auf das interne QSortFilterProxyModel zurück.
*/

QSortFilterProxyModel* QxSqlTableView::proxyModel()
{
    return &m_proxyModel;
}

/*!
  Gibt true zurück, wenn neue Datensätze automatisch ausgewählt werden.

  \sa setSelectNewRecords(bool select)
*/
bool QxSqlTableView::selectNewRecords() const
{
    return m_selectNewRecords;
}

/*!
  Legt fest, ob neue Datensätze automatisch ausgewählt werden.

  \sa selectNewRecords()
*/
void QxSqlTableView::setSelectNewRecords(bool select)
{
    m_selectNewRecords = select;
}

/*!
  Gibt true zurück, wenn die Spaltenbreiten bei Änderungen automatisch angepasst werden.

  \sa setResizeColumnsEnabled(bool enabled)
*/
bool QxSqlTableView::isResizeColumnsEnabled() const
{
    return m_resizeColumns;
}

/*!
  Legt fest, ob die Spaltenbreiten bei Änderungen automatisch angepasst werden.

  \sa isResizeColumnsEnabled()
*/
void QxSqlTableView::setResizeColumnsEnabled(bool enabled)
{
    m_resizeColumns = enabled;
    updateConnections();
}

/*!
  Setzt das Model für die View.
*/
void QxSqlTableView::setModel(QAbstractItemModel *model)
{
    m_proxyModel.setSourceModel(model);

    if (m_proxy) {
        QTableView::setModel(&m_proxyModel);
    } else {
        QTableView::setModel(model);
    }
    updateConnections();
}

/*!
  Ruft mapToSource() des internen QSortFilterProxyModel auf.

  \sa mapFromSource(const QModelIndex &sourceIndex)
*/
QModelIndex QxSqlTableView::mapToSource(const QModelIndex &proxyIndex) const
{
    QModelIndex index;

    if (m_proxy) {
        index = m_proxyModel.mapToSource(proxyIndex);
    } else {
        index = proxyIndex;
    }

    return index;
}

/*!
  Ruft mapFromSource() des internen QSortFilterProxyModel auf.

  \sa mapToSource(const QModelIndex &proxyIndex)
*/
QModelIndex QxSqlTableView::mapFromSource(const QModelIndex &sourceIndex) const
{
    QModelIndex index;

    if (m_proxy) {
        index = m_proxyModel.mapFromSource(sourceIndex);
    } else {
        index = sourceIndex;
    }

    return index;
}

/*!
  Wird aufgerufen wenn ein neuer Datensatz eingefügt wurde.
*/
void QxSqlTableView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    QTableView::rowsInserted(parent, start, end);

    if (m_selectNewRecords)
        selectRow(start);
}

void QxSqlTableView::updateConnections()
{
    if (model()) {
        if (m_resizeColumns) {
            connect(model(), SIGNAL(modelReset()), this, SLOT(resizeColumnsToContents()));
            connect(model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this,
                SLOT(resizeColumnsToContents()));
            connect(model(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(resizeColumnsToContents()));
        } else {
            disconnect(model(), SIGNAL(modelReset()), this, SLOT(resizeColumnsToContents()));
            disconnect(model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this,
                SLOT(resizeColumnsToContents()));
            disconnect(model(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(resizeColumnsToContents()));
        }
    }
}
