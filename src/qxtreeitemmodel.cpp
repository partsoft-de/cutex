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

#include "qxtreeitemmodel.h"
#include "qxtreeitem.h"

using namespace cutex;

const QString QxTreeItemModel::MIMETYPE = "application/cutex/qxtreeitemmodel";

/*!
  Erzeugt ein neues Model mit dem Elternobjekt <i>parent</i>.
*/
QxTreeItemModel::QxTreeItemModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_rootItem = new QxTreeItem;
    m_rootItem->setModel(this);
}

QxTreeItemModel::~QxTreeItemModel()
{
    delete m_rootItem;
}

/*!
  Gibt den Index zur Zeile <i>row</i> und dem Elternelement <i>parent</i> zurück.
*/
QModelIndex QxTreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QxTreeItem *parentItem = nullptr;
    if (parent.isValid()) {
        parentItem = static_cast<QxTreeItem*>(parent.internalPointer());
    } else {
        parentItem = m_rootItem;
    }

    QxTreeItem *item = parentItem->child(row);
    if (item)
        return createIndex(row, column, item);

    return QModelIndex();
}

/*!
  Gibt den Index des Elternelements von <i>index</i> zurück.
*/
QModelIndex QxTreeItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QxTreeItem *item = static_cast<QxTreeItem*>(index.internalPointer());
    QxTreeItem *parentItem = item->parent();

    if (parentItem != m_rootItem)
        return createIndex(parentItem->row(), 0, parentItem);

    return QModelIndex();
}

/*!
  Gibt die Anzahl der untergeordneten Elemente von <i>parent</i> zurück.
*/
int	QxTreeItemModel::rowCount(const QModelIndex &parent) const
{
    QxTreeItem *parentItem = nullptr;

    if (parent.isValid()) {
        parentItem = static_cast<QxTreeItem*>(parent.internalPointer());
    } else {
        parentItem = m_rootItem;
    }

    return parentItem->rowCount();
}

/*!
  Gibt die Anzahl der Spalten von <i>parent</i> zurück.
*/
int	QxTreeItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

/*!
  Gibt die Daten zum Element <i>index</i> und der Rolle <i>role</i> zurück.
*/
QVariant QxTreeItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QxTreeItem *item = itemFromIndex(index);

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return item->text();

    return QVariant();
}

/*!
  Gibt die ItemFlags zum Element <i>index</i> zurück.
*/
Qt::ItemFlags QxTreeItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsDropEnabled;

    QxTreeItem *item = itemFromIndex(index);

    return item->flags();
}

/*!
  Gibt das Root-Element zurück.
*/
QxTreeItem* QxTreeItemModel::invisibleRootItem() const
{
    return m_rootItem;
}

/*!
  Gibt das Element zum Index <i>index</i> zurück.

  \sa indexFromItem(const QxTreeItem *item)
*/
QxTreeItem* QxTreeItemModel::itemFromIndex(const QModelIndex &index) const
{
    QxTreeItem *item = m_rootItem;

    if (index.isValid())
        item = static_cast<QxTreeItem*>(index.internalPointer());

    return item;
}

/*!
  Gibt den Index zum Element <i>item</i> zurück.

  \sa itemFromIndex(const QModelIndex &index)
*/
QModelIndex QxTreeItemModel::indexFromItem(const QxTreeItem *item) const
{
    int row = item->row();
    QxTreeItem *parentItem = item->parent();

    if (parentItem)
        return index(row, 0, indexFromItem(parentItem));

    return QModelIndex();
}

/*!
  Fügt das Element <i>item</i> an der Position <i>row</i> ein.

  \sa appendRow(QxTreeItem *item)
*/
void QxTreeItemModel::insertRow(int row, QxTreeItem *item)
{
    m_rootItem->insertRow(row, item);
}

/*!
  Fügt das Element <i>item</i> ein.

  \sa insertRow(int row, QxTreeItem *item)
*/
void QxTreeItemModel::appendRow(QxTreeItem *item)
{
    m_rootItem->appendRow(item);
}

/*!
  Entfernt <i>count</i> untergeordnete Elemente ab der Zeile <i>row</i> des Elements <i>parent</i>.
*/
bool QxTreeItemModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QxTreeItem *parentItem = nullptr;

    if (parent.isValid()) {
        parentItem = itemFromIndex(parent);
    } else {
        parentItem = m_rootItem;
    }

    if (row < 0 || row + count > parentItem->rowCount())
        return false;

    beginRemoveRows(parent, row, row + count);
    for (int n = row; n < row + count; n++)
        parentItem->takeRow(n);
    endRemoveRows();

    return true;
}

/*!
  Setzt alle Daten des Models zurück.
*/
void QxTreeItemModel::clear()
{
    beginResetModel();
    qDeleteAll(m_rootItem->children());
    endResetModel();
}

/*!
  Gibt true zurück, wenn das Element <i>index</i> nach oben verschoben werden kann.
*/
bool QxTreeItemModel::canMoveUp(const QModelIndex &index) const
{
    bool result = false;
    QxTreeItem *item = itemFromIndex(index);

    if (item) {
        int row = item->row();
        result = row > 0;
    }

    return result;
}

/*!
  Gibt true zurück, wenn das Element <i>index</i> nach unten verschoben werden kann.
*/
bool QxTreeItemModel::canMoveDown(const QModelIndex &index) const
{
    bool result = false;
    QxTreeItem *item = itemFromIndex(index);

    if (item) {
        int row = item->row();
        result = row < (rowCount(parent(index)) - 1);
    }

    return result;
}

