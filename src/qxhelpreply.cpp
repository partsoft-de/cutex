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

#include "qxhelpreply.h"

using namespace cutex;

QxHelpReply::QxHelpReply(const QNetworkRequest &request, const QByteArray &data, const QString &mimeType)
{
    m_data = data;
    m_length = data.length();

    setRequest(request);
    setOpenMode(QIODevice::ReadOnly);
    setHeader(QNetworkRequest::ContentTypeHeader, mimeType);
    setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(m_length));

    QTimer::singleShot(0, this, SIGNAL(metaDataChanged()));
    QTimer::singleShot(0, this, SIGNAL(readyRead()));
}

qint64 QxHelpReply::bytesAvailable() const
{
    return m_data.length() + QNetworkReply::bytesAvailable();
}

qint64 QxHelpReply::readData(char *data, qint64 maxSize)
{
    qint64 length = qMin(qint64(m_data.length()), maxSize);
    if (length) {
        memcpy(data, m_data.constData(), length);
        m_data.remove(0, length);
    }

    if (!m_data.length())
        QTimer::singleShot(0, this, SIGNAL(finished()));

    return length;
}

void QxHelpReply::abort()
{
}
