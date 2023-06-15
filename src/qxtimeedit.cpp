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

#include "qxtimeedit.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxTimeEdit::QxTimeEdit(QWidget *parent) : QTimeEdit(parent)
{
    m_emptyTimeEnabled = false;
    m_valid = true;

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(focusChanged(QWidget*,QWidget*)));
}

/*!
  Gibt true zurück, wenn eine leere Uhrzeit erlaubt ist.

  \sa setEmptyTimeEnabled(bool enabled)
*/
bool QxTimeEdit::isEmptyTimeEnabled() const
{
    return m_emptyTimeEnabled;
}

/*!
  Ändert die Einstellung ob eine leere Uhrzeit erlaubt ist auf den Wert <i>enabled</i>.

  \sa isEmptyTimeEnabled() const
*/
void QxTimeEdit::setEmptyTimeEnabled(bool enabled)
{
    m_emptyTimeEnabled = enabled;
}

/*!
  Gibt die aktuelle Uhrzeit zurück.

  \sa setTime(const QTime &time)
*/
QTime QxTimeEdit::time() const
{
    QTime time;

    if (m_valid)
        time = QTimeEdit::time();

    return time;
}

/*!
  Ändert die aktuelle Uhrzeit auf den Wert <i>time</i>.

  \sa time() const
*/
void QxTimeEdit::setTime(const QTime &time)
{
    bool valid = m_valid;

    if (time.isValid()) {
        QTimeEdit::setTime(time);
        m_valid = true;

        if (!valid) {
            lineEdit()->setSelection(0, 0);
            emit timeChanged(time);
        }
    } else if (m_emptyTimeEnabled) {
        lineEdit()->setText(QString());
        m_valid = false;
        emit timeChanged(QTime());
    }
}

/*!
  Wird aufgerufen wenn eine Taste gedrückt wurde.
*/
void QxTimeEdit::keyPressEvent(QKeyEvent *event)
{
    if (m_emptyTimeEnabled) {
        int key = event->key();

        if (!m_valid) {
            if (key >= Qt::Key_0 && key <= Qt::Key_9) {
                setTime(QTimeEdit::time());
                setCurrentSectionIndex(0);
                setSelectedSection(currentSection());
            } else if (key == Qt::Key_Tab || key == Qt::Key_Backtab) {
                QAbstractSpinBox::keyPressEvent(event);
                return;
            }
        }

        if (key == Qt::Key_Backspace) {
            setTime(QTime(24, 0));
            return;
        }
    }

    QTimeEdit::keyPressEvent(event);
}

void QxTimeEdit::focusChanged(QWidget *old, QWidget *now)
{
    Q_UNUSED(old);
    Q_UNUSED(now);

    if (!m_valid)
        lineEdit()->setText(QString());
}
