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

#include "qxmainwindow.h"

using namespace cutex;

namespace cutex {
QxMainWindow *qxMainWin;
}

/*!
  Erzeugt ein neues Hauptfenster mit dem Elternobjekt <i>parent</i>.
*/
QxMainWindow::QxMainWindow(QWidget *parent) : QMainWindow(parent)
{
    qxMainWin = this;

    m_initialized = false;
    m_modified = false;
    m_recentFiles = 0;
    m_mapper = new QSignalMapper(this);
    m_mdiArea = 0;
    m_windowMenu = 0;
}

/*!
  Gibt den Namen der aktuellen Datei zurück.

  \sa setCurrentFile(QString fileName)
*/
QString QxMainWindow::currentFile()
{
    return m_currentFile;
}

/*!
  Gibt die Liste der zuletzt verwendeten Dateien zurück.

  \sa setRecentFiles(QxRecentFiles *recentFiles)
*/
QxRecentFiles* QxMainWindow::recentFiles()
{
    return m_recentFiles;
}

/*!
  Setzt die Liste der zuletzt verwendeten Dateien.

  \sa recentFiles()
*/
void QxMainWindow::setRecentFiles(QxRecentFiles *recentFiles)
{
    m_recentFiles = recentFiles;
}

/*!
  Initialisiert den MDI-Bereich <i>mdiArea</i>. In MDI-Anwendungen muss diese Methode im Konstruktor des Hauptfensters
  aufgerufen werden, damit die MDI-Schnittstelle korrekt funktioniert. Wenn das Hauptfenster über ein Fenster-Menü
  verfügt, kann der Zeiger im Parameter <i>windowMenu</i> übergeben werden. Die entsprechenden Menüaktionen werden
  dann automatisch eingefügt, bzw. aktualisiert.
*/
void QxMainWindow::setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu)
{
    m_mdiArea = mdiArea;
    m_windowMenu = windowMenu;

    connect(m_mapper, SIGNAL(mapped(QWidget*)), this, SLOT(setActiveSubWindow(QWidget*)));
    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(relockActions()));
    connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateWindowMenu()));

    updateWindowMenu();
}

/*!
  Gibt einen Zeiger auf den MDI-Bereich zurück.

  \sa setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu)
*/
QMdiArea* QxMainWindow::mdiArea()
{
    return m_mdiArea;
}

/*!
  Erzeugt ein neues MDI-Kindfenster für das Formularobjekt <i>form</i> und fügt dieses in den MDI-Bereich ein. Die
  Fenstergröße wird auf den Wert <i>size</i> gesetzt.

  \sa setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu)
*/
QMdiSubWindow* QxMainWindow::addSubWindow(QxForm *form, QSize size)
{
    QMdiSubWindow *window = new QMdiSubWindow(m_mdiArea);
    QString title = form->windowTitle();

    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setWidget(form);
    window->setWindowIcon(form->windowIcon());
    window->setPalette(form->palette());
    window->setStyleSheet(form->styleSheet());

    connect(window, SIGNAL(windowTitleChanged(QString)), this, SLOT(updateWindowMenu()));
    connect(window, SIGNAL(destroyed(QObject*)), this, SLOT(updateWindowMenu()));

    if (!size.isEmpty())
        window->resize(size);

    if (m_mdiArea->viewMode() == QMdiArea::SubWindowView) {
        window->showNormal();
    } else {
        window->showMaximized();
    }

    window->setWindowTitle(title);
    updateWindowMenu();

    return window;
}

/*!
  Wird aufgerufen wenn die Sprache geändert wurde.
*/
void QxMainWindow::retranslateUi()
{
}

/*!
  Zeigt den in <i>statusText</i> angegebenen Text für <i>timeout</i> Millisekunden in der Statusleiste an.
*/
void QxMainWindow::setStatusText(const QString &statusText, int timeout)
{
    statusBar()->showMessage(statusText, timeout);
}

