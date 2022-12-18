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

#include "qxmousegripband.h"

using namespace cutex;

/*!
  Erzeugt ein neues Grip-Band mit dem Elternobjekt <i>parent</i>.
*/
QxMouseGripBand::QxMouseGripBand(QWidget *parent) : QWidget(parent)
{
    m_moveEnabled = true;
    m_gripSize = QSize(8, 8);
    m_gripColor = QColor(Qt::blue);
    m_dragPos = QPointF();
    m_dragGrip = QxMouseGripBand::NoGrip;

    setMouseTracking(true);
    setMinimumSize(m_gripSize);
}

/*!
  Gibt true zurück, wenn das Grip-Band verschoben werden darf.
*/
bool QxMouseGripBand::isMoveEnabled() const
{
    return m_moveEnabled;
}

/*!
  Legt in Abhängigkeit von <i>enabled</i> fest, ob das Grip-Band verschoben werden darf.
*/
void QxMouseGripBand::setMoveEnabled(bool enabled)
{
    m_moveEnabled = enabled;
}

/*!
  Gibt die Größe der Greifer zurück.
*/
QSize QxMouseGripBand::gripSize() const
{
    return m_gripSize;
}

/*!
  Setzt die Größe der Greifer auf den Wert <i>size</i>.
*/
void QxMouseGripBand::setGripSize(const QSize &size)
{
    if (m_gripSize != size && size.isValid()) {
        m_gripSize = size;
        update();
    }
}

/*!
  Gibt die Farbe der Greifer zurück.
*/
QColor QxMouseGripBand::gripColor() const
{
    return m_gripColor;
}

/*!
  Setzt die Farbe der Greifer auf den Wert <i>color</i>.
*/
void QxMouseGripBand::setGripColor(const QColor &color)
{
    if (m_gripColor != color) {
        m_gripColor = color;
        update();
    }
}

void QxMouseGripBand::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QMap<QxMouseGripBand::Grip, QRectF> positions = gripPositions();
    QPainter painter(this);

    if (!m_dragPos.isNull()) {
        painter.setPen(QPen(m_gripColor, 1, Qt::SolidLine));
        painter.drawRect(0, 0, size().width() - 1, size().height() - 1);
    }

    for (const QRectF &rc : positions.values())
        painter.fillRect(rc, QBrush(m_gripColor));
}

void QxMouseGripBand::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isVisible()) {
        QMap<QxMouseGripBand::Grip, QRectF> positions = gripPositions();
        QPoint pos = event->pos();

        for (const QxMouseGripBand::Grip &key : positions.keys()) {
            const QRectF &rc = positions.value(key);

            if (rc.contains(pos)) {
                m_dragPos = event->windowPos();
                m_dragGrip = key;
                break;
            }
        }

        if (m_dragGrip == QxMouseGripBand::NoGrip && m_moveEnabled)
            m_dragPos = event->windowPos();
    }
}

