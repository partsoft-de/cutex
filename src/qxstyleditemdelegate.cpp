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

#include "qxstyleditemdelegate.h"
#include "qxapplication.h"
#include "qxmainwindow.h"
#include "qxuifield.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Delegate mit dem Elternobjekt <i>parent</i>.
*/
QxStyledItemDelegate::QxStyledItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    m_fieldHeight = 20;
    m_fieldButtonClicked = false;
}

/*!
  Übernimmt die Daten des Models in den Editor <i>editor</i>.
*/
void QxStyledItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (QWidget *uiField = editor->focusProxy()) {
        QxUiField::setValue(uiField, index.data(Qt::EditRole));
        QxUiField::initialize(uiField, const_cast<QxStyledItemDelegate*>(this));
        QxUiField::setErrorText(uiField, validateUiField(editor));
        if (qxMainWin)
            qxMainWin->setStatusText(QxUiField::errorText(uiField));
    }

    if (QToolButton *button = fieldButton(editor))
        connect(button, SIGNAL(clicked(bool)), this, SLOT(fieldButtonClicked()));
}

/*!
  Übernimmt die Daten des Editors <i>editor</i> in das Model.
*/
void QxStyledItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index, uiFieldValue(editor), Qt::EditRole);
}

/*!
  Gibt die Standardhöhe der Eingabefelder zurück.

  \sa setFieldHeight(int height, QWidget *editor)
*/
int QxStyledItemDelegate::fieldHeight() const
{
    return m_fieldHeight;
}

/*!
  Ändert die Standardhöhe für Eingabefelder auf den Wert <i>height</i>.

  \sa fieldHeight() const
*/
void QxStyledItemDelegate::setFieldHeight(int height, QWidget *editor)
{
    m_fieldHeight = height;

    if (editor && editor->focusProxy())
        editor->focusProxy()->setFixedHeight(height);
}

/*!
  Erzeugt einen Editor für ein QLineEdit mit dem Namen <i>name</i>. Wird für <i>fieldButton</i> der Wert true
  übergeben, wird im Editor zusätzlich ein Toolbutton für weitere Aktionen erzeugt.

  \sa fieldButtonClicked()
*/
QWidget* QxStyledItemDelegate::createLineEditEditor(QWidget *parent, const QString &name, bool fieldButton) const
{
    QWidget *editor = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(editor);
    QLineEdit *uiField = new QLineEdit(editor);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(uiField);

    editor->setObjectName(name);
    editor->setFont(qxApp->font());
    editor->setLayout(layout);
    editor->setFocusProxy(uiField);

    uiField->setFixedHeight(m_fieldHeight);

    if (fieldButton) {
        QToolButton *button = new QToolButton(editor);
        button->setFixedSize(23, 22);
        button->setText("...");
        layout->addWidget(button);
    }

    return editor;
}

/*!
  Erzeugt einen Editor für eine QSpinBox mit dem Namen <i>name</i>.
*/
QWidget* QxStyledItemDelegate::createSpinBoxEditor(QWidget *parent, const QString &name) const
{
    QWidget *editor = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(editor);
    QSpinBox *uiField = new QSpinBox(editor);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(uiField);

    editor->setObjectName(name);
    editor->setFont(qxApp->font());
    editor->setLayout(layout);
    editor->setFocusProxy(uiField);

    uiField->setFixedHeight(m_fieldHeight);
    uiField->setButtonSymbols(QSpinBox::NoButtons);

    return editor;
}

/*!
  Erzeugt einen Editor für eine QDoubleSpinBox mit dem Namen <i>name</i>.
*/
QWidget* QxStyledItemDelegate::createDoubleSpinBoxEditor(QWidget *parent, const QString &name) const
{
    QWidget *editor = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(editor);
    QDoubleSpinBox *uiField = new QDoubleSpinBox(editor);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(uiField);

    editor->setObjectName(name);
    editor->setFont(qxApp->font());
    editor->setLayout(layout);
    editor->setFocusProxy(uiField);

    uiField->setFixedHeight(m_fieldHeight);
    uiField->setButtonSymbols(QDoubleSpinBox::NoButtons);

    return editor;
}

