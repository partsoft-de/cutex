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
    setAttribute(Qt::WA_AcceptTouchEvents, true);

    m_stackedWidget = new QStackedWidget();
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
            if (m_touchPoints.size() == 1 && touchPoints.size() == 1) {
                if (touchPoints[0].pos().x() < m_touchPoints[0].pos().x()) {
                    setCurrentIndex(currentIndex() + 1);
                } else {
                    setCurrentIndex(currentIndex() - 1);
                }
            }
        }
        break;
    default:
        break;
    }
}

/*!
  \fn QxSwipeWidget::currentChanged(int index)

  Das Signal wird ausgelöst wenn das Widget mit dem Index <i>index</i> angezeigt wird.
*/

/*!
  \fn QxSwipeWidget::widgetRemoved(int index)

  Das Signal wird ausgelöst wenn das Widget mit dem Index <i>index</i> entfernt wurde.
*/
