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

#include "qxhelpbrowser.h"
#include "qxhelpmanager.h"

using namespace cutex;

#ifdef QT_WEBKITWIDGETS_LIB
QxHelpBrowser::QxHelpBrowser(QWidget *parent) : QWebView(parent)
{
    m_helpEngine = 0;

    connect(this, SIGNAL(linkClicked(QUrl)), this, SLOT(setSource(QUrl)));
}

void QxHelpBrowser::setHelpEngine(QHelpEngine *helpEngine)
{
    m_helpEngine = helpEngine;
    page()->setNetworkAccessManager(new QxHelpManager(helpEngine, this));
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

bool QxHelpBrowser::isBackwardAvailable() const
{
    return pageAction(QWebPage::Back)->isEnabled();
}

bool QxHelpBrowser::isForwardAvailable() const
{
    return pageAction(QWebPage::Forward)->isEnabled();
}

void QxHelpBrowser::setSource(const QUrl &url)
{
    if (m_helpEngine) {
        if (url.scheme() == "qthelp") {
            load(url);
            if (m_home.isEmpty())
                m_home = url;
        } else {
            QDesktopServices::openUrl(url);
        }
    }
}

void QxHelpBrowser::home()
{
    if (m_home.isValid())
        setSource(m_home);
}

void QxHelpBrowser::zoomIn(int range)
{
    setZoomFactor(zoomFactor() + (0.1 * range));
}

void QxHelpBrowser::zoomOut(int range)
{
    setZoomFactor(qMax(0.0, zoomFactor() - (0.1 * range)));
}

#else
/*!
  Erzeugt einen neuen Hilfebrowser mit dem Elternobjekt <i>parent</i>.
*/
QxHelpBrowser::QxHelpBrowser(QWidget *parent) : QTextBrowser(parent)
{
    m_helpEngine = 0;

    setOpenExternalLinks(false);
}

/*!
  Lädt die unter <i>url</i> angegebene Ressource vom Typ <i>type</i>.
*/
QVariant QxHelpBrowser::loadResource(int type, const QUrl &url)
{
    if (url.scheme() == "qthelp" && m_helpEngine)
        return QVariant(m_helpEngine->fileData(url));

    return QTextBrowser::loadResource(type, url);
}

/*!
  Setzt die unter <i>helpEnginge</i> angegebene Hilfe-Engine.
*/
void QxHelpBrowser::setHelpEngine(QHelpEngine *helpEngine)
{
    m_helpEngine = helpEngine;
}

/*!
  Setzt das unter <i>name</i> angegebene Dokument als Quelle.
*/
void QxHelpBrowser::setSource(const QUrl &name)
{
    if (name.scheme() == "http" || name.scheme() == "https") {
        QDesktopServices::openUrl(name);
    } else {
        QTextBrowser::setSource(name);

#ifdef Q_OS_MAC
        zoomFonts(1.33);
#endif
    }
}

void QxHelpBrowser::zoomFonts(double factor)
{
    QTextDocument *doc = document();
    QTextBlock block = doc->begin();

    while (block.isValid()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextFragment fragment = it.fragment();
            QTextCharFormat format = fragment.charFormat();
            QFont font = format.font();
            QTextCursor cursor(doc);

            cursor.setPosition(fragment.position());
            cursor.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
            font.setPointSizeF(font.pointSizeF() * factor);
            format.setFont(font);
            cursor.setCharFormat(format);
        }
        block = block.next();
    }
}

#endif // QT_WEBKITWIDGETS_LIB
