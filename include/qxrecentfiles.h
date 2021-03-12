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

#ifndef QXRECENTFILES_H
#define QXRECENTFILES_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxRecentFiles verwaltet eine Liste zuletzt verwendeter Dateien.

  Die Klasse %QxRecentFiles wird von QxMainWindow zur Verwaltung der Liste zuletzt verwendeter Dateien verwendet. Eine
  Instanz dieser Klasse kann dem Hauptfenster zugewiesen und mit einem Menü verbunden werden. Die Aktualisierung des
  verbundenen Menüs erfolgt automatisch.

  \sa QxMainWindow
*/
class QxRecentFiles : public QObject
{
    Q_OBJECT

public:
    QxRecentFiles(int maxFiles = 8);
    QxRecentFiles(QMenu *menu, int maxFiles = 8);
    QStringList files();
    void setFiles(const QStringList &files);
    int maxFiles() const;
    void setMaxFiles(int maxFiles);
    QMenu *menu();
    void setMenu(QMenu *menu);

private:
    QStringList m_files;
    int m_maxFiles;
    QMenu *m_menu;

private slots:
    void updateMenu();

signals:
    void filesChanged();
};

} // namespace

#endif // QXRECENTFILES_H
