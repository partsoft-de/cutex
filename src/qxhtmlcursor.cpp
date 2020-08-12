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

#include "qxhtmlcursor.h"

using namespace cutex;

/*!
  Erzeugt einen HTML-Cursor.
*/
QxHtmlCursor::QxHtmlCursor()
{
}

/*!
  Erzeugt einen HTML-Cursor aus dem QTextCursor <i>textCursor</i>.
*/
QxHtmlCursor::QxHtmlCursor(const QTextCursor &textCursor)
{
    m_textCursor = textCursor;
}

/*!
  Gibt true zurück, wenn der Cursor gültig ist.
*/
bool QxHtmlCursor::isNull() const
{
    return m_textCursor.isNull();
}

/*!
  Gibt die Cursorposition im HTML-Code zurück.
*/
int QxHtmlCursor::position() const
{
    int index = -1;

    QString html = m_textCursor.document()->toHtml();
    index = html.indexOf("<body", 0, Qt::CaseInsensitive);
    index = html.indexOf('>', index + 1);

    int textPosition = m_textCursor.position();
    int htmlPosition = 0;
    bool tag = false;
    bool special = false;

    while (htmlPosition <= textPosition && index < html.size()) {
        switch (html.at(index).toLatin1()) {
        case '<':
            tag = true;
            break;
        case '>':
            tag = false;
            break;
        case '&':
            special = true;
            break;
        case ';':
            if (!tag) {
                if (special) {
                    special = false;
                } else {
                    htmlPosition++;
                }
            }
            break;
        default:
            if (!tag && !special) {
                if (htmlPosition > 0 || html.at(index).toLatin1() != '\n')
                    htmlPosition++;
            }
        }

        if (htmlPosition <= textPosition)
            index++;
    }

    return index;
}

/*!
  Gibt den Text zurück, auf dem der HTML-Cursor positioniert ist.
*/
QString QxHtmlCursor::text() const
{
    QString html = m_textCursor.document()->toHtml();
    int first = html.lastIndexOf('>', position()) + 1;
    int last = html.indexOf('<', first);
    QString text = html.mid(first, last - first);

    return text;
}
