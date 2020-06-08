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

#ifndef QXSWIPEWIDGETCONTAINEREXTENSION_H
#define QXSWIPEWIDGETCONTAINEREXTENSION_H

#include "plugins.h"
#include "qxswipewidget.h"

namespace cutex {

class QxSwipeWidgetContainerExtension: public QObject, public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    QxSwipeWidgetContainerExtension(QxSwipeWidget *widget, QObject *parent);
    void addWidget(QWidget *widget);
    int count() const;
    int currentIndex() const;
    void insertWidget(int index, QWidget *widget);
    void remove(int index);
    void setCurrentIndex(int index);
    QWidget *widget(int index) const;

private:
    QxSwipeWidget *m_widget;
};

} // namespace

#endif // QXSWIPEWIDGETCONTAINEREXTENSION_H
