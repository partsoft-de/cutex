/***********************************************************************************************************************
**
** Copyright (C) 2016-2020 Partsoft UG (haftungsbeschränkt)
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

#include "qxswipewidgetplugin.h"
#include "qxswipewidget.h"
#include "qxswipewidgetextensionfactory.h"

using namespace cutex;

QxSwipeWidgetPlugin::QxSwipeWidgetPlugin(QObject *parent) : QObject(parent)
{
    m_initialized = false;
}

QString QxSwipeWidgetPlugin::name() const
{
    return "cutex::QxSwipeWidget";
}

QString QxSwipeWidgetPlugin::includeFile() const
{
    return "qxswipewidget.h";
}

QString QxSwipeWidgetPlugin::group() const
{
    return "cutex";
}

QIcon QxSwipeWidgetPlugin::icon() const
{
    return QIcon();
}

QString QxSwipeWidgetPlugin::toolTip() const
{
    return QString();
}

QString QxSwipeWidgetPlugin::whatsThis() const
{
    return QString();
}

bool QxSwipeWidgetPlugin::isContainer() const
{
    return true;
}

QWidget* QxSwipeWidgetPlugin::createWidget(QWidget *parent)
{
    return new QxSwipeWidget(parent);
}

bool QxSwipeWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

void QxSwipeWidgetPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (m_initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new QxSwipeWidgetExtensionFactory(manager);

    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));
    m_initialized = true;
}

QString QxSwipeWidgetPlugin::domXml() const
{
    QString result;
    QFile file(":/xml/qxswipewidgetplugin.xml");

    if (file.open(QIODevice::ReadOnly))
        result = file.readAll();

    return result;
}