/*!
  Gibt true zurück, wenn das Element <i>index</i> eine Ebene höher verschoben werden kann.
*/
bool QxTreeItemModel::canPromote(const QModelIndex &index) const
{
    return (parent(index).isValid());
}

/*!
  Gibt true zurück, wenn das Element <i>index</i> eine Ebene tiefer verschoben werden kann.
*/
bool QxTreeItemModel::canDemote(const QModelIndex &index) const
{
    bool result = false;
    QxTreeItem *item = itemFromIndex(index);

    if (item)
        result = item->row() > 0;

    return result;
}

/*!
  Verschiebt das Element <i>index</i> eine Position nach oben.
*/
QModelIndex QxTreeItemModel::moveUp(const QModelIndex &index)
{
    if (!canMoveUp(index))
        return QModelIndex();

    int row = index.row();
    QxTreeItem *item = itemFromIndex(index);
    QxTreeItem *parentItem = item->parent();

    beginMoveRows(index.parent(), row, row, index.parent(), row - 1);
    parentItem->swapChildren(row, row - 1);
    endMoveRows();

    return indexFromItem(item);
}

/*!
  Verschiebt das Element <i>index</i> eine Position nach unten.
*/
QModelIndex QxTreeItemModel::moveDown(const QModelIndex &index)
{
    if (!canMoveDown(index))
        return QModelIndex();

    int row = index.row();
    QxTreeItem *item = itemFromIndex(index);
    QxTreeItem *parentItem = item->parent();

    beginMoveRows(index.parent(), row, row, index.parent(), row + 2);
    parentItem->swapChildren(row, row + 1);
    endMoveRows();

    return indexFromItem(item);
}

/*!
  Verschiebt das Element <i>index</i> eine Ebene höher.
*/
QModelIndex QxTreeItemModel::promote(const QModelIndex &index)
{
    if (!canPromote(index))
        return QModelIndex();

    int row = index.row();
    QxTreeItem *item = itemFromIndex(index);
    QxTreeItem *parentItem = item->parent();
    QxTreeItem *grandParentItem = parentItem->parent();
    QModelIndex grandParent = indexFromItem(grandParentItem);

    beginMoveRows(index.parent(), row, row, grandParent, grandParentItem->rowCount());
    grandParentItem->appendRow(item);
    parentItem->takeRow(row);
    item->m_parentItem = grandParentItem;
    endMoveRows();

    return indexFromItem(item);
}

/*!
  Verschiebt das Element <i>index</i> eine Ebene tiefer.
*/
QModelIndex QxTreeItemModel::demote(const QModelIndex &index)
{
    if (!canDemote(index))
        return QModelIndex();

    int row = index.row();
    QxTreeItem *item = itemFromIndex(index);
    QxTreeItem *parentItem = item->parent();
    QxTreeItem *siblingItem = parentItem->child(row - 1);
    QModelIndex sibling = indexFromItem(siblingItem);

    beginMoveRows(index.parent(), row, row, sibling, siblingItem->rowCount());
    siblingItem->appendRow(item);
    parentItem->takeRow(row);
    item->m_parentItem = siblingItem;
    endMoveRows();

    return indexFromItem(item);
}

/*!
  Ermittelt welche Drag-Operationen das Model unterstützt.
*/
Qt::DropActions	QxTreeItemModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

/*!
  Ermittelt welche Drop-Operationen das Model unterstützt.
*/
Qt::DropActions	QxTreeItemModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

/*!
  Ermittelt welche MIME-Typen das Model unterstützt.
*/
QStringList	QxTreeItemModel::mimeTypes() const
{
    return QStringList() << QxTreeItemModel::MIMETYPE;
}

/*!
  Erzeugt das Datenobjekt für eine Drag&Drop-Operation.
*/
QMimeData* QxTreeItemModel::mimeData(const QModelIndexList &indexes) const
{
    if (indexes.count() != 1)
        return nullptr;

    QxTreeItem *item = itemFromIndex(indexes.at(0));

    if (item) {
        QMimeData *data = new QMimeData;
        QByteArray array;
        QBuffer buffer(&array);
        buffer.open(QBuffer::WriteOnly);
        QDataStream out(&buffer);
        item->write(out);
        data->setData(QxTreeItemModel::MIMETYPE, array);
        return data;
    }

    return nullptr;
}

/*!
  Fügt die Daten <i>data</i> der Drag&Drop-Operation <i>action</i> ein.
*/
bool QxTreeItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
    const QModelIndex &parent)
{
    Q_UNUSED(column);

    if (action == Qt::IgnoreAction)
        return true;

    if (action != Qt::MoveAction || !data || !data->hasFormat(QxTreeItemModel::MIMETYPE))
        return false;

    QxTreeItem *parentItem = itemFromIndex(parent);

    if (parentItem) {
        if (row == -1)
            row = parentItem->rowCount();

        QxTreeItem *item = new QxTreeItem();
        QByteArray array = data->data(QxTreeItemModel::MIMETYPE);
        QBuffer buffer(&array);
        buffer.open(QBuffer::ReadOnly);
        QDataStream in(&buffer);
        item->read(in);
        parentItem->insertRow(row, item);
        return true;
    }

    return false;
}
