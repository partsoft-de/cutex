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

#ifndef QXXMLNODE_H
#define QXXMLNODE_H

#include "cutex.h"

namespace cutex {

class QxXmlDocument;

/*!
  \brief Die Klasse %QxXmlNode repräsentiert einen XML-Knoten.

  Ein Objekt der Klasse %QxXmlNode repräsentiert einen Knoten in einer XML-Datei.

  \sa QxXmlDocument
*/
class QxXmlNode
{
    friend class QxXmlDocument;

public:
    QxXmlNode(const QString &name = "node", const QString &value = QString());
    QxXmlNode(const QxXmlNode &other);
    ~QxXmlNode();
    QxXmlNode& operator=(const QxXmlNode &other);
    QString name() const;
    void setName(const QString &name);
    QString prefix() const;
    void setPrefix(const QString &prefix);
    QString value() const;
    void setValue(const QString &value);
    QMap<QString, QString> attributes() const;
    QString attribute(const QString &name) const;
    void setAttribute(const QString &name, const QString &value);
    QxXmlNode* insertChild(const QString &name = "node", const QString &value = QString());
    QxXmlNode* insertChild(const QxXmlNode &node);
    void insertChild(QxXmlNode *node);
    QxXmlNode* takeChild(QxXmlNode *node);
    QList<QxXmlNode*> children() const;
    QxXmlNode* findChild(const QString &name, Qt::FindChildOptions options = Qt::FindChildrenRecursively);

private:
    QString m_name;
    QString m_prefix;
    QString m_value;
    QMap<QString, QString> m_attributes;
    QList<QxXmlNode*> m_children;

private:
    void load(QXmlStreamReader *reader);
    void save(QXmlStreamWriter *writer) const;
};

} // namespace

#endif // QXXMLNODE_H
