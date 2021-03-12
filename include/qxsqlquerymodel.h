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

#ifndef QXSQLQUERYMODEL_H
#define QXSQLQUERYMODEL_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Die Klasse %QxSqlQueryModel ist eine Alternative zur Qt-Klasse QSqlQueryModel.

  Die Klasse ist nicht von der Qt-Klasse QSqlQueryModel abgeleitet, stellt weitestgehend aber dieselben Schnittstellen
  bereit. Im Gegensatz zu QSqlQueryModel (welches ein reines Read-Only-Model ist) stellt %QxSqlQueryModel zusätzliche
  Methoden zum Einfügen, Ändern und Löschen von Datensätzen zur Verfügung.
*/
class QxSqlQueryModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QxSqlQueryModel(QObject *parent = 0);
    virtual ~QxSqlQueryModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
        int role = Qt::EditRole);
    virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void clear();
    QSqlError lastError() const;
    virtual bool setQuery(QSqlQuery &query);
    virtual bool setQuery(const QString &query);
    QSqlRecord record() const;
    QSqlRecord record(int row) const;
    bool setRecord(int row, const QSqlRecord &values);
    bool insertRecord(int row, const QSqlRecord &record);
    bool appendRecord(const QSqlRecord &record);
    bool removeRecord(int row);
    template<typename T> QList<T> columnValues(int column = 0) const
    {
        QList<T> list;

        if (column < columnCount()) {
            for (int n = 0; n < rowCount(); n++)
                list.append(record(n).value(column).value<T>());
        }

        return list;
    }
    template<typename T> static QList<T> columnValues(QSqlQuery query, int column = 0)
    {
        QxSqlQueryModel model;
        QList<T> list;

        if (model.setQuery(query))
            list = model.columnValues<T>(column);

        return list;
    }
    template<typename T> static QList<T> columnValues(const QString &query, int column = 0)
    {
        QxSqlQueryModel model;
        QList<T> list;

        if (model.setQuery(query))
            list = model.columnValues<T>(column);

        return list;
    }
    void setColumnCaption(int column, const QString &caption, Qt::AlignmentFlag alignment = Qt::AlignLeft);
    void setColumnCaption(const QString &column, const QString &caption, Qt::AlignmentFlag alignment = Qt::AlignLeft);
    void setColumnAlignment(int column, Qt::AlignmentFlag alignment);
    void setColumnAlignment(const QString &column, Qt::AlignmentFlag alignment);
    void setColumnType(int column, QVariant::Type type, const QString &format = QString());
    void setColumnType(const QString &column, QVariant::Type type, const QString &format = QString());
    QCompleter* createCompleter(int column = 0, QObject *parent = 0);
    static QCompleter* createCompleter(QSqlQuery query, int column = 0, QObject *parent = 0);
    static QCompleter* createCompleter(const QString &query, int column = 0, QObject *parent = 0);

protected:
    int columnIndex(const QString &caption);

private:
    //! @cond struct
    struct ColumnInfo {
        QString caption;
        Qt::Alignment alignment;
        QVariant::Type type;
        QString format;
    };
    //! @endcond

private:
    QVector<QSqlRecord*> m_data;
    QSqlRecord m_dummy;
    QVector<ColumnInfo*> m_columns;
    QSqlError m_error;
};

} // namespace

#endif // QXSQLQUERYMODEL_H
