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

#include "qxsqlquerymodel.h"
#include "qxwaitcursor.h"

using namespace cutex;

/*!
  Erzeugt eine neue Instanz mit dem Elternobjekt <i>parent</i>.
*/
QxSqlQueryModel::QxSqlQueryModel(QObject *parent) : QAbstractTableModel(parent)
{
}

QxSqlQueryModel::~QxSqlQueryModel()
{
    while (!m_data.isEmpty())
        delete m_data.takeFirst();
}

/*!
  Gibt die Anzahl der Datensätze zurück.
*/
int QxSqlQueryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_data.count();
}

/*!
  Gibt die Anzahl der Spalten zurück.
*/
int QxSqlQueryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_columns.count();
}

/*!
  Gibt die Kopfdaten zur Spalte <i>section</i> und der Rolle <i>role</i> zurück.
*/
QVariant QxSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section >= 0 && section < columnCount())
            return m_columns.at(section)->caption;
    }

    if (role == Qt::TextAlignmentRole && orientation == Qt::Horizontal) {
        if (section >= 0 && section < columnCount())
            return QVariant(m_columns.at(section)->alignment);
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

/*!
  Setzt die Kopfdaten zur Spalte <i>section</i> und der Rolle <i>role</i> auf den Wert <i>value</i>.
*/
bool QxSqlQueryModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role == Qt::EditRole && orientation == Qt::Horizontal) {
        if (section >= 0 && section < columnCount()) {
            m_columns.at(section)->caption = value.toString();
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }

    if (role == Qt::TextAlignmentRole && orientation == Qt::Horizontal) {
        if (section >= 0 && section < columnCount()) {
            m_columns.at(section)->alignment = static_cast<Qt::Alignment>(value.toInt());
            emit headerDataChanged(orientation, section, section);
            return true;
        }
    }

    return QAbstractItemModel::setHeaderData(section, orientation, value, role);
}

/*!
  Gibt die Daten zur Zelle <i>index</i> und der Rolle <i>role</i> zurück.
*/
QVariant QxSqlQueryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        ColumnInfo *column = m_columns.at(index.column());
        QxSqlRecord *record = m_data.at(index.row());
        QVariant value;

        if (record->hasRelationValue(index.column())) {
            value = record->relationValue(index.column());
        } else {
            value = record->value(index.column());
        }

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        QMetaType::Type type = static_cast<QMetaType::Type>(value.metaType().id());

        switch (column->type) {
        case QMetaType::QDate:
            if (type == QMetaType::QDate) {
                if (column->format.isEmpty()) {
                    return value.toDate().toString(Qt::TextDate);
                } else {
                    return value.toDate().toString(column->format);
                }
            }

            if (type == QMetaType::Int || type == QMetaType::LongLong) {
                if (column->format.isEmpty()) {
                    return QDate::fromJulianDay(value.toLongLong()).toString(Qt::TextDate);
                } else {
                    return QDate::fromJulianDay(value.toLongLong()).toString(column->format);
                }
            }
            break;
        case QMetaType::Bool:
            return QVariant();
        default:
            return value;
        }
#else
        QVariant::Type type = value.type();

        switch (column->type) {
        case QVariant::Date:
            if (type == QVariant::Date) {
                if (column->format.isEmpty()) {
                    return value.toDate().toString(Qt::TextDate);
                } else {
                    return value.toDate().toString(column->format);
                }
            }

            if (type == QVariant::Int || type == QVariant::LongLong) {
                if (column->format.isEmpty()) {
                    return QDate::fromJulianDay(value.toLongLong()).toString(Qt::TextDate);
                } else {
                    return QDate::fromJulianDay(value.toLongLong()).toString(column->format);
                }
            }
            break;
        case QVariant::Bool:
            return QVariant();
        default:
            return value;
        }
#endif
    }

    if (role == Qt::EditRole)
        return m_data.at(index.row())->value(index.column());

    if (role == Qt::TextAlignmentRole)
        return (headerData(index.column(), Qt::Horizontal, Qt::TextAlignmentRole).toInt() | Qt::AlignVCenter);

    if (role == Qt::CheckStateRole) {
        ColumnInfo *column = m_columns.at(index.column());
        QVariant value = m_data.at(index.row())->value(index.column());

        switch (column->type) {
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        case QMetaType::Bool:
#else
        case QVariant::Bool:
#endif
            if (value.toBool()) {
                return Qt::Checked;
            } else {
                return Qt::Unchecked;
            }
        default:
            return QVariant();
        }
    }

    return QVariant();
}

