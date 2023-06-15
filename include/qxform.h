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

#ifndef QXFORM_H
#define QXFORM_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxForm vereinfacht die Implementierung von Formularen.

  %QxForm erweitert die Klasse QWidget um eine Sammlung virtueller Methoden, mit deren Hilfe sich das Implementieren
  vieler Slots erübrigt. Zudem stellt die Formularklasse einen speziellen Mechanismus zur Validierung von Eingabefeldern
  bereit, bei dem ungültige Eingaben farblich hervorgehoben werden, ohne den User am weiterarbeiten zu behindern.

  \sa QxUiField
*/
class QxForm : public QWidget
{
    Q_OBJECT

public:
    QxForm(QWidget *parent = nullptr);
    bool isModified();
    bool isValid();
    void validate(QWidget *uiField = nullptr);
    bool isUiFieldValid(QWidget *uiField);
    virtual void retranslateUi();

public slots:
    virtual void setModified(bool modified = true);

protected:
    void processUiField(QWidget *uiField);
    virtual QString validateUiField(QWidget *uiField);
    virtual void preProcessUiField(QWidget *uiField);
    virtual void postProcessUiField(QWidget *uiField);
    virtual void relockUiField(QWidget *uiField);
    virtual void buttonClicked(QAbstractButton *button);
    virtual void setUiFieldModified(QWidget *uiField, bool modified = true);
    QVariant uiFieldValue(QWidget *uiField) const;
    bool setUiFieldValue(QWidget *uiField, QVariant value, const QSqlRelation &sqlRelation = QSqlRelation());
    void relockUiFields();
    virtual void focusFirstUiField(QWidget *parent = nullptr);
    void resetUiField(QWidget *uiField);
    void resetUiFields();
    QString uiFieldSqlMapping(QWidget *uiField);
    void setUiFieldSqlMapping(QWidget *uiField, const QString &sqlField);
    QSqlRelation uiFieldSqlRelation(QWidget *uiField);
    void setUiFieldSqlRelation(QWidget *uiField, const QSqlRelation &sqlRelation);
    void uiFieldValues(QSqlRecord *record);
    void setUiFieldValues(QSqlRecord *record);
    virtual bool eventFilter(QObject *object, QEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void changeEvent(QEvent *event);

protected slots:
    virtual void processLink(const QString &link);

private:
    bool m_initialized;
    bool m_modified;
    QList<QWidget*> m_invalidUiFields;
    QMap<QWidget*, QSqlRelation> m_sqlRelations;

private:
    void initialize(const QObject *object);
    void relockUiFields(QWidget *uiField);
    void resetUiFields(QWidget *uiField);
    void uiFieldValues(QSqlRecord *record, QWidget *uiField);
    void setUiFieldValues(QSqlRecord *record, QWidget *uiField);

private slots:
    void processUiField();
    void setUiFieldModified();
    void buttonClicked();
};

} // namespace

#endif // QXFORM_H
