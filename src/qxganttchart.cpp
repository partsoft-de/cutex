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

#include "qxganttchart.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Gantt-Chart mit dem Elternobjekt <i>parent</i>.
*/
QxGanttChart::QxGanttChart(QWidget *parent) : QAbstractScrollArea(parent)
{
    m_model = nullptr;

    updateDateRange();
}

void QxGanttChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void QxGanttChart::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    updateScrollbars();
}

void QxGanttChart::updateScrollbars()
{
    int days = m_minDate.daysTo(m_maxDate) + 1;
    int step = viewport()->width() / fontMetrics().maxWidth();

    QScrollBar *horizontal = horizontalScrollBar();
    horizontal->setRange(0, days - step);
    horizontal->setPageStep(step);
}

void QxGanttChart::updateDateRange()
{
    if (m_model)
        m_model->dateRange(m_minDate, m_maxDate);

    if (m_minDate.isNull() || m_maxDate.isNull()) {
        m_minDate = QDate::currentDate().addDays(-10);
        m_maxDate = m_minDate.addDays(30);
    } else {
        m_minDate = m_minDate.addDays(-10);
        if (m_minDate.daysTo(m_maxDate) < 30) {
            m_maxDate = m_minDate.addDays(30);
        } else {
            m_maxDate = m_maxDate.addDays(10);
        }
    }
}
