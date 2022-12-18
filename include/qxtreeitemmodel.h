/***********************************************************************************************************************
**
** Copyright (C) 2016-2022 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXTREEITEMMODEL_H
#define QXTREEITEMMODEL_H

#include "cutex.h"

namespace cutex {

class QxTreeItem;

/*!
  \brief Die Klasse %QxTreeItemModel stellt ein Model zur Implementierung von Baumstrukturen bereit.

  %QxTreeItemModel ist ein Model zur Realisierung von Baumstrukturen und arbeitet optimal mit dem Steuerelement
  QTreeView zusammen. Die Klasse stellt alle wichtigen Funktionen, einschließlich Drag&Drop-Unterstützung, bereit.

  \sa QxTreeItem
*/
class QxTreeItemModel : public QAbstractItemModel
{
    Q_OBJECT

    friend class QxTreeItem;

public:
    QxTreeItemModel(QObject *parent = nullptr);
    ~QxTreeItemModel();
    virtual QModelIndex	index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex &index) const;
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    QxTreeItem* invisibleRootItem() const;
    QxTreeItem* itemFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromItem(const QxTreeItem *item) const;
    void insertRow(int row, QxTreeItem *item);
    void appendRow(QxTreeItem *item);
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual void clear();
    bool canMoveUp(const QModelIndex &index) const;
    bool canMoveDown(const QModelIndex &index) const;
    bool canPromote(const QModelIndex &index) const;
    bool canDemote(const QModelIndex &index) const;
    QModelIndex moveUp(const QModelIndex &index);
    QModelIndex moveDown(const QModelIndex &index);
    QModelIndex promote(const QModelIndex &index);
    QModelIndex demote(const QModelIndex &index);
    virtual Qt::DropActions	supportedDragActions() const;
    virtual Qt::DropActions	supportedDropActions() const;
    virtual QStringList	mimeTypes() const;
    virtual QMimeData* mimeData(const QModelIndexList &indexes) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
        const QModelIndex &parent);

private:
    static const QString MIMETYPE;
    QxTreeItem *m_rootItem;
};

} // namespace

#endif // QXTREEITEMMODEL_H
