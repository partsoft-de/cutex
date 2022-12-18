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

#include "qxxmlnode.h"

using namespace cutex;

/*!
  Erzeugt einen neuen XML-Knoten mit dem Namen <i>name</i> und dem (optionalen) Wert <i>value</i>.
*/
QxXmlNode::QxXmlNode(const QString &name, const QString &value)
{
    m_name = name;
    m_value = value;
}

/*!
  Erzeugt eine Kopie des XML-Knotens <i>other</i>.
*/
QxXmlNode::QxXmlNode(const QxXmlNode &other)
{
    m_name = other.m_name;
    m_prefix = other.m_prefix;
    m_value = other.m_value;
    m_attributes = other.m_attributes;

    for (const QxXmlNode *child : other.children())
        insertChild(new QxXmlNode(*child));
}

/*!
  Der Destruktor löscht alle untergeordneten Elemente.
*/
QxXmlNode::~QxXmlNode()
{
    qDeleteAll(m_children);
}

/*!
  Weißt dem XML-Knoten die Inhalte des XML-Knotens <i>other</i> zu.
*/
QxXmlNode& QxXmlNode::operator=(const QxXmlNode &other)
{
    if (this != &other) {
        qDeleteAll(m_children);

        m_name = other.m_name;
        m_prefix = other.m_prefix;
        m_value = other.m_value;
        m_attributes = other.m_attributes;

        for (const QxXmlNode *child : other.children())
            insertChild(new QxXmlNode(*child));
    }

    return *this;
}

/*!
  Gibt den Namen des XML-Knoten zurück.

  \sa setName(const QString &name)
*/
QString QxXmlNode::name() const
{
    return m_name;
}

/*!
  Setzt den Namen des XML-Knoten auf den Wert <i>name</i>.

  \sa name()
*/
void QxXmlNode::setName(const QString &name)
{
    m_name = name;
}

/*!
  Gibt das Präfix des KML-Knoten zurück.

  \sa setPrefix(const QString &prefix)
*/
QString QxXmlNode::prefix() const
{
    return m_prefix;
}

/*!
  Setzt das Präfix des KML-Knoten auf den Wert <i>prefix</i>.

  \sa prefix()
*/
void QxXmlNode::setPrefix(const QString &prefix)
{
    m_prefix = prefix;
}

/*!
  Gibt den Wert des XML-Knoten zurück.

  \sa setValue(const QString &value)
*/
QString QxXmlNode::value() const
{
    return m_value;
}

/*!
  Setzt den Wert des XML-Knoten auf den Wert <i>value</i>.

  \sa value()
*/
void QxXmlNode::setValue(const QString &value)
{
    m_value = value;
}

/*!
  Gibt eine Liste mit allen Attributen des XML-Knoten zurück.
*/
QMap<QString, QString> QxXmlNode::attributes() const
{
    return m_attributes;
}

/*!
  Gibt den Wert des Attributs mit dem Namen <i>name</i> zurück.

  \sa setAttribute(const QString &name, const QString &value)
*/
QString QxXmlNode::attribute(const QString &name) const
{
    return m_attributes.value(name);
}

/*!
  Setzt den Wert des Attributs mit dem Namen <i>name</i> auf den Wert <i>value</i>.

  \sa attribute(const QString &name)
*/
void QxXmlNode::setAttribute(const QString &name, const QString &value)
{
    if (value.isEmpty()) {
        m_attributes.remove(name);
    } else {
        m_attributes.insert(name, value);
    }
}

/*!
  Fügt einen neuen Kindknoten mit dem Namen <i>name</i> und dem (optionalen) Wert <i>value</i> hinzu.
*/
QxXmlNode* QxXmlNode::insertChild(const QString &name, const QString &value)
{
    QxXmlNode *child = new QxXmlNode(name, value);
    m_children.append(child);

    return child;
}

/*!
  Fügt einen neuen Kindknoten hinzu.
*/
QxXmlNode* QxXmlNode::insertChild(const QxXmlNode &node)
{
    QxXmlNode *child = new QxXmlNode(node.m_name, node.m_value);
    m_children.append(child);

    return child;
}

/*!
  Fügt einen neuen Kindknoten hinzu.
*/
void QxXmlNode::insertChild(QxXmlNode *node)
{
    m_children.append(node);
}

/*!
  Entfernt den angegebenen Kindknoten <i>node</i>.
*/
QxXmlNode* QxXmlNode::takeChild(QxXmlNode *node)
{
    m_children.removeOne(node);

    return node;
}

/*!
  Gibt eine Liste aller Kindknoten zurück.
*/
QList<QxXmlNode*> QxXmlNode::children() const
{
    return m_children;
}

/*!
  Gibt einen Zeiger auf den Kindknoten mit dem Namen <i>name</i> zurück.
*/
QxXmlNode* QxXmlNode::findChild(const QString &name, Qt::FindChildOptions options)
{
    for (QxXmlNode *child : m_children) {
        if (child->name() == name)
            return child;
    }

    if (options == Qt::FindChildrenRecursively) {
        for (QxXmlNode *child : m_children) {
            QxXmlNode *node = child->findChild(name, options);
            if (node)
                return node;
        }
    }

    return 0;
}

void QxXmlNode::load(QXmlStreamReader *reader)
{
    m_name = reader->name().toString();
    m_prefix = reader->prefix().toString();

    for (const QXmlStreamAttribute &attribute : reader->attributes())
        setAttribute(attribute.name().toString(), attribute.value().toString());

    reader->readNext();
    while (!reader->atEnd()) {
        if (reader->isCharacters()) {
            m_value = reader->text().toString();
        } else if (reader->isStartElement()) {
            QxXmlNode *child = insertChild(reader->name().toString());
            child->load(reader);
        } else if (reader->isEndElement()) {
            reader->readNext();
            return;
        }

        reader->readNext();
    }
}

void QxXmlNode::save(QXmlStreamWriter *writer) const
{   
    if (m_prefix.isEmpty()) {
        writer->writeStartElement(m_name);
    } else {
        writer->writeStartElement(QString("%1:%2").arg(m_prefix).arg(m_name));
    }

    for (const QString &key : m_attributes.keys())
        writer->writeAttribute(key, m_attributes.value(key));

    if (!m_value.isEmpty())
        writer->writeCharacters(m_value);

    for (QxXmlNode *child : m_children)
        child->save(writer);

    writer->writeEndElement();
}
