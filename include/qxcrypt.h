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

#ifndef QXCRYPT_H
#define QXCRYPT_H

#include "cutex.h"

namespace cutex {

/*!
  \brief Mit der Klasse %QxCrypt können Zeichenketten ver- und entschlüsselt werden.

  Die Klasse stellt verschiedene statische Methoden zum ver- und entschlüsseln von Zeichenketten bereit. Dabei wird nur
  ein einfacher Algorithmus verwendet, weshalb die Klasse nicht zum verschlüsseln sensibler Daten geeignet ist.
*/
class QxCrypt
{
public:
    static QByteArray encrypt(const QByteArray &text, const QByteArray &key = CRYPT_KEY);
    static QByteArray decrypt(const QByteArray &text, const QByteArray &key = CRYPT_KEY);
    static QString encrypt(const QString &text, const QByteArray &key = CRYPT_KEY);
    static QString decrypt(const QString &text, const QByteArray &key = CRYPT_KEY);

private:
    static const QByteArray CRYPT_KEY;
};

} // namespace

#endif // QXCRYPT_H