/*!
  Setzt die Daten zur Zelle <i>index</i> für die Rolle <i>role</i> auf den Wert <i>value</i>.
*/
bool QxSqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::EditRole) {
        if (index.row() >= 0 && index.row() < m_data.size()) {
            QxSqlRecord *record = m_data.at(index.row());

            if (index.column() >= 0 && index.column() < record->count()) {
                record->setValue(index.column(), value);
                emit dataChanged(createIndex(index.row(), index.column()), createIndex(index.row(), index.column()));
                return true;
            }
        }
    }

    return false;
}

/*!
  Gibt den zuletzt aufgetretenen Fehler zurück.

  \sa setQuery(const QString &query)
*/
QSqlError QxSqlQueryModel::lastError() const
{
    return m_error;
}

/*!
  Setzt alle Daten des Models zurück.
*/
void QxSqlQueryModel::clear()
{
    beginResetModel();
    while (!m_data.isEmpty())
        delete m_data.takeFirst();
    m_data.clear();
    m_dummy = QSqlRecord();
    while (!m_columns.isEmpty())
        delete m_columns.takeFirst();
    m_columns.clear();
    m_error = QSqlError();
    endResetModel();
}

/*!
  Führt die in <i>query</i> angegebene Abfrage aus und übernimmt die Ergebnismenge.

  \sa setQuery(QSqlQuery &query)
  \sa lastError()
*/
bool QxSqlQueryModel::setQuery(QSqlQuery &query)
{
    bool success = false;

    clear();
    beginResetModel();

    success = query.exec();
    m_error = query.lastError();
    m_dummy = query.record();

    for (int n = 0; n < query.record().count(); n++) {
        ColumnInfo *column = new ColumnInfo;
        column->caption = query.record().fieldName(n);
        column->alignment = Qt::AlignCenter;
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        column->type = static_cast<QMetaType::Type>(query.record().field(n).metaType().id());
#else
        column->type = query.record().field(n).type();
#endif
        column->format = QString();
        m_columns.insert(n, column);
    }

    while (query.next())
        m_data.append(new QxSqlRecord(query.record()));

    selectSqlRelations();
    endResetModel();

    return success;
}

/*!
  Führt die in <i>query</i> angegebene Abfrage aus und übernimmt die Ergebnismenge.

  \sa setQuery(QSqlQuery &query)
  \sa lastError()
*/
bool QxSqlQueryModel::setQuery(const QString &query)
{
    QSqlQuery sqlQuery;
    sqlQuery.prepare(query);

    return setQuery(sqlQuery);
}

/*!
  Gibt einen leeren Datensatz zurück.
*/
QSqlRecord QxSqlQueryModel::record() const
{
    return m_dummy;
}

/*!
  Gibt den Datensatz an Position <i>row</i> zurück.
*/
QSqlRecord QxSqlQueryModel::record(int row) const
{
    if (row >= 0 && row < rowCount())
        return QSqlRecord(*(m_data.at(row)));

    return QSqlRecord();
}

/*!
  Aktualisiert den Datensatz an Position <i>row</i> mit den Daten von <i>values</i>. Die Änderungen werden dabei nicht
  in die Datenbank geschrieben (für die Aktualisierung der Datenbank ist der Aufrufer verantwortlich).
*/
bool QxSqlQueryModel::setRecord(int row, const QSqlRecord &values)
{
    if (row >= 0 && row < rowCount()) {
        QxSqlRecord *record = m_data.at(row);
        for (int n = 0; n < m_dummy.count(); n++) {
            QString fieldName = m_dummy.fieldName(n);
            record->setValue(fieldName, values.value(fieldName));
        }
        selectSqlRelations(record);
        emit dataChanged(index(row, 0), index(row, columnCount() - 1));

        return true;
    }

    return false;
}

/*!
  Fügt an Position <i>row</i> einen neuen Datensatz mit den Werten <i>record</i> ein. Die Änderungen werden dabei nicht
  in die Datenbank geschrieben (für die Aktualisierung der Datenbank ist der Aufrufer verantwortlich).

  \sa appendRecord(const QSqlRecord &record)
*/
bool QxSqlQueryModel::insertRecord(int row, const QSqlRecord &record)
{
    bool success = false;

    if (row == -1)
        row = rowCount();

    if (row >= 0 && row <= rowCount()) {
        beginInsertRows(QModelIndex(), row, row);
        m_data.insert(row, new QxSqlRecord(m_dummy));
        endInsertRows();
        success = setRecord(row, record);
    }

    return success;
}

