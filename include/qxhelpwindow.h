/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXHELPWINDOW_H
#define QXHELPWINDOW_H

#include "cutex.h"
#include "qxhelpbrowser.h"

namespace Ui {
class QxHelpWindow;
}

namespace cutex {

/*!
  \brief %QxHelpWindow ist ein fertiges Fenster zur Anzeige von Hilfedateien.

  Fenster vom Typ %QxHelpWindow können verwendet werden um Hilfedateien anzuzeigen. Somit benötigen Sie für Ihre
  Programmhilfe keine externe Anwendung mehr, wie z.B. Qt Assistant. In der aktuellen Version ist ein
  Inhaltsverzeichnis, sowie eine Indexfunktion integriert. Eine Suchfunktion ist für spätere Versionen geplant.

  \sa QxHelpBrowser
*/
class QxHelpWindow : public QWidget {
    Q_OBJECT

public:
    QxHelpWindow(const QString &collectionFile, QWidget *parent = 0);
    ~QxHelpWindow();

public slots:
    void setUrl(const QUrl &url);
    void showContents() const;
    void showIndex() const;
    void zoomIn(int range);
    void zoomOut(int range);

protected:
    void changeEvent(QEvent *event);

private:
    Ui::QxHelpWindow *m_ui;
    QHelpEngine *m_helpEngine;
    QHelpContentWidget *m_contentTree;
    QHelpIndexWidget *m_indexList;

private slots:
    void relockActions();
};

} // namespace

#endif // QXHELPWINDOW_H
