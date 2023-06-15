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

#include "qxinteditplugin.h"
#include "qxintedit.h"

using namespace cutex;

QxIntEditPlugin::QxIntEditPlugin(QObject *parent) : QObject(parent)
{
}

QString QxIntEditPlugin::name() const
{
    return "cutex::QxIntEdit";
}

QString QxIntEditPlugin::includeFile() const
{
    return "qxintedit.h";
}

QString QxIntEditPlugin::group() const
{
    return "cutex";
}

QIcon QxIntEditPlugin::icon() const
{
    return QIcon();
}

QString QxIntEditPlugin::toolTip() const
{
    return QString();
}

QString QxIntEditPlugin::whatsThis() const
{
    return QString();
}

bool QxIntEditPlugin::isContainer() const
{
    return false;
}

QWidget* QxIntEditPlugin::createWidget(QWidget *parent)
{
    return new QxIntEdit(parent);
}
