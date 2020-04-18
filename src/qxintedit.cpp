/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#include "qxintedit.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxIntEdit::QxIntEdit(QWidget *parent) : QLineEdit(parent)
{
    m_minimum = 0;
    m_maximum = 99;
    m_validator = new QIntValidator(m_minimum, m_maximum, this);

    setValidator(m_validator);
    setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    setValue(0);
}

/*!
  Gibt den kleinsten erlaubten Wert zurück.

  \sa setMinimum(int minimum)
*/
int QxIntEdit::minimum() const
{
    return m_minimum;
}

/*!
  Setzt den kleinsten erlaubten Wert auf <i>minimum</i>.

  \sa minimum() const
*/
void QxIntEdit::setMinimum(int minimum)
{
    m_minimum = minimum;
    m_validator->setRange(m_minimum, m_maximum);

    if (value() < m_minimum)
        setValue(m_minimum);
}

/*!
  Gibt den grössten erlaubten Wert zurück.

  \sa setMaximum(int maximum)
*/
int QxIntEdit::maximum() const
{
    return m_maximum;
}

/*!
  Setzt den grössten erlaubten Wert auf <i>maximum</i>.

  \sa maximum() const
*/
void QxIntEdit::setMaximum(int maximum)
{
    m_maximum = maximum;
    m_validator->setRange(m_minimum, m_maximum);

    if (value() > m_maximum)
        setValue(m_maximum);
}

/*!
  Gibt den aktuellen Wert zurück.

  \sa setValue(int value)
*/
int QxIntEdit::value() const
{
    return text().toInt();
}

/*!
  Setzt den aktuellen Wert auf <i>value</i>.

  \sa value() const
*/
void QxIntEdit::setValue(int value)
{
    if (value >= m_minimum && value <= m_maximum)
        setText(QString::number(value));
}

void QxIntEdit::focusOutEvent(QFocusEvent *event)
{
    setValue(value());

    QLineEdit::focusOutEvent(event);
}
