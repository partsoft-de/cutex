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

#include "qxsqldatabase.h"
#include "qxcrypt.h"

using namespace cutex;

/*!
  Erzeugt eine neue Instanz mit dem Elternobjekt <i>parent</i>.
*/
QxSqlDatabase::QxSqlDatabase(QObject *parent) : QObject(parent)
{
    m_transactionCounter = 0;
    m_interleavedTransactions = true;
}

/*!
  Erzeugt eine Kopie des Objekts <i>other</i> mit dem Elternobjekt <i>parent</i>.
*/
QxSqlDatabase::QxSqlDatabase(const QxSqlDatabase &other, QObject *parent) : QObject(parent)
{
    m_database = other.m_database;
    m_transactionCounter = 0;
    m_interleavedTransactions = true;
}

QxSqlDatabase::~QxSqlDatabase()
{
    removeDatabase();
}

/*!
  Gibt die verfügbaren Datenbanktreiber in einem QMap-Container zurück. Die Treibernamen werden dabei als Schlüssel
  hinterlegt, die Werte enthalten die Beschreibungen der Treiber im Klartext.
*/
QMap<QString, QString> QxSqlDatabase::drivers()
{
    QStringList list = QSqlDatabase::drivers();
    QMap<QString, QString> map;

    for (QString driver : list)
        map.insert(driver, driver);

    if (map.contains("QSQLITE"))
        map.insert("QSQLITE", tr("SQLite-Datenbanktreiber"));
    if (map.contains("QMYSQL"))
        map.insert("QMYSQL", tr("MySQL-Datenbanktreiber"));
    if (map.contains("QMYSQL3"))
        map.insert("QMYSQL3", tr("MySQL-Datenbanktreiber (v3)"));
    if (map.contains("QODBC"))
        map.insert("QODBC", tr("ODBC-Datenbanktreiber"));
    if (map.contains("QODBC3"))
        map.insert("QODBC3", tr("ODBC-Datenbanktreiber (v3)"));
    if (map.contains("QPSQL"))
        map.insert("QPSQL", tr("PostgreSQL-Datenbanktreiber"));
    if (map.contains("QPSQL7"))
        map.insert("QPSQL7", tr("PostgreSQL-Datenbanktreiber (v7)"));

    return map;
}

/*!
  Prüft ob der Datenbanktreiber <i>name</i> verfügbar ist.
*/
bool QxSqlDatabase::isDriverAvailable(const QString &name)
{
    return QSqlDatabase::isDriverAvailable(name);
}

/*!
  Registriert einen neuen Datenbanktreiber mit dem Namen <i>name</i>.
*/
void QxSqlDatabase::registerSqlDriver(const QString &name, QSqlDriverCreatorBase *creator)
{
    QSqlDatabase::registerSqlDriver(name, creator);
}

/*!
  Gibt die Namen aller aktuellen Datenbankverbindungen zurück.
*/
QStringList QxSqlDatabase::connectionNames()
{
    return QSqlDatabase::connectionNames();
}

/*!
  Prüft ob eine Datenbankverbindung mit dem Namen <i>connectionName</i> existiert.
*/
bool QxSqlDatabase::contains(const QString &connectionName)
{
    return QSqlDatabase::contains(connectionName);
}

/*!
  Erzeugt eine neue Datenbankverbindung mit dem Namen <i>connectionName</i>.

  \sa addDatabase(QSqlDriver *driver, const QString &connectionName)
*/
void QxSqlDatabase::addDatabase(const QString &type, const QString &connectionName)
{
    m_database = QSqlDatabase::addDatabase(type, connectionName);
    m_transactionCounter = 0;
}

/*!
  Erzeugt eine neue Datenbankverbindung mit dem Namen <i>connectionName</i>.

  \sa addDatabase(const QString &type, const QString &connectionName)
*/
void QxSqlDatabase::addDatabase(QSqlDriver *driver, const QString &connectionName)
{
    m_database = QSqlDatabase::addDatabase(driver, connectionName);
    m_transactionCounter = 0;
}

/*!
  Entfernt die aktuelle Datenbankverbindung.
*/
void QxSqlDatabase::removeDatabase()
{
    QSqlDatabase::removeDatabase(m_database.databaseName());
    m_transactionCounter = 0;
}

/*!
  Gibt einen Zeiger auf den Datenbanktreiber zurück.
*/
QSqlDriver* QxSqlDatabase::driver() const
{
    return m_database.driver();
}

/*!
  Gibt den Namen des Datenbanktreibers zurück.
*/
QString QxSqlDatabase::driverName() const
{
    return m_database.driverName();
}

/*!
  Gibt den Namen der Datenbankverbindung zurück.
*/
QString QxSqlDatabase::connectionName() const
{
    return m_database.connectionName();
}

/*!
  Gibt den Hostnamen zurück.

  \sa setHostName(const QString &host)
*/
QString QxSqlDatabase::hostName() const
{
    return m_database.hostName();
}

