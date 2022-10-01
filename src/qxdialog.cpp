/***********************************************************************************************************************
**
** Copyright (C) 2016-2022 Partsoft UG (haftungsbeschränkt)
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

#include "qxdialog.h"
#include "qxapplication.h"
#include "qxmainwindow.h"
#include "qxuifield.h"
#include "qxtextedit.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Dialog mit dem Elternobjekt <i>parent</i>.
*/
QxDialog::QxDialog(QWidget *parent) : QDialog(parent)
{
    m_initialized = false;
    m_modified = false;
}

/*!
  Gibt true zurück, wenn Dialogdaten geändert wurden.

  \sa setModified(bool modified)
*/
bool QxDialog::isModified()
{
    return m_modified;
}

/*!
  Setzt das Änderungsflag der Dialogdaten auf den Wert <i>modified</i>.

  \sa isModified()
*/
void QxDialog::setModified(bool modified)
{
    m_modified = modified;
}

/*!
  Gibt true zurück, wenn alle Benutzereingaben gütlig sind.

  \sa isUiFieldValid(QWidget *uiField)
*/
bool QxDialog::isValid()
{
    return m_invalidUiFields.isEmpty();
}

/*!
  Validiert die Benutzereingaben im Feld <i>uiField</i>. Wenn kein Feld angegeben wird, werden alle Dialogdaten
  validiert.
*/
void QxDialog::validate(QWidget *uiField)
{
    if (uiField == 0)
        uiField = this;

    if (QxUiField::isUiField(uiField)) {
        QString error = validateUiField(uiField);
        QxUiField::setErrorText(uiField, error);
        if (error.isEmpty()) {
            if (m_invalidUiFields.contains(uiField))
                m_invalidUiFields.removeOne(uiField);
        } else {
            if (!m_invalidUiFields.contains(uiField))
                m_invalidUiFields.append(uiField);
        }
        return;
    }

    QObjectList children = uiField->children();
    for (QObject *child : children) {
        uiField = qobject_cast<QWidget*>(child);
        if (uiField)
            validate(uiField);
    }
}

/*!
  Gibt true zurück, wenn die Benutzereingaben im Feld <i>uiField</i> gültig sind.

  \sa isValid()
*/
bool QxDialog::isUiFieldValid(QWidget *uiField)
{
    return !m_invalidUiFields.contains(uiField);
}

/*!
  Wird aufgerufen wenn die Sprache geändert wurde.
*/
void QxDialog::retranslateUi()
{
}

/*!
  Ändert die Sichtbarkeit des Dialogs auf den Wert <i>visible</i>.
*/
void QxDialog::setVisible(bool visible)
{
    QDialog::setVisible(visible);

    emit visibilityChanged(visible);
}

/*!
  Prüft ob die Benutzereingaben gültig sind. Bei Erfolg wird das Dialogfenster versteckt und der Dialogcode auf
  QDialog::Accepted gesetzt.

  \sa reject()
*/
void QxDialog::accept()
{
#ifdef Q_OS_MAC
    validate(focusWidget());
#endif

    if (!m_invalidUiFields.isEmpty()) {
        QMessageBox::information(this, tr("Fehler"),
            tr("Es sind fehlerhafte Eingaben vorhanden, bitte prüfen Sie die farblich markierten Felder!"),
            QMessageBox::Ok);
    } else {
        if (qxMainWin)
            qxMainWin->setStatusText("");
        QDialog::accept();
    }
}

/*!
  Versteckt das Dialogfenster und setzt den Dialogcode auf QDialog::Rejected.

  \sa accept()
*/
void QxDialog::reject()
{
    if (qxMainWin)
        qxMainWin->setStatusText("");
    QDialog::reject();
}

/*!
  Wird zur Validierung des Feldes <i>uiField</i> aufgerufen. Geben Sie eine passende Fehlerbeschreibung zurück, bzw.
  einen Leerstring wenn der Feldinhalt gültig ist.
*/
QString QxDialog::validateUiField(QWidget *uiField)
{
    Q_UNUSED(uiField);
    return QString();
}

/*!
  Wird aufgerufen wenn der Inhalt des Feldes <i>uiField</i> geändert wurde. Der neue Inhalt wurde noch nicht validiert
  und kann hier noch einmal geändert werden.

  \sa postProcessUiField(QWidget *uiField)
*/
void QxDialog::preProcessUiField(QWidget *uiField)
{
    Q_UNUSED(uiField);
}

