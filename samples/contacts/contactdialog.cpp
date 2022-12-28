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

#include "contactdialog.h"

ContactDialog::ContactDialog(Contact *contact, QWidget *parent) : QxDialog(parent)
{
    m_contact = contact;

    m_ui.setupUi(this);
    m_ui.AnredeField->addItems(QStringList() << tr("Herr") << tr("Frau") << tr("Firma"));

    // setUiFieldValue() stellt eine einheitliche Methode zum ändern von Feldinhalten zur Verfügung
    setUiFieldValue(m_ui.AnredeField, m_contact->anrede());
    setUiFieldValue(m_ui.VornameField, m_contact->vorname());
    setUiFieldValue(m_ui.NameField, m_contact->name());
    setUiFieldValue(m_ui.LandField, m_contact->land());
    setUiFieldValue(m_ui.PostleitzahlField, m_contact->postleitzahl());
    setUiFieldValue(m_ui.OrtField, m_contact->ort());
    setUiFieldValue(m_ui.StrasseField, m_contact->strasse());
    setUiFieldValue(m_ui.TelefonField, m_contact->telefon());
    setUiFieldValue(m_ui.MobilField, m_contact->mobil());
    setUiFieldValue(m_ui.EmailField, m_contact->email());

    if (contact->name().isEmpty())
        setWindowTitle(tr("Kontakt hinzufügen"));

    m_ui.AnredeField->setFocus();
}

void ContactDialog::accept()
{
    // Kontakt nur aktualisieren wenn Daten geändert wurden und alle Inhalte gültig sind
    if (isValid() && isModified()) {
        m_contact->setAnrede(uiFieldValue(m_ui.AnredeField).toString());
        m_contact->setVorname(uiFieldValue(m_ui.VornameField).toString());
        m_contact->setName(uiFieldValue(m_ui.NameField).toString());
        m_contact->setLand(uiFieldValue(m_ui.LandField).toString());
        m_contact->setPostleitzahl(uiFieldValue(m_ui.PostleitzahlField).toString());
        m_contact->setOrt(uiFieldValue(m_ui.OrtField).toString());
        m_contact->setStrasse(uiFieldValue(m_ui.StrasseField).toString());
        m_contact->setTelefon(uiFieldValue(m_ui.TelefonField).toString());
        m_contact->setMobil(uiFieldValue(m_ui.MobilField).toString());
        m_contact->setEmail(uiFieldValue(m_ui.EmailField).toString());
    }

    // Die Methode der Basisklasse prüft ob alle Daten gültig sind und zeigt im Fehlerfall eine Meldung an
    QxDialog::accept();
}

// Die Methode validateUiField() wird aufgerufen wenn Feldinhalte (neu) validiert werden müssen. Geben Sie bei Erfolg
// einen Leerstring, bzw. im Fehlerfall eine entsprechende Beschreibung zurück. Felder mit ungültigen Eingaben werden
// farblich hervorgehoben. Wenn das Feld den Fokus besitzt, wird die Fehlerbeschreibung in der Statusleiste des
// Hauptfensters angezeigt.
QString ContactDialog::validateUiField(QWidget *uiField)
{
    QString value = uiFieldValue(uiField).toString();

    if (uiField == m_ui.AnredeField) {
        if (value.isEmpty())
            return tr("Eingabe erforderlich");
        if (m_ui.AnredeField->findText(value) == -1)
            return tr("Anrede ist ungültig");
    }

    if (uiField == m_ui.NameField) {
        if (value.isEmpty())
            return tr("Eingabe erforderlich");
    }

    if (uiField == m_ui.EmailField) {
        if (!value.isEmpty()) {
            QUrl url = QUrl::fromUserInput(uiFieldValue(m_ui.EmailField).toString());
            if (!url.isValid())
                return tr("E-Mail ist ungültig");
        }
    }

    return QString();
}

// Die Methode preProcessUiField() wird aufgerufen wenn Feldinhalte geändert wurden. Die Inhalte können hier noch
// einmal geändert werden, da die Validierung erst im Anschluß durchgeführt wird.
void ContactDialog::preProcessUiField(QWidget *uiField)
{
    QString value = uiFieldValue(uiField).toString();

    if (uiField == m_ui.LandField)
        setUiFieldValue(m_ui.LandField, value.toUpper());
}

void ContactDialog::buttonClicked(QAbstractButton *button)
{
    if (button == m_ui.EMailButton) {
        QString url = uiFieldValue(m_ui.EmailField).toString();
        if (!url.isEmpty())
            QDesktopServices::openUrl(QUrl("mailto:" + url));
    }
}
