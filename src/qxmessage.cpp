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

#include "qxmessage.h"
#include "qxmainwindow.h"
#include "qxmessagedialog.h"

using namespace cutex;

/*!
  Erzeugt ein neues Message-Objekt.
*/
QxMessage::QxMessage(const QString &titel)
{
    m_title = titel;
}

/*!
  Fügt die Meldung <i>text</i> hinzu.

  \sa prepend(const QString &text)
*/
void QxMessage::append(const QString &text)
{
    m_messages.append(text);
}

/*!
  Fügt die Meldung <i>text</i> am Anfang der Kette ein.

  \sa append(const QString &text)
*/
void QxMessage::prepend(const QString &text)
{
    m_messages.prepend(text);
}

/*!
  Fügt dem Message-Objekt <i>message</i> die Meldung <i>text</i> hinzu.

  \sa prepend(QxMessage *message, const QString &text)
*/
void QxMessage::append(QxMessage *message, const QString &text)
{
    if (message)
        message->append(text);
}

/*!
  Fügt am Anfang der Kette des Message-Objekt <i>message</i> die Meldung <i>text</i> ein.

  \sa append(QxMessage *message, const QString &text)
*/
void QxMessage::prepend(QxMessage *message, const QString &text)
{
    if (message)
        message->prepend(text);
}

/*!
  Zeigt die Meldungen an. Eine einzelne Meldung wird in einer QMessageBox angezeigt, mehrere Meldungen werden in einem
  Dialog vom Typ QxMessageDialog angezeigt.

  \sa QxMessageDialog
*/
void QxMessage::show(QWidget *parent)
{
    if (!parent)
        parent = qxMainWin;

    switch (m_messages.size()) {
    case 0:
        break;
    case 1:
        QMessageBox::information(parent, m_title, m_messages.at(0));
        break;
    default:
        QxMessageDialog dialog(m_title, m_messages, parent);
        dialog.exec();
    }
}
