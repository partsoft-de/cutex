/***********************************************************************************************************************
**
** Copyright (C) 2016 Partsoft UG (haftungsbeschränkt)
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

#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include "contacts.h"
#include "contact.h"

class ContactsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum {
        AnredeColumn = 0, VornameColumn, NameColumn, LandColumn, PostleitzahlColumn, OrtColumn, StrasseColumn,
        TelefonColumn, MobilColumn, EmailColumn
    };

public:
    ContactsModel(QObject *parent = 0);
    void clear();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    Contact* contact(const QModelIndex &index);
    void insertContact(Contact *contact);
    void removeContact(Contact *contact);
    friend QDataStream& operator <<(QDataStream &out, const ContactsModel &model);
    friend QDataStream& operator >>(QDataStream &in, ContactsModel &model);

private:
    QList<Contact*> m_contacts;

signals:
    void rowChanged(QModelIndex);
};

#endif // CONTACTSMODEL_H
