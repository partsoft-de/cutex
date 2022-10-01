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

#ifndef QXSWIPEBUTTON_H
#define QXSWIPEBUTTON_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Ein %QxSwipeButton repräsentiert eine Schaltfläche für die Navigationsleiste QxSwipeBar.

  Ein Objekt der Klasse %QxSwipeButton stellt eine einzelne Schaltfläche für die Navigationsleiste QxSwipeBar bereit.

  \sa QxSwipeBar
*/
class QxSwipeButton : public QLabel
{
    Q_OBJECT

public:
    QxSwipeButton(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual bool event(QEvent *event);

signals:
    void clicked();
};

} // namespace

#endif // QXSWIPEBUTTON_H
