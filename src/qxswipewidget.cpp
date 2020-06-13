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

#include "qxswipewidget.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxSwipeWidget::QxSwipeWidget(QWidget *parent) : QWidget(parent)
{
    m_animated = true;
    m_stackedWidget = new QStackedWidget();
    m_currentWidget = nullptr;
    m_nextWidget = nullptr;
    m_animation = nullptr;

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    connect(m_stackedWidget, SIGNAL(currentChanged(int)), this, SIGNAL(currentChanged(int)));
    connect(m_stackedWidget, SIGNAL(widgetRemoved(int)), this, SIGNAL(widgetRemoved(int)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_stackedWidget);
}

/*!
  Gibt die empfohlene Größe für das Widget zurück.
*/
QSize QxSwipeWidget::sizeHint() const
{
    return QSize(120, 80);
}

bool QxSwipeWidget::isAnimated() const
{
    return m_animated;
}

void QxSwipeWidget::setAnimated(bool animated)
{
    m_animated = animated;
}

/*!
  Fügt das Wigdet <i>widget</i> dem Container hinzu.
*/
void QxSwipeWidget::addWidget(QWidget *widget)
{
    m_stackedWidget->addWidget(widget);
}

/*!
  Gibt die Anzahl der Widgets zurück.
*/
int QxSwipeWidget::count() const
{
    return m_stackedWidget->count();
}

/*!
  Gibt den Index des aktuellen Widgets zurück.
*/
int QxSwipeWidget::currentIndex() const
{
    return m_stackedWidget->currentIndex();
}

/*!
  Gibt einen Zeiger auf das aktuelle Widget zurück.
*/
QWidget* QxSwipeWidget::currentWidget() const
{
    return m_stackedWidget->currentWidget();
}

/*!
  Gibt den Index des Widgets <i>widget</i> zurück.
*/
int QxSwipeWidget::indexOf(QWidget *widget) const
{
    return m_stackedWidget->indexOf(widget);
}

/*!
  Fügt das Widget <i>widget</i> an der Position <i>index</i> ein.
*/
void QxSwipeWidget::insertWidget(int index, QWidget *widget)
{
    m_stackedWidget->insertWidget(index, widget);
}

/*!
  Entfernt das Widget <i>widget</i>.
*/
void QxSwipeWidget::removeWidget(int index)
{
    m_stackedWidget->removeWidget(m_stackedWidget->widget(index));
}

/*!
  Gibt einen Zeiger auf das Widget an Position <i>index</i> zurück.
*/
QWidget* QxSwipeWidget::widget(int index) const
{
    return m_stackedWidget->widget(index);
}

/*!
  Zeigt das Widget mit dem Index <i>index</i> an.
*/
void QxSwipeWidget::setCurrentIndex(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}

/*!
  Zeigt das Widget <i>widget</i> an.
*/
void QxSwipeWidget::setCurrentWidget(QWidget *widget)
{
    m_stackedWidget->setCurrentWidget(widget);
}

/*!
  "Wischt" zu dem Widget mit dem Index <i>index</i>.
*/
void QxSwipeWidget::swipeTo(int index)
{
    swipeTo(widget(index));
}

/*!
  "Wischt" zu dem Widget <i>widget</i>.
*/
void QxSwipeWidget::swipeTo(QWidget *widget)
{
    if (!widget)
        return;

    if (m_animation) {
        m_animation->stop();
        animationFinished();
        QApplication::processEvents();
    }

    const int current = currentIndex();
    const int next = indexOf(widget);

    if (!m_animated || widget == currentWidget())
    {
        setCurrentWidget(widget);
    } else {
        m_currentWidget = currentWidget();
        m_nextWidget = widget;

        const int width = m_stackedWidget->frameRect().width();
        const int height = m_stackedWidget->frameRect().height();
        const int offset = (next > current) ? width : -width;

        m_currentPoint = m_currentWidget->pos();
        m_nextWidget->setGeometry(0, 0, width, height);

        QPoint nextPoint = m_nextWidget->pos();
        m_nextWidget->move(nextPoint.x() + offset, nextPoint.y());
        m_nextWidget->show();
        m_nextWidget->raise();

        m_animation = new QParallelAnimationGroup(this);
        QPropertyAnimation *animation;

        animation = new QPropertyAnimation(m_currentWidget, "pos", m_animation);
        animation->setDuration(300);
        animation->setStartValue(m_currentPoint);
        animation->setEndValue(QPoint(m_currentPoint.x() - offset, m_currentPoint.y()));
        animation->setEasingCurve(QEasingCurve::OutQuad);
        m_animation->addAnimation(animation);

        animation = new QPropertyAnimation(m_nextWidget, "pos", m_animation);
        animation->setDuration(300);
        animation->setStartValue(QPoint(nextPoint.x() + offset, nextPoint.y()));
        animation->setEndValue(nextPoint);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        m_animation->addAnimation(animation);

        connect(m_animation, SIGNAL(finished()), this, SLOT(animationFinished()));
        m_animation->start();
    }
}

/*!
  "Wischt" zu dem vom aktuellen linken Widget.
*/
void QxSwipeWidget::swipeLeft()
{
    swipeTo(currentIndex() - 1);
}

/*!
  "Wischt" zu dem vom aktuellen rechten Widget.
*/
void QxSwipeWidget::swipeRight()
{
    swipeTo(currentIndex() + 1);
}

bool QxSwipeWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    case QEvent::TouchCancel:
        touchEvent(static_cast<QTouchEvent*>(event));
        return true;
    default:
        break;
    }

    return QWidget::event(event);
}

void QxSwipeWidget::touchEvent(QTouchEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
        m_touchPoints = event->touchPoints();
        break;
    case QEvent::TouchEnd:
        {
            QList<QTouchEvent::TouchPoint> touchPoints = event->touchPoints();
            const qreal minDistance = 150.0;

            if (m_touchPoints.size() == 1 && touchPoints.size() == 1) {
                if (touchPoints[0].pos().x() + minDistance < m_touchPoints[0].pos().x()) {
                    swipeRight();
                } else if (touchPoints[0].pos().x() > m_touchPoints[0].pos().x() + minDistance) {
                    swipeLeft();
                }
            }
        }
        break;
    default:
        break;
    }
}

void QxSwipeWidget::animationFinished()
{
    setCurrentWidget(m_nextWidget);
    m_currentWidget->hide();
    m_currentWidget->move(m_currentPoint);
    m_currentWidget->update();

    delete m_animation;
    m_animation = nullptr;
}

/*!
  \fn QxSwipeWidget::currentChanged(int index)

  Das Signal wird ausgelöst wenn das Widget mit dem Index <i>index</i> angezeigt wird.
*/

/*!
  \fn QxSwipeWidget::widgetRemoved(int index)

  Das Signal wird ausgelöst wenn das Widget mit dem Index <i>index</i> entfernt wurde.
*/
