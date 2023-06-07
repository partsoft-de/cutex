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

#include "qxdatevalidator.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Validator mit dem Elternobjekt <i>parent</i>.
*/
QxDateValidator::QxDateValidator(QObject *parent) : QValidator(parent)
{
    m_format = tr("dd.MM.yyyy");

    determineSeparator();
}

/*!
  Erzeugt einen neuen Validator für das Datumsformat <i>format</i> und dem Elternobjekt <i>parent</i>.
*/
QxDateValidator::QxDateValidator(const QString &format, QObject *parent) : QValidator(parent)
{
    m_format = format;

    determineSeparator();
}

/*!
  Gibt das Datumsformat zurück.
*/
QString QxDateValidator::format() const
{
    return m_format;
}

/*!
  Nimmt automatische Korrekturen der Eingabe <i>input</i> vor.
*/
void QxDateValidator::fixup(QString &input) const
{
    if (input.isEmpty())
        return;

    QDate date;
    QString year;
    QString month;
    QString day;

#if QT_VERSION >= QT_VERSION_CHECK(5,14,0)
    for (QString part : m_format.split(m_separator, Qt::SkipEmptyParts)) {
#else
    for (QString part : m_format.split(m_separator, QString::SkipEmptyParts)) {
#endif
        int pos = m_format.indexOf(part[0]);

        switch (part[0].toLatin1()) {
        case 'y':
            year = input.mid(pos, part.length());
            break;
        case 'M':
            month = input.mid(pos, part.length());
            break;
        case 'd':
            day = input.mid(pos, part.length());
            break;
        }
    }

    if (year.toInt() == 0)
        year = QString::number(QDate::currentDate().year());
    if (month.toInt() == 0)
        month = "01";
    if (day.toInt() == 0) {
        day = "01";
    } else {
        date = QDate(year.toInt(), month.toInt(), 1);
        if (day.toInt() > date.daysInMonth())
            day = QString::number(date.daysInMonth());
    }

    date = QDate(year.toInt(), month.toInt(), day.toInt());
    if (date.isValid())
        input = date.toString(m_format);
}

/*!
  Führt die Validierung der Eingabe <i>input</i> durch.
*/
QValidator::State QxDateValidator::validate(QString &input, int &pos) const
{
    int len = input.length();

    if (len > m_format.length())
        return QValidator::Invalid;

    prepare(input);
    pos += input.length() - len;

    QString year;
    QString month;
    QString day;

#if QT_VERSION >= QT_VERSION_CHECK(5,14,0)
    for (QString part : m_format.split(m_separator, Qt::SkipEmptyParts)) {
#else
    for (QString part : m_format.split(m_separator, QString::SkipEmptyParts)) {
#endif
        int pos = m_format.indexOf(part[0]);

        switch (part[0].toLatin1()) {
        case 'y':
            year = input.mid(pos, part.length());
            break;
        case 'M':
            month = input.mid(pos, part.length());
            if ((month.length() == part.length() && month.toInt() < 1) || month.toInt() > 12)
                return QValidator::Invalid;
            break;
        case 'd':
            day = input.mid(pos, part.length());
            if ((day.length() == part.length() && day.toInt() < 1) || day.toInt() > 31)
                return QValidator::Invalid;
            break;
        }
    }

    for (int n = 0; n < input.length(); ++n) {
        if (input[n] == m_separator && m_format[n] != m_separator)
            return QValidator::Invalid;
    }

    if (input.length() < m_format.length())
        return QValidator::Intermediate;

    if (!QDate(year.toInt(), month.toInt(), day.toInt()).isValid())
        return QValidator::Intermediate;

    return QValidator::Acceptable;
}

void QxDateValidator::determineSeparator()
{
    for (QChar ch : m_format) {
        switch (ch.toLatin1()) {
        case 'y':
        case 'M':
        case 'd':
            break;
        default:
            m_separator = ch;
            return;
        }
    }
}

void QxDateValidator::prepare(QString &input) const
{
    if (input.isEmpty())
        return;

    input = input.replace(QRegularExpression(QString("[^0-9%1]").arg(m_separator)), "");

    QString year;
    QString month;
    QString day;

#if QT_VERSION >= QT_VERSION_CHECK(5,14,0)
    for (QString part : m_format.split(m_separator, Qt::SkipEmptyParts)) {
#else
    for (QString part : m_format.split(m_separator, QString::SkipEmptyParts)) {
#endif
        int pos = m_format.indexOf(part[0]);

        switch (part[0].toLatin1()) {
        case 'y':
            year = input.mid(pos, part.length());
            break;
        case 'M':
            month = input.mid(pos, part.length());
            break;
        case 'd':
            day = input.mid(pos, part.length());
            break;
        }
    }

    for (int n = 0; n < input.length() && n < m_format.length(); ++n) {
        if (m_format[n] == m_separator && input[n] != m_separator)
            input = input.insert(n, m_separator);
    }

    input = input.replace(QString("%1%1").arg(m_separator), m_separator);
}
