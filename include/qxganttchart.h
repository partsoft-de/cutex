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

#ifndef QXGANTTCHART_H
#define QXGANTTCHART_H

#include "cutex.h"
#include "qxganttitemmodel.h"

namespace cutex {

/*!
*/
class QxGanttChart : public QAbstractScrollArea
{
    Q_OBJECT

public:
    QxGanttChart(QWidget *parent = nullptr);
    QxGanttItemModel* model() const;
    void setModel(QxGanttItemModel *model);
    int headerHeight() const;

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void changeEvent(QEvent *event);

private:
    QxGanttItemModel *m_model;
    QDate m_minDate;
    QDate m_maxDate;
    int m_margins;
    int m_fmHeight;
    int m_fmMaxWidth;
    int m_headerHeight;

private:
    void updateMetrics();
    void updateScrollbars();
    void updateDateRange();
    void paintHeader(QPainter &painter);

private slots:
    void dataChanged();
};

} // namespace

#endif // QXGANTTCHART_H