/*!
  Setzt den Hostnamen auf den Wert <i>host</i>.

  \sa hostName() const
*/
void QxSqlDatabase::setHostName(const QString &host)
{
    m_database.setHostName(host);
}

/*!
  Gibt die Portnummer zurück.

  \sa setPort(int port)
*/
int QxSqlDatabase::port() const
{
    return m_database.port();
}

/*!
  Setzt die Portnummer auf den Wert <i>port</i>.

  \sa port() const
*/
void QxSqlDatabase::setPort(int port)
{
    m_database.setPort(port);
}

/*!
  Gibt den Datenbanknamen zurück.

  \sa setDatabaseName(const QString &name)
*/
QString QxSqlDatabase::databaseName() const
{
    return m_database.databaseName();
}

/*!
  Setzt den Datenbanknamen auf den Wert <i>name</i>.

  \sa databaseName() const
*/
void QxSqlDatabase::setDatabaseName(const QString &name)
{
    m_database.setDatabaseName(name);
}

/*!
  Gibt den Benutzernamen zurück.

  \sa setUserName(const QString &name)
*/
QString QxSqlDatabase::userName() const
{
    return m_database.userName();
}

/*!
  Setzt den Benutzernamen auf den Wert <i>name</i>.

  \sa userName() const
*/
void QxSqlDatabase::setUserName(const QString &name)
{
    m_database.setUserName(name);
}

/*!
  Gibt das Passwort zurück.

  \sa setPassword(const QString &password)
*/
QString QxSqlDatabase::password() const
{
    return m_database.password();
}

/*!
  Setzt das Passwort auf den Wert <i>password</i>.

  \sa password() const
*/
void QxSqlDatabase::setPassword(const QString &password)
{
    m_database.setPassword(password);
}

/*!
  Gibt die Verbindungsoptionen zurück.

  \sa setConnectOptions(const QString &options)
*/
QString QxSqlDatabase::connectOptions() const
{
    return m_database.connectOptions();
}

/*!
  Setzt die Verbindungsoptionen auf den Wert <i>options</i>.

  \sa connectOptions() const
*/
void QxSqlDatabase::setConnectOptions(const QString &options)
{
    m_database.setConnectOptions(options);
}

/*!
  Gibt das Verhalten zur Behandlung numerischer Werte zurück.

  \sa setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy)
*/
QSql::NumericalPrecisionPolicy QxSqlDatabase::numericalPrecisionPolicy() const
{
    return m_database.numericalPrecisionPolicy();
}

/*!
  Setzt das Verhalten zur Behandlung numerischer Werte auf den Wert <i>precisionPolicy</i>.

  \sa numericalPrecisionPolicy() const
*/
void QxSqlDatabase::setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy)
{
    m_database.setNumericalPrecisionPolicy(precisionPolicy);
}

/*!
  Stellt die Verbindung zur Datenbank her.

  \sa open(const QString &user, const QString &password)
*/
bool QxSqlDatabase::open()
{
    bool success = false;

    m_transactionCounter = 0;
    success = m_database.open();
    if (success)
        emit opened();

    return success;
}

/*!
  Stellt die Verbindung zur Datenbank mit dem Benutzernamen <i>user</i> und dem Passwort <i>password</i> her.

  \sa open()
*/
bool QxSqlDatabase::open(const QString &user, const QString &password)
{
    bool success = false;

    m_transactionCounter = 0;
    success = m_database.open(user, password);
    if (success)
        emit opened();

    return success;
}

/*!
  Schließt die Verbindung zur Datenbank.
*/
void QxSqlDatabase::close()
{
    m_transactionCounter = 0;
    m_database.close();

    emit closed();
}

/*!
  Prüft ob die Datenbankverbindung gültig ist.
*/
bool QxSqlDatabase::isValid() const
{
    return m_database.isValid();
}

/*!
  Prüft ob eine Verbindung zur Datenbank besteht.
*/
bool QxSqlDatabase::isOpen() const
{
    return m_database.isOpen();
}

/*!
  Prüft ob bei der Verbindung zur Datenbank ein Fehler aufgetreten ist.
*/
bool QxSqlDatabase::isOpenError() const
{
    return m_database.isOpenError();
}

/*!
  Gibt eine Liste aller Tabellen vom Typ <i>type</i> in der Datenbank zurück.
*/
QStringList QxSqlDatabase::tables(QSql::TableType type) const
{
    return m_database.tables(type);
}

/*!
  Gibt den Primärschlüssel der Tabelle <i>tablename</i> zurück.
*/
QSqlIndex QxSqlDatabase::primaryIndex(const QString &tablename) const
{
    return m_database.primaryIndex(tablename);
}

/*!
  Erstellt einen leeren Datensatz für die Tabelle <i>tablename</i>.
*/
QSqlRecord QxSqlDatabase::record(const QString &tablename) const
{
    return m_database.record(tablename);
}

/*!
  Gibt den zuletzt aufgetretenen Fehler zurück.
*/
QSqlError QxSqlDatabase::lastError() const
{
    return m_database.lastError();
}

