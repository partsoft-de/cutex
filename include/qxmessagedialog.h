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

#ifndef QXMESSAGEDIALOG_H
#define QXMESSAGEDIALOG_H

#include "cutex.h"
#include "qxdialog.h"

namespace Ui {
class QxMessageDialog;
}

namespace cutex {

/*!
  \brief %QxMessageDialog ist ein fertiger Dialog zur Anzeige von Meldungen.

  Dialoge vom Typ %QxMessageDialog können zur Anzeige von Meldungen (Statushinweise, Fehlermeldungen, etc.) verwendet
  werden.

  \sa QxMessage
*/
class QxMessageDialog : public QxDialog
{
    Q_OBJECT

public:
    QxMessageDialog(const QString &title, const QStringList &messages, QWidget *parent = 0);
    ~QxMessageDialog();
    void retranslateUi();

private:
    Ui::QxMessageDialog *m_ui;
};

} // namespace

#endif // QXMESSAGEDIALOG_H
