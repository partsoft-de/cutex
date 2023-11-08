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

#ifndef QXFILTERHEADERVIEW_H
#define QXFILTERHEADERVIEW_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxFilterHeaderView stellt eine Suchleiste für Views zur Verfügung.

  Die Klasse %QxFilterHeaderView stellt einen horizontalen Header mit einer Suchleiste für Views bereit. Für jede Spalte
  kann ein Suchbegriff eingegeben werden. Das Projekt filterheader (im Ordner samples) ist ein Beispiel zur Verwendung.
*/
class QxFilterHeaderView : public QHeaderView
{
    Q_OBJECT

public:
    QxFilterHeaderView(QAbstractItemView *view);
    virtual QSize sizeHint() const;

protected:
    virtual void changeEvent(QEvent *event);
    virtual bool eventFilter(QObject *object, QEvent *event);

protected slots:
    virtual void updateGeometries();

private:
    QVector<QLineEdit*> m_filters;

private:
    void updateFilters();

private slots:
    void createFilters();
    void adjustFilters() const;
    void filterChanged();

signals:
    void filterChanged(int index, const QString &text);
};

} // namespace

#endif // QXFILTERHEADERVIEW_H
