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

#include "qxswipebar.h"

using namespace cutex;

/*!
  Erzeugt ein neues Widget mit dem Elternobjekt <i>parent</i>.
*/
QxSwipeBar::QxSwipeBar(QWidget *parent) : QScrollArea(parent)
{
    QWidget *widget = new QWidget(this);
    m_layout = new QHBoxLayout(widget);
    m_layout->setContentsMargins(QMargins());
    m_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

    QScroller::grabGesture(this);
    setWidget(widget);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(true);
}

/*!
  Gibt die Anzahl der Schaltflächen zurück.
*/
int QxSwipeBar::count() const
{
    return m_buttons.count();
}

/*!
  Fügt eine neue Schaltfläche mit dem Text <i>text</i> hinzu.

  \sa insertButton(int index, const QString &text)
*/
int QxSwipeBar::addButton(const QString &text)
{
    return insertButton(-1, text);
}

/*!
  Fügt eine neue Schaltfläche mit dem Text <i>text</i> an der Position <i>index</i> ein.
*/
int QxSwipeBar::insertButton(int index, const QString &text)
{
    if (index < 0 || index >= m_buttons.count())
        index = m_buttons.count();

    QxSwipeButton *button = new QxSwipeButton(this);
    button->setText(text);
    connect(button, SIGNAL(clicked()), this, SLOT(processButton()));

    m_buttons.insert(index, button);
    m_layout->insertWidget(index, button);

    return index;
}

/*!
  Entfernt die Schaltfläche an der Position <i>index</i>.
*/
void QxSwipeBar::removeButton(int index)
{
    QxSwipeButton *button = m_buttons.value(index);
    if (button) {
        m_buttons.removeAt(index);
        delete button;
    }
}

/*!
  Gibt den Text der Schaltfläche an der Position <i>index</i> zurück.

  \sa setButtonText(int index, const QString &text)
*/
QString QxSwipeBar::buttonText(int index) const
{
    QxSwipeButton *button = m_buttons.value(index);
    if (button)
        return button->text();

    return QString();
}

/*!
  Setzt den Text der Schaltfläche an der Position <i>index</i> auf den Wert <i>text</i>.

  \sa setButtonText(int index, const QString &text)
*/
void QxSwipeBar::setButtonText(int index, const QString &text)
{
    QxSwipeButton *button = m_buttons.value(index);
    if (button)
        button->setText(text);
}

/*!
  Hebt die Schaltfläche an der Position <i>index</i> hervor.
*/
void QxSwipeBar::setCurrentIndex(int index)
{
    for (int n = 0; n < count(); ++n) {
        QxSwipeButton *button = m_buttons.at(n);
        QFont font = button->font();

        font.setUnderline(n == index);
        button->setFont(font);
        if (n == index)
            ensureWidgetVisible(button);
    }
}

void QxSwipeBar::processButton()
{
    QxSwipeButton *button = qobject_cast<QxSwipeButton*>(sender());
    if (button)
        emit currentChanged(m_buttons.indexOf(button));
}

/*!
  \fn QxSwipeBar::currentChanged(int index)

  Das Signal wird ausgelöst wenn die Schaltfläche an der Position <i>index</i> aktiviert wurde.
*/
