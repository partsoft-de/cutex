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

#ifndef QXDESIGNERCUSTOMWIDGETCOLLECTIONINTERFACE_H
#define QXDESIGNERCUSTOMWIDGETCOLLECTIONINTERFACE_H

#include "plugins.h"

namespace cutex {

class QxDesignerCustomWidgetCollectionInterface: public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.partsoft.cutex")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    QxDesignerCustomWidgetCollectionInterface(QObject *parent = 0);
    QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
    QList<QDesignerCustomWidgetInterface*> m_widgets;
};

} // namespace

#endif // QXDESIGNERCUSTOMWIDGETCOLLECTIONINTERFACE_H