/*!
  Wird aufgerufen wenn der Inhalt des Feldes <i>uiField</i> geändert wurde. Hier können z.B. abhängige Felder validiert
  oder ent-/sperrt werden.

  \sa processUiField(QWidget *uiField)
  \sa relockUiField(QWidget *uiField)
*/
void QxDialog::postProcessUiField(QWidget *uiField)
{
    Q_UNUSED(uiField);
}

/*!
  Wird aufgerufen wenn der Sperrzustand des Feldes <i>uiField</i> aktualisiert werden soll.
*/
void QxDialog::relockUiField(QWidget *uiField)
{
    Q_UNUSED(uiField);
}

/*!
  Wird aufgerufen wenn die Schaltfläche <i>button</i> betätigt wurde.
*/
void QxDialog::buttonClicked(QAbstractButton *button)
{
    Q_UNUSED(button);
}

/*!
  Setzt den Änderungsstatus des Feldes <i>uiField</i> auf den Wert <i>modified</i>.
*/
void QxDialog::setUiFieldModified(QWidget *uiField, bool modified)
{
    QxUiField::setModified(uiField, modified);

    if (modified)
        setModified(true);
}

/*!
  Wird aufgerufen wenn der Inhalt des Feldes <i>uiField</i> geändert wurde. Die Methode kann auch manuell aufgerufen
  werden um die Inhalte erneut zu verarbeiten (z.B. wenn die Inhalte abhängiger Felder geändert wurden).

  \sa preProcessUiField(QWidget *uiField)
  \sa postProcessUiField(QWidget *uiField)
*/
void QxDialog::processUiField(QWidget *uiField)
{
    bool modified = QxUiField::isModified(uiField);

    // Rekursive Aufrufe verhindern
    static int calls = 0;
    if (calls > 0)
        return;

    calls = 1;
    preProcessUiField(uiField);
    calls = 0;
    validate(uiField);

    if (modified) {
        QxUiField::setModified(uiField, false);
        postProcessUiField(uiField);
    }
}

/*!
  Gibt den aktuellen Wert des Feldes <i>uiField</i> zurück.

  \sa setUiFieldValue(QWidget *uiField, const QVariant &value)
*/
QVariant QxDialog::uiFieldValue(QWidget *uiField) const
{
    return QxUiField::value(uiField);
}

/*!
  Setzt den Wert des Feldes <i>uiField</i> auf den Wert <i>value</i>.

  \sa uiFieldValue(QWidget *uiField)
*/
bool QxDialog::setUiFieldValue(QWidget *uiField, QVariant value, const QSqlRelation &sqlRelation)
{
    bool success = true;

    if (sqlRelation.isValid()) {
        QSqlQuery query;
        query.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :value").arg(sqlRelation.displayColumn())
            .arg(sqlRelation.tableName()).arg(sqlRelation.indexColumn()));
        query.bindValue(":value", value);
        if (query.exec() && query.first()) {
            value = query.value(sqlRelation.displayColumn());
        } else {
            value.clear();
        }
    }

    if (uiFieldValue(uiField) != value)
        success = QxUiField::setValue(uiField, value);

    if (success && m_initialized)
        processUiField(uiField);

    return success;
}

/*!
  Aktualisiert den Sperrzustand aller Felder.
*/
void QxDialog::relockUiFields()
{
    relockUiFields(this);
}

/*!
  Setzt den Eingabefokus auf das erste Feld in der Tabulatorreihenfolge.
*/
void QxDialog::focusFirstUiField(QWidget *parent)
{
    QWidget *uiField = parent;

    if (uiField == 0)
        uiField = this;

    if (QxUiField::isUiField(uiField) && uiField->isEnabled() && !QxUiField::isReadOnly(uiField)) {
        uiField->setFocus();
        return;
    }

    uiField = uiField->nextInFocusChain();
    if (uiField && focusWidget() != uiField)
        focusFirstUiField(uiField);
}

/*!
  Setzt den Inhalt des Feldes <i>uiField</i> auf den Startwert zurück.

  \sa resetUiFields()
*/
void QxDialog::resetUiField(QWidget *uiField)
{
    QxUiField::reset(uiField);
}

/*!
  Setzt die Inhalte aller Dialogdaten auf die Startwerte zurück.

  \sa resetUiFields()
*/
void QxDialog::resetUiFields()
{
    resetUiFields(this);
}

