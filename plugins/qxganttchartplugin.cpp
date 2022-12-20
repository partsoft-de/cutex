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

#include "qxganttchartplugin.h"
#include "qxganttchart.h"

using namespace cutex;

QxGanttChartPlugin::QxGanttChartPlugin(QObject *parent) : QObject(parent)
{
}

QString QxGanttChartPlugin::name() const
{
    return "cutex::QxGanttChart";
}

QString QxGanttChartPlugin::includeFile() const
{
    return "qxganttchart.h";
}

QString QxGanttChartPlugin::group() const
{
    return "cutex";
}

QIcon QxGanttChartPlugin::icon() const
{
    return QIcon();
}

QString QxGanttChartPlugin::toolTip() const
{
    return QString();
}

QString QxGanttChartPlugin::whatsThis() const
{
    return QString();
}

bool QxGanttChartPlugin::isContainer() const
{
    return false;
}

QWidget* QxGanttChartPlugin::createWidget(QWidget *parent)
{
    return new QxGanttChart(parent);
}
