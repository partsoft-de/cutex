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

#include "qxganttmodel.h"

using namespace cutex;

/*!
*/
QxGanttModel::QxGanttModel(QObject *parent) : QxTreeItemModel(parent)
{
    m_workDays = WorkDay::Monday | WorkDay::Tuesday | WorkDay::Wednesday | WorkDay::Thursday | WorkDay::Friday;
}

/*!
*/
void QxGanttModel::dateRange(QDate &min, QDate &max) const
{
    min = max = QDate();
}

/*!
*/
QxGanttModel::WorkDays QxGanttModel::workDays() const
{
    return m_workDays;
}

/*!
*/
bool QxGanttModel::isWorkDay(const QDate &date) const
{
    bool result = false;

    switch (date.dayOfWeek()) {
    case Qt::Monday:
        result = (m_workDays & QxGanttModel::Monday);
        break;
    case Qt::Tuesday:
        result = (m_workDays & QxGanttModel::Tuesday);
        break;
    case Qt::Wednesday:
        result = (m_workDays & QxGanttModel::Wednesday);
        break;
    case Qt::Thursday:
        result = (m_workDays & QxGanttModel::Thursday);
        break;
    case Qt::Friday:
        result = (m_workDays & QxGanttModel::Friday);
        break;
    case Qt::Saturday:
        result = (m_workDays & QxGanttModel::Saturday);
        break;
    case Qt::Sunday:
        result = (m_workDays & QxGanttModel::Sunday);
        break;
    }

    return result;
}

void QxGanttModel::setWorkDays(WorkDays workDays)
{
    if (m_workDays != workDays) {
        beginResetModel();
        m_workDays = workDays;
        endResetModel();
    }
}
