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

#include "qxsqlscript.h"

using namespace cutex;

/*!
  Erzeugt eine neue Instanz mit dem Elternobjekt <i>parent</i>.
*/
QxSqlScript::QxSqlScript(QObject *parent) : QObject(parent)
{
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
    m_encoding = QStringConverter::Utf8;
#else
    m_codec = "UTF-8";
#endif
    m_error = QxSqlScript::NoError;
}

/*!
  Erzeugt eine neue Instanz zur Ausführung des SQL-Skript <i>fileName</i> und dem Elternobjekt <i>parent</i>.
*/
QxSqlScript::QxSqlScript(const QString &fileName, QObject *parent) : QObject(parent)
{
    m_fileName = fileName;
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
    m_encoding = QStringConverter::Utf8;
#else
    m_codec = "UTF-8";
#endif
    m_error = QxSqlScript::NoError;
}

/*!
  Führt die SQL-Anweisungen in der Datei <i>fileName</i> aus.

  \sa exec()
*/
bool QxSqlScript::exec(const QString &fileName, QSqlDatabase database)
{
    if (!database.isValid())
        database = QSqlDatabase::database(QLatin1String(QSqlDatabase::defaultConnection), false);

    bool success = false;
    QFile file(fileName);
    QTextStream in(&file);
    QString statement;

    m_query = QSqlQuery(database);
    m_fileName = fileName;

    BREAKABLE_BLOCK {
        if (!database.isValid() || !database.isOpen()) {
            m_error = QxSqlScript::ConnectionError;
            break;
        }

        success = file.open(QIODevice::ReadOnly);
        if (!success) {
            m_error = QxSqlScript::FileOpenError;
            break;
        }

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        in.setEncoding(m_encoding);
#else
        in.setCodec(m_codec.toLatin1());
#endif
        while (!in.atEnd()) {
            statement.append(in.readLine());
            if (statement.endsWith(';')) {
                m_statement = statement;
                success = m_query.exec(statement);
                emit processed(statement);
                if (!success) {
                    m_error = QxSqlScript::StatementError;
                    break;
                }
                statement.clear();
            }
        }
    }

    if (file.isOpen())
        file.close();

    return success;
}

/*!
  Führt die SQL-Anweisungen der im Konstruktor übergebenen Datei aus.

  \sa exec(const QString &fileName)
*/
bool QxSqlScript::exec(QSqlDatabase database)
{
    return exec(m_fileName, database);
}

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
/*!
  Gibt die Zeichenkodierung zurück.

  \sa setEncoding(QStringConverter::Encoding encoding)
*/
QStringConverter::Encoding QxSqlScript::encoding() const
{
    return m_encoding;
}

/*!
  Setzt die Zeichenkodierung auf den Wert <i>encoding</i>.

  \sa encoding() const
*/
void QxSqlScript::setEncoding(QStringConverter::Encoding encoding)
{
    m_encoding = encoding;
}

#else
/*!
  Gibt die Zeichenkodierung zurück.

  \sa setCodec(const QString &codec)
*/
QString QxSqlScript::codec() const
{
    return m_codec;
}

/*!
  Setzt die Zeichenkodierung auf den Wert <i>codec</i>.

  \sa codec() const
*/
void QxSqlScript::setCodec(const QString &codec)
{
    m_codec = codec;
}
#endif

/*!
  Gibt den Dateinamen des Skripts zurück.
*/
QString QxSqlScript::fileName() const
{
    return m_fileName;
}

/*!
  Gibt die zuletzt ausgeführte SQL-Anweisung zurück.
*/
QString QxSqlScript::lastStatement() const
{
    return m_statement;
}

/*!
  Gibt den letzten Fehlerstatus zurück.
*/
QxSqlScript::Error QxSqlScript::lastError() const
{
    return m_error;
}

/*!
  Gibt das interne Query-Objekt zurück. Das Objekt ist erst nach einem Aufruf der Methode exec() gültig.
*/
QSqlQuery QxSqlScript::query() const
{
    return m_query;
}

/*!
  \var QxSqlScript::NoError

  Es ist kein Fehler aufgetreten.
*/

/*!
  \var QxSqlScript::FileOpenError

  Die Datei konnte nicht geöffnet werden.
*/

/*!
  \var QxSqlScript::ConnectionError

  Es besteht keine Verbindung zur Datenbank.
*/

/*!
  \var QxSqlScript::StatementError

  Beim Ausführen einer SQL-Anweisung ist ein Fehler aufgetreten.
*/

/*!
  \fn QxSqlScript::processed(const QString &statement)

  Das Signal wird jeweils nach der Ausführung einer SQL-Anweisung ausgelöst.
*/
