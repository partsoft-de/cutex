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

#include "qxuifield.h"
#include "qxintedit.h"
#include "qxdoubleedit.h"
#include "qxdateedit.h"

using namespace cutex;

const QString QxUiField::STYLE_VALID = "background-color: none; selection-background-color: none;";
const QString QxUiField::STYLE_INVALID = "background-color: orange; selection-background-color: orange;";

bool QxUiField::isUiField(QWidget *widget)
{
    QString className = QxUiField::className(widget);

    if (className == "QLineEdit")
        return true;

    if (className == "QPlainTextEdit")
        return true;

    if (className == "QSpinBox")
        return true;

    if (className == "QDoubleSpinBox")
        return true;

    if (className == "QCheckBox")
        return true;

    if (className == "QComboBox")
        return true;

    if (className == "QDateEdit")
        return true;

    if (className == "QRadioButton")
        return true;

    if (className == "QFontComboBox")
        return true;

    if (className == "cutex::QxDateEdit")
        return true;

    return false;
}

bool QxUiField::initialize(QWidget *uiField, QObject *uiController)
{
    QString className = QxUiField::className(uiField);

    if (className == "QLineEdit" || className == "QxIntEdit" || className == "QxDoubleEdit") {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(uiField);
        QObject::connect(lineEdit, SIGNAL(textChanged(QString)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(lineEdit, SIGNAL(editingFinished()), uiController, SLOT(processUiField()));
        if (lineEdit->completer()) {
            QObject::connect(lineEdit->completer(), SIGNAL(activated(QString)), uiController,
                SLOT(setUiFieldModified()));
            QObject::connect(lineEdit->completer(), SIGNAL(activated(QString)), uiController,
                SLOT(processUiField()));
        }
        lineEdit->installEventFilter(uiController);
        lineEdit->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QPlainTextEdit") {
        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit*>(uiField);
        QObject::connect(plainTextEdit, SIGNAL(textChanged()), uiController, SLOT(setUiFieldModified()));
        plainTextEdit->installEventFilter(uiController);
        plainTextEdit->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QSpinBox") {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(uiField);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(spinBox, SIGNAL(editingFinished()), uiController, SLOT(processUiField()));
        spinBox->installEventFilter(uiController);
        spinBox->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QDoubleSpinBox") {
        QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox*>(uiField);
        QObject::connect(doubleSpinBox, SIGNAL(valueChanged(double)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(doubleSpinBox, SIGNAL(editingFinished()), uiController, SLOT(processUiField()));
        doubleSpinBox->installEventFilter(uiController);
        doubleSpinBox->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QCheckBox") {
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(uiField);
        QObject::connect(checkBox, SIGNAL(toggled(bool)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(checkBox, SIGNAL(toggled(bool)), uiController, SLOT(processUiField()));
        checkBox->installEventFilter(uiController);
        checkBox->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QComboBox") {
        QComboBox *comboBox = qobject_cast<QComboBox*>(uiField);
        if (comboBox->lineEdit()) {
            QObject::connect(comboBox->lineEdit(), SIGNAL(textChanged(QString)), uiController,
                SLOT(setUiFieldModified()));
            QObject::connect(comboBox->lineEdit(), SIGNAL(editingFinished()), uiController, SLOT(processUiField()));
        }
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), uiController, SLOT(processUiField()));
        if (comboBox->completer()) {
            QObject::connect(comboBox->completer(), SIGNAL(activated(QString)), uiController,
                SLOT(setUiFieldModified()));
            QObject::connect(comboBox->completer(), SIGNAL(activated(QString)), uiController,
                SLOT(processUiField()));
        }
        comboBox->installEventFilter(uiController);
        comboBox->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QDateEdit") {
        QDateEdit *dateEdit = qobject_cast<QDateEdit*>(uiField);
        QObject::connect(dateEdit, SIGNAL(dateChanged(QDate)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(dateEdit, SIGNAL(editingFinished()), uiController, SLOT(processUiField()));
        dateEdit->installEventFilter(uiController);
        dateEdit->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QRadioButton") {
        QRadioButton *radioButton = qobject_cast<QRadioButton*>(uiField);
        QObject::connect(radioButton, SIGNAL(toggled(bool)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), uiController, SLOT(processUiField()));
        radioButton->installEventFilter(uiController);
        radioButton->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "QFontComboBox") {
        QFontComboBox *fontComboBox = qobject_cast<QFontComboBox*>(uiField);
        if (fontComboBox->lineEdit()) {
            QObject::connect(fontComboBox->lineEdit(), SIGNAL(textChanged(QString)), uiController,
                SLOT(setUiFieldModified()));
            QObject::connect(fontComboBox->lineEdit(), SIGNAL(editingFinished()), uiController,
                SLOT(processUiField()));
        }
        QObject::connect(fontComboBox, SIGNAL(currentIndexChanged(int)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(fontComboBox, SIGNAL(currentIndexChanged(int)), uiController, SLOT(processUiField()));
        fontComboBox->installEventFilter(uiController);
        fontComboBox->setProperty("initialValue", QxUiField::value(uiField));
        return true;
    }

    if (className == "cutex::QxDateEdit") {
        QxDateEdit *dateEdit = qobject_cast<QxDateEdit*>(uiField);
        QObject::connect(dateEdit, SIGNAL(dateChanged(QDate)), uiController, SLOT(setUiFieldModified()));
        QObject::connect(dateEdit, SIGNAL(editingFinished()), uiController, SLOT(processUiField()));
        dateEdit->installEventFilter(uiController);
        dateEdit->setProperty("initialValue", QxUiField::value(uiField));
    }

    return false;
}

bool QxUiField::isModified(QWidget *uiField)
{
    return uiField->property("modified").toBool();
}

void QxUiField::setModified(QWidget *uiField, bool modified)
{
    uiField->setProperty("modified", QVariant(modified));
}

bool QxUiField::isReadOnly(QWidget *uiField)
{
    QString className = QxUiField::className(uiField);

    if (className == "QLineEdit" || className == "QxIntEdit" || className == "QxDoubleEdit") {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(uiField);
        return lineEdit->isReadOnly();
    }

    if (className == "QPlainTextEdit") {
        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit*>(uiField);
        return plainTextEdit->isReadOnly();
    }

    if (className == "QSpinBox") {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(uiField);
        return spinBox->isReadOnly();
    }

    if (className == "QDoubleSpinBox") {
        QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox*>(uiField);
        return doubleSpinBox->isReadOnly();
    }

    if (className == "QCheckBox") {
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(uiField);
        return (!checkBox->isEnabled());
    }

    if (className == "QComboBox") {
        QComboBox *comboBox = qobject_cast<QComboBox*>(uiField);
        return !comboBox->isEditable();
    }

    if (className == "QDateEdit") {
        QDateEdit *dateEdit = qobject_cast<QDateEdit*>(uiField);
        return dateEdit->isReadOnly();
    }

    if (className == "QRadioButton") {
        QRadioButton *radioButton = qobject_cast<QRadioButton*>(uiField);
        return (!radioButton->isEnabled());
    }

    if (className == "cutex::QxDateEdit") {
        QxDateEdit *dateEdit = qobject_cast<QxDateEdit*>(uiField);
        return dateEdit->isReadOnly();
    }

    return false;
}

QVariant QxUiField::value(QWidget *uiField, QVariant::Type type)
{
    QString className = QxUiField::className(uiField);

    if (className == "QLineEdit") {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(uiField);
        return lineEdit->text();
    }

    if (className == "QxIntEdit") {
        QxIntEdit *intEdit = qobject_cast<QxIntEdit*>(uiField);
        return intEdit->value();
    }

    if (className == "QxDoubleEdit") {
        QxDoubleEdit *doubleEdit = qobject_cast<QxDoubleEdit*>(uiField);
        return doubleEdit->value();
    }

    if (className == "QPlainTextEdit") {
        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit*>(uiField);
        return plainTextEdit->toPlainText();
    }

    if (className == "QSpinBox") {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(uiField);
        return spinBox->value();
    }

    if (className == "QDoubleSpinBox") {
        QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox*>(uiField);
        return doubleSpinBox->value();
    }

    if (className == "QCheckBox") {
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(uiField);
        return checkBox->isChecked();
    }

    if (className == "QComboBox") {
        QComboBox *comboBox = qobject_cast<QComboBox*>(uiField);
        if (type == QVariant::Int || type == QVariant::Double || type == QVariant::LongLong) {
            return comboBox->currentIndex();
        } else {
            return comboBox->currentText();
        }
    }

    if (className == "QDateEdit") {
        QDateEdit *dateEdit = qobject_cast<QDateEdit*>(uiField);
        if (type == QVariant::Int || type == QVariant::LongLong) {
            return dateEdit->date().toJulianDay();
        } else if (type == QVariant::String) {
            return dateEdit->date().toString(Qt::ISODate);
        } else {
            return dateEdit->date();
        }
    }

    if (className == "QRadioButton") {
        QRadioButton *radioButton = qobject_cast<QRadioButton*>(uiField);
        return radioButton->isChecked();
    }

    if (className == "QFontComboBox") {
        QFontComboBox *fontComboBox = qobject_cast<QFontComboBox*>(uiField);
        return fontComboBox->currentFont().family();
    }

    if (className == "cutex::QxDateEdit") {
        QxDateEdit *dateEdit = qobject_cast<QxDateEdit*>(uiField);
        if (type == QVariant::Int || type == QVariant::LongLong) {
            return dateEdit->date().toJulianDay();
        } else if (type == QVariant::String) {
            return dateEdit->date().toString(Qt::ISODate);
        } else {
            return dateEdit->date();
        }
    }

    return QVariant();
}

bool QxUiField::setValue(QWidget *uiField, const QVariant &value)
{
    QString className = QxUiField::className(uiField);

    if (className == "QLineEdit") {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(uiField);
        lineEdit->setText(value.toString());
        return true;
    }

    if (className == "QxIntEdit") {
        QxIntEdit *intEdit = qobject_cast<QxIntEdit*>(uiField);
        intEdit->setValue(value.toInt());
        return true;
    }

    if (className == "QxDoubleEdit") {
        QxDoubleEdit *doubleEdit = qobject_cast<QxDoubleEdit*>(uiField);
        doubleEdit->setValue(value.toDouble());
        return true;
    }

    if (className == "QPlainTextEdit") {
        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit*>(uiField);
        plainTextEdit->setPlainText(value.toString());
        return true;
    }

    if (className == "QSpinBox") {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(uiField);
        spinBox->setValue(value.toInt());
        return true;
    }

    if (className == "QDoubleSpinBox") {
        QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox*>(uiField);
        doubleSpinBox->setValue(value.toDouble());
        return true;
    }

    if (className == "QCheckBox") {
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(uiField);
        checkBox->setChecked(value.toBool());
        return true;
    }

    if (className == "QComboBox") {
        QComboBox *comboBox = qobject_cast<QComboBox*>(uiField);
        bool success = false;
        if (value.type() == QVariant::String) {
            QLineEdit *lineEdit = comboBox->lineEdit();
            if (lineEdit) {
                lineEdit->setText(value.toString());
                success = true;
            }
            int index = comboBox->findText(value.toString());
            if (index > -1) {
                comboBox->setCurrentIndex(index);
                success = true;
            }
            return success;
        }
        if (value.type() == QVariant::Int || value.type() == QVariant::Double || value.type() == QVariant::LongLong) {
            comboBox->setCurrentIndex(value.toInt());
            if (comboBox->currentIndex() == value.toInt())
                success = true;
            return success;
        }
    }

    if (className == "QDateEdit") {
        QDateEdit *dateEdit = qobject_cast<QDateEdit*>(uiField);
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            dateEdit->setDate(QDate::fromJulianDay(value.toLongLong()));
        } else if (value.type() == QVariant::String) {
            dateEdit->setDate(QDate::fromString(value.toString(), Qt::ISODate));
        } else {
            dateEdit->setDate(value.toDate());
        }
        return true;
    }

    if (className == "QRadioButton") {
        QRadioButton *radioButton = qobject_cast<QRadioButton*>(uiField);
        radioButton->setChecked(value.toBool());
        return true;
    }

    if (className == "QFontComboBox") {
        QFontComboBox *fontComboBox = qobject_cast<QFontComboBox*>(uiField);
        if (value.type() == QVariant::Font) {
            fontComboBox->setCurrentFont(value.value<QFont>());
            return true;
        }
        if (value.type() == QVariant::String) {
            fontComboBox->setCurrentFont(QFont(value.toString()));
            return true;
        }
    }

    if (className == "cutex::QxDateEdit") {
        QxDateEdit *dateEdit = qobject_cast<QxDateEdit*>(uiField);
        if (value.type() == QVariant::Int || value.type() == QVariant::LongLong) {
            dateEdit->setDate(QDate::fromJulianDay(value.toLongLong()));
        } else if (value.type() == QVariant::String) {
            dateEdit->setDate(QDate::fromString(value.toString(), Qt::ISODate));
        } else {
            dateEdit->setDate(value.toDate());
        }
        return true;
    }

    return false;
}

void QxUiField::reset(QWidget *uiField)
{
    if (isUiField(uiField))
        setValue(uiField, uiField->property("initialValue"));
}

void QxUiField::selectAll(QWidget *uiField)
{
    QString className = QxUiField::className(uiField);

    if (className == "QLineEdit" || className == "QxIntEdit" || className == "QxDoubleEdit") {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(uiField);
        lineEdit->selectAll();
        return;
    }

    if (className == "QPlainTextEdit") {
        QPlainTextEdit *plainTextEdit = qobject_cast<QPlainTextEdit*>(uiField);
        plainTextEdit->selectAll();
        return;
    }

    if (className == "QSpinBox") {
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(uiField);
        spinBox->selectAll();
        return;
    }

    if (className == "QDoubleSpinBox") {
        QDoubleSpinBox *doubleSpinBox = qobject_cast<QDoubleSpinBox*>(uiField);
        doubleSpinBox->selectAll();
        return;
    }

    if (className == "QComboBox") {
        QComboBox *comboBox = qobject_cast<QComboBox*>(uiField);
        QLineEdit *lineEdit = comboBox->lineEdit();
        if (lineEdit)
            lineEdit->selectAll();
        return;
    }

    if (className == "QDateEdit") {
        QDateEdit *dateEdit = qobject_cast<QDateEdit*>(uiField);
        dateEdit->selectAll();
        return;
    }

    if (className == "QxDateEdit") {
        QxDateEdit *dateEdit = qobject_cast<QxDateEdit*>(uiField);
        dateEdit->selectAll();
        return;
    }
}

void QxUiField::setErrorText(QWidget *uiField, const QString &errorText)
{
    QString className = QxUiField::className(uiField);

    uiField->setProperty("errorText", errorText);

    if (className == "QComboBox") {
        QComboBox *comboBox = qobject_cast<QComboBox*>(uiField);
        QLineEdit *lineEdit = comboBox->lineEdit();
        if (lineEdit)
            uiField = lineEdit;
    }

    if (errorText.isEmpty()) {
        uiField->setStyleSheet(QxUiField::STYLE_VALID);
    } else {
        uiField->setStyleSheet(QxUiField::STYLE_INVALID);
    }
}

QString QxUiField::errorText(QWidget *uiField)
{
    return uiField->property("errorText").toString();
}

QCompleter* QxUiField::completer(QWidget *uiField)
{
    QString className = QxUiField::className(uiField);

    if (className == "QLineEdit")
        return qobject_cast<QLineEdit*>(uiField)->completer();

    if (className == "QComboBox")
        return qobject_cast<QComboBox*>(uiField)->completer();

    return 0;
}

QString QxUiField::sqlMapping(QWidget *uiField)
{
    return uiField->property("sqlMapping").toString();
}

void QxUiField::setSqlMapping(QWidget *uiField, const QString &sqlField)
{
    uiField->setProperty("sqlMapping", sqlField);
}

QString QxUiField::className(QWidget *uiField)
{
    QString name;

    int index = uiField->metaObject()->indexOfClassInfo("QxUiField");
    if (index == -1) {
        name = CLASSNAME(uiField);
    } else {
        name = uiField->metaObject()->classInfo(index).value();
    }

    return name;
}

QxUiField::QxUiField()
{
}