/*!
  Fügt einen neuen Datensatz mit den Werten <i>record</i> hinzu. Die Änderungen werden dabei nicht in die Datenbank
  geschrieben (für die Aktualisierung der Datenbank ist der Aufrufer verantwortlich).

  \sa insertRecord(int row, const QSqlRecord &record)
  \sa appendRecords(const QVector<QSqlRecord> &records)
*/
bool QxSqlQueryModel::appendRecord(const QSqlRecord &record)
{
    return insertRecord(-1, record);
}

/*!
  Fügt neue Datensätze mit den Werten <i>records</i> hinzu. Die Änderungen werden dabei nicht in die Datenbank
  geschrieben (für die Aktualisierung der Datenbank ist der Aufrufer verantwortlich).

  \sa appendRecord(const QSqlRecord &record)
*/
bool QxSqlQueryModel::appendRecords(const QVector<QSqlRecord> &records)
{
    QxWaitCursor wait;
    bool success = false;
    int row = rowCount();
    Q_UNUSED(wait);

    if (records.count()) {
        beginInsertRows(QModelIndex(), row, row + records.count() - 1);
        blockSignals(true);
        for (int n = 0; n < records.count(); ++n) {
            m_data.append(new QxSqlRecord(m_dummy));
            success = setRecord(row + n, records.at(n));
            if (!success)
                break;
        }
        blockSignals(false);
        endInsertRows();
    }

    return success;
}

/*!
  Entfernt den Datensatz an Position <i>row</i>. Die Änderungen werden dabei nicht in die Datenbank geschrieben (für
  die Aktualisierung der Datenbank ist der Aufrufer verantwortlich).

  \sa removeRecords(QVector<int> rows)
*/
bool QxSqlQueryModel::removeRecord(int row)
{
    if (row < 0 || row >= rowCount())
        return false;

    beginRemoveRows(QModelIndex(), row, row);
    delete m_data.takeAt(row);
    endRemoveRows();

    return true;
}

/*!
  Entfernt die Datensätze an den Positionen <i>rows</i>. Die Änderungen werden dabei nicht in die Datenbank geschrieben
  (für die Aktualisierung der Datenbank ist der Aufrufer verantwortlich).

  \sa removeRecord(int row)
*/
bool QxSqlQueryModel::removeRecords(QVector<int> rows)
{
    bool success = false;

    if (rows.count()) {
#if QT_VERSION < QT_VERSION_CHECK(5,6,0)
        std::vector<int> temp = rows.toStdVector();
        std::sort(temp.rbegin(), temp.rend());
        rows = QVector<int>::fromStdVector(temp);
#else
        std::sort(rows.rbegin(), rows.rend());
#endif
        beginResetModel();
        for (int row : rows) {
            if (row >= 0 && row < m_data.size())
                delete m_data.takeAt(row);
        }
        endResetModel();
    }

    return success;
}

/*!
  Gibt den Wert in Zeile <i>row</i> und Spalte <i>column</i> zurück.

  \sa value(int row, const QString &column) const
  \sa value(const QModelIndex &index) const
*/
QVariant QxSqlQueryModel::value(int row, int column) const
{
    QVariant value;

    if (row >= 0 && row < rowCount() && column >= 0 && column < columnCount())
        value = m_data.at(row)->value(column);

    return value;
}

/*!
  Gibt den Wert in Zeile <i>row</i> und Spalte <i>column</i> zurück.

  \sa value(int row, int column) const
  \sa value(const QModelIndex &index) const
*/
QVariant QxSqlQueryModel::value(int row, const QString &column) const
{
    return value(row, record().indexOf(column));
}

/*!
  Gibt den Wert für die Zelle <i>index</i> zurück.

  \sa value(int row, int column) const
  \sa value(int row, const QString &column) const
*/
QVariant QxSqlQueryModel::value(const QModelIndex &index) const
{
    return value(index.row(), index.column());
}

/*!
  Gibt den Relationswert in Zeile <i>row</i> und Spalte <i>column</i> zurück.

  \sa relationValue(int row, const QString &column) const
  \sa relationValue(const QModelIndex &index) const
*/
QVariant QxSqlQueryModel::relationValue(int row, int column) const
{
    QVariant value;

    if (row >= 0 && row < rowCount() && column >= 0 && column < columnCount())
        value = m_data.at(row)->relationValue(column);

    return value;
}

