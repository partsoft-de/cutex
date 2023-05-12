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

#include <qxwaitcursor.h>
#include <qxganttitem.h>
#include "mainwindow.h"

MainWindow::MainWindow() : QxMainWindow()
{
    m_ui.setupUi(this);
    setWindowTitle(APP_TITLE);
    setWindowIcon(QIcon(":/icons/32x32/gantt.ico"));

    initGanttTree();

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
    QModelIndex index = m_ui.GanttTree->currentIndex();

    m_ui.DateiSpeichernAction->setEnabled(isWindowModified());
    m_ui.VorgangBearbeitenAction->setEnabled(index.isValid());
    m_ui.VorgangLoeschenAction->setEnabled(index.isValid());
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

    if (action == m_ui.VorgangHinzufuegenAction)
        insertVorgang();

    if (action == m_ui.VorgangBearbeitenAction)
        editVorgang();

    if (action == m_ui.VorgangLoeschenAction)
        removeVorgang();
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

void MainWindow::initGanttTree()
{
    QHeaderView *header = m_ui.GanttTree->header();

    m_ui.GanttTree->setModel(&m_model);
//    m_ui.GanttTree->setItemDelegate(new QxGanttDelegate(this));

    header->setMinimumHeight(m_ui.GanttChart->headerHeight());
    header->resizeSection(QxGanttItemModel::Text, 250);
//    header->resizeSection(QxGanttModel::Duration, 80);
//    header->resizeSection(QxGanttModel::Start, 90);
//    header->resizeSection(QxGanttModel::Finish, 90);
//    header->restoreState(Settings::instance()->ganttHeaderState());

//    connect(m_ui.GanttTree, SIGNAL(collapsed(QModelIndex)), model, SLOT(setItemCollapsed(QModelIndex)));
//    connect(m_ui.GanttTree, SIGNAL(expanded(QModelIndex)), model, SLOT(setItemExpanded(QModelIndex)));
    connect(m_ui.GanttTree->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
        this, SLOT(relockActions()));
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

//    in >> m_model;
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

//    out << m_model;
    setStatusText(QString(tr("Datei \"%1\" gespeichert").arg(fileName)), 3000);

    return true;
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

void MainWindow::insertVorgang()
{
    QxGanttItem *item = new QxGanttItem(tr("Neuer Vorgang"));
    QModelIndex index;

    m_model.appendRow(item);
    setModified(true);
    relockActions();
}

void MainWindow::editVorgang()
{
}

void MainWindow::removeVorgang()
{
}
