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

#ifndef QXUIFIELD_H
#define QXUIFIELD_H

#include "cutex.h"

namespace cutex {

#define QX_REGISTER_UIFIELD(classname) Q_CLASSINFO("QxUiField", classname)

/*!
  \brief Die Klasse %QxUiField ist eine Wrapper-Klasse für diverse Eingabe-Steuerelemente.

  %QxUiField stellt u.a. einheitliche Methoden zum Ändern und Abfragen der Werte von Eingabe-Steuerelementen bereit.
  Die Methoden der Klasse dürfen nicht direkt verwendet werden, der Aufruf erfolgt stattdessen über die entsprechenden
  Methoden der Klassen QxDialog, QxForm und QxWizard.

  \sa QxDialog
  \sa QxForm
  \sa QxWizard
*/
class QxUiField
{
    friend class QxDialog;
    friend class QxForm;
    friend class QxWizard;
    friend class QxStyledItemDelegate;

private:
    static const QString STYLE_VALID;
    static const QString STYLE_INVALID;

private:
    QxUiField();
    static bool isUiField(QWidget *widget);
    static bool initialize(QWidget *uiField, QObject *uiController);
    static bool isModified(QWidget *uiField);
    static void setModified(QWidget *uiField, bool modified);
    static bool isReadOnly(QWidget *uiField);
    static QVariant value(QWidget *uiField, QVariant::Type type = QVariant::Invalid);
    static bool setValue(QWidget *uiField, const QVariant &value);
    static void reset(QWidget *uiField);
    static void selectAll(QWidget *uiField);
    static void setErrorText(QWidget *uiField, const QString &errorText);
    static QString errorText(QWidget *uiField);
    static QCompleter* completer(QWidget *uiField);
    static QString sqlMapping(QWidget *uiField);
    static void setSqlMapping(QWidget *uiField, const QString &sqlField);
    static QString className(QWidget *uiField);
};

} // namespace

#endif // QXUIFIELD_H
