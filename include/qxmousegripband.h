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

#ifndef QXMOUSEGRIPBAND_H
#define QXMOUSEGRIPBAND_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxMouseGripBand kann zum Verschieben, bzw. zur Größenänderung von Widgets verwendet werden.

  Ein %QxMouseGripBand wird als Rahmen dargestellt, der an den Ecken (und Seiten) über kleine Rechtecke (Greifer)
  verfügt, die der Benutzer mit der Maus ziehen kann um die Größe zu verändern. Das %QxMouseGripBand wird üblicherweise
  in einem Texteditor verwendet, um z.B. die Größe von Bildern, etc. zu verändern.

  \sa QxTextEdit
*/
class QxMouseGripBand : public QWidget
{
    Q_OBJECT

public:
    QxMouseGripBand(QWidget *parent = nullptr);
    bool isMoveEnabled() const;
    void setMoveEnabled(bool enabled);
    QSize gripSize() const;
    void setGripSize(const QSize &size);
    QColor gripColor() const;
    void setGripColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    enum Grip { NoGrip = 0, BottomRight, TopLeft, TopMiddle, TopRight, Left, Right, BottomLeft, BottomMiddle };

private:
    bool m_moveEnabled;
    QSize m_gripSize;
    QColor m_gripColor;
    QPointF m_dragPos;
    Grip m_dragGrip;

private:
    QMap<Grip, QRectF> gripPositions() const;

signals:
    void resized(const QRect &rect);
    void resizeFinished(const QRect &rect);
    void moved(const QRect &rect);
    void moveFinished(const QRect &rect);
};

} // namespace

#endif // QXMOUSEGRIPBAND_H