/*!
  Gibt den Namen des Datenbankfeldes zurück, mit dem das Feld <i>uiField</i> verbunden ist.

  \sa setUiFieldSqlMapping(QWidget *uiField, const QString &sqlField)
  \sa uiFieldValues(QSqlRecord *record)
  \sa setUiFieldValues(QSqlRecord *record)
*/
QString QxDialog::uiFieldSqlMapping(QWidget *uiField)
{
    return QxUiField::sqlMapping(uiField);
}

/*!
  Verbindet das Feld <i>uiField</i> mit dem Datenbankfeld <i>sqlField</i>.

  \sa uiFieldSqlMapping(QWidget *uiField)
  \sa uiFieldValues(QSqlRecord *record)
  \sa setUiFieldValues(QSqlRecord *record)
*/
void QxDialog::setUiFieldSqlMapping(QWidget *uiField, const QString &sqlField)
{
    QxUiField::setSqlMapping(uiField, sqlField);
}

/*!
  Gibt die Datenbankrelation für das Feld <i>uiField</i> zurück.

  \sa setUiFieldSqlRelation(QWidget *uiField, const QSqlRelation &sqlRelation)
*/
QSqlRelation QxDialog::uiFieldSqlRelation(QWidget *uiField)
{
    return m_sqlRelations.value(uiField);
}

/*!
  Verbindet das Feld <i>uiField</i> mit der Datenbankrelation <i>sqlRelation</i>.

  \sa uiFieldSqlRelation(QWidget *uiField)
*/
void QxDialog::setUiFieldSqlRelation(QWidget *uiField, const QSqlRelation &sqlRelation)
{
    m_sqlRelations.insert(uiField, sqlRelation);
}

/*!
  Aktualisiert die Feldinhalte mit den Werten aus dem Datensatz <i>record</i>.

  \sa setUiFieldSqlMapping(QWidget *uiField, const QString &sqlField)
  \sa setUiFieldValues(QSqlRecord *record)
*/
void QxDialog::uiFieldValues(QSqlRecord *record)
{
    uiFieldValues(record, this);
}

/*!
  Schreibt die aktuellen Feldinhalte in den Datensatz <i>record</i>.

  \sa setUiFieldSqlMapping(QWidget *uiField, const QString &sqlField)
  \sa uiFieldValues(QSqlRecord *record)
*/
void QxDialog::setUiFieldValues(QSqlRecord *record)
{
    setUiFieldValues(record, this);
}

/*!
  Wird aufgerufen um das Ereignis <i>event</i> zu verarbeiten.
*/
bool QxDialog::eventFilter(QObject *object, QEvent *event)
{
    QWidget *widget = qobject_cast<QWidget*>(object);

    if (widget) {
        if (event->type() == QEvent::FocusIn) {
            if (m_invalidUiFields.contains(widget)) {
                QString error = QxUiField::errorText(widget);
                if (qxMainWin)
                    qxMainWin->setStatusText(error);
            } else {
                if (qxMainWin)
                    qxMainWin->setStatusText("");
            }
            if (!QxUiField::isReadOnly(widget))
                QxUiField::selectAll(widget);
        }

        if (event->type() == QEvent::FocusOut) {
            if (CLASSNAME(widget) == "QPlainTextEdit")
                processUiField(widget);
        }

        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (CLASSNAME(widget) == "QPlainTextEdit") {
                if (keyEvent->key() == Qt::Key_Return && keyEvent->modifiers() == Qt::NoModifier) {
                    QPushButton *button = defaultButton();
                    if (button)
                        button->click();
                }
            }

            if (qxApp && keyEvent->key() == qxApp->fieldButtonHotkey() && QxUiField::isUiField(widget)) {
                QAbstractButton *button = findChild<QAbstractButton*>(widget->objectName() + "Button");
                if (button && button->isEnabled() && button->isVisible())
                    buttonClicked(button);
            }
        }
    }

    return QDialog::eventFilter(object, event);
}

/*!
  Wird aufgerufen wenn der Dialog sichtbar gemacht wird.
*/
void QxDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    if (!m_initialized)
        initialize(this);
}

/*!
  Wird aufgerufen wenn sich der Status geändert hat.
*/
void QxDialog::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        bool modified = isModified();
        retranslateUi();
        setModified(modified);
    }

    QDialog::changeEvent(event);
}

/*!
  Wird aufgerufen wenn der Hyperlink <i>link</i> angeklickt wurde.
*/
void QxDialog::processLink(const QString &link)
{
    Q_UNUSED(link);
}

