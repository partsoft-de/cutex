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

#ifndef QXTEXTDOCUMENT_H
#define QXTEXTDOCUMENT_H

#include "cutex.h"
#include "qxhyperlink.h"

namespace cutex {

/*!
  \brief Die Klasse %QxTextDocument erweitert die Qt-Klasse QTextDocument.

  %QxTextDocument stellt Methoden zum Laden und Speichern von Textdokumenten zur Verfügung, wobei auch eingebettete
  Elemente (z.B. Bilder) berücksichtigt werden.
*/
class QxTextDocument : public QTextDocument
{
    Q_OBJECT

public:
    QxTextDocument(QObject *parent = nullptr);
    QList<QUrl> images() const;
    QStringList anchors() const;
    QList<QxHyperlink> hyperlinks() const;
    bool loadHtml(const QString &fileName);
    friend QDataStream& operator <<(QDataStream &out, const QxTextDocument &document);
    friend QDataStream& operator >>(QDataStream &in, QxTextDocument &document);    
};

} // namespace

#endif // QXTEXTDOCUMENT_H
