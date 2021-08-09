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

#ifndef QXLOGGER_H
#define QXLOGGER_H

#include "cutex.h"

namespace cutex {

#define QX_LOG_DEBUG(text) qxApp->logger()->log(QxLogger::Debug, text)
#define QX_LOG_INFO(text) qxApp->logger()->log(QxLogger::Info, text)
#define QX_LOG_WARNING(text) qxApp->logger()->log(QxLogger::Warning, text)
#define QX_LOG_CRITICAL(text) qxApp->logger()->log(QxLogger::Critical, text)

class QxLogger : public QObject
{
    Q_OBJECT

public:
    enum LogLevel {
        Debug = 0, Info, Warning, Critical
    };
    Q_ENUM(LogLevel)

public:
    QxLogger(QObject *parent = nullptr);
    ~QxLogger();
    QString fileName() const;
    bool setFileName(const QString &fileName);
    int maxLines() const;
    void setMaxLines(int count);
    bool log(LogLevel level, const QString &text);
    bool cleanUp();

private:
    QFile m_file;
    QString m_dateFormat;
    int m_maxLines;
};

} // namespace

#endif // QXLOGGER_H
