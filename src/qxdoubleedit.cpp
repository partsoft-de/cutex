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

#include "qxdoubleedit.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxDoubleEdit::QxDoubleEdit(QWidget *parent) : QLineEdit(parent)
{
    m_minimum = 0.0;
    m_maximum = 99.0;
    m_decimals = 2;
    m_validator = new QDoubleValidator(m_minimum, m_maximum, m_decimals, this);

    m_validator->setNotation(QDoubleValidator::StandardNotation);

    setValidator(m_validator);
    setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    setValue(0.0);
}

/*!
  Gibt die Anzahl der Nachkommastellen zurück.

  \sa setDecimals(int decimals) const
*/
int QxDoubleEdit::decimals() const
{
    return m_decimals;
}

/*!
  Setzt die Anzahl der Nachkommastellen auf den Wert <i>decimals</i>.

  \sa decimals() const
*/
void QxDoubleEdit::setDecimals(int decimals)
{
    if (decimals >= 0) {
        m_decimals = decimals;
        m_validator->setDecimals(m_decimals);
    }
}

/*!
  Gibt den kleinsten erlaubten Wert zurück.

  \sa setMinimum(double minimum)
*/
double QxDoubleEdit::minimum() const
{
    return m_minimum;
}

/*!
  Setzt den kleinsten erlaubten Wert auf <i>minimum</i>.

  \sa minimum() const
*/
void QxDoubleEdit::setMinimum(double minimum)
{
    m_minimum = minimum;
    m_validator->setRange(m_minimum, m_maximum);

    if (value() < m_minimum)
        setValue(m_minimum);
}

/*!
  Gibt den grössten erlaubten Wert zurück.

  \sa setMaximum(double maximum)
*/
double QxDoubleEdit::maximum() const
{
    return m_maximum;
}

/*!
  Setzt den grössten erlaubten Wert auf <i>maximum</i>.

  \sa maximum() const
*/
void QxDoubleEdit::setMaximum(double maximum)
{
    m_maximum = maximum;
    m_validator->setRange(m_minimum, m_maximum);

    if (value() > m_maximum)
        setValue(m_maximum);
}

/*!
  Gibt den aktuellen Wert zurück.

  \sa setValue(double value)
*/
double QxDoubleEdit::value() const
{
    return QLocale::system().toDouble(text());
}

/*!
  Setzt den aktuellen Wert auf <i>value</i>.

  \sa value() const
*/
void QxDoubleEdit::setValue(double value)
{
    if (value >= m_minimum && value <= m_maximum)
        setText(QLocale::system().toString(value));
}

void QxDoubleEdit::focusOutEvent(QFocusEvent *event)
{
    setValue(value());

    QLineEdit::focusOutEvent(event);
}
