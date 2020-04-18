/***********************************************************************************************************************
**
** Copyright (C) 2016-2019 Partsoft UG (haftungsbeschränkt)
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

#ifndef QXHELPREPLY_H
#define QXHELPREPLY_H

#include "cutex.h"

namespace cutex {

class QxHelpReply : public QNetworkReply
{
    Q_OBJECT

public:
    QxHelpReply(const QNetworkRequest &request, const QByteArray &data, const QString &mimeType);
    virtual qint64 bytesAvailable() const;

protected:
    virtual qint64 readData(char *data, qint64 maxSize);

public slots:
    virtual void abort();

private:
    QByteArray m_data;
    qint64 m_length;
};

} // namespace

#endif // QXHELPREPLY_H