void QxDialog::initialize(const QObject *object)
{
    QObjectList children = object->children();

    for (QObject *child : children) {
        QWidget *widget = qobject_cast<QWidget*>(child);
        if (widget == 0) {
            initialize(child);
            continue;
        }

        if (QxUiField::isUiField(widget)) {
            QxUiField::initialize(widget, this);
        } else {
            initialize(child);
        }

        if (CLASSNAME(widget) == "QPushButton") {
            QPushButton *button = qobject_cast<QPushButton*>(widget);
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }

        if (CLASSNAME(widget) == "QToolButton") {
            QToolButton *button = qobject_cast<QToolButton*>(widget);
            connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
        }

        if (CLASSNAME(widget) == "QRadioButton") {
            QRadioButton *button = qobject_cast<QRadioButton*>(widget);
            connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
        }

        if (CLASSNAME(widget) == "QLabel") {
            QLabel *label = qobject_cast<QLabel*>(widget);
            connect(label, SIGNAL(linkActivated(QString)), this, SLOT(processLink(QString)));
        }

        if (CLASSNAME(widget) == "cutex::QxTextEdit") {
            QxTextEdit *edit = qobject_cast<QxTextEdit*>(widget);
            connect(edit, SIGNAL(linkActivated(QString)), this, SLOT(processLink(QString)));
        }
    }

    if (object == this) {
        m_initialized = true;
        validate();
        relockUiFields(this);
    }
}

void QxDialog::relockUiFields(QWidget *uiField)
{
    if (QxUiField::isUiField(uiField)) {
        relockUiField(uiField);
        return;
    }

    QObjectList children = uiField->children();
    for (QObject *child : children) {
        uiField = qobject_cast<QWidget*>(child);
        if (uiField)
            relockUiFields(uiField);
    }
}

void QxDialog::resetUiFields(QWidget *uiField)
{
    if (QxUiField::isUiField(uiField)) {
        resetUiField(uiField);
        return;
    }

    QObjectList children = uiField->children();
    for (QObject *child : children) {
        uiField = qobject_cast<QWidget*>(child);
        if (uiField)
            resetUiFields(uiField);
    }
}

void QxDialog::uiFieldValues(QSqlRecord *record, QWidget *uiField)
{
    if (QxUiField::isUiField(uiField)) {
        QString name = QxUiField::sqlMapping(uiField);
        if (!name.isEmpty() && record->contains(name)) {
            QVariant value = QxUiField::value(uiField, record->field(name).type());
            if (m_sqlRelations.contains(uiField)) {
                QSqlRelation relation = m_sqlRelations.value(uiField);
                QSqlQuery query;
                query.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :value").arg(relation.indexColumn())
                    .arg(relation.tableName()).arg(relation.displayColumn()));
                query.bindValue(":value", value);
                if (query.exec() && query.first()) {
                    value = query.value(relation.indexColumn());
                } else {
                    value.clear();
                }
            }
            record->setValue(name, value);
        }
        return;
    }

    QObjectList children = uiField->children();
    for (QObject *child : children) {
        uiField = qobject_cast<QWidget*>(child);
        if (uiField)
            uiFieldValues(record, uiField);
    }
}

void QxDialog::setUiFieldValues(QSqlRecord *record, QWidget *uiField)
{
    if (QxUiField::isUiField(uiField)) {
        QString name = QxUiField::sqlMapping(uiField);
        if (!name.isEmpty() && record->contains(name))
            setUiFieldValue(uiField, record->value(name), m_sqlRelations.value(uiField));
        return;
    }

    QObjectList children = uiField->children();
    for (QObject *child : children) {
        uiField = qobject_cast<QWidget*>(child);
        if (uiField)
            setUiFieldValues(record, uiField);
    }
}

QPushButton* QxDialog::defaultButton()
{
     QList<QPushButton*> buttons = findChildren<QPushButton*>();

     for (QPushButton *button : buttons) {
         if (button->isDefault())
             return button;
     }

     return 0;
}

void QxDialog::processUiField()
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

    processUiField(uiField);
}

void QxDialog::setUiFieldModified()
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

    setUiFieldModified(uiField);
}

void QxDialog::buttonClicked()
{
#ifdef Q_OS_MAC
    validate(focusWidget());
#endif

    QAbstractButton *button = qobject_cast<QAbstractButton*>(sender());
    buttonClicked(button);
}

/*!
  \fn QxDialog::visibilityChanged(bool visible)

  Das Signal wird ausgelöst wenn der Dialog sichtbar gemacht, bzw. versteckt wurde.
*/
