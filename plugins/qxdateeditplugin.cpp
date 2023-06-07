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

#include "qxdateeditplugin.h"
#include "qxdateedit.h"

using namespace cutex;

QxDateEditPlugin::QxDateEditPlugin(QObject *parent) : QObject(parent)
{
}

QString QxDateEditPlugin::name() const
{
    return "cutex::QxDateEdit";
}

QString QxDateEditPlugin::includeFile() const
{
    return "qxdateedit.h";
}

QString QxDateEditPlugin::group() const
{
    return "cutex";
}

QIcon QxDateEditPlugin::icon() const
{
    return QIcon();
}

QString QxDateEditPlugin::toolTip() const
{
    return QString();
}

QString QxDateEditPlugin::whatsThis() const
{
    return QString();
}

bool QxDateEditPlugin::isContainer() const
{
    return false;
}

QWidget* QxDateEditPlugin::createWidget(QWidget *parent)
{
    return new QxDateEdit(parent);
}
