/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#include "qxmessagedialog.h"
#include "ui_qxmessagedialog.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Dialog mit dem Titel <i>title</i> und dem Elternobjekt <i>parent</i>. Die anzuzeigenden Meldungen
  werden im Parameter <i>messages</i> übergeben.
*/
QxMessageDialog::QxMessageDialog(const QString &title, const QStringList &messages, QWidget *parent) : QxDialog(parent),
    m_ui(new Ui::QxMessageDialog)
{
    m_ui->setupUi(this);

    setWindowTitle(title);
    foreach (QString text, messages)
        m_ui->MessageField->append(text);
}

QxMessageDialog::~QxMessageDialog()
{
    delete m_ui;
}

/*!
  Wird aufgerufen wenn die Sprache geändert wurde.
*/
void QxMessageDialog::retranslateUi()
{
    m_ui->retranslateUi(this);
}