/*!
  Erzeugt einen Editor für ein QPlainTextEdit mit dem Namen <i>name</i>.
*/
QWidget* QxStyledItemDelegate::createPlainTextEditEditor(QWidget *parent, const QString &name) const
{
    QWidget *editor = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(editor);
    QPlainTextEdit *uiField = new QPlainTextEdit(editor);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(uiField);

    editor->setObjectName(name);
    editor->setFont(qxApp->font());
    editor->setLayout(layout);
    editor->setFocusProxy(uiField);

    uiField->setFixedHeight(m_fieldHeight);

    return editor;
}

/*!
  Gibt einen Zeiger auf das QLineEdit des Editors <i>editor</i> zurück.
*/
QLineEdit* QxStyledItemDelegate::lineEditField(QWidget *editor) const
{
    return editor->findChild<QLineEdit*>();
}

/*!
  Gibt einen Zeiger auf die QSpinBox des Editors <i>editor</i> zurück.
*/
QSpinBox* QxStyledItemDelegate::spinBoxField(QWidget *editor) const
{
    return editor->findChild<QSpinBox*>();
}

/*!
  Gibt einen Zeiger auf die QDoubleSpinBox des Editors <i>editor</i> zurück.
*/
QDoubleSpinBox* QxStyledItemDelegate::doubleSpinBoxField(QWidget *editor) const
{
    return editor->findChild<QDoubleSpinBox*>();
}

/*!
  Gibt einen Zeiger auf das QPlainTextEdit des Editors <i>editor</i> zurück.
*/
QPlainTextEdit* QxStyledItemDelegate::plainTextEditField(QWidget *editor) const
{
    return editor->findChild<QPlainTextEdit*>();
}

/*!
  Gibt einen Zeiger auf den Toolbutton des Editors <i>editor</i> zurück.
*/
QToolButton* QxStyledItemDelegate::fieldButton(QWidget *editor) const
{
    return editor->findChild<QToolButton*>();
}

/*!
  Wird aufgerufen wenn der Inhalt des Editors <i>editor</i> geändert wurde. Die Methode kann auch manuell aufgerufen
  werden um die Inhalte erneut zu verarbeiten.

  \sa preProcessUiField(QWidget *editor)
  \sa postProcessUiField(QWidget *editor)
*/
void QxStyledItemDelegate::processUiField(QWidget *editor)
{
    QWidget *uiField = editor->focusProxy();
    bool modified = QxUiField::isModified(uiField);

    static int calls = 0;
    if (calls > 0)
        return;

    calls = 1;
    preProcessUiField(editor);
    calls = 0;
    QxUiField::setErrorText(uiField, validateUiField(editor));

    if (modified) {
        QxUiField::setModified(uiField, false);
        postProcessUiField(editor);
    }
}

/*!
  Wird zur Validierung des Editors <i>editor</i> aufgerufen. Geben Sie eine passende Fehlerbeschreibung zurück, bzw.
  einen Leerstring wenn der Inhalt gültig ist.
*/
QString QxStyledItemDelegate::validateUiField(QWidget *editor) const
{
    Q_UNUSED(editor);
    return QString();
}

/*!
  Wird aufgerufen wenn der Inhalt des Editors <i>editor</i> geändert wurde. Der neue Inhalt wurde noch nicht validiert
  und kann hier noch einmal geändert werden.

  \sa postProcessUiField(QWidget *editor)
*/
void QxStyledItemDelegate::preProcessUiField(QWidget *editor)
{
    Q_UNUSED(editor);
}

/*!
  Wird aufgerufen wenn der Inhalt des Editors <i>editor</i> geändert wurde.

  \sa processUiField(QWidget *editor)
*/
void QxStyledItemDelegate::postProcessUiField(QWidget *editor)
{
    Q_UNUSED(editor);
}

/*!
  Gibt den aktuellen Wert des Editors <i>editor</i> zurück.

  \sa setUiFieldValue(QWidget *editor, const QVariant &value)
*/
QVariant QxStyledItemDelegate::uiFieldValue(QWidget *editor) const
{
    return QxUiField::value(editor->focusProxy());
}

