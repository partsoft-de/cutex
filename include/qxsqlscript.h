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

#ifndef SQLSCRIPT_H
#define SQLSCRIPT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Mit Hilfe der Klasse %QxSqlScript kann eine Datei mit SQL-Anweisungen ausgeführt werden.

  Die Klasse %QxSqlScript stellt Methoden zum Ausführen einer Datei mit SQL-Anweisungen bereit.
*/
class QxSqlScript : public QObject
{
    Q_OBJECT

public:
    enum Error {
        NoError = 0, FileOpenError, ConnectionError, StatementError
    };

public:
    QxSqlScript(QObject *parent = 0);
    QxSqlScript(const QString &fileName, QObject *parent = 0);
    bool exec(const QString &fileName, QSqlDatabase database = QSqlDatabase());
    bool exec(QSqlDatabase database = QSqlDatabase());
    QString codec() const;
    void setCodec(const QString &codec);
    QString fileName() const;
    QString lastStatement() const;
    QxSqlScript::Error lastError() const;
    QSqlQuery query() const;

private:
    QString m_fileName;
    QString m_codec;
    QString m_statement;
    QxSqlScript::Error m_error;
    QSqlQuery m_query;

signals:
    void processed(const QString &statement);
};

} // namespace

#endif // SQLSCRIPT_H
