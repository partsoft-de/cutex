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

#include "qxhelpmanager.h"
#include "qxhelpreply.h"

using namespace cutex;

QxHelpManager::QxHelpManager(QHelpEngine *helpEngine, QObject *parent) : QNetworkAccessManager(parent)
{
    m_helpEngine = helpEngine;
}

QNetworkReply* QxHelpManager::createRequest(Operation op, const QNetworkRequest &request, QIODevice *data)
{
    QString url = request.url().toString().toLower();
    QString mimeType;

    if (request.url().scheme() == "qthelp") {
        if (url.endsWith(QLatin1String(".svg")) || url.endsWith(QLatin1String(".svgz"))) {
            mimeType = QLatin1String("image/svg+xml");
        } else if (url.endsWith(QLatin1String(".css"))) {
            mimeType = QLatin1String("text/css");
        } else if (url.endsWith(QLatin1String(".png"))) {
            mimeType = QLatin1String("image/png");
        } else if (url.endsWith(QLatin1String(".js"))) {
            mimeType = QLatin1String("text/javascript");
        } else {
            mimeType = QLatin1String("text/html");
        }

        return new QxHelpReply(request, m_helpEngine->fileData(request.url()), mimeType);
    }

    return QNetworkAccessManager::createRequest(op, request, data);
}
