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

#ifndef QXHELPBROWSER_H
#define QXHELPBROWSER_H

#include "cutex.h"

#ifdef QT_WEBKITWIDGETS_LIB
#include <QtWebKitWidgets>
#endif

namespace cutex {

#ifdef QT_WEBKITWIDGETS_LIB
class QxHelpBrowser : public QWebView
{
    Q_OBJECT

public:
    QxHelpBrowser(QWidget *parent = 0);
    void setHelpEngine(QHelpEngine *helpEngine);
    bool isBackwardAvailable() const;
    bool isForwardAvailable() const;

public slots:
    void setSource(const QUrl &url);
    void home();
    void zoomIn(int range);
    void zoomOut(int range);

private:
    QHelpEngine *m_helpEngine;
    QUrl m_home;
};

#else
/*!
  \brief Die Klasse %QxHelpBrowser stellt ein Steuerelement zur Anzeige von Hilfedateien zur Verfügung.

  %QxHelpBrowser erweitert die Klasse QTextBrowser um Funktionen zur Anzeige von Hilfedateien.

  \sa QxHelpWindow
*/
class QxHelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    QxHelpBrowser(QWidget *parent = 0);
    virtual QVariant loadResource(int type, const QUrl &url);
    void setHelpEngine(QHelpEngine *helpEngine);

public slots:
    void setSource(const QUrl &name);

private:
    QHelpEngine *m_helpEngine;

private slots:
    void zoomFonts(double factor);
};

#endif // QT_WEBKITWIDGETS_LIB
} // namespace

#endif // QXHELPBROWSER_H
