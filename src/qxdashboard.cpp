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

#include "qxdashboard.h"

using namespace cutex;

/*!
  Erzeugt ein neues Dashboard mit dem Elternobjekt <i>parent</i>.
*/
QxDashboard::QxDashboard(QWidget *parent) : QxForm(parent)
{
    m_dashboard = new QTextBrowser(this);
    m_font = QFont("Arial", 10, 400);
    m_introText = tr("Willkommen");
    m_fileNewText = tr("Neue Datei");
    m_fileOpenText = tr("Datei öffnen");
    m_recentFilesText = tr("Zuletzt verwendete Dateien");
    m_customIntroText = false;
    m_customFileNewText = false;
    m_customFileOpenText = false;
    m_customRecentFilesText = false;
    m_fileNewEnabled = true;
    m_fileOpenEnabled = true;
    m_recentFilesEnabled = true;
    m_recentFiles = 0;

#ifdef Q_OS_MAC
    m_font = QFont("Arial", 14, 400);
#endif

    setWindowTitle(tr("Dashboard"));
    setWindowIcon(QIcon(":/icons/16x16/house.png"));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_dashboard);
    setLayout(layout);

    m_dashboard->setOpenLinks(false);
    connect(m_dashboard, SIGNAL(anchorClicked(QUrl)), this, SLOT(processLink(QUrl)));
    update();
}

/*!
  Gibt die aktuelle Schriftart zurück.
*/
QFont QxDashboard::font() const
{
    return m_font;
}

/*!
  Setzt die Schriftart auf den Wert <i>font</i>.
*/
void QxDashboard::setFont(const QFont &font)
{
    m_font = font;
    update();
}

/*!
  Setzt den Einleitungstext auf den Wert <i>text</i>.
*/
void QxDashboard::setIntroText(const QString &text)
{
    m_introText = text;
    m_customIntroText = true;
    update();
}

/*!
  Setzt den Text zur Neuanlage einer Datei auf den Wert <i>text</i>.
*/
void QxDashboard::setFileNewText(const QString &text)
{
    m_fileNewText = text;
    m_customFileNewText = true;
    update();
}

/*!
  Setzt den Text zum Öffnen einer Datei auf den Wert <i>text</i>.
*/
void QxDashboard::setFileOpenText(const QString &text)
{
    m_fileOpenText = text;
    m_customFileOpenText = true;
    update();
}

/*!
  Setzt die Überschrift für die zuletzt verwendeten Dateien auf den Wert <i>text</i>.
*/
void QxDashboard::setRecentFilesText(const QString &text)
{
    m_recentFilesText = text;
    m_customRecentFilesText = true;
    update();
}

/*!
  Aktiviert oder deaktiviert die Neuanlage von Dateien.
*/
void QxDashboard::setFileNewEnabled(bool enabled)
{
    m_fileNewEnabled = enabled;
    update();
}

/*!
  Aktiviert oder deaktiviert das Öffnen von Dateien.
*/
void QxDashboard::setFileOpenEnabled(bool enabled)
{
    m_fileOpenEnabled = enabled;
    update();
}

/*!
  Aktiviert oder deaktiviert die Liste der zuletzt verwendeten Dateien.
*/
void QxDashboard::setRecentFilesEnabled(bool enabled)
{
    m_recentFilesEnabled = enabled;
    update();
}

/*!
  Setzt die Liste der zuletzt verwendeten Dateien.
*/
void QxDashboard::setRecentFiles(QxRecentFiles *recentFiles)
{
    m_recentFiles = recentFiles;
    connect(m_recentFiles, SIGNAL(filesChanged()), this, SLOT(update()));
    update();
}

/*!
  Wird aufgerufen wenn die Sprache geändert wurde.
*/
void QxDashboard::retranslateUi()
{
    setWindowTitle(tr("Dashboard"));

    if (!m_customIntroText)
        m_introText = tr("Willkommen");
    if (!m_customFileNewText)
        m_fileNewText = tr("Neue Datei");
    if (!m_customFileOpenText)
        m_fileOpenText = tr("Datei öffnen");
    if (!m_customRecentFilesText)
        m_recentFilesText = tr("Zuletzt verwendete Dateien");

    update();
}

/*!
  Aktualisiert das Dashboard.
*/
void QxDashboard::update()
{
    QString html;
    html = QString("<body style=\"font-family:'%1'; ").arg(m_font.family());
    html += QString("font-size:%1pt; ").arg(m_font.pointSize());
    html += QString("font-weight:%1; ").arg(m_font.weight());
    html += "font-style:normal\">";

    if (!m_introText.isEmpty())
        html += m_introText + "<hr>";

    html += "<table width=\"100%\"><tr><td>";
    if (m_fileNewEnabled) {
        html += "<p><table><tr><td><a href=\"filenew\">" + m_fileNewText;
        html += "<td>&nbsp;<a href=\"filenew\"><img src=\":/icons/16x16/page_white.png\"</a></td></tr></table>";
    }

    if (m_fileOpenEnabled) {
        html += "<p><table><tr><td><a href=\"fileopen\">" + m_fileOpenText;
        html += "<td>&nbsp;<a href=\"fileopen\"><img src=\":/icons/16x16/folder.png\"</a></td></tr></table>";
    }

    html += "</td><td width=\"75%\">";
    if (m_recentFilesEnabled && m_recentFiles) {
        html += "<p>" + m_recentFilesText + "</p>";
        if (m_recentFiles) {
            for (QString file : m_recentFiles->files())
                html += "<p><a href=\"file:///" + file + "\">" + file + "</a></p>";
        }
    }

    html += "</td></tr></table></body>";

    m_dashboard->setHtml(html);
}

void QxDashboard::processLink(const QUrl &url)
{
    if (url.isLocalFile()) {
        emit fileOpenClicked(url.toLocalFile());
    } else {
        if (url.toString() == "filenew") {
            emit fileNewClicked();
        } else if (url.toString() == "fileopen") {
            emit fileOpenClicked();
        }
    }
}

/*!
  \fn QxDashboard::fileNewClicked()

  Das Signal wird ausgelöst wenn der Anwender eine neue Datei anlegen will.
*/

/*!
  \fn QxDashboard::fileOpenClicked()

  Das Signal wird ausgelöst wenn der Anwender eine Datei öffnen will.
*/

/*!
  \fn QxDashboard::fileOpenClicked(const QString &fileName)

  Das Signal wird ausgelöst wenn der Anwender die Datei <i>fileName</i> öffnen will.
*/