/*!
  Wird aufgerufen wenn die Statusleiste aktualisiert werden muss. Die Methode kann überschrieben werden um spezielle
  Steuerelemente der Statusleiste zu aktualisieren.
*/
void QxMainWindow::updateStatusBar()
{
}

/*!
  Setzt das Änderungsflag des Hauptfensters auf den Wert <i>modified</i>.
*/
void QxMainWindow::setModified(bool modified)
{
    m_modified = modified;

    setWindowModified(modified);
    relockActions();
}

/*!
  Wird aufgerufen wenn der Sperrzustand der Menüaktionen aktualisiert werden muss. Die Methode kann überschrieben
  werden, um Menüaktionen zu ent-/sperren.
*/
void QxMainWindow::relockActions()
{
}

/*!
  Holt das MDI-Kindfenster <i>widget</i> in den Vordergrund.

  \sa setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu)
*/
void QxMainWindow::setActiveSubWindow(QWidget *widget)
{
    if (!widget)
        return;

    m_mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(widget));
}

/*!
  Schließt alle MDI-Kindfenster.

  \sa setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu)
*/
void QxMainWindow::closeAllSubWindows()
{
    if (m_mdiArea)
        m_mdiArea->closeAllSubWindows();
}

/*!
  Aktualisiert das Fenster-Menü.

  \sa setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu)
*/
void QxMainWindow::updateWindowMenu()
{
    if (!m_windowMenu)
        return;

    for (QAction *action : m_windowMenu->actions()) {
        if (action->property("cutex").toBool()) {
            m_windowMenu->removeAction(action);
            delete action;
        }
    }

    QList<QMdiSubWindow*> windows = m_mdiArea->subWindowList();
    QAction *action = nullptr;

    if (m_mdiArea->viewMode() == QMdiArea::SubWindowView) {
        action = m_windowMenu->addAction(tr("Überlappend"));
        action->setProperty("cutex", true);
        action->setDisabled(!windows.count());
        connect(action, SIGNAL(triggered()), m_mdiArea, SLOT(cascadeSubWindows()));

        action = m_windowMenu->addAction(tr("Nebeneinander"));
        action->setProperty("cutex", true);
        action->setDisabled(!windows.count());
        connect(action, SIGNAL(triggered()), m_mdiArea, SLOT(tileSubWindows()));
    }

    action = m_windowMenu->addAction(tr("Alle schließen"));
    action->setProperty("cutex", true);
    action->setDisabled(!windows.count());
    connect(action, SIGNAL(triggered()), this, SLOT(closeAllSubWindows()));

    if (windows.count()) {
        action = m_windowMenu->addSeparator();
        action->setProperty("cutex", true);
    }

    for (QMdiSubWindow *window : windows) {
        QString title = window->windowTitle();
        action = m_windowMenu->addAction(title.remove("[*]"));
        action->setProperty("cutex", true);
        action->setCheckable(true);
        action->setChecked(window == m_mdiArea->activeSubWindow());
        connect(action, SIGNAL(triggered()), m_mapper, SLOT(map()));
        m_mapper->setMapping(action, window);
    }
}

/*!
  Wird aufgerufen wenn das Hauptfenster sichtbar gemacht wird.
*/
void QxMainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    if (!m_initialized) {        
        initActions(this);
        m_initialized = true;
    }
}

/*!
  Wird aufgerufen wenn sich der Status geändert hat.
*/
void QxMainWindow::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        updateWindowMenu();
        break;
    case QEvent::ModifiedChange:
        if (isWindowModified() != m_modified)
            setWindowModified(m_modified);
        break;
    default:
        break;
    }

    QMainWindow::changeEvent(event);
}

/*!
  Wird aufgerufen wenn das Menü <i>menu</i> angezeigt wird.
*/
void QxMainWindow::updateMenu(QMenu *menu)
{
    Q_UNUSED(menu);
}

