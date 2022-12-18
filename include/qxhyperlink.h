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

#ifndef QXHYPERLINK_H
#define QXHYPERLINK_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxHyperlink ist eine Wrapper-Klasse für Hyperlinks.

  %QxHyperlink stellt diverse Funktionen zur einfachen Implementierung von Hyperlinks zur Verfügung.

  \sa QxTextDocument
  \sa QxTextEdit
*/
class QxHyperlink
{
public:
    QxHyperlink();
    QxHyperlink(const QString &url, const QString &text);
    bool isValid() const;
    QString text() const;
    void setText(const QString &text);
    QString url() const;
    void setUrl(const QString &url);
    QString toHtml() const;
    void fromHtml(const QString &html);
    friend bool operator ==(const QxHyperlink &link1, const QxHyperlink &link2);

private:
    QString m_text;
    QString m_url;
};

} // namespace

#endif // QXHYPERLINK_H
