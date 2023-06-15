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

#include "qxsqlrecord.h"

using namespace cutex;

/*!
  Erzeugt eine neue Instanz der Klasse.
*/
QxSqlRecord::QxSqlRecord()
{
}

/*!
  Erzeugt eine neue Instanz mit dem Wert <i>record</i>.
*/
QxSqlRecord::QxSqlRecord(const QSqlRecord &record) : QSqlRecord(record)
{
}

/*!
  Prüft ob für das Datenbankfeld mit dem Index <i>index</i> ein Relationswert existiert.

  \sa hasRelationValue(const QString &name) const
*/
bool QxSqlRecord::hasRelationValue(int index) const
{
    return m_relationValues.contains(index);
}

/*!
  Prüft ob für das Datenbankfeld mit dem Namen <i>name</i> ein Relationswert existiert.

  \sa hasRelationValue(const QString &name) const
*/
bool QxSqlRecord::hasRelationValue(const QString &name) const
{
    return m_relationValues.contains(indexOf(name));
}

/*!
  Gibt den Relationswert des Datenbankfeldes mit dem Index <i>index</i> zurück.

  \sa setRelationValue(int index, const QVariant &value)
*/
QVariant QxSqlRecord::relationValue(int index) const
{
    return m_relationValues.value(index);
}

/*!
  Gibt den Relationswert des Datenbankfeldes mit dem Namen <i>name</i> zurück.

  \sa setRelationValue(const QString &name, const QVariant &value)
*/
QVariant QxSqlRecord::relationValue(const QString &name) const
{
    return m_relationValues.value(indexOf(name));
}

/*!
  Setzt den Relationswert des Datenbankfeldes mit dem Index <i>index</i> auf den Wert <i>value</i>.

  \sa relationValue(int index) const
*/
void QxSqlRecord::setRelationValue(int index, const QVariant &value)
{
    m_relationValues.insert(index, value);
}

/*!
  Setzt den Relationswert des Datenbankfeldes mit dem Namen <i>name</i> auf den Wert <i>value</i>.

  \sa relationValue(const QString &name) const
*/
void QxSqlRecord::setRelationValue(const QString &name, const QVariant &value)
{
    int index = indexOf(name);

    if (index != -1)
        m_relationValues.insert(index, value);
}
