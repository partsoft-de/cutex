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

#include "qxxmldocument.h"

using namespace cutex;

/*!
  Erzeugt ein neues XML-Dokument mit dem Root-Knoten <i>rootName</i>.
*/
QxXmlDocument::QxXmlDocument(const QString &rootName)
{
    m_root = new QxXmlNode(rootName);
}

/*!
  Erzeugt ein neues XML-Dokument mit dem Root-Knoten <i>root</i>.
*/
QxXmlDocument::QxXmlDocument(const QxXmlNode &root)
{
    m_root = new QxXmlNode(root.m_name, root.m_value);
}

/*!
  Erzeugt eine Kopie des XML-Dokuments <i>other</i>.
*/
QxXmlDocument::QxXmlDocument(const QxXmlDocument &other)
{
    m_root = new QxXmlNode(*other.root());
    m_namespaces = other.m_namespaces;
}

/*!
  Der Destruktor löscht den Root-Knoten und alle untergeordneten Elemente.
*/
QxXmlDocument::~QxXmlDocument()
{
    delete m_root;
}

/*!
  Weißt dem XML-Dokument die Inhalte des XML-Dokuments <i>other</i> zu.
*/
QxXmlDocument& QxXmlDocument::operator=(const QxXmlDocument &other)
{
    if (this != &other) {
        delete m_root;

        m_root = new QxXmlNode(*other.root());
        m_namespaces = other.m_namespaces;
    }

    return *this;
}

/*!
  Setzt das XML-Dokument zurück und löscht alle Daten.
*/
void QxXmlDocument::clear()
{
    delete m_root;

    m_root = new QxXmlNode("root");
    m_namespaces.clear();
}

/*!
  Gibt einen Zeiger auf den Root-Knoten des XML-Dokuments zurück.
*/
QxXmlNode* QxXmlDocument::root() const
{
    return m_root;
}

/*!
  Gibt eine Liste aller Namesräume zurück.
*/
QMap<QString, QString> QxXmlDocument::namespaces() const
{
    return m_namespaces;
}

/*!
  Gibt den URI des Namensraums mit dem Präfix <i>prefix</i> zurück.

  \sa setNamespaceUri(const QString &uri, const QString &prefix)
*/
QString QxXmlDocument::namepace(const QString &prefix) const
{
    return m_namespaces.value(prefix);
}

/*!
  Setzt den URI des Namensraums mit dem Präfix <i>prefix</i> auf den Wert <i>uri</i>.

  \sa namepace(const QString &prefix)
*/
void QxXmlDocument::setNamespace(const QString &uri, const QString &prefix)
{
    m_namespaces.insert(prefix, uri);
}

/*!
  Gibt den Inhalt des XML-Dokuments als String zurück.

  \sa setContent(const QString &content)
*/
QString QxXmlDocument::content() const
{
    QString buffer;
    QXmlStreamWriter writer(&buffer);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    for (const QString &prefix : m_namespaces.keys())
        writer.writeNamespace(m_namespaces.value(prefix), prefix);

    m_root->save(&writer);

    writer.writeEndDocument();

    return buffer;
}

/*!
  Setzt den Inhalt des XML-Dokuments auf den Wert <i>content</i>

  \sa content()
*/
bool QxXmlDocument::setContent(const QString &content)
{
    QXmlStreamReader reader(content);
    bool success = reader.readNextStartElement();

    if (success) {
        clear();

        for (const QXmlStreamNamespaceDeclaration &declaration : reader.namespaceDeclarations()) {
            QString uri = declaration.namespaceUri().toString();
            QString prefix = declaration.prefix().toString();
            m_namespaces.insert(prefix, uri);
        }

        m_root->load(&reader);
    }

    return success;
}

/*!
  Lädt die XML-Datei mit dem Namen <i>path</i>.

  \sa save(const QString &path)
*/
bool QxXmlDocument::load(const QString &path)
{
    QFile file(path);
    bool success = file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (success) {
        QXmlStreamReader reader(&file);
        success = reader.readNextStartElement();

        if (success) {
            clear();

            for (const QXmlStreamNamespaceDeclaration &declaration : reader.namespaceDeclarations()) {
                QString uri = declaration.namespaceUri().toString();
                QString prefix = declaration.prefix().toString();
                m_namespaces.insert(prefix, uri);
            }

            m_root->load(&reader);
        }
    }

    return success;
}

/*!
  Speichert das XML-Dokument unter dem Namen <i>path</i>.

  \sa load(const QString &path)
*/
bool QxXmlDocument::save(const QString &path) const
{
    QFile file(path);
    bool success = file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (success) {
        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();

        for (const QString &prefix : m_namespaces.keys())
            writer.writeNamespace(m_namespaces.value(prefix), prefix);

        m_root->save(&writer);

        writer.writeEndDocument();
    }

    return success;
}
