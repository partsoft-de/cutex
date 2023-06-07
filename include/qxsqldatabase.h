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

#ifndef QXSQLDATABASE_H
#define QXSQLDATABASE_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSqlDatabase ersetzt die Qt-Klasse QSqlDatabase.

  Die meisten Methoden der Klasse %QxSqlDatabase sind reine Delegates, welche die entsprechenden Methoden der Qt-Klasse
  QSqlDatabase aufrufen. Bei einigen Methoden wurde das Verhalten jedoch geändert oder erweitert. Daneben stellt die
  Klasse einige zusätzliche Methoden bereit, z.B. zum Laden und Speichern der Verbindungsinformationen.
*/
class QxSqlDatabase : public QObject
{
    Q_OBJECT

public:
    QxSqlDatabase(QObject *parent = nullptr);
    QxSqlDatabase(const QxSqlDatabase &other, QObject *parent = nullptr);
    virtual ~QxSqlDatabase();    
    static QMap<QString, QString> drivers();
    static bool isDriverAvailable(const QString &name);
    static void registerSqlDriver(const QString &name, QSqlDriverCreatorBase *creator);
    static QStringList connectionNames();
    static bool contains(const QString &connectionName = QLatin1String(QSqlDatabase::defaultConnection));
    void addDatabase(const QString &type,
        const QString &connectionName = QLatin1String(QSqlDatabase::defaultConnection));    
    void addDatabase(QSqlDriver *driver,
        const QString &connectionName = QLatin1String(QSqlDatabase::defaultConnection));
    void removeDatabase();
    QSqlDriver* driver() const;
    QString driverName() const;    
    QString connectionName() const;
    QString hostName() const;
    void setHostName(const QString &host);
    int port() const;
    void setPort(int port);
    QString databaseName() const;
    void setDatabaseName(const QString &name);
    QString userName() const;
    void setUserName(const QString &name);
    QString password() const;
    void setPassword(const QString &password);
    QString connectOptions() const;
    void setConnectOptions(const QString &options = QString());
    QSql::NumericalPrecisionPolicy numericalPrecisionPolicy() const;
    void setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy);
    virtual bool open();
    virtual bool open(const QString &user, const QString &password);
    void close();
    bool isValid() const;
    bool isOpen() const;
    bool isOpenError() const;    
    QSqlError lastError() const;        
    QStringList tables(QSql::TableType type = QSql::Tables) const;
    QSqlIndex primaryIndex(const QString &tablename) const;
    QSqlRecord record(const QString &tablename) const;
    QSqlQuery exec(const QString &query = QString()) const;
    bool interleavedTransactions() const;
    void setInterleavedTransactions(bool enabled);
    bool transaction();
    bool commit();
    bool hasTransactions() const;
    bool rollback();
    bool recordExist(const QString &table, const QString &field, const QVariant &value);
    bool loadSettings(QSettings &settings, const QString &group = QString("Database"));
    void saveSettings(QSettings &settings, bool savePassword = false, const QString &group = QString("Database"));

private:
    QSqlDatabase m_database;
    int m_transactionCounter;
    bool m_interleavedTransactions;

signals:
    void opened();
    void closed();
};

} // namespace

#endif // QXSQLDATABASE_H
