/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXLINENUMBERAREA_H
#define QXLINENUMBERAREA_H

#include "cutex.h"
#include "qxplaintextedit.h"

namespace cutex {

class QxLineNumberArea : public QWidget
{
public:
    QxLineNumberArea(QxPlainTextEdit *editor);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QxPlainTextEdit *m_editor;
};

} // namespace

#endif // QXLINENUMBERAREA_H