/*!
  Führt die Anweisung <i>query</i> aus.
*/
QSqlQuery QxSqlDatabase::exec(const QString &query) const
{
    return m_database.exec(query);
}

/*!
  Prüft ob verschachtelte Transaktionen erlaubt sind.

  \sa setInterleavedTransactions(bool enabled)
*/
bool QxSqlDatabase::interleavedTransactions() const
{
    return m_interleavedTransactions;
}

/*!
  Aktiviert, bzw. deaktiviert verschachtelte Transaktionen. Wenn verschachtelte Transaktionen deaktiviert wurden,
  werden nach dem Start einer Transaktion alle weiteren Aufrufe von transaction() ignoriert, bis die Transaktion
  abgeschlossen wurde.

  \sa interleavedTransactions() const
*/
void QxSqlDatabase::setInterleavedTransactions(bool enabled)
{
    m_interleavedTransactions = enabled;
}

/*!
  Startet eine Transaktion. Alle Änderungen innerhalb einer Transaktion werden erst beim Aufruf von commit() in die
  Datenbank geschrieben.

  \sa commit()
  \sa rollback()
  \sa setInterleavedTransactions(bool enabled)
*/
bool QxSqlDatabase::transaction()
{
    bool success = false;

    if (driver()->hasFeature(QSqlDriver::Transactions)) {
        if (m_interleavedTransactions) {
            success = m_database.transaction();
        } else {
            m_transactionCounter++;
            if (m_transactionCounter == 1)
                success = m_database.transaction();
        }
    }

    return success;
}

/*!
  Beendet die Transaktion und schreibt alle Änderungen, die seit dem Aufruf von transaction() durchgeführt wurden, in
  die Datenbank.

  \sa transaction()
  \sa rollback()
  \sa setInterleavedTransactions(bool enabled)
*/
bool QxSqlDatabase::commit()
{
    bool success = false;

    if (driver()->hasFeature(QSqlDriver::Transactions)) {
        if (m_interleavedTransactions) {
            success = m_database.commit();
        } else {
            m_transactionCounter--;
            Q_ASSERT(m_transactionCounter >= 0);
            if (m_transactionCounter == 0)
                success = m_database.commit();
        }
    }

    return success;
}

/*!
  Beendet die Transaktion und verwirft alle Änderungen, die seit dem Aufruf von transaction() durchgeführt wurden.

  \sa transaction()
  \sa commit()
  \sa setInterleavedTransactions(bool enabled)
*/
bool QxSqlDatabase::rollback()
{
    bool success = false;

    if (driver()->hasFeature(QSqlDriver::Transactions)) {
        if (m_interleavedTransactions) {
            success = m_database.rollback();
        } else {
            m_transactionCounter--;
            Q_ASSERT(m_transactionCounter >= 0);
            if (m_transactionCounter == 0)
                success = m_database.rollback();
        }
    }

    return success;
}

/*!
  Prüft ob Transaktionen aktiv sind.
*/
bool QxSqlDatabase::hasTransactions() const
{
    return (m_transactionCounter > 0);
}

/*!
  Prüft ob der Datensatz bereits existiert.
*/
bool QxSqlDatabase::recordExist(const QString &table, const QString &field, const QVariant &value)
{
    bool result = false;

    if (isOpen()) {
        QSqlQuery query;
        query.prepare(QString("SELECT COUNT (%1) AS count FROM %2 WHERE %1 = :value").arg(field).arg(table));
        query.bindValue(":value", value);
        if (query.exec() && query.first())
            result = (query.value("count").toInt() > 0);
    }

    return result;
}

/*!
  Stellt die gespeicherten Verbindungsinformationen wieder her.

  \sa saveSettings(QSettings &settings, const QString &group)
*/
bool QxSqlDatabase::loadSettings(QSettings &settings, const QString &group)
{
    QString driverName;

    settings.beginGroup(group);
    driverName = settings.value("driverName", QString()).toString();
    if (!driverName.isEmpty()) {
        m_database = QSqlDatabase::addDatabase(driverName);
        setHostName(settings.value("hostName", QString()).toString());
        setPort(settings.value("port", 0).toInt());
        setDatabaseName(settings.value("databaseName", QString()).toString());
        setUserName(settings.value("userName", QString()).toString());
        setPassword(QxCrypt::decrypt(settings.value("password").toString()));
    }
    settings.endGroup();

    return (!driverName.isEmpty());
}

/*!
  Speichert die Verbindungsinformationen.

  \sa saveSettings(QSettings &settings, const QString &group)
*/
void QxSqlDatabase::saveSettings(QSettings &settings, bool savePassword, const QString &group)
{
    settings.beginGroup(group);
    settings.setValue("driverName", driverName());
    settings.setValue("hostName", hostName());
    settings.setValue("port", port());
    settings.setValue("databaseName", databaseName());
    settings.setValue("userName", userName());
    if (savePassword)
        settings.setValue("password", QxCrypt::encrypt(m_database.password()));
    settings.endGroup();
}
