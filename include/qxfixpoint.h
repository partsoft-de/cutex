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

#ifndef QXFIXPOINT_H
#define QXFIXPOINT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief %QxFixPoint ist ein Datentyp zum Speichern von Festkommazahlen.

  Mit Variablen vom Typ %QxFixPoint können Festkommazahlen gespeichert werden. Diese haben im Vergleich zu
  Gleitkommazahlen den Vorteil, das bei Berechnungen keine Differenzen durch Rundungsfehler auftreten.
*/
class QxFixPoint
{
public:
    QxFixPoint();
    QxFixPoint(double value);
    void operator =(double value);
    operator double() const;
    QString toString(int decimals = DECIMALS) const;
    QxFixPoint& operator +=(const QxFixPoint &value);
    QxFixPoint operator +(const QxFixPoint &value);
    friend QDataStream& operator <<(QDataStream &out, const QxFixPoint &fp);
    friend QDataStream& operator >>(QDataStream &in, QxFixPoint &fp);

private:
    static const double DECIMALS;
    qint64 m_value;
};

} // namespace

#endif // QXFIXPOINT_H
