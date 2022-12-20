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

#include "qxdesignercustomwidgetcollectioninterface.h"
#include "qxresource.h"
#include "qxdateeditplugin.h"
#include "qxdoubleeditplugin.h"
#include "qxganttchartplugin.h"
#include "qxhelpbrowserplugin.h"
#include "qxinteditplugin.h"
#include "qxplaintexteditplugin.h"
#include "qxsqltableviewplugin.h"
#include "qxswipewidgetplugin.h"
#include "qxtexteditplugin.h"
#include "qxtimeeditplugin.h"

using namespace cutex;

QxDesignerCustomWidgetCollectionInterface::QxDesignerCustomWidgetCollectionInterface(QObject *parent) : QObject(parent)
{
    initResource();

    m_widgets.append(new QxDateEditPlugin(this));
    m_widgets.append(new QxDoubleEditPlugin(this));
    m_widgets.append(new QxGanttChartPlugin(this));
    m_widgets.append(new QxHelpBrowserPlugin(this));
    m_widgets.append(new QxIntEditPlugin(this));
    m_widgets.append(new QxPlainTextEditPlugin(this));
    m_widgets.append(new QxSqlTableViewPlugin(this));
    m_widgets.append(new QxTextEditPlugin(this));
    m_widgets.append(new QxTimeEditPlugin(this));
    m_widgets.append(new QxSwipeWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QxDesignerCustomWidgetCollectionInterface::customWidgets() const
{
    return m_widgets;
}
