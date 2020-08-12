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

#include "qxwaitcursor.h"

using namespace cutex;

int QxWaitCursor::m_counter = 0;

/*!
  Blockiert alle Benutzereingaben und stellt den Mauszeiger als Sanduhr dar, bis die letzte Instanz der Klasse wieder
  freigegeben wurde.
*/
QxWaitCursor::QxWaitCursor()
{
    m_counter++;

    if (m_counter == 1)
        qApp->setOverrideCursor(QCursor(Qt::WaitCursor));
}

/*!
  Bei der Freigabe der letzten Instanz, wird die Blockade der Benutzereingaben wieder aufgehoben und der ursprüngliche
  Mauszeiger wiederhergestellt.
*/
QxWaitCursor::~QxWaitCursor()
{
    m_counter--;

    if (m_counter == 0)
        qApp->restoreOverrideCursor();
}
