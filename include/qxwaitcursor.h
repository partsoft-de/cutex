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

#ifndef QXWAITCURSOR_H
#define QXWAITCURSOR_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxWaitCursor stellt den Mauszeiger als Sanduhr dar.

  Beim Instanziieren eines Objekts der Klasse %QxWaitCursor werden alle Benutzerinteraktionen blockiert und der
  Mauszeiger als Sanduhr dargestellt. Sobald die letzte Instanz der Klasse freigegeben wurde, wird der ursprüngliche
  Zustand wiederhergestellt.
*/
class QxWaitCursor
{
public:
    QxWaitCursor();
    ~QxWaitCursor();

private:
    static int m_counter;
};

} // namespace

#endif // QXWAITCURSOR_H
