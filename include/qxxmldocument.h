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

#ifndef QXXMLDOCUMENT_H
#define QXXMLDOCUMENT_H

#include "cutex.h"
#include "qxxmlnode.h"

namespace cutex {

/*!
  \brief Die Klasse %QxXmlDocument verwaltet eine XML-Datei im Hauptspeicher.

  Die Klasse %QxXmlDocument vereinfacht den Umgang mit XML-Dateien unter Qt. Ein Objekt dieser Klasse repräsentiert
  eine XML-Datei und enthält einen Root-Knoten vom Typ QxXmlNode. %QxXmlDocument wurde als einfache Alternative zu
  QDomDocument implementiert und nutzt zum speichern, bzw. laden die Qt-Klassen QXmlStreamWriter und QXmlStreamReader.

  \sa QxXmlNode
*/
class QxXmlDocument
{
public:
    QxXmlDocument(const QString &rootName = "root");
    QxXmlDocument(const QxXmlNode &root);
    QxXmlDocument(const QxXmlDocument &other);
    ~QxXmlDocument();
    QxXmlDocument& operator=(const QxXmlDocument &other);
    void clear();
    QxXmlNode* root() const;
    QMap<QString, QString> namespaces() const;
    QString namepace(const QString &prefix = QString()) const;
    void setNamespace(const QString &uri, const QString &prefix = QString());
    QString content() const;
    bool setContent(const QString &content);
    bool load(const QString &path);
    bool save(const QString &path) const;

private:
    QxXmlNode *m_root;
    QMap<QString, QString> m_namespaces;
};

} // namespace

#endif // QXXMLDOCUMENT_H
