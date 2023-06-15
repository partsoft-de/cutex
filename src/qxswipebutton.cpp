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

#include "qxswipebutton.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxSwipeButton::QxSwipeButton(QWidget *parent) : QLabel(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    setAttribute(Qt::WA_AcceptTouchEvents, true);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void QxSwipeButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit clicked();
}

bool QxSwipeButton::event(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        emit clicked();
        return true;
    }

    return QWidget::event(event);
}
