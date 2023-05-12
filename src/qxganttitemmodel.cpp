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

#include "qxganttitem.h"
#include "qxganttitemmodel.h"

using namespace cutex;

/*!
*/
QxGanttItemModel::QxGanttItemModel(QObject *parent) : QxTreeItemModel(parent)
{
    m_workDays = WorkDay::Monday | WorkDay::Tuesday | WorkDay::Wednesday | WorkDay::Thursday | WorkDay::Friday;
}

/*!
*/
int	QxGanttItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return (Column::Finish + 1);
}

/*!
*/
QVariant QxGanttItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);

    QVariant result;

    if (role == Qt::DisplayRole) {
        switch (section) {
        case Column::Text:
            result = tr("Name");
            break;
        }
    }

    if (role == Qt::TextAlignmentRole)
        result = Qt::AlignTop + Qt::AlignLeft;

    return result;
}

/*!
*/
QVariant QxGanttItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QxGanttItem *item = static_cast<QxGanttItem*>(itemFromIndex(index));
        QVariant value;

        switch (index.column()) {
        case Column::Text:
            value = item->text();
            break;
        }

        return value;
    }

    if (role == Qt::SizeHintRole)
        return QSize(100, 30);

    return QVariant();
}

/*!
*/
void QxGanttItemModel::dateRange(QDate &min, QDate &max) const
{
    min = max = QDate();
}

/*!
*/
QxGanttItemModel::WorkDays QxGanttItemModel::workDays() const
{
    return m_workDays;
}

/*!
*/
bool QxGanttItemModel::isWorkDay(const QDate &date) const
{
    bool result = false;

    switch (date.dayOfWeek()) {
    case Qt::Monday:
        result = (m_workDays & QxGanttItemModel::Monday);
        break;
    case Qt::Tuesday:
        result = (m_workDays & QxGanttItemModel::Tuesday);
        break;
    case Qt::Wednesday:
        result = (m_workDays & QxGanttItemModel::Wednesday);
        break;
    case Qt::Thursday:
        result = (m_workDays & QxGanttItemModel::Thursday);
        break;
    case Qt::Friday:
        result = (m_workDays & QxGanttItemModel::Friday);
        break;
    case Qt::Saturday:
        result = (m_workDays & QxGanttItemModel::Saturday);
        break;
    case Qt::Sunday:
        result = (m_workDays & QxGanttItemModel::Sunday);
        break;
    }

    return result;
}

void QxGanttItemModel::setWorkDays(WorkDays workDays)
{
    if (m_workDays != workDays) {
        beginResetModel();
        m_workDays = workDays;
        endResetModel();
    }
}
