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

#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H

#include "cutex.h"
#include "qxdialog.h"

namespace Ui {
class QxCalculatorDialog;
}

namespace cutex {

/*!
  \brief %QxCalculatorDialog ist ein fertiger Dialog für einen einfachen Taschenrechner.

  Die Klasse stellt einen einfachen Taschenrechner bereit, der die Grundrechenarten implementiert.
*/
class QxCalculatorDialog : public QxDialog
{
    Q_OBJECT

public:
    QxCalculatorDialog(QWidget *parent = nullptr);
    ~QxCalculatorDialog();
    void showButtonBox(bool show);
    double value() const;
    void setValue(double value);

protected:
    void buttonClicked(QAbstractButton *button);

private:
    Ui::QxCalculatorDialog *m_ui;
    double m_value;
    QChar m_operator;
    bool m_clear;

private:
    QString calculate();
};

} // namespace

#endif // CALCULATORDIALOG_H
