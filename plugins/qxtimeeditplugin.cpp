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

#include "qxtimeeditplugin.h"
#include "qxtimeedit.h"

using namespace cutex;

QxTimeEditPlugin::QxTimeEditPlugin(QObject *parent) : QObject(parent)
{
}

QString QxTimeEditPlugin::name() const
{
    return "cutex::QxTimeEdit";
}

QString QxTimeEditPlugin::includeFile() const
{
    return "qxtimeedit.h";
}

QString QxTimeEditPlugin::group() const
{
    return "cutex";
}

QIcon QxTimeEditPlugin::icon() const
{
    return QIcon();
}

QString QxTimeEditPlugin::toolTip() const
{
    return QString();
}

QString QxTimeEditPlugin::whatsThis() const
{
    return QString();
}

bool QxTimeEditPlugin::isContainer() const
{
    return false;
}

QWidget* QxTimeEditPlugin::createWidget(QWidget *parent)
{
    return new QxTimeEdit(parent);
}
