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

#include "qxrecentfiles.h"
#include "qxmainwindow.h"

using namespace cutex;

/*!
  Erzeugt eine Liste zuletzt verwendeter Dateien. Die maximale Anzahl der Dateien kann in <i>maxFiles</i> angegeben
  werden.
*/
QxRecentFiles::QxRecentFiles(int maxFiles)
{
    m_maxFiles = maxFiles;
    m_menu = 0;
}

/*!
  Erzeugt eine Liste zuletzt verwendeter Dateien und verbindet diese mit dem Menü <i>menu</i>, wodurch dieses
  automatisch aktualisiert wird. Die maximale Anzahl der Dateien kann in <i>maxFiles</i> angegeben werden.
*/
QxRecentFiles::QxRecentFiles(QMenu *menu, int maxFiles)
{
    m_maxFiles = maxFiles;
    m_menu = menu;

    if (m_menu)
        connect(m_menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));
}

/*!
  Gibt die zuletzt verwendeten Dateien zurück.

  \sa setFiles(const QStringList &files)
*/
QStringList QxRecentFiles::files()
{
    QStringList files;

    for (QString fileName : m_files) {
        if (QFile::exists(fileName))
            files.append(fileName);
    }

    return files;
}

/*!
  Aktualisiert die Liste zuletzt verwendeter Dateien mit der Liste <i>files</i>.

  \sa files()
*/
void QxRecentFiles::setFiles(const QStringList &files)
{
    m_files.clear();

    for (QString fileName : files) {
        QFileInfo info(fileName);
        if (info.exists()) {
            fileName = info.absoluteFilePath();
#ifdef Q_OS_WIN32
            fileName = fileName.replace("/", "\\");
#endif
            if (!m_files.contains(fileName))
                m_files.append(fileName);
        }
    }

    emit filesChanged();
}

/*!
  Gibt die maximale Anzahl der Dateien zurück.

  \sa setMaxFiles(int maxFiles)
*/
int QxRecentFiles::maxFiles() const
{
    return m_maxFiles;
}

/*!
  Setzt die maximale Anzahl der Dateien.

  \sa maxFiles()
*/
void QxRecentFiles::setMaxFiles(int maxFiles)
{
    m_maxFiles = maxFiles;
}

/*!
  Gibt das mit der Liste zuletzt verwendeter Dateien verbundene Menü zurück.

  \sa setMenu(QMenu *menu)
*/
QMenu* QxRecentFiles::menu()
{
    return m_menu;
}

/*!
  Verbindet die Liste zuletzt verwendeter Dateien mit dem Menü <i>menu</i>, wodurch dieses automatisch aktualisiert
  wird.

  \sa menu()
*/
void QxRecentFiles::setMenu(QMenu *menu)
{
    if (m_menu)
        disconnect(m_menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));

    m_menu = menu;

    if (m_menu)
        connect(m_menu, SIGNAL(aboutToShow()), this, SLOT(updateMenu()));
}

void QxRecentFiles::updateMenu()
{
    QList<QAction*> actions = m_menu->actions();
    for (QAction *action : actions) {
        m_menu->removeAction(action);
        delete action;
    }

    for (QString fileName : m_files) {
        if (QFile::exists(fileName)) {
            QAction *action = m_menu->addAction(fileName);
            connect(action, SIGNAL(triggered()), qxMainWin, SLOT(processAction()));
        }
    }
}

/*!
  \fn QxRecentFiles::filesChanged()

  Das Signal wird ausgelöst wenn sich die Liste der zuletzt verwendeten Dateien geändert hat.
*/
