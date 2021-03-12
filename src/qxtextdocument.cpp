/***********************************************************************************************************************
**
** Copyright (C) 2016-2021 Partsoft UG (haftungsbeschränkt)
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

#include "qxtextdocument.h"

using namespace cutex;

/*!
  Erzeugt ein neues Textdokument mit dem Elternobjekt <i>parent</i>.
*/
QxTextDocument::QxTextDocument(QObject *parent) : QTextDocument(parent)
{
}

/*!
  Gibt eine Liste aller Image-Ressourcen im Dokument zurück.
*/
QList<QUrl> QxTextDocument::images() const
{
    QList<QUrl> list;
    QTextBlock block = begin();

    while (block.isValid()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextCharFormat format = it.fragment().charFormat();
            if (format.isImageFormat())
                list.append(format.toImageFormat().name());
        }
        block = block.next();
    }

    return list;
}

/*!
  Gibt die Namen aller Sprungmarken im Dokument zurück.
*/
QStringList QxTextDocument::anchors() const
{
    QStringList list;
    QTextBlock block = begin();

    while (block.isValid()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextCharFormat format = it.fragment().charFormat();
            QStringList names = format.anchorNames();
            if (names.count())
                list.append(names.first());
        }
        block = block.next();
    }

    return list;
}

/*!
  Gibt eine Liste aller Hyperlinks im Dokument zurück.

  \sa QxHyperlink
*/
QList<QxHyperlink> QxTextDocument::hyperlinks() const
{
    QList<QxHyperlink> list;
    QString html = toHtml();
    QTextBlock block = begin();

    while (block.isValid()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextCharFormat format = it.fragment().charFormat();
            if (!format.anchorHref().isEmpty())
                list.append(QxHyperlink(format.anchorHref(), it.fragment().text()));
        }
        block = block.next();
    }

    return list;
}

/*!
  Lädt die HTML-Datei <i>fileName</i>.
*/
bool QxTextDocument::loadHtml(const QString &fileName)
{
    bool success = true;
    QFile file(fileName);
    QFileInfo fileInfo(fileName);

    success = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (success) {
#ifdef Q_WS_WIN
        setMetaInformation(QTextDocument::DocumentUrl, fileInfo.absolutePath() + "/" );
#else
        setMetaInformation(QTextDocument::DocumentUrl, "file:" + fileInfo.absolutePath() + "/");
#endif
        setHtml(file.readAll());
    }

    return success;
}

namespace cutex {

/*!
  Schreibt das Textdokument <i>document</i> in den Ausgabestream <i>out</i>.
*/
QDataStream& operator <<(QDataStream &out, const QxTextDocument &document)
{
    QList<QUrl> images = document.images();

    out << document.toHtml();
    out << images.count();
    for (int n = 0; n < images.count(); n++) {
        out << images.at(n);
        out << document.resource(QTextDocument::ImageResource, images.at(n));
    }

    return out;
}

/*!
  Liest das Textdokument <i>document</i> aus dem Eingabestream <i>in</i>.
*/
QDataStream& operator >>(QDataStream &in, QxTextDocument &document)
{
    QString htmlText = "";
    QUrl url;
    QVariant data;
    int count = 0;

    in >> htmlText;
    document.setHtml(htmlText);
    in >> count;
    for (int n = 0; n < count; n++) {
        in >> url;
        in >> data;
        document.addResource(QTextDocument::ImageResource, url, data.value<QImage>());
    }

    return in;
}

} // namespace
