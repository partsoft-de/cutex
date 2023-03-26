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
    m_margins = 5;

    updateMetrics();
    updateDateRange();
}

/*!
*/
QxGanttItemModel* QxGanttChart::model() const
{
    return m_model;
}

/*!
*/
void QxGanttChart::setModel(QxGanttItemModel *model)
{
    if (m_model)
        m_model->disconnect();

    m_model = model;
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(dataChanged()));
    connect(m_model, SIGNAL(modelReset()), this, SLOT(dataChanged()));
}

void QxGanttChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(viewport());
    paintHeader(painter);
}

void QxGanttChart::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    updateScrollbars();
}

void QxGanttChart::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::FontChange)
        updateMetrics();
}

void QxGanttChart::updateMetrics()
{
    QFontMetrics fm = fontMetrics();
    m_fmHeight = fm.height();
    m_fmMaxWidth = fm.maxWidth();
    m_headerHeight = (fontMetrics().height() * 2) + (2 * m_margins);

    viewport()->update();
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

    viewport()->update();
}

void QxGanttChart::paintHeader(QPainter &painter)
{
    QStyleOption option;
    int hint = QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &option, this);
    QPen gridPen(QColor(static_cast<QRgb>(hint)));

    painter.save();

    int days = m_minDate.daysTo(m_maxDate) + 1;
    int start = horizontalScrollBar()->value();

    for (int n = 0; n < days - start; ++n) {
        QDate date = m_minDate.addDays(start + n);
        int x1 = n * m_fmMaxWidth;
        int x2 = x1 + m_fmMaxWidth;

        painter.setPen(Qt::black);
        if (date.dayOfWeek() == Qt::Monday)
            painter.drawText(x1 + m_margins, m_fmHeight, date.toString("d MMM yy"));
        painter.drawText(x1 + m_margins, m_fmHeight * 2 + m_margins, date.toString("ddd").at(0));

        if (n < days - start - 1) {
            int y1 = (date.dayOfWeek() == Qt::Sunday) ? 0 : m_fmHeight + m_margins;
            int y2 = m_headerHeight;
            painter.setPen(gridPen);
            painter.drawLine(x2, y1, x2, y2);
        }

        bool workDay = false;
        if (m_model) {
            workDay = m_model->isWorkDay(date);
        } else {
            workDay = QxGanttItemModel().isWorkDay(date);
        }
        if (!workDay)
            painter.fillRect(x1, m_headerHeight, x2 - x1, viewport()->height(), Qt::lightGray);
    }

    painter.setPen(gridPen);
    painter.drawLine(0, m_headerHeight, viewport()->width(), m_headerHeight);
    painter.restore();
}

void QxGanttChart::dataChanged()
{
    updateDateRange();
    updateScrollbars();
}
