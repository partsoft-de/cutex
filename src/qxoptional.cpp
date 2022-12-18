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

#include "qxoptional.h"

using namespace cutex;

/*!
  \fn QxOptional::QxOptional()

  Erzeugt ein neues Objekt ohne Wert.
*/

/*!
  \fn QxOptional::QxOptional(const T &value)

  Erzeugt ein neues Objekt mit dem Wert <i>value</i>.
*/

/*!
  \fn QxOptional::clear()

  Löscht den optionalen Wert.
*/

/*!
  \fn QxOptional::hasValue()

  Gibt true zurück, wenn ein Wert vorhanden ist.
*/

/*!
  \fn QxOptional::value(const T &defaultValue = T()) const

  Gibt den Wert, bzw. wenn kein Wert vorhanden ist <i>defaultValue</i> zurück.

  \sa setValue(const T &value)
*/

/*!
  \fn QxOptional::setValue(const T &value)

  Setzt den Wert auf den Wert <i>value</i>.

  \sa value(const T &defaultValue = T()) const
*/
