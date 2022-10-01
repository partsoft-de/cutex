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

#ifndef QXTREEITEM_H
#define QXTREEITEM_H

#include "cutex.h"

namespace cutex {

class QxTreeItemModel;

/*!
  \brief %QxTreeItem stellt die Elemente für das Model QxTreeItemModel zur Verfügung.

  Ein Objekt der Klasse %QxTreeItem entspricht einem einzelnen Element des Models QxTreeItemModel. Einem Element können
  beliebig untergeordnete Elemente hinzugefügt werden, wodurch eine Baumstruktur für QTreeView realisiert werden kann.

  \sa QxTreeItemModel
*/
class QxTreeItem
{
    friend class QxTreeItemModel;

public:
    QxTreeItem(const QString &text = QString());
    virtual ~QxTreeItem();
    virtual QString text() const;
    void setText(const QString &text);
    virtual Qt::ItemFlags flags() const;
    QxTreeItemModel* model() const;
    void setModel(QxTreeItemModel *model);
    QxTreeItem* parent() const;
    bool hasChildren();
    QxTreeItem* child(int row) const;
    QList<QxTreeItem*> children() const;
    int row() const;
    int rowCount();
    void insertRow(int row, QxTreeItem *item);
    void appendRow(QxTreeItem *item);
    QxTreeItem* takeRow(int row);
    QModelIndex index() const;
    virtual void read(QDataStream &in);
    virtual void write(QDataStream &out);

protected:
    void emitDataChanged();

private:
    QString m_text;
    QxTreeItemModel *m_model;
    QxTreeItem *m_parentItem;
    QList<QxTreeItem*> m_childItems;

private:
    void swapChildren(int row1, int row2);
};

} // namespace

#endif // QXTREEITEM_H
