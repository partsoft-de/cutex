/***********************************************************************************************************************
**
** Copyright (C) 2016-2022 Partsoft UG (haftungsbeschränkt)
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

#include "qxfindoptions.h"

using namespace cutex;

/*!
  Erzeugt eine neue Instanz zur Verwaltung von Suchoptionen.
*/
QxFindOptions::QxFindOptions()
{
    m_mode = QxFindOptions::Find;
    m_wholeWords = false;
    m_caseSensitive = false;
    m_regularExpression = false;
    m_backward = false;
}

/*!
  Gibt den Suchmodus zurück.

  \sa setMode(QxFindOptions::Mode mode)
*/
QxFindOptions::Mode QxFindOptions::mode() const
{
    return m_mode;
}

/*!
  Ändert den Suchmodus auf den Wert <i>mode</i>.

  \sa mode()
*/
void QxFindOptions::setMode(QxFindOptions::Mode mode)
{
    m_mode = mode;
}

/*!
  Gibt den Text zurück nach dem gesucht werden soll.

  \sa setFindText(const QString &text)
*/
QString QxFindOptions::findText() const
{
    return m_findText;
}

/*!
  Ändert den Text nach dem gesucht werden soll auf den Wert <i>text</i>.

  \sa findText()
*/
void QxFindOptions::setFindText(const QString &text)
{
    m_findText = text;
}

/*!
  Gibt den Text zurück mit dem ersetzt werden soll.

  \sa setReplaceText(const QString &text)
*/
QString QxFindOptions::replaceText() const
{
    return m_replaceText;
}

/*!
  Ändert den Text mit dem ersetzt werden soll auf den Wert <i>text</i>.

  \sa replaceText()
*/
void QxFindOptions::setReplaceText(const QString &text)
{
    m_replaceText = text;
}

/*!
  Gibt true zurück, wenn nur nach ganzen Wörtern gesucht werden soll.

  \sa setWholeWords(bool wholeWords)
*/
bool QxFindOptions::wholeWords() const
{
    return m_wholeWords;
}

/*!
  Legt fest, ob nur nach ganzen Wörtern gesucht werden soll.

  \sa wholeWords()
*/
void QxFindOptions::setWholeWords(bool wholeWords)
{
    m_wholeWords = wholeWords;
}

/*!
  Gibt true zurück, wenn Groß-/Kleinschreibung berücksichtigt werden soll.

  \sa setCaseSensitive(bool caseSensitive)
*/
bool QxFindOptions::caseSensitive() const
{
    return m_caseSensitive;
}

/*!
  Legt fest, ob Groß-/Kleinschreibung berücksichtigt werden soll.

  \sa caseSensitive()
*/
void QxFindOptions::setCaseSensitive(bool caseSensitive)
{
    m_caseSensitive = caseSensitive;
}

/*!
  Gibt true zurück, wenn nach regulären Ausdrücken gesucht werden soll.
*/
bool QxFindOptions::regularExpression() const
{
    return m_regularExpression;
}

/*!
  Legt fest, ob nach regulären Ausdrücken gesucht werden soll.
*/
void QxFindOptions::setRegularExpression(bool regularExpression)
{
    m_regularExpression = regularExpression;
}

/*!
  Gibt true zurück, wenn Rückwärts gesucht werden soll.

  \sa setBackward(bool backward)
*/
bool QxFindOptions::backward() const
{
    return m_backward;
}

/*!
  Legt fest, ob Rückwärts gesucht werden soll.

  \sa backward()
*/
void QxFindOptions::setBackward(bool backward)
{
    m_backward = backward;
}

/*!
  \var QxFindOptions::Find

  Suchen wurde ausgewählt.
*/

/*!
  \var QxFindOptions::Replace

  Ersetzen wurde ausgewählt.
*/

/*!
  \var QxFindOptions::ReplaceAll

  Alles ersetzen wurde ausgewählt.
*/