/*!
  Gibt den Relationswert in Zeile <i>row</i> und Spalte <i>column</i> zurück.

  \sa relationValue(int row, int column) const
  \sa relationValue(const QModelIndex &index) const
*/
QVariant QxSqlQueryModel::relationValue(int row, const QString &column) const
{
    return relationValue(row, record().indexOf(column));
}

/*!
  Gibt den Relationswert für die Zelle <i>index</i> zurück.

  \sa relationValue(int row, int column) const
  \sa relationValue(int row, const QString &column) const
*/
QVariant QxSqlQueryModel::relationValue(const QModelIndex &index) const
{
    return relationValue(index.row(), index.column());
}

/*!
  Setzt den Relationswert für Zeile <i>row</i> und Spalte <i>column</i> auf den Wert <i>value</i>.

  \sa relationValue(int row, const QString &column) const
  \sa relationValue(const QModelIndex &index) const
*/
void QxSqlQueryModel::setRelationValue(int row, int column, const QVariant &value)
{
    if (row >= 0 && row < rowCount() && column >= 0 && column < columnCount()) {
        m_data.at(row)->setRelationValue(column, value);
        emit dataChanged(createIndex(row, column), createIndex(row, column));
    }
}

/*!
  Setzt den Relationswert für Zeile <i>row</i> und Spalte <i>column</i> auf den Wert <i>value</i>.

  \sa setRelationValue(int row, const QString &column, const QVariant &value)
  \sa setRelationValue(const QModelIndex &index, const QVariant &value)
*/
void QxSqlQueryModel::setRelationValue(int row, const QString &column, const QVariant &value)
{
    setRelationValue(row, record().indexOf(column), value);
}

/*!
  Setzt den Relationswert für die Zelle <i>index</i> auf den Wert <i>value</i>.

  \sa setRelationValue(int row, int column, const QVariant &value)
  \sa setRelationValue(int row, const QString &column, const QVariant &value)
*/
void QxSqlQueryModel::setRelationValue(const QModelIndex &index, const QVariant &value)
{
    setRelationValue(index.row(), index.column(), value);
}

/*!
  Sucht in der Spalte <i>column</i> nach dem Wert <i>value</i> und gibt eine Liste der übereinstimmenden Indizes zurück.

  \sa find(const QString &column, const QVariant &value) const
*/
QModelIndexList QxSqlQueryModel::find(int column, const QVariant &value) const
{
    QModelIndexList list;

    if (column >= 0 && column < columnCount()) {
        for (int row = 0; row < rowCount(); ++row) {
            if (m_data[row]->value(column) == value)
                list.append(createIndex(row, column));
        }
    }

    return list;
}

/*!
  Sucht in der Spalte <i>column</i> nach dem Wert <i>value</i> und gibt eine Liste der übereinstimmenden Indizes zurück.

  \sa find(int column, const QVariant &value) const
*/
QModelIndexList QxSqlQueryModel::find(const QString &column, const QVariant &value) const
{
    return find(record().indexOf(column), value);
}

/*!
  Setzt den Spaltentitel der Spalte <i>column</i> auf den Wert <i>caption</i>.
*/
void QxSqlQueryModel::setColumnCaption(int column, const QString &caption, Qt::AlignmentFlag alignment)
{
    setColumnAlignment(column, alignment);
    setHeaderData(column, Qt::Horizontal, caption);
}

/*!
  Setzt den Spaltentitel der Spalte <i>column</i> auf den Wert <i>caption</i>.
*/
void QxSqlQueryModel::setColumnCaption(const QString &column, const QString &caption, Qt::AlignmentFlag alignment)
{
    setColumnCaption(columnIndex(column), caption, alignment);
}

/*!
  Setzt die Ausrichtung der Spalte <i>column</i> auf den Wert <i>alignment</i>.
*/
void QxSqlQueryModel::setColumnAlignment(int column, Qt::AlignmentFlag alignment)
{
    setHeaderData(column, Qt::Horizontal, alignment, Qt::TextAlignmentRole);
}

/*!
  Setzt die Ausrichtung der Spalte <i>column</i> auf den Wert <i>alignment</i>.
*/
void QxSqlQueryModel::setColumnAlignment(const QString &column, Qt::AlignmentFlag alignment)
{
    setColumnAlignment(columnIndex(column), alignment);
}

/*!
  Setzt den Datentyp der Spalte <i>column</i> auf den Typ <i>type</i>.
*/
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
void QxSqlQueryModel::setColumnType(int column, QMetaType::Type type, const QString &format)
#else
void QxSqlQueryModel::setColumnType(int column, QVariant::Type type, const QString &format)
#endif
{
    if (column >= 0 && column < m_columns.count()) {
        ColumnInfo *info = m_columns.at(column);
        info->type = type;
        info->format = format;

        if (rowCount() > 0)
            emit dataChanged(index(0, column), index(rowCount() - 1, column));
    }
}

