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

#include "qxcrypt.h"

using namespace cutex;

const QByteArray QxCrypt::CRYPT_KEY = "XHRILVJ7HFMBAK5YNJZG";

/*!
  Verschlüsselt die Zeichenkette <i>text</i> mit dem Schlüssel <i>key</i>. Wird kein Schlüssel angegeben, verwendet die
  Methode den Standardschlüssel <i>CRYPT_KEY</i>.

  \sa decrypt(const QByteArray &text, const QByteArray &key)
*/
QByteArray QxCrypt::encrypt(const QByteArray &text, const QByteArray &key)
{
    QByteArray result;
    int pos = 0;

    foreach (char ch, text) {
        ch = (ch + key.at(pos)) % 256;
        result += ch;
        if (++pos >= key.size())
            pos = 0;
    }

    return result;
}

/*!
  Entschlüsselt die Zeichenkette <i>text</i> mit dem Schlüssel <i>key</i>. Dabei muss derselbe Schlüssel verwendet
  werden, mit dem die Zeichenkette vorher verschlüsselt wurde. Wird kein Schlüssel angegeben, verwendet die Methode den
  Standardschlüssel <i>CRYPT_KEY</i>.

  \sa encrypt(const QByteArray &text, const QByteArray &key)
*/
QByteArray QxCrypt::decrypt(const QByteArray &text, const QByteArray &key)
{
    QByteArray result;
    int pos = 0;

    foreach (char ch, text) {
        ch = (ch + 256 - key.at(pos)) % 256;
        result += ch;
        if (++pos >= key.size())
            pos = 0;
    }

    return result;
}

/*!
  Verschlüsselt die Zeichenkette <i>text</i> mit dem Schlüssel <i>key</i>. Wird kein Schlüssel angegeben, verwendet die
  Methode den Standardschlüssel <i>CRYPT_KEY</i>.

  \sa decrypt(const QString &text, const QByteArray &key)
*/
QString QxCrypt::encrypt(const QString &text, const QByteArray &key)
{
    QByteArray array = text.toUtf8();
    array = encrypt(array, key);
    QString result = QString::fromLatin1(array.toBase64());

    return result;
}

/*!
  Entschlüsselt die Zeichenkette <i>text</i> mit dem Schlüssel <i>key</i>. Dabei muss derselbe Schlüssel verwendet
  werden, mit dem die Zeichenkette vorher verschlüsselt wurde. Wird kein Schlüssel angegeben, verwendet die Methode den
  Standardschlüssel <i>CRYPT_KEY</i>.

  \sa encrypt(const QString &text, const QByteArray &key)
*/
QString QxCrypt::decrypt(const QString &text, const QByteArray &key)
{
    QByteArray array = QByteArray::fromBase64(text.toLatin1());
    array = decrypt(array, key);
    QString result = QString::fromUtf8(array, array.size());

    return result;
}
