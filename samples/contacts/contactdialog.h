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

#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include "contacts.h"
#include "ui_contactdialog.h"
#include "contact.h"

class ContactDialog : public QxDialog, private Ui::ContactDialog
{
    Q_OBJECT

public:
    ContactDialog(Contact *contact, QWidget *parent = 0);

public slots:
    void accept();

protected:
    QString validateUiField(QWidget *uiField);
    virtual void preProcessUiField(QWidget *uiField);
    void buttonClicked(QAbstractButton *button);

private:
    Ui::ContactDialog m_ui;
    Contact *m_contact;
};

#endif // CONTACTDIALOG_H
