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

#include "qxfixpoint.h"

using namespace cutex;

const double QxFixPoint::DECIMALS = 5.0;

/*!
  Erzeugt eine neue Variable mit dem Wert 0,0.
*/
QxFixPoint::QxFixPoint()
{
    m_value = 0;
}

/*!
  Erzeugt eine neue Variable mit dem Wert <i>value</i>.
*/
QxFixPoint::QxFixPoint(double value)
{
    value *= pow(10, DECIMALS);
    m_value = static_cast<qint64>(value);
}

/*!
  Setzt die Variable auf den Wert <i>value</i>.
*/
void QxFixPoint::operator =(double value)
{
    value *= pow(10, DECIMALS);
    m_value = static_cast<qint64>(value);
}

/*!
  Gibt den Wert der Variablen zurück.
*/
QxFixPoint::operator double() const
{
    double value = static_cast<double>(m_value);
    value /= pow(10, DECIMALS);

    return value;
}

/*!
  Gibt den Wert der Variablen als Zeichenkette zurück.
*/
QString QxFixPoint::toString(int decimals) const
{
    double value = static_cast<double>(m_value);
    value /= pow(10, DECIMALS);

    return QLocale::system().toString(value, 'f', decimals);
}

/*!
  Addiert den Wert <i>value</i>.
*/
QxFixPoint& QxFixPoint::operator +=(const QxFixPoint &value)
{
    m_value += value.m_value;

    return *this;
}

/*!
  Addiert den Wert <i>value</i>.
*/
QxFixPoint QxFixPoint::operator +(const QxFixPoint &value)
{
    QxFixPoint fp;
    fp.m_value = m_value;

    return fp += value;
}

namespace cutex {

/*!
  Schreibt den Wert der Variablen <i>fp</i> in den Ausgabestream <i>out</i>.
*/
QDataStream& operator <<(QDataStream &out, const QxFixPoint &fp)
{
    out << fp.m_value;

    return out;
}

/*!
  Liest den Wert der Variablen <i>fp</i> aus dem Eingabestream <i>in</i>.
*/
QDataStream& operator >>(QDataStream &in, QxFixPoint &fp)
{
    in >> fp.m_value;

    return in;
}

} // namespace
