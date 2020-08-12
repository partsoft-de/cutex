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

#ifndef QXDOUBLEEDIT_H
#define QXDOUBLEEDIT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxDoubleEdit stellt ein Widget zur Eingabe von Gleitkommazahlen bereit.

  %QxDoubleEdit ist eine Erweiterung der Qt-Klasse QLineEdit, welches nur die Eingabe von Gleitkommazahlen erlaubt. Das
  Widget wurde als Alternative zu QDoubleSpinBox implementiert, da dieses unter dem Betriebssystem Android nicht
  richtig dargestellt wird.

  \sa QxIntEdit
*/
class QxDoubleEdit : public QLineEdit
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double value READ value WRITE setValue)
    //! @endcond

public:
    QxDoubleEdit(QWidget *parent = 0);
    int decimals() const;
    void setDecimals(int decimals);
    double minimum() const;
    void setMinimum(double minimum);
    double maximum() const;
    void setMaximum(double maximum);
    double value() const;
    void setValue(double value);

protected:
    void focusOutEvent(QFocusEvent *event);

private:
    QDoubleValidator *m_validator;
    int m_decimals;
    double m_minimum;
    double m_maximum;
};

} // namespace

#endif // QXDOUBLEEDIT_H
