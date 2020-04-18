/***********************************************************************************************************************
**
** Copyright (C) 2016 Partsoft UG (haftungsbeschränkt)
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

#include "mainwindow.h"
#include "contactdialog.h"
#include "contact.h"
#include "qxwaitcursor.h"

MainWindow::MainWindow() : QxMainWindow()
{
    m_ui.setupUi(this);
    setWindowTitle(APP_TITLE);
    setWindowIcon(QIcon(":/icons/32x32/contacts.ico"));
    initView();

    // Die Liste der zuletzt verwendeten Dateien erzeugen und mit dem Menü verbinden
    m_recentFiles = new QxRecentFiles();
    m_recentFiles->setMenu(m_ui.LetzteDateienMenu);
    setRecentFiles(m_recentFiles);

    // Einstellungen wiederherstellen
    QSettings settings(APP_PUBLISHER, APP_NAME);
    restoreSettings(&settings);

    setCurrentFile("");
}

// Die Methode relockActions() wird zum ent-/sperren der Menüaktionen aufgerufen
void MainWindow::relockActions()
{
    QModelIndex index = selection();
    Contact *contact = m_model.contact(index);

    m_ui.DateiSpeichernAction->setEnabled(isWindowModified());
    m_ui.KontaktBearbeitenAction->setEnabled(contact);
    m_ui.KontaktLoeschenAction->setEnabled(contact);
}

// Die Methode processAction() wird aufgerufen, wenn eine Menüaktion ausgelöst wurde
void MainWindow::processAction(QAction *action)
{
    QxMainWindow::processAction(action);

    if (action == m_ui.DateiNeuAction)
        fileNew();

    if (action == m_ui.DateiOeffnenAction)
        fileOpen();

    if (action->parent() == m_ui.LetzteDateienMenu)
        fileOpen(action->text());

    if (action == m_ui.DateiSpeichernAction)
        fileSave();

    if (action == m_ui.DateiSpeichernUnterAction)
        fileSaveAs();

    if (action == m_ui.DateiBeendenAction)
        close();

    if (action == m_ui.KontaktHinzufuegenAction)
        insertContact();

    if (action == m_ui.KontaktBearbeitenAction)
        editContact();

    if (action == m_ui.KontaktLoeschenAction)
        removeContact();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (saveRequest()) {
        QSettings settings(APP_PUBLISHER, APP_NAME);
        saveSettings(&settings);
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::initView()
{
    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(&m_model);
    m_proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setDynamicSortFilter(true);

    m_ui.ContactsTable->setModel(m_proxyModel);
    m_ui.ContactsTable->horizontalHeader()->setSortIndicator(ContactsModel::NameColumn, Qt::AscendingOrder);

    m_ui.ContactsTable->setColumnWidth(ContactsModel::AnredeColumn, 50);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::VornameColumn, 100);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::NameColumn, 120);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::LandColumn, 50);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::PostleitzahlColumn, 50);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::OrtColumn, 120);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::StrasseColumn, 120);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::TelefonColumn, 120);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::MobilColumn, 120);
    m_ui.ContactsTable->setColumnWidth(ContactsModel::EmailColumn, 150);

    connect(m_ui.ContactsTable->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this,
        SLOT(relockActions()));
    connect(&m_model, SIGNAL(rowChanged(QModelIndex)), this, SLOT(setSelection(QModelIndex)));
    connect(m_ui.ContactsTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editContact()));
}

QModelIndex MainWindow::selection()
{
    QModelIndex index;

    index = m_ui.ContactsTable->selectionModel()->currentIndex();
    index = m_proxyModel->mapToSource(index);

    return index;
}

bool MainWindow::saveRequest()
{
    bool success = true;

    if (isWindowModified()) {
        int result = QMessageBox::question(this, APP_TITLE, tr("Änderungen speichern?"),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (result == QMessageBox::Yes) {
            success = fileSave();
        } else if (result == QMessageBox::Cancel) {
            success = false;
        }
    }

    return success;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QString appId;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, APP_TITLE, tr("Die Datei konnte nicht geöffnet werden!"));
        return false;
    }

    QDataStream in(&file);
    in >> appId;
    if (appId != APP_ID) {
        QMessageBox::warning(this, APP_TITLE, tr("Die Datei hat ein ungültiges Format!"));
        return false;
    }

    // Solange eine Instanz der Klasse QxWaitCursor existiert, werden alle Benutzereingaben blockiert und der Mauszeiger
    // als Sanduhr dargestellt
    QxWaitCursor wait;
    Q_UNUSED(wait);

    in >> m_model;
    setStatusText(QString(tr("Datei \"%1\" geladen").arg(fileName)), 3000);

    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, APP_TITLE, tr("Die Datei konnte nicht gespeichert werden!"));
        return false;
    }

    QDataStream out(&file);
    out << QString(APP_ID);

    // Solange eine Instanz der Klasse QxWaitCursor existiert, werden alle Benutzereingaben blockiert und der Mauszeiger
    // als Sanduhr dargestellt
    QxWaitCursor wait;
    Q_UNUSED(wait);

    out << m_model;
    setStatusText(QString(tr("Datei \"%1\" gespeichert").arg(fileName)), 3000);

    return true;
}

void MainWindow::setSelection(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    int row = m_proxyModel->mapFromSource(index).row();
    m_ui.ContactsTable->selectRow(row);
    m_ui.ContactsTable->scrollTo(selection());
}

void MainWindow::fileNew()
{
    bool success = saveRequest();

    if (success) {
        m_model.clear();
        setCurrentFile("");
    }
}

void MainWindow::fileOpen()
{
    bool success = saveRequest();

    if (success) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Datei öffnen"),
            QDir::homePath(), tr("Contacts-Dateien (*.con)"));

        if (!fileName.isEmpty()) {
            success = loadFile(fileName);
            if (success) {
                setCurrentFile(fileName);
            } else {
                fileNew();
            }
        }
    }
}

void MainWindow::fileOpen(const QString &fileName)
{
    bool success = saveRequest();

    if (success) {
        success = loadFile(fileName);
        if (success) {
            setCurrentFile(fileName);
        } else {
            fileNew();
        }
    }
}

bool MainWindow::fileSave()
{
    bool success = false;

    if (currentFile().isEmpty()) {
        success = fileSaveAs();
    } else {
        success = saveFile(currentFile());
        if (success) {
            setWindowModified(false);
            relockActions();
        }
    }

    return success;
}

bool MainWindow::fileSaveAs()
{
    bool success = false;
    QString path;

    if (currentFile().isEmpty()) {
        path = QDir::homePath() + '/' + tr("Unbenannt.con");
    } else {
        path = currentFile();
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Datei speichern"),
        path, tr("Contact-Dateien (*.con)"));

    if (!fileName.isEmpty()) {
        success = saveFile(fileName);
        if (success)
            setCurrentFile(fileName);
    }

    return success;
}

void MainWindow::insertContact()
{
    Contact *contact = new Contact();
    ContactDialog dialog(contact, this);

    if (dialog.exec()) {
        m_model.insertContact(contact);
        setWindowModified(true);
        relockActions();
    } else {
        delete contact;
    }

}

void MainWindow::editContact()
{
    Contact *contact = m_model.contact(selection());
    ContactDialog dialog(contact, this);

    if (!contact)
        return;

    if (dialog.exec() && dialog.isModified()) {
        setWindowModified(dialog.isModified());
        relockActions();
    }
}

void MainWindow::removeContact()
{
    Contact *contact = m_model.contact(selection());

    if (!contact)
        return;

    int result = QMessageBox::question(this, tr("Kontakt löschen"), tr("Sind Sie sicher das Sie den Kontakt \"") +
        contact->name() + tr("\" löschen möchten?"), QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        m_model.removeContact(contact);
        setWindowModified(true);
        relockActions();
    }
}
