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

#ifndef QXSWIPEWIDGET_H
#define QXSWIPEWIDGET_H

#include "cutex.h"
#include "qxswipebar.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSwipeWidget erweitert die Qt-Klasse QStackedWidget mit Gesten zum "wischen".

  %QxSwipeWidget erweitert die Qt-Klasse QStackedWidget mit Gesten zum "wischen". Zudem verfügt es über eine integrierte
  Navigationsleiste und unterstützt Navigationen.

  \sa QxSwipeBar
*/
class QxSwipeWidget : public QWidget
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(bool showNavigation READ showNavigation WRITE setShowNavigation)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString currentWidgetTitle READ currentWidgetTitle WRITE setCurrentWidgetTitle)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
    //! @endcond

public:
    QxSwipeWidget(QWidget *parent = nullptr);
    virtual QSize sizeHint() const;
    bool showNavigation() const;
    void setShowNavigation(bool show);
    bool isAnimated() const;
    void setAnimated(bool animated);
    void addWidget(QWidget *widget, const QString &title = QString());
    int count() const;
    int currentIndex() const;
    QWidget* currentWidget() const;
    int indexOf(QWidget *widget) const;
    void insertWidget(int index, QWidget *widget, const QString &title = QString());
    void removeWidget(int index);
    QWidget* widget(int index) const;
    void setSwipeEnabled(QWidget *widget, bool enabled);

public slots:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);
    QString currentWidgetTitle() const;
    void setCurrentWidgetTitle(const QString &title);
    void swipeTo(int index);
    void swipeTo(QWidget *widget);
    void swipeLeft();
    void swipeRight();

protected:
    virtual bool event(QEvent *event);
    virtual bool touchEvent(QTouchEvent *event);

private:
    bool m_animated;
    QStackedWidget *m_stackedWidget;
    QxSwipeBar *m_swipeBar;
    QWidget *m_currentWidget;
    QWidget *m_nextWidget;
    QList<QWidget*> m_ignoredWidgets;
    QPoint m_currentPoint;
    QParallelAnimationGroup *m_animation;

private slots:
    void widgetTitleChanged();
    void animationFinished();

signals:
    void currentChanged(int index);
    void currentTitleChanged(const QString &title);
    void widgetRemoved(int index);
};

} // namespace

#endif // QXSWIPEWIDGET_H
