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

#ifndef QXEXCEPTION_H
#define QXEXCEPTION_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxException ist eine Ausnahmeklasse zur Verwendung mit Zeichenketten vom Typ QString.

  %QxException ist eine Ausnahmeklasse, der im Konstruktor eine Zeichenkette vom Typ QString übergeben wird und diese
  in der Standardmethode what() wieder zurückgibt.
*/
class QxException : public QException
{
public:
    QxException(const QString &what = QString());
    void raise() const;
    QxException* clone() const;
    virtual const char* what() const throw();

private:
    QString m_what;
};

} // namespace

#endif // QXEXCEPTION_H
