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

#ifndef QXMAINWINDOW_H
#define QXMAINWINDOW_H

#include "cutex.h"
#include "qxform.h"
#include "qxrecentfiles.h"

namespace cutex {

class QxMainWindow;
extern QxMainWindow *qxMainWin;

/*!
  \brief Die Klasse %QxMainWindow vereinfacht die Implementierung von Hauptfenstern.

  Bei Verwendung der Klasse %QxMainWindow erübrigt sich die Implementierung vieler in Hauptfenstern häufig benötigten
  Slots, z.B. für das Auslösen oder ent-/sperren von Menüaktionen. Die automatische Verwaltung, bzw. Aktualisierung des
  Fenster-Menüs vereinfacht die Programmierung von MDI-Anwendungen. Weiterhin stellt die Klasse Methoden zum Laden und
  Speichern von Einstellungen, sowie der Liste der zuletzt verwendeten Dateien zur Verfügung.

  \sa QxRecentFiles
*/
class QxMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QxMainWindow(QWidget *parent = nullptr);
    QString currentFile();
    QxRecentFiles* recentFiles();
    void setRecentFiles(QxRecentFiles *recentFiles);
    void setupMdiArea(QMdiArea *mdiArea, QMenu *windowMenu = nullptr);
    QMdiArea* mdiArea();
    QMdiSubWindow* addSubWindow(QxForm *form, QSize size = QSize());
    virtual void retranslateUi();

public slots:
    void setStatusText(const QString &statusText, int timeout = 0);
    virtual void updateStatusBar();
    virtual void setModified(bool modified = true);
    virtual void relockActions();
    void setActiveSubWindow(QWidget *widget);
    virtual void closeAllSubWindows();
    void updateWindowMenu();

protected:
    virtual void showEvent(QShowEvent *event);
    virtual void changeEvent(QEvent *event);
    virtual void updateMenu(QMenu *menu);
    virtual void processAction(QAction *action);
    virtual void restoreSettings(QSettings *settings, int version = 0);
    virtual void saveSettings(QSettings *settings, int version = 0);
    virtual void setCurrentFile(QString fileName);

private:
    bool m_initialized;
    QString m_currentFile;
    QxRecentFiles *m_recentFiles;
    QSignalMapper *m_mapper;
    QMdiArea *m_mdiArea;
    QMenu *m_windowMenu;

private:
    void initActions(const QObject *object);

private slots:
    void updateMenu();
    void processAction();

signals:
    void recentFilesChanged(QxRecentFiles *recentFiles);
};

} // namespace

#endif // QXMAINWINDOW_H
