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

#include "qxexception.h"

using namespace cutex;

/*!
  Erzeugt eine neue Exception mit der Fehlerbeschreibung <i>what</i>.
*/
QxException::QxException(const QString &what)
{
    m_what = what;
}

/*!
  Löst die Exception aus.
*/
void QxException::raise() const
{
    throw *this;
}

/*!
  Kopiert die Exception.
*/
QxException* QxException::clone() const
{
    return new QxException(*this);
}

/*!
  Gibt die Fehlerbeschreibung der Exception zurück.
*/
const char* QxException::what() const throw()
{
    return m_what.toStdString().c_str();
}
