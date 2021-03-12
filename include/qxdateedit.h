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

#ifndef QXDATEEDIT_H
#define QXDATEEDIT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxDateEdit stellt ein Widget zur Eingabe von Datumswerten bereit.

  Ein Widget der Klasse %QxDateEdit enthält neben einem gewöhnlichen QDateEdit zusätzlich eine Checkbox, mit der das
  Datum deaktiviert werden kann. Dadurch kann eine Eingabe optionaler Datumswerte realisiert werden, z.B. für
  Geburtstage in einer Adressenverwaltung.

  \sa QxDateValidator
*/
class QxDateEdit : public QWidget
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(QDate maximumDate READ maximumDate WRITE setMaximumDate)
    Q_PROPERTY(QDate minimimDate READ minimumDate WRITE setMinimumDate)
    Q_PROPERTY(QString displayFormat READ displayFormat WRITE setDisplayFormat)
    Q_PROPERTY(bool calendarPopup READ calendarPopup WRITE setCalendarPopup)
    Q_PROPERTY(bool emptyDateEnabled READ isEmptyDateEnabled WRITE setEmptyDateEnabled)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
    //! @endcond

public:
    QxDateEdit(QWidget *parent = 0);
    QDate date() const;
    void setDate(const QDate &date);
    QDate maximumDate() const;
    void setMaximumDate(const QDate &date);
    QDate minimumDate() const;
    void setMinimumDate(const QDate &date);
    QString displayFormat() const;
    void setDisplayFormat(const QString &format);
    bool calendarPopup() const;
    void setCalendarPopup(bool enable);
    bool isEmptyDateEnabled() const;
    void setEmptyDateEnabled(bool enabled);
    bool isReadOnly() const;
    void setReadOnly(bool readOnly);

public slots:
    void selectAll();

private:
    QDateEdit *m_dateField;
    QCheckBox *m_dateEnableBox;
    bool m_emptyDateEnabled;
    bool m_emptyDate;
    bool m_readOnly;

private slots:
    void setDateEnabled(bool enabled);

signals:
    void dateChanged(const QDate &date);
    void editingFinished();
};

} // namespace

#endif // QXDATEEDIT_H
