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

#include "qxswipewidgetcontainerextension.h"

using namespace cutex;

QxSwipeWidgetContainerExtension::QxSwipeWidgetContainerExtension(QxSwipeWidget *widget, QObject *parent)
    : QObject(parent)
{
    m_widget = widget;
}

bool QxSwipeWidgetContainerExtension::canAddWidget() const
{
    return true;
}

void QxSwipeWidgetContainerExtension::addWidget(QWidget *widget)
{
    m_widget->addWidget(widget);
}

int QxSwipeWidgetContainerExtension::count() const
{
    return m_widget->count();
}

int QxSwipeWidgetContainerExtension::currentIndex() const
{
    return m_widget->currentIndex();
}

void QxSwipeWidgetContainerExtension::insertWidget(int index, QWidget *widget)
{
    m_widget->insertWidget(index, widget);
}

bool QxSwipeWidgetContainerExtension::canRemove(int index) const
{
    Q_UNUSED(index);

    return true;
}

void QxSwipeWidgetContainerExtension::remove(int index)
{
    m_widget->removeWidget(index);
}

void QxSwipeWidgetContainerExtension::setCurrentIndex(int index)
{
    m_widget->setCurrentIndex(index);
}

QWidget* QxSwipeWidgetContainerExtension::widget(int index) const
{
    return m_widget->widget(index);
}
