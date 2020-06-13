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

#ifndef QXSWIPEWIDGET_H
#define QXSWIPEWIDGET_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSwipeWidget erweitert die Qt-Klasse QStackedWidget mit Gesten zum "wischen".

  %QxSwipeWidget erweitert die Qt-Klasse QStackedWidget mit Gesten zum "wischen".
*/
class QxSwipeWidget : public QWidget
{
    Q_OBJECT
    //! @cond Q_PROPERTY
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
    //! @endcond

public:
    QxSwipeWidget(QWidget *parent = nullptr);
    virtual QSize sizeHint() const;
    bool isAnimated() const;
    void setAnimated(bool animated);
    void addWidget(QWidget *widget);
    int count() const;
    int currentIndex() const;
    QWidget* currentWidget() const;
    int indexOf(QWidget *widget) const;
    void insertWidget(int index, QWidget *widget);
    void removeWidget(int index);
    QWidget* widget(int index) const;

public slots:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);
    void swipeTo(int index);
    void swipeTo(QWidget *widget);
    void swipeLeft();
    void swipeRight();

protected:
    virtual bool event(QEvent *event);
    virtual void touchEvent(QTouchEvent *event);

private:
    bool m_animated;
    QStackedWidget *m_stackedWidget;
    QList<QTouchEvent::TouchPoint> m_touchPoints;
    QWidget *m_currentWidget;
    QWidget *m_nextWidget;
    QPoint m_currentPoint;
    QParallelAnimationGroup *m_animation;

private slots:
    void animationFinished();

signals:
    void currentChanged(int index);
    void widgetRemoved(int index);

};

} // namespace

#endif // QXSWIPEWIDGET_H