/*!
  Setzt den Datentyp der Spalte <i>column</i> auf den Typ <i>type</i>.
*/
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
void QxSqlQueryModel::setColumnType(const QString &column, QMetaType::Type type, const QString &format)
#else
void QxSqlQueryModel::setColumnType(const QString &column, QVariant::Type type, const QString &format)
#endif
{
    setColumnType(columnIndex(column), type, format);
}

/*!
  Setzt für die Spalte <i>column</i> die SQL-Relation <i>sqlRelation</i>.
*/
void QxSqlQueryModel::setSqlRelation(int column, const QSqlRelation &sqlRelation)
{
    m_sqlRelations.insert(column, sqlRelation);
    selectSqlRelation(column);

    if (column < columnCount())
        emit dataChanged(index(0, column), index(rowCount() - 1, column));
}

/*!
  Erzeugt einen Completer aus den Werten der Spalte <i>column</i>.
*/
QCompleter* QxSqlQueryModel::createCompleter(int column, QObject *parent)
{
    QStringList list = columnValues<QString>(column);
    list.sort();

    QCompleter *completer = new QCompleter(list, parent);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    return completer;
}

/*!
  Führt die in <i>query</i> angegebene Abfrage aus und erzeugt einen Completer aus den Werten der Spalte <i>column</i>.
*/
QCompleter* QxSqlQueryModel::createCompleter(QSqlQuery &query, int column, QObject *parent)
{
    QStringList list = QxSqlQueryModel::columnValues<QString>(query, column);
    list.sort();

    QCompleter *completer = new QCompleter(list, parent);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    return completer;
}

/*!
  Führt die in <i>query</i> angegebene Abfrage aus und erzeugt einen Completer aus den Werten der Spalte <i>column</i>.
*/
QCompleter* QxSqlQueryModel::createCompleter(const QString &query, int column, QObject *parent)
{
    QStringList list = QxSqlQueryModel::columnValues<QString>(query, column);
    list.sort();

    QCompleter *completer = new QCompleter(list, parent);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    return completer;
}

/*!
  Gibt den Index der Spalte mit dem Spaltentitel <i>caption</i> zurück.
*/
int QxSqlQueryModel::columnIndex(const QString &caption)
{
    int column = -1;

    for (int n = 0; n < m_columns.count(); n++) {
        if (m_columns.at(n)->caption == caption) {
            column = n;
            break;
        }
    }

    return column;
}

void QxSqlQueryModel::selectSqlRelation(QxSqlRecord *record, int column, const QSqlRelation &sqlRelation)
{
    QSqlQuery query;

    query.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :%3").
        arg(sqlRelation.displayColumn()).arg(sqlRelation.tableName()).arg(sqlRelation.indexColumn()));
    query.bindValue(QString(":%1").arg(sqlRelation.indexColumn()), record->value(column));

    if (query.exec() && query.first()) {
        record->setRelationValue(column, query.value(0));
    } else {
        record->setRelationValue(column, QVariant());
    }
}

void QxSqlQueryModel::selectSqlRelation(int column)
{
    for (QxSqlRecord *record : m_data) {
        if (column < record->count())
            selectSqlRelation(record, column, m_sqlRelations.value(column));
    }
}

void QxSqlQueryModel::selectSqlRelations(QxSqlRecord *record)
{
    for (int column : m_sqlRelations.keys()) {
        if (column < record->count())
            selectSqlRelation(record, column, m_sqlRelations.value(column));
    }
}

void QxSqlQueryModel::selectSqlRelations()
{
    for (QxSqlRecord *record : m_data)
        selectSqlRelations(record);
}

/*!
  \fn QxSqlQueryModel::columnValues(int column = 0) const

  Gibt alle Werte der Spalte <i>column</i> in einer Liste zurück.
*/

/*!
  \fn QxSqlQueryModel::columnValues(QSqlQuery query, int column = 0)

  Führt die in <i>query</i> angegebene Abfrage aus und gibt alle Werte der Spalte <i>column</i> in einer Liste zurück.
*/

/*!
  \fn QxSqlQueryModel::columnValues(const QString &query, int column = 0)

  Führt die in <i>query</i> angegebene Abfrage aus und gibt alle Werte der Spalte <i>column</i> in einer Liste zurück.
*/
