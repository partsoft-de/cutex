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

#include "qxrandom.h"
#include "time.h"

using namespace cutex;

const QString QxRandom::NUMBERS = "0123456789";
const QString QxRandom::UPPERCHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const QString QxRandom::LOWERCHARS = "abcdefghijklmnopqrstuvwxyz";

bool QxRandom::m_initialized = false;

/*!
  Gibt eine zufällige Zeichenkette mit der Länge <i>length</i> aus dem Pool <i>pool</i> zurück.
*/
QString QxRandom::get(int length, const QString &pool)
{
    QString result = "";

    if (!m_initialized)
        initialize();

    for (int n = 0; n < length; n++)
        result += pool.at(rand() % pool.size());

    return result;
}

void QxRandom::initialize()
{
    m_initialized = true;
    time_t t;
    srand((unsigned)time(&t));
}
