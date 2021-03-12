/***********************************************************************************************************************
**
** Copyright (C) 2016-2021 Partsoft UG (haftungsbeschränkt)
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

#include "qxtreeitem.h"
#include "qxtreeitemmodel.h"

using namespace cutex;

/*!
  Erzeugt ein neues Element mit dem Text <i>text</i>.
*/
QxTreeItem::QxTreeItem(const QString &text)
{
    m_text = text;
    m_model = 0;
    m_parentItem = 0;
}

/*!
  Der Destruktor löscht alle untergeordneten Elemente.
*/
QxTreeItem::~QxTreeItem()
{
    if (m_parentItem)
        m_parentItem->takeRow(row());

    qDeleteAll(m_childItems);
}

/*!
  Gibt den Text des Elements zurück.

  \sa setText(const QString &text)
*/
QString QxTreeItem::text() const
{
    return m_text;
}

/*!
  Setzt den Text des Elements auf den Wert <i>text</i>.

  \sa text()
*/
void QxTreeItem::setText(const QString &text)
{
    m_text = text;
    emitDataChanged();
}

/*!
  Gibt die erlaubten Aktionen zum Element zurück.
*/
Qt::ItemFlags QxTreeItem::flags() const
{
    return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
}

/*!
  Gibt das mit dem Element verbundene Model zurück.

  \sa setModel(QxTreeItemModel *model)
*/
QxTreeItemModel* QxTreeItem::model() const
{
    return m_model;
}

/*!
  Verbindet das Model <i>model</i> mit dem Element und allen untergeordneten Elementen.

  \sa model()
*/
void QxTreeItem::setModel(QxTreeItemModel *model)
{
    m_model = model;
    for (QxTreeItem *childItem : children())
        childItem->setModel(model);
}

/*!
  Gibt das übergeordnete Element zurück.
*/
QxTreeItem* QxTreeItem::parent() const
{
    return m_parentItem;
}

/*!
  Gibt true zurück, wenn das Element untergeordnete Elemente hat.
*/
bool QxTreeItem::hasChildren()
{
    return !m_childItems.isEmpty();
}

/*!
  Gibt das untergeordnete Element an der Position <i>row</i> zurück.
*/
QxTreeItem* QxTreeItem::child(int row) const
{
    return m_childItems.value(row);
}

/*!
  Gibt eine Liste aller untergeordneten Elemente zurück.
*/
QList<QxTreeItem*> QxTreeItem::children() const
{
    return m_childItems;
}

/*!
  Gibt die Position des Elements zurück.
*/
int QxTreeItem::row() const
{
    int row = 0;

    if (m_parentItem)
        row = m_parentItem->m_childItems.indexOf(const_cast<QxTreeItem*>(this));

    return row;
}

/*!
  Gibt die Anzahl der untergeordneten Elemente zurück.
*/
int QxTreeItem::rowCount()
{
    return m_childItems.count();
}

/*!
  Fügt das Element <i>item</i> an der Position <i>row</i> ein.

  \sa appendRow(QxTreeItem *item)
*/
void QxTreeItem::insertRow(int row, QxTreeItem *item)
{
    if (row < 0 || row > rowCount())
        return;

    if (m_model)
        m_model->beginInsertRows(index(), row, row);

    item->m_parentItem = this;
    item->setModel(m_model);
    m_childItems.insert(row, item);

    if (m_model)
        m_model->endInsertRows();
}

/*!
  Fügt das Element <i>item</i> ein.

  \sa insertRow(int row, QxTreeItem *item)
*/
void QxTreeItem::appendRow(QxTreeItem *item)
{
    insertRow(rowCount(), item);
}

/*!
  Entfernt das untergeordnete Element an Position <i>row</i>.
*/
QxTreeItem* QxTreeItem::takeRow(int row)
{
    QxTreeItem *item = child(row);

    if (item) {
        item->m_parentItem = 0;
        m_childItems.takeAt(row);
    }

    return item;
}

/*!
  Gibt den Index zum Element zurück.
*/
QModelIndex QxTreeItem::index() const
{
    if (m_model)
        return m_model->indexFromItem(this);

    return QModelIndex();
}

/*!
  Liest das Element aus dem Eingabestrom <i>in</i>.

  \sa write(QDataStream &out)
*/
void QxTreeItem::read(QDataStream &in)
{
    int count = 0;

    in >> m_text >> count;
    for (int row = 0; row < count; row++) {
        QxTreeItem *childItem = new QxTreeItem();
        childItem->read(in);
        appendRow(childItem);
    }
}

/*!
  Schreibt das Element in den Ausgabestrom <i>out</i>.

  \sa read(QDataStream &in)
*/
void QxTreeItem::write(QDataStream &out)
{
    out << m_text << quint32(rowCount());
    for (QxTreeItem *childItem : children())
        childItem->write(out);
}

/*!
  Teilt dem Model mit das Daten geändert wurden.
*/
void QxTreeItem::emitDataChanged()
{
    if (!m_model)
        return;

    QModelIndex index = m_model->indexFromItem(this);
    emit m_model->dataChanged(index, index);
}

void QxTreeItem::swapChildren(int row1, int row2)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,13,0)
    m_childItems.swapItemsAt(row1, row2);
#else
    m_childItems.swap(row1, row2);
#endif
}
