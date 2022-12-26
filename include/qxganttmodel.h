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

#ifndef QXGANTTMODEL_H
#define QXGANTTMODEL_H

#include "cutex.h"
#include "qxtreeitemmodel.h"

namespace cutex {

/*!
*/
class QxGanttModel : public QxTreeItemModel
{
    Q_OBJECT

public:
    enum WorkDay {
        NoDay = 0x00,
        Monday = 0x01,
        Tuesday = 0x02,
        Wednesday = 0x04,
        Thursday = 0x08,
        Friday = 0x10,
        Saturday = 0x20,
        Sunday = 0x40,
        Everyday = 0x3f
    };
    Q_DECLARE_FLAGS(WorkDays, WorkDay)
    Q_FLAG(WorkDays)

public:
    QxGanttModel(QObject *parent = nullptr);
    void dateRange(QDate &min, QDate &max) const;
    WorkDays workDays() const;
    bool isWorkDay(const QDate &date) const;

public slots:
    void setWorkDays(WorkDays workDays);

private:
    WorkDays m_workDays;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QxGanttModel::WorkDays)

} // namespace

#endif // QXGANTTMODEL_H