void QxMouseGripBand::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragPos.isNull()) {
        QPointF pos = event->pos();
        QMap<QxMouseGripBand::Grip, QRectF> positions = gripPositions();

        for (const QxMouseGripBand::Grip&key : positions.keys()) {
            const QRectF &rc = positions.value(key);

            if (rc.contains(pos)) {
                switch (key) {
                case QxMouseGripBand::NoGrip:
                    break;
                case QxMouseGripBand::Left:
                case QxMouseGripBand::Right:
                    setCursor(Qt::SizeHorCursor);
                    break;
                case QxMouseGripBand::TopMiddle:
                case QxMouseGripBand::BottomMiddle:
                    setCursor(Qt::SizeVerCursor);
                    break;
                case QxMouseGripBand::TopLeft:
                case QxMouseGripBand::BottomRight:
                    setCursor(Qt::SizeFDiagCursor);
                    break;
                case QxMouseGripBand::TopRight:
                case QxMouseGripBand::BottomLeft:
                    setCursor(Qt::SizeBDiagCursor);
                    break;
                }
                break;
            } else {
                setCursor(Qt::ArrowCursor);
            }
        }
    } else {
        QPointF pos = event->windowPos();
        QRectF rc = geometry();

        switch (m_dragGrip) {
        case QxMouseGripBand::NoGrip:
            rc.moveLeft(rc.left() + pos.rx() - m_dragPos.rx());
            rc.moveTop(rc.top() + pos.ry() - m_dragPos.ry());
            break;
        case QxMouseGripBand::BottomRight:
            rc.setWidth(rc.width() + pos.rx() - m_dragPos.rx());
            rc.setHeight(rc.height() + pos.ry() - m_dragPos.ry());
            break;
        case QxMouseGripBand::TopLeft:
            rc.setLeft(rc.left() + pos.rx() - m_dragPos.rx());
            rc.setTop(rc.top() + pos.ry() - m_dragPos.ry());
            break;
        case QxMouseGripBand::TopMiddle:
            rc.setTop(rc.top() + pos.ry() - m_dragPos.ry());
            break;
        case QxMouseGripBand::TopRight:
            rc.setWidth(rc.width() + pos.rx() - m_dragPos.rx());
            rc.setTop(rc.top() + pos.ry() - m_dragPos.ry());
            break;
        case QxMouseGripBand::Left:
            rc.setLeft(rc.left() + pos.rx() - m_dragPos.rx());
            break;
        case QxMouseGripBand::Right:
            rc.setWidth(rc.width() + pos.rx() - m_dragPos.rx());
            break;
        case QxMouseGripBand::BottomLeft:
            rc.setLeft(rc.left() + pos.rx() - m_dragPos.rx());
            rc.setHeight(rc.height() + pos.ry() - m_dragPos.ry());
            break;
        case QxMouseGripBand::BottomMiddle:
            rc.setHeight(rc.height() + pos.ry() - m_dragPos.ry());
            break;
        }

        BREAKABLE_BLOCK {
            QSize minSize = minimumSize();
            if (minSize.isValid() && (rc.width() < minSize.width() || rc.height() < minSize.height()))
                break;

            QSize maxSize = maximumSize();
            if (maxSize.isValid() && (rc.width() > maxSize.width() || rc.height() > maxSize.height()))
                break;

            m_dragPos = pos;
            setGeometry(rc.toRect());

            if (m_dragGrip == QxMouseGripBand::NoGrip) {
                emit moved(geometry());
            } else {
                emit resized(geometry());
            }
        }
    }
}

void QxMouseGripBand::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    if (!m_dragPos.isNull()) {
        if (m_dragGrip == QxMouseGripBand::NoGrip) {
            emit moveFinished(geometry());
        } else {
            emit resizeFinished(geometry());
        }
    }

    m_dragPos = QPointF();
    m_dragGrip = QxMouseGripBand::NoGrip;

    update();
}

QMap<QxMouseGripBand::Grip, QRectF> QxMouseGripBand::gripPositions() const
{
    QMap<QxMouseGripBand::Grip, QRectF> positions;
    QRectF rc = rect();
    double gw = m_gripSize.width();
    double gh = m_gripSize.height();
    double rw = rc.width();
    double rh = rc.height();

    positions.insert(QxMouseGripBand::TopLeft, QRectF(0, 0, gw, gh));
    positions.insert(QxMouseGripBand::TopRight, QRectF(rw - gw, 0, gw, gh));
    positions.insert(QxMouseGripBand::BottomLeft, QRectF(0, rh - gh, gw, gh));
    positions.insert(QxMouseGripBand::BottomRight, QRectF(rw - gw, rh - gh, gw, gh));

    if (rw >= gw * 3.0) {
        positions.insert(QxMouseGripBand::TopMiddle, QRectF((rw / 2.0) - (gw / 2.0), 0, gw, gh));
        positions.insert(QxMouseGripBand::BottomMiddle, QRectF((rw / 2.0) - (gw / 2.0), rh - gh, gw, gh));
    }

    if (rh >= gh * 2.0) {
        positions.insert(QxMouseGripBand::Left, QRectF(0, (rh / 2.0) - (gh / 2.0), gw, gh));
        positions.insert(QxMouseGripBand::Right, QRectF(rw - gw, (rh / 2.0) - (gh / 2.0), gw, gh));
    }

    return positions;
}

/*!
  \fn QxMouseGripBand::resized(const QRect &rect)

  Das Signal wird ausgelöst wenn der Anwender die Größe auf den neuen Bereich <i>rect</i> geändert hat.
*/

/*!
  \fn QxMouseGripBand::resizeFinished(const QRect &rect)

  Das Signal wird ausgelöst wenn der Anwender die Größenänderung auf den Bereich <i>rect</i> abgeschlossen hat.
*/

/*!
  \fn QxMouseGripBand::moved(const QRect &rect)

  Das Signal wird ausgelöst wenn der Anwender das Grip-Band auf den Bereich <i>rect</i> verschoben hat.
*/

/*!
  \fn QxMouseGripBand::moveFinished(const QRect &rect)

  Das Signal wird ausgelöst wenn der Anwender die Verschiebung auf den Bereich <i>rect</i> abgeschlossen hat.
*/
