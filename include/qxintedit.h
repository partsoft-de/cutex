/***********************************************************************************************************************
**
** Copyright (C) 2016-2022 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXINTEDIT_H
#define QXINTEDIT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxIntEdit stellt ein Widget zur Eingabe von Ganzzahlen bereit.

  %QxIntEdit ist eine Erweiterung der Qt-Klasse QLineEdit, welches nur die Eingabe von Ganzzahlen erlaubt. Das Widget
  wurde als Alternative zu QSpinBox implementiert, da dieses unter dem Betriebssystem Android nicht richtig dargestellt
  wird.

  \sa QxDoubleEdit
*/
class QxIntEdit : public QLineEdit
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue)
    //! @endcond

public:
    QxIntEdit(QWidget *parent = nullptr);
    int minimum() const;
    void setMinimum(int minimum);
    int maximum() const;
    void setMaximum(int maximum);
    int value() const;
    void setValue(int value);

protected:
    void focusOutEvent(QFocusEvent *event);

private:
    QIntValidator *m_validator;
    int m_minimum;
    int m_maximum;
};

} // namespace

#endif // QXINTEDIT_H