/*!
  Wird aufgerufen wenn die Menüaktion <i>action</i> ausgelöst wurde.
*/
void QxMainWindow::processAction(QAction *action)
{
    Q_UNUSED(action);
}

/*!
  Stellt die gespeicherten Einstellungen des Hauptfensters wieder her.

  \sa saveSettings(QSettings *settings)
*/
void QxMainWindow::restoreSettings(QSettings *settings, int version)
{
    settings->beginGroup(CLASSNAME(this));
    restoreGeometry(settings->value("geometry").toByteArray());
    restoreState(settings->value("state").toByteArray(), version);
    if (m_recentFiles) {
        QStringList recentFiles = settings->value("recentFiles").toStringList();
        m_recentFiles->setFiles(recentFiles);
    }

    settings->endGroup();
}

/*!
  Speichert die Einstellungen des Hauptfensters.

  \sa restoreSettings(QSettings *settings)
*/
void QxMainWindow::saveSettings(QSettings *settings, int version)
{
    settings->beginGroup(CLASSNAME(this));
    settings->setValue("geometry", saveGeometry());
    settings->setValue("state", saveState(version));
    if (m_recentFiles) {
        QStringList recentFiles = m_recentFiles->files();
        settings->setValue("recentFiles", recentFiles);
    }
    settings->endGroup();
}

/*!
  Setzt die Datei <i>fileName</i> als aktuelle Datei und fügt diese der Liste der zuletzt verwendeten Dateien hinzu.

  \sa currentFile()
*/
void QxMainWindow::setCurrentFile(QString fileName)
{
    static QString originTitle = windowTitle();

    m_currentFile = fileName;
    setModified(false);

    if (!m_mdiArea) {
        QString title;
        if (fileName.isEmpty()) {
            title = tr("Unbenannt");
        } else {
            title = QFileInfo(fileName).fileName();
        }
        setWindowTitle(title + "[*] - " + originTitle);
    }

    if (m_recentFiles && !fileName.isEmpty()) {
#ifdef Q_OS_WIN32
        fileName = fileName.replace("/", "\\");
#endif
        QStringList recentFiles = m_recentFiles->files();
        int maxFiles = m_recentFiles->maxFiles();
        recentFiles.removeAll(fileName);
        recentFiles.prepend(fileName);
        while (recentFiles.size() > maxFiles) {
            recentFiles.removeLast();
        }
        m_recentFiles->setFiles(recentFiles);
        emit recentFilesChanged(m_recentFiles);
    }
}

void QxMainWindow::initActions(const QObject *object)
{
    QObjectList children = object->children();
    for (QObject *child : children) {

        initActions(child);

        if (CLASSNAME(child) == "QMenu") {
            QList<QAction*> actions = qobject_cast<QMenu*>(child)->actions();
            for (QAction *action : actions)
                connect(action, SIGNAL(triggered()), this, SLOT(processAction()));
            QMenu *menu = qobject_cast<QMenu*>(child);
            connect(menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));
        }

        if (CLASSNAME(child) == "QToolBar") {
            QList<QAction*> actions = qobject_cast<QToolBar*>(child)->actions();
            for (QAction *action : actions) {
                disconnect(action, SIGNAL(triggered()), this, SLOT(processAction()));
                connect(action, SIGNAL(triggered()), this, SLOT(processAction()));
            }
        }
    }

    if (object == this)
        relockActions();
}

void QxMainWindow::updateMenu()
{
    updateMenu(qobject_cast<QMenu*>(sender()));
}

void QxMainWindow::processAction()
{
    processAction(qobject_cast<QAction*>(sender()));
}

/*!
  \fn QxMainWindow::recentFilesChanged(QxRecentFiles *recentFiles)

  Das Signal wird ausgelöst wenn sich die Liste der zuletzt verwendeten Dateien geändert hat.

  \sa QxRecentFiles
*/
