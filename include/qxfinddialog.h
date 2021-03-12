/***********************************************************************************************************************
**
** Copyright (C) 2016-2021 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXFINDDIALOG_H
#define QXFINDDIALOG_H

#include "cutex.h"
#include "qxdialog.h"
#include "qxfindoptions.h"

namespace Ui {
class QxFindDialog;
}

namespace cutex {

/*!
  \brief %QxFindDialog ist ein fertiger Dialog zum Suchen und Ersetzen von Text.

  Dialoge vom Typ %QxFindDialog stellen die GUI für eine Suchen/Ersetzen-Funktion von Text bereit.

  \sa QxFindOptions
*/
class QxFindDialog : public QxDialog
{
    Q_OBJECT

public:
    enum Mode {
        Find = 1, Replace
    };

public:
    QxFindDialog(QWidget *parent = 0);
    ~QxFindDialog();
    void setMode(QxFindDialog::Mode mode);
    void retranslateUi();

protected:
    virtual void buttonClicked(QAbstractButton *button);

private:
    Ui::QxFindDialog *m_ui;

private slots:
    void relockButtons();

signals:
    void findClicked(const QxFindOptions &options);
};

} // namespace

#endif // QXFINDDIALOG_H
