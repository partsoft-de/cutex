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

#include "qxdateedit.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxDateEdit::QxDateEdit(QWidget *parent) : QDateEdit(parent)
{
    m_emptyDateEnabled = false;
    m_valid = true;

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(focusChanged(QWidget*,QWidget*)));
}

/*!
  Gibt true zurück, wenn leere Datumswerte erlaubt sind.

  \sa setEmptyDateEnabled(bool enabled)
*/
bool QxDateEdit::isEmptyDateEnabled() const
{
    return m_emptyDateEnabled;
}

/*!
  Ändert die Einstellung ob leere Datumswerte erlaubt sind auf den Wert <i>enabled</i>.

  \sa isEmptyDateEnabled() const
*/
void QxDateEdit::setEmptyDateEnabled(bool enabled)
{
    m_emptyDateEnabled = enabled;
}

/*!
  Gibt das aktuelle Datum zurück.

  \sa setDate(const QDate &date)
*/
QDate QxDateEdit::date() const
{
    QDate date;

    if (m_valid)
        date = QDateEdit::date();

    return date;
}

/*!
  Ändert das aktuelle Datum auf den Wert <i>date</i>.

  \sa date() const
*/
void QxDateEdit::setDate(const QDate &date)
{
    bool valid = m_valid;

    if (date.isValid() && date.toJulianDay() > 0) {
        QDateEdit::setDate(date);
        m_valid = true;

        if (!valid) {
            lineEdit()->setSelection(0, 0);
            emit dateChanged(date);
        }
    } else if (m_emptyDateEnabled) {
        lineEdit()->setText(QString());
        m_valid = false;
        emit dateChanged(QDate());
    }
}

/*!
  Wird aufgerufen wenn eine Taste gedrückt wurde.
*/
void QxDateEdit::keyPressEvent(QKeyEvent *event)
{
    if (m_emptyDateEnabled) {
        int key = event->key();

        if (!m_valid) {
            if (key >= Qt::Key_0 && key <= Qt::Key_9) {
                setDate(QDateEdit::date());
            } else if (key == Qt::Key_Tab || key == Qt::Key_Backtab) {
                QAbstractSpinBox::keyPressEvent(event);
                return;
            }
        }

        if (key == Qt::Key_Backspace) {
            setDate(QDate());
            return;
        }
    }

    QDateEdit::keyPressEvent(event);
}

void QxDateEdit::focusChanged(QWidget *old, QWidget *now)
{
    Q_UNUSED(old);
    Q_UNUSED(now);

    if (!m_valid)
        lineEdit()->setText(QString());
}
