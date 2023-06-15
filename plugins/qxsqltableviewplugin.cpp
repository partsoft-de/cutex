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

#include "qxsqltableviewplugin.h"
#include "qxsqltableview.h"

using namespace cutex;

QxSqlTableViewPlugin::QxSqlTableViewPlugin(QObject *parent) : QObject(parent)
{
}

QString QxSqlTableViewPlugin::name() const
{
    return "cutex::QxSqlTableView";
}

QString QxSqlTableViewPlugin::includeFile() const
{
    return "qxsqltableview.h";
}

QString QxSqlTableViewPlugin::group() const
{
    return "cutex";
}

QIcon QxSqlTableViewPlugin::icon() const
{
    return QIcon();
}

QString QxSqlTableViewPlugin::toolTip() const
{
    return QString();
}

QString QxSqlTableViewPlugin::whatsThis() const
{
    return QString();
}

bool QxSqlTableViewPlugin::isContainer() const
{
    return false;
}

QWidget* QxSqlTableViewPlugin::createWidget(QWidget *parent)
{
    return new QxSqlTableView(parent);
}
