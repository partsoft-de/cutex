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

#include "addressesmodel.h"

AddressesModel::AddressesModel(QObject *parent) : QAbstractTableModel(parent)
{
    readData(":/data/addresses.csv");
}

int AddressesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_data.count();
}

int AddressesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_headerData.count();
}

QVariant AddressesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_headerData.at(section);

    return QVariant();
}

QVariant AddressesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        QStringList data = m_data.at(index.row());
        if (index.column() < data.count())
            return data.at(index.column());
    }

    return QVariant();
}

void AddressesModel::readData(const QString &fileName)
{
    beginResetModel();
    m_headerData.clear();
    m_data.clear();

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {        
        if (!file.atEnd()) {
            QString line = file.readLine();
            for (const QString &str : line.split(';'))
                m_headerData.append(str.simplified());
        }

        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList data;
            for (const QString &str : line.split(';'))
                data.append(str.simplified());
            m_data.append(data);
        }
    }

    endResetModel();
}
