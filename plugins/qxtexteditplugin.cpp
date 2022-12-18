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

#include "qxtexteditplugin.h"
#include "qxtextedit.h"

using namespace cutex;

QxTextEditPlugin::QxTextEditPlugin(QObject *parent) : QObject(parent)
{
}

QString QxTextEditPlugin::name() const
{
    return "cutex::QxTextEdit";
}

QString QxTextEditPlugin::includeFile() const
{
    return "qxtextedit.h";
}

QString QxTextEditPlugin::group() const
{
    return "cutex";
}

QIcon QxTextEditPlugin::icon() const
{
    return QIcon();
}

QString QxTextEditPlugin::toolTip() const
{
    return QString();
}

QString QxTextEditPlugin::whatsThis() const
{
    return QString();
}

bool QxTextEditPlugin::isContainer() const
{
    return false;
}

QWidget* QxTextEditPlugin::createWidget(QWidget *parent)
{
    return new QxTextEdit(parent);
}
