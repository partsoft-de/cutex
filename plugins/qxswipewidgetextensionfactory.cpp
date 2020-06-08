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

#include "qxswipewidgetextensionfactory.h"
#include "qxswipewidgetcontainerextension.h"

using namespace cutex;

QxSwipeWidgetExtensionFactory::QxSwipeWidgetExtensionFactory(QExtensionManager * parent) : QExtensionFactory(parent)
{
}

QObject* QxSwipeWidgetExtensionFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    QxSwipeWidget *widget = qobject_cast<QxSwipeWidget*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension)))
        return new QxSwipeWidgetContainerExtension(widget, parent);

    return nullptr;
}
