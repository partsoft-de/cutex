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

#include <qxfilterheaderview.h>
#include "filterheader.h"
#include "addressesmodel.h"
#include "proxymodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTableView view;

    ProxyModel *model = new ProxyModel(&view);
    model->setSourceModel(new AddressesModel(&view));

    QxFilterHeaderView *header = new QxFilterHeaderView(&view);
    QObject::connect(header, SIGNAL(filterChanged(int,QString)), model, SLOT(setFilter(int,QString)));

    view.setWindowIcon(QIcon(":/icons/32x32/filterheader.ico"));
    view.setModel(model);
    view.setHorizontalHeader(header);
    view.setSortingEnabled(true);
    view.verticalHeader()->setVisible(false);
    view.resize(800, 600);
    view.show();

    return app.exec();
}