/*!
  Setzt den Wert des Editors <i>editor</i> auf den Wert <i>value</i>.

  \sa uiFieldValue(QWidget *editor)
*/
bool QxStyledItemDelegate::setUiFieldValue(QWidget *editor, QVariant value)
{
    bool success = true;
    QWidget *uiField = editor->focusProxy();

    if (uiFieldValue(editor) != value)
        success = QxUiField::setValue(uiField, value);

    if (success)
        processUiField(editor);

    return success;
}

/*!
  Wird aufgerufen wenn der Toolbutton des Editors <i>editor</i> betätigt wurde.
*/
void QxStyledItemDelegate::fieldButtonClicked(QWidget *editor)
{
    Q_UNUSED(editor);
}

/*!
  Wird aufgerufen um das Ereignis <i>event</i> zu verarbeiten.
*/
bool QxStyledItemDelegate::eventFilter(QObject *object, QEvent *event)
{
    QWidget *widget = static_cast<QWidget*>(object);
    QWidget *editor = 0;
    QWidget *uiField = 0;

    if (widget->focusProxy()) {
        editor = widget;
        uiField = editor->focusProxy();
    } else {
        uiField = widget;
        editor = static_cast<QWidget*>(widget->parent());
    }

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Tab:
            emit commitData(editor);
            emit closeEditor(editor, QAbstractItemDelegate::EditNextItem);
            return true;
        case Qt::Key_Backtab:
            emit commitData(editor);
            emit closeEditor(editor, QAbstractItemDelegate::EditPreviousItem);
            return true;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if (keyEvent->modifiers() == Qt::NoModifier) {
                emit commitData(editor);
                emit closeEditor(editor, QAbstractItemDelegate::NoHint);
                return true;
            }
        }

        if (keyEvent->key() == qxApp->fieldButtonHotkey()) {
            m_fieldButtonClicked = true;
            fieldButtonClicked(editor);
            m_fieldButtonClicked = false;
            return true;
        }
    }

    if (event->type() == QEvent::ShortcutOverride) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Escape:
            emit closeEditor(editor, QAbstractItemDelegate::NoHint);
            event->accept();
            return true;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if (keyEvent->modifiers() == Qt::NoModifier) {
                emit commitData(editor);
                emit closeEditor(editor, QAbstractItemDelegate::NoHint);
                return true;
            }
        }
    }

    if (!m_fieldButtonClicked) {
        if (event->type() == QEvent::FocusOut || (event->type() == QEvent::Hide && uiField->isWindow())) {
            if (!editor->isActiveWindow() || qxApp->focusWidget() != uiField) {
                emit commitData(editor);
                emit closeEditor(editor, QAbstractItemDelegate::NoHint);
                return true;
            }
        }
    }

    return false;
}

void QxStyledItemDelegate::processUiField()
{
    QWidget *uiField = qobject_cast<QWidget*>(sender());

    if (!uiField) {
        QCompleter *completer = qobject_cast<QCompleter*>(sender());
        if (completer)
            uiField = completer->widget();
    }

    if (uiField->objectName().isEmpty()) {
        QWidget *parent = uiField->parentWidget();
        if (parent && QxUiField::isUiField(parent))
            uiField = parent;
    }

    processUiField(qobject_cast<QWidget*>(uiField->parent()));
}

void QxStyledItemDelegate::setUiFieldModified()
{
    QWidget *uiField = qobject_cast<QWidget*>(sender());

    if (!uiField) {
        QCompleter *completer = qobject_cast<QCompleter*>(sender());
        if (completer)
            uiField = completer->widget();
    }

    if (uiField->objectName().isEmpty()) {
        QWidget *parent = uiField->parentWidget();
        if (parent && QxUiField::isUiField(parent))
            uiField = parent;
    }

    QxUiField::setModified(uiField, true);
}

void QxStyledItemDelegate::fieldButtonClicked()
{
    QToolButton *button = qobject_cast<QToolButton*>(sender());

    m_fieldButtonClicked = true;
    fieldButtonClicked(qobject_cast<QWidget*>(button->parent()));
    m_fieldButtonClicked = false;
}
