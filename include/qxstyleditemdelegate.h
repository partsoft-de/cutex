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

#ifndef QXSTYLEDITEMDELEGATE_H
#define QXSTYLEDITEMDELEGATE_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxStyledItemDelegate erweitert die Qt-Klasse QStyledItemDelegate.

  %QxStyledItemDelegate stellt Methoden zum erzeugen von Standard-, sowie cutex-spezifischen Editoren zur Verfügung.
  Zudem stellt die Klasse einen speziellen Mechanismus zur Validierung bereit, bei dem ungültige Eingaben farblich
  hervorgehoben werden.
*/
class QxStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QxStyledItemDelegate(QObject *parent = 0);
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

protected:
    int fieldHeight() const;
    void setFieldHeight(int height, QWidget *editor = 0);
    QWidget* createLineEditEditor(QWidget *parent, const QString &name, bool fieldButton = false) const;
    QWidget* createSpinBoxEditor(QWidget *parent, const QString &name) const;
    QWidget* createDoubleSpinBoxEditor(QWidget *parent, const QString &name) const;
    QWidget* createPlainTextEditEditor(QWidget *parent, const QString &name) const;
    QLineEdit* lineEditField(QWidget *editor) const;
    QSpinBox* spinBoxField(QWidget *editor) const;
    QDoubleSpinBox* doubleSpinBoxField(QWidget *editor) const;
    QPlainTextEdit* plainTextEditField(QWidget *editor) const;
    QToolButton* fieldButton(QWidget *editor) const;
    void processUiField(QWidget *editor);
    virtual QString validateUiField(QWidget *editor) const;
    virtual void preProcessUiField(QWidget *editor);
    virtual void postProcessUiField(QWidget *editor);
    QVariant uiFieldValue(QWidget *editor) const;
    bool setUiFieldValue(QWidget *editor, QVariant value);
    virtual void fieldButtonClicked(QWidget *editor);
    virtual bool eventFilter(QObject *object, QEvent *event);

private:
    int m_fieldHeight;
    bool m_fieldButtonClicked;

private slots:
    void processUiField();
    void setUiFieldModified();
    void fieldButtonClicked();
};

} // namespace

#endif // QXSTYLEDITEMDELEGATE_H
