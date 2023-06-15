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

#include "qxfinddialog.h"
#include "ui_qxfinddialog.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Dialog mit dem Titel mit dem Elternobjekt <i>parent</i>.
*/
QxFindDialog::QxFindDialog(QWidget *parent) : QxDialog(parent), m_ui(new Ui::QxFindDialog)
{
    m_ui->setupUi(this);

    connect(m_ui->FindField, SIGNAL(textChanged(QString)), this, SLOT(relockButtons()));
    connect(m_ui->ReplaceField, SIGNAL(textChanged(QString)), this, SLOT(relockButtons()));
    connect(m_ui->CancelButton, SIGNAL(clicked(bool)), this, SLOT(hide()));

    setMode(QxFindDialog::Find);
    relockButtons();
}

QxFindDialog::~QxFindDialog()
{
    delete m_ui;
}

/*!
  Legt fest ob der Dialog nur die Suche oder auch das Ersetzen von Text ermöglichen soll. Im Suchmodus werden die
  Steuerelemente zum Ersetzen von Text versteckt.

  \sa Mode
*/
void QxFindDialog::setMode(QxFindDialog::Mode mode)
{
    switch (mode) {
    case QxFindDialog::Find:
        setWindowTitle(tr("Suchen"));
        break;
    case QxFindDialog::Replace:
        setWindowTitle(tr("Ersetzen"));
        break;
    }

    m_ui->ReplaceLabel->setVisible(mode == QxFindDialog::Replace);
    m_ui->ReplaceField->setVisible(mode == QxFindDialog::Replace);
    m_ui->ReplaceButton->setVisible(mode == QxFindDialog::Replace);
    m_ui->ReplaceAllButton->setVisible(mode == QxFindDialog::Replace);
}

/*!
  Wird aufgerufen wenn die Sprache geändert wurde.
*/
void QxFindDialog::retranslateUi()
{
    m_ui->retranslateUi(this);
}

void QxFindDialog::buttonClicked(QAbstractButton *button)
{
    QxFindOptions options;

    options.setFindText(m_ui->FindField->text());
    options.setWholeWords(m_ui->WholeWordsField->isChecked());
    options.setCaseSensitive(m_ui->CaseSensitiveField->isChecked());
    options.setBackward(m_ui->SearchUpButton->isChecked());

    if (button == m_ui->FindButton)
        emit findClicked(options);

    if (button == m_ui->ReplaceButton) {
        options.setMode(QxFindOptions::Replace);
        options.setReplaceText(m_ui->ReplaceField->text());
        emit findClicked(options);
    }

    if (button == m_ui->ReplaceAllButton) {
        options.setMode(QxFindOptions::ReplaceAll);
        options.setReplaceText(m_ui->ReplaceField->text());
        emit findClicked(options);
    }

    if (button == m_ui->CancelButton)
        reject();
}

void QxFindDialog::relockButtons()
{
    QString find = m_ui->FindField->text();
    QString replace = m_ui->ReplaceField->text();

    m_ui->FindButton->setDisabled(find.isEmpty());
    m_ui->ReplaceButton->setDisabled(find.isEmpty() || replace.isEmpty());
    m_ui->ReplaceAllButton->setDisabled(find.isEmpty() || replace.isEmpty());
}

/*!
  \var QxFindDialog::Find

  Stellt dem Anwender nur Funktionen zur Suche von Text zur Verfügung.
*/

/*!
  \var QxFindDialog::Replace

  Stellt dem Anwender Funktionen zum Suchen und Ersetzen von Text zur Verfügung.
*/

/*!
  \fn QxFindDialog::findClicked(const QxFindOptions &options)

  Das Signal wird ausgelöst wenn der Anwender eine der Schaltflächen zum Suchen oder Ersetzen betätigt hat.

  \sa QxFindOptions
*/
