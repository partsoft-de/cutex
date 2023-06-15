/***********************************************************************************************************************
**
** Copyright (C) 2016-2023 Partsoft UG (haftungsbeschränkt)
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

#include "qxhelpwindow.h"

using namespace cutex;

#include "ui_qxhelpwindow.h"

#ifdef QT_WEBKITWIDGETS_LIB
QxHelpWindow::QxHelpWindow(const QString &collectionFile, QWidget *parent) : QWidget(parent),
    m_ui(new Ui::QxHelpWindow)
{
    m_ui->setupUi(this);
    setWindowFlags(Qt::Window);

    m_helpEngine = new QHelpEngine(collectionFile);
    m_helpEngine->setupData();
    m_contentTree = m_helpEngine->contentWidget();
    m_indexList = m_helpEngine->indexWidget();
    m_ui->ContentLayout->addWidget(m_contentTree);
    m_ui->IndexLayout->addWidget(m_indexList);
    m_ui->HelpBrowser->setHelpEngine(m_helpEngine);
    m_ui->HelpBrowser->setContextMenuPolicy(Qt::NoContextMenu);

    connect(m_contentTree, SIGNAL(linkActivated(QUrl)), this, SLOT(setUrl(QUrl)));
    connect(m_ui->IndexEdit, SIGNAL(textEdited(QString)), m_indexList, SLOT(filterIndices(QString)));
    connect(m_indexList, SIGNAL(linkActivated(QUrl,QString)), this, SLOT(setUrl(QUrl)));
    connect(m_ui->HelpBrowser, SIGNAL(loadFinished(bool)), this, SLOT(relockActions()));
    connect(m_ui->HomeAction, SIGNAL(triggered(bool)), m_ui->HelpBrowser, SLOT(home()));
    connect(m_ui->BackwardAction, SIGNAL(triggered(bool)), m_ui->HelpBrowser, SLOT(back()));
    connect(m_ui->ForwardAction, SIGNAL(triggered(bool)), m_ui->HelpBrowser, SLOT(forward()));
    connect(m_ui->ExitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    relockActions();
}

#else
/*!
  Erzeugt ein neues Hilfefenster mit dem Elternobjekt <i>parent</i>. Der Pfad zur Hilfedatei (qhc) muss unter
  <i>collectionFile</i> angegeben werden.
*/
QxHelpWindow::QxHelpWindow(const QString &collectionFile, QWidget *parent) : QWidget(parent),
    m_ui(new Ui::QxHelpWindow)
{
    m_ui->setupUi(this);
    setWindowFlags(Qt::Window);

    m_helpEngine = new QHelpEngine(collectionFile);
    m_helpEngine->setupData();
    m_contentTree = m_helpEngine->contentWidget();
    m_indexList = m_helpEngine->indexWidget();
    m_ui->ContentLayout->addWidget(m_contentTree);
    m_ui->IndexLayout->addWidget(m_indexList);
    m_ui->HelpBrowser->setHelpEngine(m_helpEngine);

    connect(m_contentTree, SIGNAL(linkActivated(QUrl)), this, SLOT(setUrl(QUrl)));
    connect(m_ui->IndexEdit, SIGNAL(textEdited(QString)), m_indexList, SLOT(filterIndices(QString)));
    connect(m_indexList, SIGNAL(linkActivated(QUrl,QString)), this, SLOT(setUrl(QUrl)));
    connect(m_ui->HelpBrowser, SIGNAL(historyChanged()), this, SLOT(relockActions()));
    connect(m_ui->HomeAction, SIGNAL(triggered(bool)), m_ui->HelpBrowser, SLOT(home()));
    connect(m_ui->BackwardAction, SIGNAL(triggered(bool)), m_ui->HelpBrowser, SLOT(backward()));
    connect(m_ui->ForwardAction, SIGNAL(triggered(bool)), m_ui->HelpBrowser, SLOT(forward()));
    connect(m_ui->ExitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    relockActions();
}
#endif // QT_WEBKITWIDGETS_LIB

QxHelpWindow::~QxHelpWindow()
{
    delete m_ui;
}

/*!
  Setzt das unter <i>name</i> angegebene Dokument als Quelle.
*/
void QxHelpWindow::setUrl(const QUrl &url)
{
    m_ui->HelpBrowser->setSource(url);    
    relockActions();
}

/*!
  Wechselt im Navigationsbereich zu dem Kartenreiter "Inhalt".
*/
void QxHelpWindow::showContents() const
{
    m_ui->NavigationTab->setCurrentWidget(m_ui->ContentPage);
}

/*!
  Wechselt im Navigationsbereich zu dem Kartenreiter "Index".
*/
void QxHelpWindow::showIndex() const
{
    m_ui->NavigationTab->setCurrentWidget(m_ui->IndexPage);
}

/*!
  Vergrössert die Schrift um den Faktor <i>range</i>.
*/
void QxHelpWindow::zoomIn(int range)
{
    m_ui->HelpBrowser->zoomIn(range);
}

/*!
  Verkleinert die Schrift um den Faktor <i>range</i>.
*/
void QxHelpWindow::zoomOut(int range)
{
    m_ui->HelpBrowser->zoomOut(range);
}

/*!
  Wird aufgerufen wenn sich der Status geändert hat.
*/
void QxHelpWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
        m_ui->retranslateUi(this);

    QWidget::changeEvent(event);
}

#ifdef QT_WEBKITWIDGETS_LIB
void QxHelpWindow::relockActions()
{
    m_ui->HomeAction->setEnabled(m_ui->HelpBrowser->url().isValid());
    m_ui->BackwardAction->setEnabled(m_ui->HelpBrowser->isBackwardAvailable());
    m_ui->ForwardAction->setEnabled(m_ui->HelpBrowser->isForwardAvailable());
}

#else
void QxHelpWindow::relockActions()
{
    m_ui->HomeAction->setEnabled(m_ui->HelpBrowser->source().isValid());
    m_ui->BackwardAction->setEnabled(m_ui->HelpBrowser->isBackwardAvailable());
    m_ui->ForwardAction->setEnabled(m_ui->HelpBrowser->isForwardAvailable());
}
#endif // QT_WEBKITWIDGETS_LIB
