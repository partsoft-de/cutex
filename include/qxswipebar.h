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

#ifndef QXSWIPEBAR_H
#define QXSWIPEBAR_H

#include "cutex.h"
#include "qxswipebutton.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSwipeBar stellt eine Navigationsleiste mit Gesten zum "wischen" zur Verfügung.

  %QxSwipeBar stellt eine Navigationsleiste mit Schaltflächen und Gesten zum "wischen" zur Verfügung.

  \sa QxSwipeWidget
*/
class QxSwipeBar : public QScrollArea
{
    Q_OBJECT

public:
    QxSwipeBar(QWidget *parent = nullptr);    
    int count() const;
    int addButton(const QString &text);
    int insertButton(int index, const QString &text);
    void removeButton(int index);
    QString buttonText(int index) const;
    void setButtonText(int index, const QString &text);

public slots:
    void setCurrentIndex(int index);

private:
    QHBoxLayout *m_layout;
    QList<QxSwipeButton*> m_buttons;

private slots:
    void processButton();

signals:
    void currentChanged(int index);
};

} // namespace

#endif // QXSWIPEBAR_H
