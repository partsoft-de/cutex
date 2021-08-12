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

#include "qxlogger.h"

using namespace cutex;

/*!
  Erzeugt ein neues Logging-Objekt mit dem Elternobjekt <i>parent</i>.
*/
QxLogger::QxLogger(QObject *parent) : QObject(parent)
{
    m_dateFormat = "yyyy-MM-dd HH:mm:ss";
    m_maxLines = 10000;
}

/*!
  Schließt die Logdatei und zerstört das Objekt.
*/
QxLogger::~QxLogger()
{
    if (m_file.isOpen()) {
        cleanUp();
        m_file.close();
    }
}

/*!
  Gibt den Pfad zur Logdatei zurück.

  \sa setFileName(const QString &fileName)
*/
QString QxLogger::fileName() const
{
    return m_file.fileName();
}

/*!
  Setzt den Pfad der Logdatei auf <i>fileName</i> und öffnet die Datei.

  \sa fileName()
*/
bool QxLogger::setFileName(const QString &fileName)
{
    bool success = false;

    if (m_file.isOpen())
        m_file.close();

    if (QFileInfo(fileName).isAbsolute()) {
        m_file.setFileName(fileName);
    } else {
        m_file.setFileName(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + '/' + fileName);
    }

    success = m_file.open(QIODevice::ReadWrite);
    if (success)
        cleanUp();

    return success;
}

/*!
  Gibt die maximale Anzahl an Zeilen zurück.

  \sa setMaxLines(int count)
*/
int QxLogger::maxLines() const
{
    return m_maxLines;
}

/*!
  Setzt die maximale Anzahl an Zeilen auf den Wert <i>count</i>.

  \sa maxLines()
*/
void QxLogger::setMaxLines(int count)
{
    if (m_maxLines != count) {
        m_maxLines = count;
        cleanUp();
    }
}

/*!
  Schreibt einen Eintrag mit dem Loglevel <i>level</i> und dem Text <i>text</i> in die Logdatei.
*/
bool QxLogger::log(LogLevel level, const QString &text)
{
    bool success = false;

    if (m_file.isOpen()) {
        QString line = QString("%1 [%2] %3").arg(QDateTime::currentDateTime().toString(m_dateFormat),
            QMetaEnum::fromType<LogLevel>().valueToKey(level), text);

        success = m_file.write(QString("%1\n").arg(line).toLatin1());
        m_file.flush();
        qDebug() << line;
    }

    return success;
}

/*!
  Löscht ältere Einträge aus der Logdatei.

  \sa setMaxLines(int count)
*/
bool QxLogger::cleanUp()
{
    bool success = false;

    if (m_file.isOpen() && m_maxLines >= 0) {
        QTextStream in(&m_file);
        QVector<QString> buffer;
        QString line;

        m_file.seek(0);
        while (in.readLineInto(&line))
            buffer.append(line);

        if (buffer.count() > m_maxLines) {
            while (buffer.count() > m_maxLines)
                buffer.removeFirst();

            m_file.resize(0);
            for (int n = 0; n < buffer.count(); ++n) {
                success = m_file.write(buffer[n].toLatin1() + '\n');
                if (!success)
                    break;
            }

            m_file.flush();
        }
    }

    return success;
}
