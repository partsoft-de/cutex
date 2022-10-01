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

#include "qxplaintexteditplugin.h"
#include "qxplaintextedit.h"

using namespace cutex;

QxPlainTextEditPlugin::QxPlainTextEditPlugin(QObject *parent) : QObject(parent)
{
}

QString QxPlainTextEditPlugin::name() const
{
    return "cutex::QxPlainTextEdit";
}

QString QxPlainTextEditPlugin::includeFile() const
{
    return "qxplaintextedit.h";
}

QString QxPlainTextEditPlugin::group() const
{
    return "cutex";
}

QIcon QxPlainTextEditPlugin::icon() const
{
    return QIcon();
}

QString QxPlainTextEditPlugin::toolTip() const
{
    return QString();
}

QString QxPlainTextEditPlugin::whatsThis() const
{
    return QString();
}

bool QxPlainTextEditPlugin::isContainer() const
{
    return false;
}

QWidget* QxPlainTextEditPlugin::createWidget(QWidget *parent)
{
    return new QxPlainTextEdit(parent);
}
