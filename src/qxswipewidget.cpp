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

#include "qxswipewidget.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxSwipeWidget::QxSwipeWidget(QWidget *parent) : QWidget(parent)
{
    m_animated = true;
    m_swipeBar = new QxSwipeBar(this);
    m_stackedWidget = new QStackedWidget(this);
    m_currentWidget = nullptr;
    m_nextWidget = nullptr;
    m_animation = nullptr;

    setAttribute(Qt::WA_AcceptTouchEvents, true);
    setShowNavigation(true);

    connect(m_swipeBar, SIGNAL(currentChanged(int)), this, SLOT(swipeTo(int)));
    connect(m_stackedWidget, SIGNAL(currentChanged(int)), this, SIGNAL(currentChanged(int)));
    connect(m_stackedWidget, SIGNAL(widgetRemoved(int)), this, SIGNAL(widgetRemoved(int)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_swipeBar);
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
  Gibt true zurück, wenn die Navigationsleiste angezeigt wird.

  \sa setShowNavigation(bool show)
*/
bool QxSwipeWidget::showNavigation() const
{
    return m_swipeBar->isVisible();
}

/*!
  Blendet die Navigationsleiste ein, bzw. aus.

  \sa showNavigation() const
*/
void QxSwipeWidget::setShowNavigation(bool show)
{
    m_swipeBar->setVisible(show);
}

/*!
  Gibt true zurück, wenn Animationen für das Widget aktiviert sind.

  \sa setAnimated(bool animated)
*/
bool QxSwipeWidget::isAnimated() const
{
    return m_animated;
}

/*!
  Schaltet die Animationen für das Widget in Abhängigkeit von dem Wert <i>animated</i> ein, bzw. aus.

  \sa isAnimated() const
*/
void QxSwipeWidget::setAnimated(bool animated)
{
    m_animated = animated;
}

/*!
  Fügt das Wigdet <i>widget</i> dem Container hinzu.

  \sa insertWidget(int index, QWidget *widget, const QString &title)
*/
void QxSwipeWidget::addWidget(QWidget *widget, const QString &title)
{
    insertWidget(m_stackedWidget->count(), widget, title);
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

  \sa setCurrentIndex(int index)
*/
int QxSwipeWidget::currentIndex() const
{
    return m_stackedWidget->currentIndex();
}

/*!
  Gibt einen Zeiger auf das aktuelle Widget zurück.

  \sa setCurrentWidget(QWidget *widget)
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
void QxSwipeWidget::insertWidget(int index, QWidget *widget, const QString &title)
{
    if (title.isEmpty()) {
        if (widget->windowTitle().isEmpty())
            widget->setWindowTitle(tr("Seite %1").arg(count() + 1));
    } else {
        widget->setWindowTitle(title);
    }

    index = m_stackedWidget->insertWidget(index, widget);
    m_swipeBar->insertButton(index, widget->windowTitle());
    setCurrentIndex(index);

    connect(widget, SIGNAL(windowTitleChanged(QString)), SLOT(widgetTitleChanged()));
}

/*!
  Entfernt das Widget <i>widget</i>.
*/
void QxSwipeWidget::removeWidget(int index)
{
    m_swipeBar->removeButton(index);
    m_stackedWidget->removeWidget(m_stackedWidget->widget(index));
    setCurrentIndex(m_stackedWidget->currentIndex());
}

/*!
  Gibt einen Zeiger auf das Widget an Position <i>index</i> zurück.
*/
QWidget* QxSwipeWidget::widget(int index) const
{
    return m_stackedWidget->widget(index);
}

/*!
  Aktiviert die Swipe-Funktionalität für das Widget <i>widget</i>. Mit Widgets bei denen die Swipe-Funktionalität
  aktiviert ist, kann nicht weiter interagiert werden.
*/
void QxSwipeWidget::setSwipeEnabled(QWidget *widget, bool enabled)
{
    if (enabled) {
        m_ignoredWidgets.removeOne(widget);
    } else {
        if (!m_ignoredWidgets.contains(widget))
            m_ignoredWidgets.append(widget);
    }
}

/*!
  Zeigt das Widget mit dem Index <i>index</i> an.

  \sa currentIndex() const
*/
void QxSwipeWidget::setCurrentIndex(int index)
{
    m_swipeBar->setCurrentIndex(index);
    m_stackedWidget->setCurrentIndex(index);
}

/*!
  Zeigt das Widget <i>widget</i> an.

  \sa currentWidget() const
*/
void QxSwipeWidget::setCurrentWidget(QWidget *widget)
{
    setCurrentIndex(indexOf(widget));
}

/*!
  Gibt den Titel des aktuellen Widgets zurück.

  \sa setCurrentWidgetTitle(const QString &title)
*/
QString QxSwipeWidget::currentWidgetTitle() const
{
    return m_swipeBar->buttonText(currentIndex());
}

/*!
  Setzt den Titel des aktuellen Widgets auf den Wert <i>title</i>.

  \sa currentWidgetTitle() const
*/
void QxSwipeWidget::setCurrentWidgetTitle(const QString &title)
{
    QWidget *widget = currentWidget();

    if (widget) {
        widget->setWindowTitle(title);
        m_swipeBar->setButtonText(indexOf(widget), widget->windowTitle());

        emit currentTitleChanged(title);
    }
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
        if (touchEvent(static_cast<QTouchEvent*>(event)))
            return true;
    default:
        break;
    }

    return QWidget::event(event);
}

bool QxSwipeWidget::touchEvent(QTouchEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
        {
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
            QList<QTouchEvent::TouchPoint> touchPoints = event->points();
#else
            QList<QTouchEvent::TouchPoint> touchPoints = event->touchPoints();
#endif
            QVariant swipeEnabled;

            if (touchPoints.size() == 1) {
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
                QPointF pos = touchPoints.at(0).position();
#else
                QPointF pos = touchPoints.at(0).pos();
#endif
                QWidget *widget = childAt(pos.x(), pos.y());

                if (widget == m_swipeBar) {
                    return false;
                } else {
                    if (currentWidget()) {
                        widget = currentWidget()->childAt(pos.x(), pos.y());
                        if (widget) {
                            if (m_ignoredWidgets.contains(widget))
                                return false;

                            swipeEnabled = widget->property("swipeEnabled");
                            if (swipeEnabled.isValid() && swipeEnabled.toBool() == false)
                                return false;

                            while (widget != currentWidget()) {
                                widget = widget->parentWidget();
                                if (m_ignoredWidgets.contains(widget))
                                    return false;

                                swipeEnabled = widget->property("swipeEnabled");
                                if (swipeEnabled.isValid() && swipeEnabled.toBool() == false)
                                    return false;
                            }
                        }
                    }
                }
            }
        }
        break;
    case QEvent::TouchEnd:
        {
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
            QList<QTouchEvent::TouchPoint> touchPoints = event->points();
#else
            QList<QTouchEvent::TouchPoint> touchPoints = event->touchPoints();
#endif

            if (touchPoints.size() == 1) {
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
                QPointF pos = touchPoints.at(0).position();
                QPointF startPos = touchPoints.at(0).pressPosition();
#else
                QPointF pos = touchPoints.at(0).pos();
                QPointF startPos = touchPoints.at(0).startPos();
#endif
                qreal minDistance = 150.0;

                if (pos.x() + minDistance < startPos.x()) {
                    swipeRight();
                } else if (pos.x() > startPos.x() + minDistance) {
                    swipeLeft();
                }
            }
        }
        break;
    default:
        break;
    }

    return true;
}

void QxSwipeWidget::widgetTitleChanged()
{
    QWidget *widget = qobject_cast<QWidget*>(sender());

    m_swipeBar->setButtonText(indexOf(widget), widget->windowTitle());
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
  \fn QxSwipeWidget::currentTitleChanged(const QString &title)

  Der Titel des aktuellen Widgets wurde auf den Wert <i>title</i> gesetzt.
*/

/*!
  \fn QxSwipeWidget::widgetRemoved(int index)

  Das Signal wird ausgelöst wenn das Widget mit dem Index <i>index</i> entfernt wurde.
*/
