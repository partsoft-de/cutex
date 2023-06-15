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

#ifndef QXTIMEEDIT_H
#define QXTIMEEDIT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxTimeEdit stellt ein Widget zur Eingabe einer Uhrzeit bereit.

  Ein Widget der Klasse %QxTimeEdit ermöglicht die Eingabe einer optionalen Uhrzeit. Die Uhrzeit kann durch betätigen
  der Backspace-Taste gelöscht werden.

  \sa QxDateEdit
*/
class QxTimeEdit : public QTimeEdit
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(bool emptyTimeEnabled READ isEmptyTimeEnabled WRITE setEmptyTimeEnabled)
    //! @endcond

public:
    QxTimeEdit(QWidget *parent = nullptr);
    bool isEmptyTimeEnabled() const;
    void setEmptyTimeEnabled(bool enabled);
    QTime time() const;

public slots:
    void setTime(const QTime &time);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    bool m_emptyTimeEnabled;
    bool m_valid;

private slots:
    void focusChanged(QWidget *old, QWidget *now);
};

} // namespace

#endif // QXTIMEEDIT_H
