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

#include "qxdateedit.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxDateEdit::QxDateEdit(QWidget *parent) : QWidget(parent)
{
    m_dateField = new QDateEdit(this);
    m_dateEnableBox = new QCheckBox(this);

    setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(2);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout()->addWidget(m_dateEnableBox);
    layout()->addWidget(m_dateField);

    m_dateField->setMinimumHeight(m_dateField->sizeHint().height());
    m_dateField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setFocusProxy(m_dateField);
    setFocusPolicy(Qt::StrongFocus);

    setEmptyDateEnabled(false);
    setDateEnabled(true);
    setReadOnly(false);

    connect(m_dateField, SIGNAL(dateChanged(QDate)), this, SIGNAL(dateChanged(QDate)));
    connect(m_dateField, SIGNAL(editingFinished()), this, SIGNAL(editingFinished()));
    connect(m_dateEnableBox, SIGNAL(clicked(bool)), this, SLOT(setDateEnabled(bool)));
}

/*!
  Gibt das aktuelle Datum zurück.

  \sa setDate(const QDate &date)
*/
QDate QxDateEdit::date() const
{
    QDate date;

    if (!m_emptyDate || !m_emptyDateEnabled)
        date = m_dateField->date();

    return date;
}

/*!
  Ändert das aktuelle Datum auf den Wert <i>date</i>.

  \sa date() const
*/
void QxDateEdit::setDate(const QDate &date)
{
    if (date.isValid() && date.toJulianDay() > 0) {
        m_dateField->setDate(date);
        setDateEnabled(true);
    } else if (m_emptyDateEnabled){
        setDateEnabled(false);
    }
}

/*!
  Gibt das größtmögliche Datum zurück.

  \sa setMaximumDate(const QDate &date)
*/
QDate QxDateEdit::maximumDate() const
{
    return m_dateField->maximumDate();
}

/*!
  Setzt das größtmögliche Datum auf den Wert <i>date</i>.

  \sa maximumDate() const
*/
void QxDateEdit::setMaximumDate(const QDate &date)
{
    m_dateField->setMaximumDate(date);
}

/*!
  Gibt das kleinstmögliche Datum zurück.

  \sa setMinimumDate(const QDate &date)
*/
QDate QxDateEdit::minimumDate() const
{
    return m_dateField->minimumDate();
}

/*!
  Setzt das kleinstmögliche Datum auf den Wert <i>date</i>.

  \sa minimumDate() const
*/
void QxDateEdit::setMinimumDate(const QDate &date)
{
    m_dateField->setMinimumDate(date);
}

/*!
  Gibt das Datumsformat zurück.

  \sa setDisplayFormat(const QString &format)
*/
QString QxDateEdit::displayFormat() const
{
    return m_dateField->displayFormat();
}

/*!
  Setzt das Datumsformat auf den Wert <i>format</i>.

  \sa displayFormat() const
*/
void QxDateEdit::setDisplayFormat(const QString &format)
{
    m_dateField->setDisplayFormat(format);
}

/*!
  Gibt true zurück, wenn das Popup für die Datumsauswahl aktiviert ist.

  \sa setCalendarPopup(bool enable)
*/
bool QxDateEdit::calendarPopup() const
{
    return m_dateField->calendarPopup();
}

/*!
  Aktiviert, bzw. deaktiviert das Popup für die Datumsauswahl.

  \sa calendarPopup() const
*/
void QxDateEdit::setCalendarPopup(bool enable)
{
    m_dateField->setCalendarPopup(enable);
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
    m_dateEnableBox->setVisible(enabled);
    if (!m_emptyDateEnabled && m_emptyDate)
        setDateEnabled(true);
}

/*!
  Gibt true zurück, wenn das Feld schreibgeschützt ist.

  \sa setReadOnly(bool readOnly)
*/
bool QxDateEdit::isReadOnly() const
{
    return m_readOnly;
}

/*!
  Aktiviert, bzw. deaktiviert den Schreibschutz für das Feld.

  \sa isReadOnly() const
*/
void QxDateEdit::setReadOnly(bool readOnly)
{
    m_readOnly = readOnly;
    m_dateField->setReadOnly(readOnly);
    m_dateEnableBox->setDisabled(readOnly);
}

/*!
  Markiert alle Benutzereingaben.
*/
void QxDateEdit::selectAll()
{
    m_dateField->selectAll();
}

void QxDateEdit::setDateEnabled(bool enabled)
{
    m_emptyDate = !enabled;
    m_dateField->setEnabled(enabled);
    m_dateEnableBox->setChecked(enabled);
}

/*!
  \fn QxDateEdit::dateChanged(const QDate &date)

  Das Signal wird ausgelöst wenn das Datum auf den Wert <i>date</i> geändert wurde.
*/

/*!
  \fn QxDateEdit::editingFinished()

  Das Signal wird ausgelöst wenn der Benutzer das Bearbeiten des Datums beendet hat.
*/
