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

#ifndef QXSQLRECORD_H
#define QXSQLRECORD_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSqlRecord ist eine Erweiterung der Qt-Klasse QSqlRecord.

  %QxSqlRecord erweitert die Qt-Klasse QSqlRecord zum Verwalten von Relationswerten.
*/
class QxSqlRecord : public QSqlRecord
{
public:
    QxSqlRecord();
    QxSqlRecord(const QSqlRecord &record);
    bool hasRelationValue(int index) const;
    bool hasRelationValue(const QString &name) const;
    QVariant relationValue(int index) const;
    QVariant relationValue(const QString &name) const;
    void setRelationValue(int index, const QVariant &value);
    void setRelationValue(const QString &name, const QVariant &value);

private:
    QMap<int, QVariant> m_relationValues;
};

} // namespace

#endif // QXSQLRECORD_H
