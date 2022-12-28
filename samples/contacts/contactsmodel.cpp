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

#include "contactsmodel.h"

ContactsModel::ContactsModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void ContactsModel::clear()
{
    beginResetModel();
    qDeleteAll(m_contacts);
    m_contacts.clear();
    endResetModel();
}

int ContactsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_contacts.count();
}

int ContactsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 10;
}

QVariant ContactsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case AnredeColumn:
            return tr("Anrede");
        case VornameColumn:
            return tr("Vorname");
        case NameColumn:
            return tr("Name");
        case LandColumn:
            return tr("Land");
        case PostleitzahlColumn:
            return tr("Postleitzahl");
        case OrtColumn:
            return tr("Ort");
        case StrasseColumn:
            return tr("Straße");
        case TelefonColumn:
            return tr("Telefon");
        case MobilColumn:
            return tr("Mobil");
        case EmailColumn:
            return tr("E-Mail");
        }
    }

    if (role == Qt::TextAlignmentRole && orientation == Qt::Horizontal) {
        switch (section) {
        default:
            return Qt::AlignLeft;
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant ContactsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        Contact *contact = m_contacts.at(index.row());
        switch (index.column()) {
        case AnredeColumn:
            return contact->anrede();
        case VornameColumn:
            return contact->vorname();
        case NameColumn:
            return contact->name();
        case LandColumn:
            return contact->land();
        case PostleitzahlColumn:
            return contact->postleitzahl();
        case OrtColumn:
            return contact->ort();
        case StrasseColumn:
            return contact->strasse();
        case TelefonColumn:
            return contact->telefon();
        case MobilColumn:
            return contact->mobil();
        case EmailColumn:
            return contact->email();
        }
    }

    if (role == Qt::TextAlignmentRole) {
        switch (index.column()) {
        default:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }

    return QVariant();
}

Contact* ContactsModel::contact(const QModelIndex &index)
{
    if (!index.isValid())
        return 0;

    return m_contacts.at(index.row());
}

void ContactsModel::insertContact(Contact *contact)
{
    int row = m_contacts.count();

    beginInsertRows(QModelIndex(), row, row);
    m_contacts.insert(row, contact);
    endInsertRows();

    emit rowChanged(index(row, 0));
}

void ContactsModel::removeContact(Contact *contact)
{
    int row = m_contacts.indexOf(contact);

    beginRemoveRows(QModelIndex(), row, row);
    delete m_contacts.at(row);
    m_contacts.removeAt(row);
    endRemoveRows();

    emit rowChanged(index(row, 0));
}

QDataStream& operator <<(QDataStream &out, const ContactsModel &model)
{
    out << qint32(model.m_contacts.count());

    for (Contact *contact : model.m_contacts)
        out << contact;

    return out;
}

QDataStream& operator >>(QDataStream &in, ContactsModel &model)
{
    model.clear();

    int count = 0;
    in >> count;

    if (count > 0) {
        model.beginInsertRows(QModelIndex(), 0, count - 1);
        for (int n = 0; n < count; n++) {
            Contact *contact = new Contact();
            in >> contact;
            model.m_contacts.append(contact);
        }
        model.endInsertRows();
    }

    return in;
}
