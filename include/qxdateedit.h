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

#ifndef QXDATEEDIT_H
#define QXDATEEDIT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxDateEdit stellt ein Widget zur Eingabe von Datumswerten bereit.

  Ein Widget der Klasse %QxDateEdit ermöglicht die Eingabe optionaler Datumswerte, z.B. für Geburtstage in einer
  Adressenverwaltung. Das Datum kann durch betätigen der Backspace-Taste gelöscht werden.

  \sa QxTimeEdit
  \sa QxDateValidator
*/
class QxDateEdit : public QDateEdit
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(bool emptyDateEnabled READ isEmptyDateEnabled WRITE setEmptyDateEnabled)
    //! @endcond

public:
    QxDateEdit(QWidget *parent = nullptr);
    bool isEmptyDateEnabled() const;
    void setEmptyDateEnabled(bool enabled);
    QDate date() const;

public slots:
    void setDate(const QDate &date);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    bool m_emptyDateEnabled;
    bool m_valid;

private slots:
    void focusChanged(QWidget *old, QWidget *now);
};

} // namespace

#endif // QXDATEEDIT_H
