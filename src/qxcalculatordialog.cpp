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

#include "qxcalculatordialog.h"
#include "ui_qxcalculatordialog.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Dialog mit dem Elternobjekt <i>parent</i>.
*/
QxCalculatorDialog::QxCalculatorDialog(QWidget *parent) : QxDialog(parent), m_ui(new Ui::QxCalculatorDialog)
{
    m_clear = false;

    m_ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/16x16/calculator.png"));
    showButtonBox(false);

    setUiFieldValue(m_ui->ValueField, "0");
}

QxCalculatorDialog::~QxCalculatorDialog()
{
    delete m_ui;
}

/*!
   Blendet die Schaltflächen "Ok" und "Abbrechen" in Abhängigkeit von dem Wert <i>show</i> ein oder aus.
*/
void QxCalculatorDialog::showButtonBox(bool show)
{
    m_ui->ButtonBox->setVisible(show);
    m_ui->ButtonSeparator->setVisible(show);

    setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    adjustSize();
    setFixedSize(size());
}

/*!
   Gibt den aktuellen Wert zurück.

   \sa setValue(double value)
*/
double QxCalculatorDialog::value() const
{
    return QLocale::system().toDouble(uiFieldValue(m_ui->ValueField).toString());
}

/*!
   Setzt alle Eingaben zurück.
*/
void QxCalculatorDialog::clear()
{
    m_clear = false;
    m_operator = QChar();

    setValue(0.0);
}

/*!
   Setzt den aktuellen Wert auf <i>value</i>.

   \sa value() const
*/
void QxCalculatorDialog::setValue(double value)
{
    m_value = value;

    setUiFieldValue(m_ui->ValueField, QLocale::system().toString(value));
}

void QxCalculatorDialog::buttonClicked(QAbstractButton *button)
{
    QString value = uiFieldValue(m_ui->ValueField).toString();
    QString buttonText = button->text();
    bool isNumber = false;
    int number = buttonText.toInt(&isNumber);

    if (button == m_ui->CommaButton) {
        if (m_clear) {
            setUiFieldValue(m_ui->ValueField, "0,");
            m_clear = false;
        } else {
            QString decimalPoint = QLocale::system().decimalPoint();
            if (!value.contains(decimalPoint)) {
                if (value.isEmpty() || value == "-") {
                    value += "0" + decimalPoint;
                } else {
                    value += decimalPoint;
                }
                setUiFieldValue(m_ui->ValueField, value);
            }
        }
    } else if (button == m_ui->DeleteButton) {
        if (value != "0") {
            value = value.left(value.length() - 1);
            if (value.isEmpty())
                value = "0";
            setUiFieldValue(m_ui->ValueField, value);
        }
    } else if (button == m_ui->AddButton) {
        if (m_operator != 0)
            value = calculate();
        m_value = QLocale::system().toDouble(value);
        if (m_value != 0.0) {
            m_operator = '+';
            m_clear = true;
        }
    } else if (button == m_ui->SubtractButton) {
        if (value == "0") {
            value = "-";
            setUiFieldValue(m_ui->ValueField, value);
        } else {
            if (m_operator != 0)
                value = calculate();
            m_value = QLocale::system().toDouble(value);
            if (m_value != 0.0) {
                m_operator = '-';
                m_clear = true;
            }
        }
    } else if (button == m_ui->MultiplyButton) {
        if (m_operator != 0)
            value = calculate();
        m_value = QLocale::system().toDouble(value);
        if (m_value != 0.0) {
            m_operator = '*';
            m_clear = true;
        }
    } else if (button == m_ui->DivideButton) {
        if (m_operator != 0)
            value = calculate();
        m_value = QLocale::system().toDouble(value);
        if (m_value != 0.0) {
            m_operator = '/';
            m_clear = true;
        }
    } else if (button == m_ui->CalculateButton) {
        calculate();
    } else if (button == m_ui->SignButton) {
        double d = QLocale::system().toDouble(value);
        if (d != 0.0) {
            if (d < 0.0) {
                value = value.remove(0, 1);
            } else {
                value = "-" + value;
            }
            setUiFieldValue(m_ui->ValueField, value);
        }
    } else if (button == m_ui->PercentButton) {
        double d = QLocale::system().toDouble(value);
        if (d != 0.0) {
            QLocale locale = QLocale::system();
            locale.setNumberOptions(QLocale::OmitGroupSeparator);
            setUiFieldValue(m_ui->ValueField, locale.toString(d / 100));
            m_clear = true;
        }
    } else if (isNumber) {
        if (number == 0 && (value == "0" || value == "-")) {
        } else {
            if (m_clear || value == "0") {
                value = "";
                m_clear = false;
            }
            value += QString::number(number);
            setUiFieldValue(m_ui->ValueField, value);
        }
    }
}

QString QxCalculatorDialog::calculate()
{
    QString value = uiFieldValue(m_ui->ValueField).toString();
    double value2 = QLocale::system().toDouble(value);
    QLocale locale = QLocale::system();
    locale.setNumberOptions(QLocale::OmitGroupSeparator);
    QString result = "0";

    if (m_operator == '+') {
        result = locale.toString(m_value + value2);
    } else if (m_operator == '-') {
        result = locale.toString(m_value - value2);
    } else if (m_operator == '*') {
        result = locale.toString(m_value * value2);
    } else if (m_operator == '/') {
        if (value2 == 0) {
            QMessageBox::information(this, tr("Fehler"), tr("Teilen durch 0 ist nicht möglich!"));
        } else {
            result = locale.toString(m_value / value2);
        }
    } else if (m_operator == 0) {
        if (m_ui->ButtonBox->isVisible())
            accept();
        return value;
    }

    setUiFieldValue(m_ui->ValueField, result);

    m_operator = QChar();
    m_value = 0.0;
    m_clear = true;

    return result;
}
