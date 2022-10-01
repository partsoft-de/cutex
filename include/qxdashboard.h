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

#ifndef QXDASHBOARD_H
#define QXDASHBOARD_H

#include "cutex.h"
#include "qxform.h"
#include "qxrecentfiles.h"

namespace cutex {

/*!
  \brief Mit der Klasse %QxDashboard kann eine Einstiegsseite für die Anwendung realisiert werden.

  Das Dashboard verfügt über Symbole zur Neuanlage und zum Öffnen von Dateien. Wenn dem Dashboard ein Objekt der Klasse
  QxRecentFiles zugewiesen wurde, wird zusätzlich die Liste der zuletzt verwendeten Dateien angezeigt.

  \sa QxRecentFiles
*/
class QxDashboard : public QxForm
{
    Q_OBJECT

public:
    QxDashboard(QWidget *parent = nullptr);
    QFont font() const;
    void setFont(const QFont &font);
    void setIntroText(const QString &text);
    void setFileNewText(const QString &text);
    void setFileOpenText(const QString &text);
    void setRecentFilesText(const QString &text);
    void setFileNewEnabled(bool enabled);
    void setFileOpenEnabled(bool enabled);
    void setRecentFilesEnabled(bool enabled);
    void setRecentFiles(QxRecentFiles *recentFiles);
    void retranslateUi();

public slots:
    void update();

private:
    QTextBrowser *m_dashboard;
    QFont m_font;
    QString m_introText;
    QString m_fileNewText;
    QString m_fileOpenText;
    QString m_recentFilesText;
    bool m_customIntroText;
    bool m_customFileNewText;
    bool m_customFileOpenText;
    bool m_customRecentFilesText;
    bool m_fileNewEnabled;
    bool m_fileOpenEnabled;
    bool m_recentFilesEnabled;
    QxRecentFiles *m_recentFiles;

private slots:
    void processLink(const QUrl &url);

signals:
    void fileNewClicked();
    void fileOpenClicked();
    void fileOpenClicked(const QString &fileName);
};

} // namespace

#endif // QXDASHBOARD_H
