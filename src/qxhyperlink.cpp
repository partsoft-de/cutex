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

#include "qxhyperlink.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Hyperlink.
*/
QxHyperlink::QxHyperlink()
{
}

/*!
  Erzeugt einen neuen Hyperlink mit dem Sprungziel <i>url</i> und dem Text <i>text</i>.
*/
QxHyperlink::QxHyperlink(const QString &url, const QString &text)
{
    m_url = url;
    m_text = text;
}

/*!
  Gibt true zurück, wenn der Hyperlink gültig ist.
*/
bool QxHyperlink::isValid() const
{
    return (!m_text.isEmpty() && !m_url.isEmpty());
}

/*!
  Gibt den Text zum Hyperlink zurück.

  \sa setText(const QString &text)
*/
QString QxHyperlink::text() const
{
    return m_text;
}

/*!
  Setzt den Text auf den Wert <i>text</i>.

  \sa text()
*/
void QxHyperlink::setText(const QString &text)
{
    m_text = text;
}

/*!
  Gibt das Sprungziel zum Hyperlink zurück.

  \sa setUrl(const QString &url)
*/
QString QxHyperlink::url() const
{
    return m_url;
}

/*!
  Setzt das Sprungziel auf den Wert <i>url</i>.

  \sa url()
*/
void QxHyperlink::setUrl(const QString &url)
{
    m_url = url;
}

/*!
  Gibt den HTML-Code zum Hyperlink zurück.

  \sa fromHtml(const QString &html)
*/
QString QxHyperlink::toHtml() const
{
    return ("<a href=\"" + m_url + "\">" + m_text + "</a>");
}

/*!
  Setzt das Sprungziel und den Text für den Hyperlink aus dem HTML-Code <i>html</i>.

  \sa toHtml()
*/
void QxHyperlink::fromHtml(const QString &html)
{
    int index = html.indexOf("<a href", Qt::CaseInsensitive);

    if (index != -1) {
        int first = html.indexOf('\"', index);
        int last = html.indexOf('\"', first + 1);
        m_url = html.mid(first + 1, last - first - 1);

        index = html.indexOf('>', last);
        while (index != -1 && html.at(++index) == '<')
            index = html.indexOf('>', index);
        first = index;
        last = html.indexOf('<', first);
        m_text = html.mid(first, last - first);
    }
}

namespace cutex {

/*!
  Gibt true zurück, wenn Sprungziel und Text der Hyperlinks <i>link1</i> und <i>link2</i> identisch sind.
*/
bool operator ==(const QxHyperlink &link1, const QxHyperlink &link2)
{
    return (link1.m_text == link2.m_text && link1.m_url == link2.m_url);
}

} // namespace
