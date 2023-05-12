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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qxganttitemmodel.h>
#include "gantt.h"
#include "ui_mainwindow.h"

class MainWindow : public QxMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void relockActions();

protected:
    void processAction(QAction *action);
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow m_ui;
    QxRecentFiles *m_recentFiles;
    QxGanttItemModel m_model;

private:
    void initGanttTree();
    bool saveRequest();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

private slots:
    void fileNew();
    void fileOpen();
    void fileOpen(const QString &fileName);
    bool fileSave();
    bool fileSaveAs();
    void insertVorgang();
    void editVorgang();
    void removeVorgang();
};

#endif // MAINWINDOW_H
