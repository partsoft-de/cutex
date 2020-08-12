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

#include "qxtimevalidator.h"

using namespace cutex;

/*!
  Erzeugt einen neuen Validator mit dem Elternobjekt <i>parent</i>.
*/
QxTimeValidator::QxTimeValidator(QObject *parent) : QValidator(parent)
{
    m_format = "hh:mm";

    determineSeparator();
}

/*!
  Erzeugt einen neuen Validator für das Zeitformat <i>format</i> und dem Elternobjekt <i>parent</i>.
*/
QxTimeValidator::QxTimeValidator(const QString &format, QObject *parent) : QValidator(parent)
{
    m_format = format;

    determineSeparator();
}

/*!
  Nimmt automatische Korrekturen der Eingabe <i>input</i> vor.
*/
void QxTimeValidator::fixup(QString &input) const
{
    if (input.isEmpty())
        return;

    QTime time;
    QString hours;
    QString minutes;
    QString seconds;

    foreach (QString part, m_format.split(m_separator, QString::SkipEmptyParts)) {
        int pos = m_format.indexOf(part[0]);

        switch (part[0].toLatin1()) {
        case 'h':
            hours = input.mid(pos, part.length());
            break;
        case 'm':
            minutes = input.mid(pos, part.length());
            break;
        case 's':
            seconds = input.mid(pos, part.length());
            break;
        }
    }

    time = QTime(hours.toInt(), minutes.toInt(), seconds.toInt());
    if (time.isValid())
        input = time.toString(m_format);
}

/*!
  Führt die Validierung der Eingabe <i>input</i> durch.
*/
QValidator::State QxTimeValidator::validate(QString &input, int &pos) const
{
    int len = input.length();

    if (len > m_format.length())
        return QValidator::Invalid;

    prepare(input);
    pos += input.length() - len;

    QString hours;
    QString minutes;
    QString seconds;

    foreach (QString part, m_format.split(m_separator, QString::SkipEmptyParts)) {
        int pos = m_format.indexOf(part[0]);

        switch (part[0].toLatin1()) {
        case 'h':
            hours = input.mid(pos, part.length());
            if (hours.toInt() < 0 || hours.toInt() > 23)
                return QValidator::Invalid;
            break;
        case 'm':
            minutes = input.mid(pos, part.length());
            if (minutes.toInt() < 0 || minutes.toInt() > 59)
                return QValidator::Invalid;
            break;
        case 's':
            seconds = input.mid(pos, part.length());
            if (seconds.toInt() < 0 || seconds.toInt() > 59)
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

    if (!QTime(hours.toInt(), minutes.toInt(), seconds.toInt()).isValid())
        return QValidator::Intermediate;

    return QValidator::Acceptable;
}

void QxTimeValidator::determineSeparator()
{
    foreach (QChar ch, m_format) {
        switch (ch.toLatin1()) {
        case 'h':
        case 'm':
        case 's':
            break;
        default:
            m_separator = ch;
            return;
        }
    }
}

void QxTimeValidator::prepare(QString &input) const
{
    if (input.isEmpty())
        return;

    input = input.replace(QRegExp(QString("[^0-9%1]").arg(m_separator)), "");

    QString hours;
    QString minutes;
    QString seconds;

    foreach (QString part, m_format.split(m_separator, QString::SkipEmptyParts)) {
        int pos = m_format.indexOf(part[0]);

        switch (part[0].toLatin1()) {
        case 'h':
            hours = input.mid(pos, part.length());
            break;
        case 'm':
            minutes = input.mid(pos, part.length());
            break;
        case 's':
            seconds = input.mid(pos, part.length());
            break;
        }
    }

    for (int n = 0; n < input.length() && n < m_format.length(); ++n) {
        if (m_format[n] == m_separator && input[n] != m_separator)
            input = input.insert(n, m_separator);
    }

    input = input.replace(QString("%1%1").arg(m_separator), m_separator);
}
